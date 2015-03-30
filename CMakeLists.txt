cmake_minimum_required(VERSION 2.8.12)
include(ExternalProject)

set(3RDPARTY_PATH ${CMAKE_BINARY_DIR}/3rdparty)

ExternalProject_Add(
    glbinding
    URL https://github.com/hpicgs/glbinding/archive/v1.0.5.zip
    URL_HASH SHA1=91137790cb56c1df303f7b3449cbde5d72153dee
    CMAKE_ARGS
        -DOPTION_BUILD_STATIC=ON
        -DOPTION_BUILD_TESTS=OFF
        -DCMAKE_INSTALL_PREFIX=${3RDPARTY_PATH}
)

ExternalProject_Add(
    glfw
    URL https://github.com/shaxbee/glfw/archive/master.zip
    CMAKE_ARGS
        -DGLFW_BUILD_EXAMPLES=OFF
        -DGLFW_BUILD_TESTS=OFF
        -DGLFW_BUILD_DOCS=OFF
        -DCMAKE_INSTALL_PREFIX=${3RDPARTY_PATH}
)

ExternalProject_Add(
    glm
    URL https://github.com/shaxbee/glm/archive/master.zip
    CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX=${3RDPARTY_PATH}
)

ExternalProject_Add(
    flatbuffers
    URL https://github.com/shaxbee/flatbuffers/archive/master.zip
    CMAKE_ARGS
        -DFLATBUFFERS_BUILD_TESTS=OFF
        -DCMAKE_INSTALL_PREFIX=${3RDPARTY_PATH}
)

ExternalProject_Add(
    googlemock
    URL https://googlemock.googlecode.com/files/gmock-1.7.0.zip
    URL_HASH SHA1=f9d9dd882a25f4069ed9ee48e70aff1b53e3c5a5
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
)

ExternalProject_Add(
    maszyna
    DEPENDS glbinding glfw glm flatbuffers
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/client
    CMAKE_ARGS
        -DCLIENT_3RDPARTY_PATH=${3RDPARTY_PATH}
    INSTALL_COMMAND ""
)

