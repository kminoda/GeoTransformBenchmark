#ifndef GEOTRANSFORM_BENCHMARK_H
#define GEOTRANSFORM_BENCHMARK_H

#include "gdal_priv.h"
#include "cpl_conv.h" // for CPLMalloc()
#include "ogr_spatialref.h"

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

// Benchmark the geodetic to Cartesian transformation
double benchmarkTransform(const LatLon& geodetic, XY& cartesian, OGRSpatialReference& oSourceSRS, OGRSpatialReference& oTargetSRS);

// Benchmark the Cartesian to geodetic transformation
double benchmarkInverseTransform(const XY& cartesian, LatLon& geodetic, OGRSpatialReference& oSourceSRS, OGRSpatialReference& oTargetSRS);

#endif //GEOTRANSFORM_BENCHMARK_H