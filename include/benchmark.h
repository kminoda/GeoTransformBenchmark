#ifndef GEOTRANSFORM_BENCHMARK_H
#define GEOTRANSFORM_BENCHMARK_H

#include <iostream>

#include "gdal_priv.h"
#include "cpl_conv.h" // for CPLMalloc()
#include "ogr_spatialref.h"
#include <GeographicLib/UTMUPS.hpp>

// Structure to hold latitude and longitude
struct LatLon {
    double lat;
    double lon;
};

// Structure to hold Cartesian coordinates
struct XY {
    double x;
    double y;
};

// Benchmark GDAL forward transformation (geodetic to cartesian)
double benchmarkTransform(const LatLon& geodetic, XY& cartesian,
                          OGRSpatialReference& oSourceSRS,
                          OGRSpatialReference& oTargetSRS);

// Benchmark GDAL inverse transformation (cartesian to geodetic)
double benchmarkInverseTransform(const XY& cartesian, LatLon& geodetic,
                                 OGRSpatialReference& oSourceSRS,
                                 OGRSpatialReference& oTargetSRS);

// Benchmark GeographicLib forward transformation (geodetic to UTM)
double benchmarkTransformGeographicLib(const LatLon& geodetic, XY& cartesian, int& zone);

// Benchmark GeographicLib inverse transformation (UTM to geodetic)
double benchmarkInverseTransformGeographicLib(const XY& cartesian, LatLon& geodetic, int& zone);

#endif //GEOTRANSFORM_BENCHMARK_H