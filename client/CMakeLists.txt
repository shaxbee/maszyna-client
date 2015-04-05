cmake_minimum_required(VERSION 2.8.12)
project(maszyna)

option(CLIENT_3RDPARTY_PATH "Path to 3rdParty binaries folder" "")
set(CMAKE_PREFIX_PATH ${CLIENT_3RDPARTY_PATH})

find_package(glbinding REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

find_package(flatbuffers REQUIRED)

include_directories(include)

add_subdirectory(src)
