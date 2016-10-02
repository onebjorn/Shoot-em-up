cmake_minimum_required(VERSION 2.8)

add_definitions(--std=c++11)

set(SOURCE_ROOT source)

project(Shoot-em-up)

aux_source_directory(${SOURCE_ROOT} SOURCE_LIST)

add_executable(${PROJECT_NAME} ${SOURCE_LIST})