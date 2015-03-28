cmake_minimum_required(VERSION 2.8.11)
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
    GIT_REPOSITORY https://github.com/shaxbee/glfw.git
    CMAKE_ARGS
        -DGLFW_BUILD_EXAMPLES=OFF
        -DGLFW_BUILD_TESTS=OFF
        -DGLFW_BUILD_DOCS=OFF
        -DCMAKE_INSTALL_PREFIX=${3RDPARTY_PATH}
)

ExternalProject_Add(
    glm
    URL https://github.com/g-truc/glm/archive/0.9.6.3.zip
    URL_HASH SHA1=b2b12e7484549a6b124a5516c1cf8bc6084e1be2
    BUILD_COMMAND ""
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
    DEPENDS glbinding glfw
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/client
    CMAKE_ARGS
        -DCLIENT_3RDPARTY_PATH=${3RDPARTY_PATH}
    INSTALL_COMMAND ""
)

