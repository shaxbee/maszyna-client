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

#include "schema/model_generated.h"

#include <Maszyna.Diagnostics/Trace.hxx>

using namespace gl33core;

//  Set this to 'Normal', to compile-out any calls to
//  MASZYNA_TRACE_WRITELINE with Debug level at compile-time.
//                                           |
//                                           V
MASZYNA_DECLARE_TRACE_SWITCH(AppMain, Debug, Debug);
MASZYNA_DEFINE_TRACE_SWITCH(AppMain);

const int GLFW_TRUE = static_cast<int>(GL_TRUE);
const int GLFW_FALSE = static_cast<int>(GL_FALSE);

void error_callback(int, const char* description)
{
    Maszyna::Diagnostics::Trace::Fail("OpenGL error", description);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int modifiers)
{
    MASZYNA_TRACE_WRITELINE(AppMain, Debug, "Window: %p, Key: %d, Scancode: %08x, Action: %08x, Modifiers: %08x",
        window,
        key,
        scancode,
        action,
        modifiers);
}

int main(int, char const* [])
{
    // Initialize tracing with 'maszyna.log' file as a target.
    Maszyna::Diagnostics::Trace::Initialize("maszyna.log");
    MASZYNA_TRACE_WRITELINE(AppMain, Debug, "Initializing OpenGL");

    glfwInit();
    glfwSetErrorCallback(error_callback);

    glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    MASZYNA_TRACE_WRITELINE(AppMain, Debug, "Context: OpenGL 3.3, Core Profile");
    MASZYNA_TRACE_WRITELINE(AppMain, Normal, "Creating OpenGL window");

    auto window = glfwCreateWindow(640, 480, "Maszyna Client", nullptr, nullptr);
    glfwSetKeyCallback(window, key_callback);
    glfwMakeContextCurrent(window);
    MASZYNA_TRACE_WRITELINE(AppMain, Debug, "Creating OpenGL window");

    glbinding::Binding::initialize();

    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    MASZYNA_TRACE_WRITELINE(AppMain, Debug, "Maszyna Closed Gracefully");
    Maszyna::Diagnostics::Trace::Shutdown();

    return EXIT_SUCCESS;
}
