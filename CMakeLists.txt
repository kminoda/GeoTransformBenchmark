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
# find_package(GeographicLib REQUIRED)
# set(GeographicLib_INCLUDE_DIRS /usr/include/geographiclib/include)
# set(GeographicLib_LIBRARIES /usr/include/geographiclib/lib)
# manually set GeographicLib
find_path(GeographicLib_INCLUDE_DIRS NAMES GeographicLib/Config.h)
find_library(GeographicLib_LIBRARIES NAMES Geographic)

include_directories(${GDAL_INCLUDE_DIRS} ${GeographicLib_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${GDAL_LIBRARIES} ${GeographicLib_LIBRARIES})

# include directories
include_directories(include)