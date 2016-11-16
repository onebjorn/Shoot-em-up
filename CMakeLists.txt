cmake_minimum_required(VERSION 2.8)

# Set up your project name.
project(Shoot-em-up)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

if(POLICY CMP0020)
cmake_policy(SET CMP0020 OLD)
endif()

find_package(Qt5Widgets REQUIRED)
find_package(Qt5OpenGL REQUIRED)

# Set up the main source folder.
set(SOURCE_ROOT src)

# Scan source folder to find all sources and put the result to SRC_LIST.
aux_source_directory(${SOURCE_ROOT} SRC_LIST)
qt5_wrap_cpp(QT_WRAPPED_SRC ${SRC_LIST})

# Create executable by SRC_LIST.
add_executable(${PROJECT_NAME} ${SRC_LIST} ${QT_WRAPPED_SRC} "src/point2d.h" "src/box2d.h" "src/ray2d.h" "src/space.h" "src/alien.h" "src/obstacle.h" "include/config_stat.h" "src/gun.h" "src/bullet.h" "src/gameEntity.h" "src/aliensManager.h" "src/bulletsManager.h" "src/logger.h" "src/main_window.h")

# Qt modules
qt5_use_modules(${PROJECT_NAME} Widgets OpenGL)

# Add subdirectory with Google Test Library.
add_subdirectory(3party/googletest)

# Enable unit testing.
enable_testing()

# Set up testing project name.
set(PROJECT_TEST_NAME ${PROJECT_NAME}_test)

# Add include directories for testing project.
include_directories(3party/googletest/googletest/include ${SOURCE_ROOT})

# Set up testing project.
set(TESTS_SOURCE_ROOT tests)
aux_source_directory(${TESTS_SOURCE_ROOT} TEST_SRC_FILES)
set(TEST_SRC_FILES ${SRC_LIST} ${TEST_SRC_FILES})
list(REMOVE_ITEM TEST_SRC_FILES src/main.cpp)
add_executable(${PROJECT_TEST_NAME} ${TEST_SRC_FILES})

# Link gtest and gtest_main libraries.
target_link_libraries(${PROJECT_TEST_NAME} gtest gtest_main)

# Finish tests setting up.
add_test(test ${PROJECT_TEST_NAME})


