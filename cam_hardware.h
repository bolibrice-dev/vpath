#include "stdio.h"
#include <stdint.h>
#include <string>
#include <iostream>

#ifndef VPATH_CAM_HARDWARE_H
#define VPATH_CAM_HARDWARE_H

class cam_hardware{
    public:
        cam_hardware();
        bool WriteControlCode(std::string ccode);
        unsigned char ReadBarcode();
        unsigned char ReadBarcodeImage();
        inline void suspendTransmit(bool b){ breakTransmission = b;};
    private:
        static uint16_t barcode_index;
        static uint16_t image_index;
        bool breakTransmission;
};

#endif