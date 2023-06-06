# GeoTransform Benchmark

You can build this project by running these commands in a terminal:

```
cd GeoTransformBenchmark: Navigate to the project root directory.
mkdir build: Create a build directory (if it doesn't already exist).
cd build: Navigate into the build directory.
cmake ..: Generate the Makefile.
make: Build the project.
```
Please note that this requires that GDAL be installed on your system and discoverable by CMake (the find_package(GDAL REQUIRED) line in the CMake file).