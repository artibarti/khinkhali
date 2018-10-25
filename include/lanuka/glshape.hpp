#ifndef GL_SHAPE_H
#define GL_SHAPE_H

#include "gltypes.hpp"
#include <glm/vec2.hpp>
#include <vector>
#include "glconsts.hpp"
#include "glutils.hpp"
#include "gllog.hpp"
#include <algorithm>

namespace Lanuka
{
    class GLShape 
    {
        public:

            ~GLShape();
            std::vector<glm::vec3>& getVertives();
            std::vector<glm::vec3>& getColors();
            void draw();
            void attachShader(std::string name);

        protected:

            void initBuffers();
            void addShader(GLShaderType shader_type, std::string filename);
            void attachShaders();

            std::vector<glm::vec3> vertices;
            std::vector<glm::vec3> colors;
            std::vector<glm::vec3> indices;

            std::vector<std::string> shaders;

            GLuint vertex_buffer = 0, color_buffer = 0;
            GLuint vertex_array = 0;
            GLuint program = 0;
            GLuint vertex_shader;
            GLuint fragment_shader;
            
            std::string vertex_shader_code;
            std::string fragment_shader_code;

            int draw_mode;
            bool use_program = false;
            bool use_vertex_shader = false;
            bool use_fragment_shader = false;
    };

    GLShape::~GLShape()
    {
        vertices.clear();
        colors.clear();
        indices.clear();
        glDeleteBuffers(1, &vertex_buffer);
        glDeleteBuffers(1, &color_buffer);
    }

    void GLShape::initBuffers()
    {        
        glGenBuffers(1, &vertex_buffer);
        glGenBuffers(1, &color_buffer);
        glGenVertexArrays(1, &vertex_array);

        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
        glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(glm::vec3), &vertices.front(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
        glBufferData(GL_ARRAY_BUFFER, colors.size()*sizeof(glm::vec3), &colors.front(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindVertexArray(vertex_array);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
        glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, 0,0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
        glVertexAttribPointer(1,3, GL_FLOAT, GL_FALSE, 0,0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void GLShape::draw()
    {
        if (use_program)
            glUseProgram(program);
        glBindVertexArray(vertex_array);
        glDrawArrays(draw_mode, 0,3);
        glBindVertexArray(0);
    }

    void GLShape::addShader(GLShaderType shader_type, std::string filename)
    {
        std::string shader_code = loadShaderFromFile(filename);
        if (shader_code != "")
            if (shader_type == GL_SHADER_TYPE_VERTEX)
            {
                vertex_shader_code = shader_code;
                vertex_shader =  glCreateShader(GL_VERTEX_SHADER);
                const GLchar* vertex_shader_code_ptr[] = { vertex_shader_code.c_str() };
                glShaderSource(vertex_shader, 1, vertex_shader_code_ptr, NULL);
                glCompileShader(vertex_shader);
            }
            else if (shader_type == GL_SHADER_TYPE_FRAGMENT)
            {
                fragment_shader_code = shader_code;
                fragment_shader =  glCreateShader(GL_FRAGMENT_SHADER);
                const GLchar* fragment_shader_code_ptr[] = { fragment_shader_code.c_str() };
                glShaderSource(fragment_shader, 1, fragment_shader_code_ptr, NULL);
                glCompileShader(fragment_shader);
            }
            else
                throw glUnknownShaderTypeException();
        else
            throw glShaderLoadException();
    }

    void GLShape::attachShaders()
    {
        program = glCreateProgram();
        glAttachShader(program, vertex_shader);
        glAttachShader(program, fragment_shader);
        glLinkProgram(program);

        glDetachShader(program, vertex_shader);
        glDeleteShader(vertex_shader);
        glDetachShader(program, fragment_shader);
        glDeleteShader(fragment_shader);      

        use_program = true;  
    }

    void GLShape::attachShader(std::string name)
    {
        if (std::find(shaders.begin(), shaders.end(), name) != shaders.end())
            return;
        else
            shaders.push_back(name);
    }

}

#endif