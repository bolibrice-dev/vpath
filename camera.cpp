//#STGET\r\n to instruct camera to  read barcode write that to camera
// read back one byte at a time bounded by 0xFFF7 ------ 0xFFF8

//#IMGET to get actual barcode image
// image data is read one byte at a time and include start and end words 0xFFD8-------0xFFD9

#include "camera.h"
#include "vpathlog.h"
#include <ios>
#include <string>
#include <vector>

/*
** ===================================================================
**     Function       :  capture_image
**
**     Description :
**         call camera hardware to read image data
**     Parameters  :
**         NAME            - DESCRIPTION
**       ------        ---------------------- 
**        n/a                   n/a
**     Returns     :  vector of bytes representing the image's binary data
** ===================================================================
*/
std::vector<unsigned char> camera::capture_image(){
    cam_hardware hardware;
    hardware.WriteControlCode("#IMGET\r\n");
    return ProcessImageData(hardware);
}

/*
** ===================================================================
**     Function       :  read_code
**
**     Description :
**         call camera hardware to read barcode string
**     Parameters  :
**         NAME            - DESCRIPTION
**       ------        ---------------------- 
**        n/a                   n/a
**     Returns     :  string representing the read barcode or empty if an error occurs
       TODO        :  provide function describing the error
** ===================================================================
*/
std::vector<std::string> camera::read_code(){
    std::string code = "";
    
    cam_hardware hardware;

    hardware.WriteControlCode("#STGET\r\n");
    return ProcessBarcodeData(hardware);
}



/*
** ===================================================================
**     Function       :  ProcessBarcodeData
**
**     Description :
**         call camera hardware to read barcode string
**     Parameters  :
**         NAME            - DESCRIPTION
**       ---------        ---------------------- 
**       hardware    reference to cam hardware object
**       ---------   ---------------------------------
**
**     Returns     :  vector of strings representing the read barcodes
       TODO        :  provide function describing the error
** ===================================================================
*/
std::vector<std::string>  camera::ProcessBarcodeData(cam_hardware &hardware){
    std::vector<std::string>   barcode_array;
    std::vector<unsigned char> barcode;
    unsigned char ch = 0;

    static FSM_BARCODE_READ_STAGE readstate = FSM_BARCODE_READ_STAGE::STATE_HEADER_HI;

    while(readstate != FSM_BARCODE_READ_STAGE::STATE_IDLE){
        try{
            ch = hardware.ReadBarcode();
            //std::cout << std::hex << ch ;
            switch(readstate){
                case FSM_BARCODE_READ_STAGE::STATE_HEADER_HI:
                if(ch != 0xfe){
                    readstate = FSM_BARCODE_READ_STAGE::STATE_IDLE;
                }
                else{
                    readstate = FSM_BARCODE_READ_STAGE::STATE_HEADER_LO;
                    //barcode.push_back(ch); - ignore header byte
                }
                break;
                case FSM_BARCODE_READ_STAGE::STATE_HEADER_LO:
                    if(ch != 0xf7){
                        readstate = FSM_BARCODE_READ_STAGE::STATE_IDLE;
                    }
                    else{
                        readstate = FSM_BARCODE_READ_STAGE::STATE_HEADER_DATA;
                       //barcode.push_back(ch); - ignore header byte
                    }
                break;
                case FSM_BARCODE_READ_STAGE::STATE_HEADER_DATA:
                    if(ch == 0xff){ //done getting barcode data
                        readstate = FSM_BARCODE_READ_STAGE::STATE_FOOTER_LO;
                    }
                    else{
                        barcode.push_back(ch);
                    }
                break;
                case FSM_BARCODE_READ_STAGE::STATE_FOOTER_LO:
                if(ch != 0xf8){ //something happened
                    return barcode_array; // send back w/e we got
                }
                else{
                    // done getting complete string, save to vector
                    std::string scode(barcode.begin(), barcode.end());
                    barcode_array.push_back(scode);
                    barcode.clear();
                    // keep probing hardware see if there are more strings
                    readstate = FSM_BARCODE_READ_STAGE::STATE_HEADER_HI;
                }
                break;
                default:
                break;
            }
        }
        catch(std::string err){
            if(err == "pwoff"){
                return barcode_array;
            }
            break;
        }
    }
    readstate = FSM_BARCODE_READ_STAGE::STATE_HEADER_HI; // for dynamic re-entrancy
    
    return barcode_array;
}


/*
** ===================================================================
**     Function       :  ProcessImageData
**
**     Description :
**         call camera hardware to read image data
**     Parameters  :
**         NAME            - DESCRIPTION
**       ---------        ---------------------- 
**       hardware    reference to cam hardware object
**       ---------   ---------------------------------
**
**     Returns     :  vector of char representing the binary image data
** ===================================================================
*/
std::vector<unsigned char> camera::ProcessImageData(cam_hardware &hardware){
    std::vector<unsigned char> image_data;
    unsigned char ch = 0;

    static FSM_IMAGE_READ_STAGE readstate = FSM_IMAGE_READ_STAGE::STATE_HEADER_HI;

    while(readstate != FSM_IMAGE_READ_STAGE::STATE_IDLE){
        try{
            ch = hardware.ReadBarcodeImage();
            image_data.push_back(ch);

            switch(readstate){
                case FSM_IMAGE_READ_STAGE::STATE_HEADER_HI:
                    if(ch != 0xff){
                        readstate = FSM_IMAGE_READ_STAGE::STATE_IDLE;
                        image_data.clear();
                    }
                    else{
                        readstate = FSM_IMAGE_READ_STAGE::STATE_HEADER_LO;
                    }
                break;
                case FSM_IMAGE_READ_STAGE::STATE_HEADER_LO:
                    if(ch != 0xd8){ // delimiter not found
                        readstate = FSM_IMAGE_READ_STAGE::STATE_IDLE;
                        // error. stop getting bytes from camera
                        image_data.clear();
                    }
                    else{
                        readstate = FSM_IMAGE_READ_STAGE::STATE_HEADER_DATA;
                    }
                break;
                case FSM_IMAGE_READ_STAGE::STATE_HEADER_DATA:
                    if(ch == 0xff){ //done getting image data
                        readstate = FSM_IMAGE_READ_STAGE::STATE_FOOTER_LO;
                    }
                break;
                case FSM_IMAGE_READ_STAGE::STATE_FOOTER_LO:
                    if(ch != 0xd9){ //something happened
                        image_data.clear(); //didn't get complete image, discard
                    }
                    // at this point we either get an empty or complete image; either way we're done
                    readstate = FSM_IMAGE_READ_STAGE::STATE_IDLE;
                break;
                default:
                break;
            }
        }
        catch(std::string err){

        }
    }
    readstate = FSM_IMAGE_READ_STAGE::STATE_HEADER_HI; // for dynamic re-entrancy
    return image_data;
}