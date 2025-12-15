add_library(OGL4REN SHARED
    RendererOGL4.cpp
    gl.c
)

target_include_directories(OGL4REN PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../..          # to reach engine/include/IRenderer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../../engine/include
)

find_package(SDL2 REQUIRED)

target_link_libraries(OGL4REN PRIVATE
    engine
    SDL2::SDL2
)

# Copy the library next to the game executable
add_custom_command(TARGET OGL4REN POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:OGL4REN>
        $<TARGET_FILE_DIR:game>
)

# Copy the shaders folder next to the game executable
add_custom_command(TARGET OGL4REN POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/shaders
        $<TARGET_FILE_DIR:game>/shaders
)
