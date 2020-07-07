cmake_minimum_required (VERSION 3.8)

set (CMAKE_C_COMPILER gcc)
set (CMAKE_CXX_COMPILER g++)
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_FLAGS "-std=c++11")

project (evo3)
enable_language(CXX)

set (SOURCE_FILES
    src
    main.cpp
)

add_executable (evo3 ${SOURCE_FILES})
