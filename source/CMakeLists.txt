cmake_minimum_required(VERSION 2.8)
project(game)

#add_definitions(-std=c++11)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(GLFW_SOURCE_DIR "external/glfw")
set(GLM_SOURCE_DIR "external/glm")
set(GLEW_SOURCE_DIR "external/glew")
set(LUA_SOURCE_DIR "external/lua")
set(SOIL_SOURCE_DIR "external/libSOIL")

# Building only the GLFW lib
set(BUILD_SHARED_LIBS OFF CACHE BOOL "")
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "")
set(GLFW_INSTALL OFF CACHE BOOL "")

include_directories(${CMAKE_SOURCE_DIR}/include)

add_subdirectory(${GLFW_SOURCE_DIR} ${GLEW_SOURCE_DIR})
add_subdirectory(${LUA_SOURCE_DIR})
add_subdirectory(${SOIL_SOURCE_DIR})

include_directories(
    ${GLFW_SOURCE_DIR}/include
    ${GLFW_SOURCE_DIR}/deps
    ${GLM_SOURCE_DIR}
    ${GLEW_SOURCE_DIR}/include
    ${LUA_SOURCE_DIR}/src
    ${SOIL_SOURCE_DIR}
)

add_library(
    glew STATIC
    ${GLEW_SOURCE_DIR}/src/glew.c
    ${GLEW_SOURCE_DIR}/include
)

target_link_libraries(glew ${GLFW_LIBRARIES})

add_definitions(
  -DGLEW_STATIC
)

set(GAME_SRC
    main.cpp
    BatchedRenderCube.cpp
    Camera.cpp
    CameraArcBall.cpp
    Debug.cpp
    Dimension.cpp
    Game.cpp
    Input.cpp
    Region.cpp
    Region.cpp
    RenderCube.cpp
    RenderQuad.cpp
    RenderRect.cpp
    Script.cpp
    ScriptEngine.cpp
    Shader.cpp
    Triangle.cpp
    util.c
    WindowContext.cpp
)
add_executable(${PROJECT_NAME} ${GAME_SRC})

target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES} glew ${OPENCL_LIBRARIES})
#target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/libs/libglfw.a)
target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/libs/libdrawtext.a)
target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/libs/libSOIL.a)
target_link_libraries(${PROJECT_NAME} liblua)
target_link_libraries(${PROJECT_NAME} libSOIL)

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/scripts $<TARGET_FILE_DIR:${PROJECT_NAME}>/scripts)

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets)
