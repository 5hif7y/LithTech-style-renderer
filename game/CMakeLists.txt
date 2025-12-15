add_executable(game
    src/main.cpp
    src/DemoScene.cpp
)

target_include_directories(engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(game PUBLIC engine)

find_package(SDL2 REQUIRED)
target_link_libraries(game PRIVATE SDL2::SDL2)

