cmake_minimum_required(VERSION 3.12)

#Include the whole include directory for this directory
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

#Source files
set(MODEL_TEST_VIEWER_SOURCES src/main_test.cpp)

#Headers files (for IntelliSense)
set(MODEL_TEST_VIEWER_HEADERS include/main_test.hpp)

find_package(GTest CONFIG REQUIRED)
find_package(GMock CONFIG REQUIRED)

add_executable(model_viewer_test ${MODEL_TEST_VIEWER_SOURCES} ${MODEL_TEST_VIEWER_HEADERS})
target_link_libraries(model_viewer_test PUBLIC GTest::main GMock::gmock)

add_test(NAME model_viewer COMMAND model_viewer_test)