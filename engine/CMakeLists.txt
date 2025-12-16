add_library(engine STATIC
    src/Engine.cpp
)

target_include_directories(engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Required in Linux for dlopen/dlsym
if(UNIX)
target_link_libraries(engine PRIVATE dl)
endif()

