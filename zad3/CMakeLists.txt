cmake_minimum_required (VERSION 3.17)

set (CMAKE_C_COMPILER gcc)
set (CMAKE_CXX_COMPILER g++)
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
# set (CMAKE_CXX_FLAGS "-std=c++11")
set (CMAKE_CXX_FLAGS "-Wall -pedantic -Wextra -Weffc++")

add_definitions("-std=c++11")

project(evo3)
enable_language(CXX)

set (SOURCE_FILES
    src/fitness/complexFitness.cpp
    src/fitness/davesBouldin.cpp
    src/fitness/dunnIndex.cpp
    src/fitness/fitness.cpp
    src/fitness/silhouette.cpp
    src/fitness/weightedFitness.cpp
    src/cluster.cpp
    src/clusterer.cpp
    src/creature.cpp
    src/point.cpp
    src/utils.cpp
    main.cpp
)

# include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
# conan_basic_setup()

add_executable (evo3 ${SOURCE_FILES})
# target_link_libraries(evo3 ${CONAN_LIBS})
