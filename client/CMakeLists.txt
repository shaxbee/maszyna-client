cmake_minimum_required(VERSION 2.8.12)
project(maszyna)

option(CLIENT_3RDPARTY_PATH "Path to 3rdParty binaries folder" "")
set(CMAKE_PREFIX_PATH ${CLIENT_3RDPARTY_PATH})

find_package(glbinding REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

find_package(flatbuffers REQUIRED)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    list(APPEND CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -std=c++11")
    list(APPEND CMAKE_CXX_FLAGS_RELEASE "-O2")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    if (CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS)
    else()
        list(APPEND CMAKE_CXX_FLAGS "/W4")
    endif()
endif()

compile_flatbuffers_schema_to_cpp(schema/model.fbs)

add_executable(maszyna src/main.cpp schema/model_generated.h)
target_include_directories(maszyna PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(maszyna ${GLBINDING_LIBRARIES} glfw glm flatbuffers)
target_compile_definitions(maszyna PRIVATE -DGLBINDING_STATIC -DGLFW_INCLUDE_NONE)
