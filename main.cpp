#include "camera.h"
#include "cam_hardware.h"
#include <ostream>
#include <stdint.h>
#include <string>

int main(){
    std::cout << "Camera Interface for Vistapath...created by B. Olibrice" << std::endl;
    camera mycam;
    //cam_hardware hardware;

    mycam.read_code();
    /*hardware.WriteControlCode("#STGET\r\n");
    for(int i = 0; i < 20; i++){
        unsigned char barcode = hardware.ReadBarcode();
        std::cout << "barcode is " << std::to_string(barcode) << std::endl;
    }*/
    return 0;
}