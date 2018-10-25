
#ifndef GL_CORE2D_H
#define GL_CORE2D_H

#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <map>
#include "glscene2D.hpp"
#include "glexcepion.hpp"
#include <thread>

namespace Lanuka
{

    class GLCore
    {
        public:
            GLCore(int win_width, int win_height, const char* win_name = NULL);
            void start();
            void terminate();
            void addScene(std::string scene_name);
            void removeScene(std::string scene_name);
            GLScene2D& lookupScene(std::string scene_name);
            void showInfo();
        
        private:
            GLFWwindow* window;
            std::map<std::string, GLScene2D> scenes;
            std::string window_name;
            int window_size[2] = {0,0}; 

    };

    GLCore::GLCore(int win_width, int win_height, const char* win_name)
    {
        if (!glfwInit())
            return;
        
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(640, 480, win_name, NULL, NULL);
        if (!window)
        {
            glfwTerminate();
            return;
        }

	    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

        glfwMakeContextCurrent(window);
        glewExperimental = GL_TRUE;
        if (glewInit() != GLEW_OK)
        {
            glfwTerminate();
                return;
        }

        glfwMakeContextCurrent(window);
    }

    void GLCore::start()
    {
        while (!glfwWindowShouldClose(window))	
        {
            glfwPollEvents();

            for (auto &scene : scenes)
                scene.second.draw();

            glfwSwapBuffers(window);
        }
    }

    void GLCore::addScene(std::string scene_name)
    {
        GLScene2D scene(scene_name, window);
        scenes[scene_name] = scene;
    }

    void GLCore::removeScene(std::string scene_name)
    {
        scenes.erase(scenes.find(scene_name));
    }
  
    GLScene2D& GLCore::lookupScene(std::string scene_name)
    {
        return scenes[scene_name];
    }

    void GLCore::showInfo()
    {
        std::cout << "GLCore object with " << scenes.size() << " scenes" << std::endl;
        for (auto const& x : scenes)
        {
            std::cout << "Scene: " << x.second.getName() << std::endl;
        }

        std::cout << std::endl;
    }

};

#endif