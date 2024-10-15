set (TEST_CPP "main.cpp"
    "Window/Window.h"
    "Window/Window.cpp"
    "Rendering/Rendering.h"
    "Rendering/Rendering.cpp"
)


add_executable(${CMAKE_PROJECT_NAME} "${TEST_CPP}")
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC LuaLib)
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC "Window/")
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC "Rendering/")
