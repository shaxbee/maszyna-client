set(DIAGNOSTICS_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include/MaSzyna.Diagnostics")

set(DIAGNOSTICS_SOURCES
    ${DIAGNOSTICS_INCLUDE_DIR}/Trace.h
    Trace.cpp)

add_library(diagnostics STATIC ${DIAGNOSTICS_SOURCES})
set_target_properties(diagnostics PROPERTIES 
    CXX_STANDARD 11 
    CXX_EXTENSIONS OFF 
    CXX_STANDARD_REQUIRED ON)
