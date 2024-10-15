set (TEST_CPP "main.cpp"
    "LuaFunctions/Window.h"
    "LuaFunctions/Window.cpp"
)


add_executable(${CMAKE_PROJECT_NAME} "${TEST_CPP}")
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC LuaLib)
