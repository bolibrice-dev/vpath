#include "cam_hardware.h"
#include <stdint.h>

unsigned char barcode[] = {
    0xfe,0xf7,0x23,0x24,0x45,0x01,0x24,0x99,0xff,0xf8
};

unsigned char barcode_image[] = {
    0xff,0xd8,0x23,0x24,0x45,0x01,0x24,0x99,0xff,0xd9
};

// static member variables
uint16_t cam_hardware::barcode_index = 0;
uint16_t cam_hardware::image_index = 0;

cam_hardware::cam_hardware() : breakTransmission(false){

}
bool cam_hardware::WriteControlCode(std::string ccode){
    std::string scancode = "#STGET\r\n";
    std::string imgcode  = "#IMGET\r\n";

    bool success = false;
    if(ccode == scancode || ccode == imgcode){
        if(ccode == scancode){
            barcode_index = 0;
            std::cout << "getting ready to scan barcode" << std::endl;
        }
        else{ //imgcode
            image_index = 0;
        }
        success = true;
    }
    std::cout << ccode << std::endl;

    return success;
}

unsigned char cam_hardware::ReadBarcode(){
    unsigned char code = 0;
    if(barcode_index < sizeof(barcode)){
        code = barcode[barcode_index++];
        if(breakTransmission && barcode_index > 5){// for testing support (user remove USB cable)
            throw static_cast<std::string>("pwoff"); 
        }
    }
    else{
        throw static_cast<std::string>("eof");
    }
    return code;
}

unsigned char cam_hardware::ReadBarcodeImage(){
    unsigned char img = 0;
    if(image_index < sizeof(barcode_image)){
        img = barcode_image[image_index++];
    }
    else{
        throw "no image";
    }
    return img;
}