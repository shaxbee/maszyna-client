/*
MaSzyna Train Simulator
Copyright (C) 2014 MaSzyna Team

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <iostream>

#include <glbinding/gl/gl33core.h>
#include <GLFW/glfw3.h>

#include <vector>

using namespace gl33core;

const int GLFW_TRUE = static_cast<int>(GL_TRUE);
const int GLFW_FALSE = static_cast<int>(GL_FALSE);

void error_callback(int, const char* description)
{
    std::cerr << description << std::endl;
}

int main(int, char const* [])
{
    std::cerr << "Initializing OpenGL." << std::endl;

    glfwInit();
    glfwSetErrorCallback(error_callback);

    glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    auto window = glfwCreateWindow(640, 480, "MaSzyna Client", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    glbinding::Binding::initialize();

    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return EXIT_SUCCESS;
}
