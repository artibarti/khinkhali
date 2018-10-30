#ifndef GL_CONSTS_H
#define GL_CONSTS_H

#include <glm/vec3.hpp>
#include <map>
#include "gltypes.hpp"

namespace Lanuka
{
    const glm::vec3 GL_COLOR_RED = {1.0, 0.0, 0.0};
    const glm::vec3 GL_COLOR_BLUE = {0.0, 0.0, 1.0};
    const glm::vec3 GL_COLOR_GREEN = {0.0, 1.0, 0.0};
    const glm::vec3 GL_COLOR_BLACK = {0.0, 0.0, 0.0};
    const glm::vec3 GL_COLOR_WHITE = {1.0, 1.0, 1.0};
    const glm::vec3 GL_COLOR_ORANGE = {0.9, 0.5, 0.0};

    std::map<GLDrawableType, int> vertexNumberConstraintForDrawables =
    {
        {GL_DRAWABLE_TYPE_TRIANGLE, 3},
        {GL_DRAWABLE_TYPE_RECTANGLE, 4},
    };

};



#endif