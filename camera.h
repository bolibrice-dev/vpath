#include <vector>
#include <string>
#include "stdio.h"

#ifndef VPATH_CAMERA_H
#define VPATH_CAMERA_H

class camera {
    public:
        std::string read_code();
        char* capture_image();
    private:
        
};

#endif