#ifndef GL_LOG_HPP
#define GL_LOG_HPP

#include <iostream>
#include <string>

namespace Lanuka
{
    void llog(std::string msg)
    {
        std::cout << msg << std::endl;
    }
};

#endif