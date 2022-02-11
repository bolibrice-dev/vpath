#include "camera.h"
#include "cam_hardware.h"
#include "vpathlog.h"
#include <ostream>
#include <stdint.h>
#include <string>

int main(){
    vpathlog log;
    log.print("Testing Camera Interface for Vistapath...created by B. Olibrice",true);
    camera mycam;
    std::vector<std::string> code = mycam.read_code();
    std::vector<unsigned char> img = mycam.capture_image();
    for(unsigned int i = 0; i < img.size(); i++){
        printf("0x%x ", img.at(i));
    }
    log.print("\n");
    return 0;
}