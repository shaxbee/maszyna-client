add_subdirectory(Maszyna.Diagnostics)

compile_flatbuffers_schema_to_cpp(schema/model.fbs)

add_executable(maszyna
    main.cpp
    schema/model_generated.h
)
target_link_libraries(maszyna diagnostics)

set_target_properties(maszyna PROPERTIES 
    CXX_STANDARD 11 
    CXX_EXTENSIONS OFF 
    CXX_STANDARD_REQUIRED ON)
target_link_libraries(maszyna ${GLBINDING_LIBRARIES} glfw glm flatbuffers)
target_compile_definitions(maszyna PRIVATE -DGLBINDING_STATIC -DGLFW_INCLUDE_NONE)
