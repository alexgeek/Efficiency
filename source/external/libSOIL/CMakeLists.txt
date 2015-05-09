cmake_minimum_required(VERSION 2.8)
project(libSOIL)

add_library(${PROJECT_NAME} image_DXT.c image_helper.c SOIL.c stb_image_aug.c)