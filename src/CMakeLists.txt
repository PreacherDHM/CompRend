set (TEST_CPP "main.cpp"
    "Window/Window.h"
    "Window/Window.cpp"
    "Window/window_lua.h"
    "Window/window_lua.cpp"
    "Rendering/Rendering.h"
    "Rendering/Rendering.cpp"
    #"Rendering/Lua_Wrapers.h"
    #"Rendering/Lua_Wrapers.cpp"
    "Rendering/Entity.h"
    "Rendering/Entity.cpp"
    "Rendering/Csprite.cpp"
    "Rendering/Csprite.h"
    "Rendering/Scene.h"
    "Rendering/Scene.cpp"
)


add_executable(${CMAKE_PROJECT_NAME} "${TEST_CPP}")
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC LuaLib)
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC "Window/")
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC "Rendering/")
