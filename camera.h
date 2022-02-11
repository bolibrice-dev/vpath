#include <vector>
#include <string>
#include "stdio.h"
#include "cam_hardware.h"

#ifndef VPATH_CAMERA_H
#define VPATH_CAMERA_H

enum class FSM_BARCODE_READ_STAGE{
    STATE_IDLE = 0,
    STATE_LOADING,
    STATE_HEADER_HI,
    STATE_HEADER_LO,
    STATE_HEADER_DATA,
    STATE_FOOTER_HI,
    STATE_FOOTER_LO
};
enum class FSM_IMAGE_READ_STAGE{
    STATE_IDLE = 0,
    STATE_HEADER_HI,
    STATE_HEADER_LO,
    STATE_HEADER_DATA,
    STATE_FOOTER_HI,
    STATE_FOOTER_LO
};

class camera {
    public:
        std::vector<std::string> read_code();
        std::vector<unsigned char> capture_image();
        std::vector<std::string> ProcessBarcodeData(cam_hardware &hardware);
        std::vector<unsigned char> ProcessImageData(cam_hardware &hardware);
    private:
        
};

#endif