cmake_minimum_required(VERSION 3.10)

# set the project name
project(GeoTransformBenchmark)

# add the executable
add_executable(${PROJECT_NAME} src/main.cpp src/benchmark.cpp)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add GDAL
find_package(GDAL REQUIRED)
include_directories(${GDAL_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${GDAL_LIBRARIES})

# include directories
include_directories(include)