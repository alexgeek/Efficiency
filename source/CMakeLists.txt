cmake_minimum_required(VERSION 2.8)
project(game)
set(GAME_LIB_NAME "gamelib")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")

# https://github.com/g-truc/glm/issues/300
add_definitions(-D__NO_INLINE__)

set(GLFW_SOURCE_DIR "external/glfw")
set(GLM_SOURCE_DIR "external/glm")
set(GLEW_SOURCE_DIR "external/glew")
set(LUA_SOURCE_DIR "external/lua")
set(SOIL_SOURCE_DIR "external/libSOIL")
set(GTEST_SOURCE_DIR "external/gtest")

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
add_subdirectory(${GTEST_SOURCE_DIR})

include_directories(
    ${GLFW_SOURCE_DIR}/include
    ${GLFW_SOURCE_DIR}/deps
    ${GLM_SOURCE_DIR}
    ${GLEW_SOURCE_DIR}/include
    ${LUA_SOURCE_DIR}/src
    ${SOIL_SOURCE_DIR}
    ${GTEST_SOURCE_DIR}/include
    ${GTEST_SOURCE_DIR}
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
    src/block/Block.cpp
    src/block/BlockRegistry.cpp
    src/camera/Camera.cpp
    src/camera/CameraArcBall.cpp
    src/Debug.cpp
    src/world/Dimension.cpp
    src/Game.cpp
    src/Input.cpp
    src/world/Region.cpp
    src/world/Region.cpp
    src/render/RenderCube.cpp
    src/render/RenderQuad.cpp
    src/render/RenderRect.cpp
    src/script/Script.cpp
    src/script/ScriptEngine.cpp
    src/render/RenderWorld.cpp
    src/render/BatchedRenderCube.cpp
    src/render/Shader.cpp
    src/render/Triangle.cpp
    src/util.c
    src/WindowContext.cpp
)
add_executable(${PROJECT_NAME} src/main.cpp)
add_library(${GAME_LIB_NAME} ${GAME_SRC})

target_link_libraries(${GAME_LIB_NAME} libSOIL glfw ${GLFW_LIBRARIES} glew ${OPENCL_LIBRARIES} liblua)

target_link_libraries(${PROJECT_NAME} ${GAME_LIB_NAME})

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/scripts $<TARGET_FILE_DIR:${PROJECT_NAME}>/scripts)

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets)


## Testing ##
enable_testing()
add_executable(test_game test/block/TestBlock.cpp test/world/TestWorld.cpp)

target_link_libraries(test_game gtest gtest_main)
target_link_libraries(test_game ${GAME_LIB_NAME})

add_test(test_game test_game)
