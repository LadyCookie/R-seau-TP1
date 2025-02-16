cmake_minimum_required(VERSION 3.12)

include("cmake/HunterGate.cmake")

HunterGate(
    URL "https://github.com/ruslo/hunter/archive/v0.23.214.tar.gz"
    SHA1 "e14bc153a7f16d6a5eeec845fb0283c8fad8c358"
)

project(exe_client 
        VERSION 0.0
        DESCRIPTION ""
        LANGUAGES CXX C)
            
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Have cmake create a compile database
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(${PROJECT_NAME}_BASE_OUTPUT_DIR ${PROJECT_SOURCE_DIR}/output)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${${PROJECT_NAME}_BASE_OUTPUT_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${${PROJECT_NAME}_BASE_OUTPUT_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${${PROJECT_NAME}_BASE_OUTPUT_DIR}/bin)

#Hunter dependencies
include(cmake/HunterLibs.cmake)

#Legacy External dependencies
add_subdirectory(external)

#Main project
add_subdirectory(main)


#Test project
enable_testing()
include(CTest)
add_subdirectory(test)



#CPack
include(cmake/Install.cmake)
include(CPack)
