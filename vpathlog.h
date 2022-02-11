#ifndef VPATH_LOG_H
#define VPATH_LOG_H

#include <string>

class vpathlog{
    public:
    vpathlog() {};
    void print(std::string data,bool addNewLine = false);
};


#endif