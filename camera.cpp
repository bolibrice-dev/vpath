//#STGET\r\n to instruct camera to  read barcode write that to camera
// read back one byte at a time bounded by 0xFFF7 ------ 0xFFF8

//#IMGET to get actual barcode image
// image data is read one byte at a time and include start and end words 0xFFD8-------0xFFD9

#include "camera.h"
#include "cam_hardware.h"

std::string camera::read_code(){
    std::string code = "";
    cam_hardware hardware;
    unsigned char ch = 0;
    std::vector<unsigned char> barcode;

    hardware.WriteControlCode("#STGET\r\n");
    std::cout << "reading camera code..[";
    for(;;){
        try{
            ch = hardware.ReadBarcode();
            std::cout << std::to_string(ch) << ",";
        }
        catch(std::string err){
            if(err == "pwoff"){
                return code;
            }
            break;
        }
    }
    // we got here cause we have valid data
    std::cout << "];" << std::endl;
    
    return code;
}