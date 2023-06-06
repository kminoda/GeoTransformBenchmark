#include "benchmark.h"
#include <chrono>

// Function to perform the transformation and return the elapsed time
double benchmarkTransform(const LatLon& geodetic, XY& cartesian, OGRSpatialReference& oSourceSRS, OGRSpatialReference& oTargetSRS) {
    // Create coordinate transformation
    OGRCoordinateTransformation *poTransform = OGRCreateCoordinateTransformation( &oSourceSRS, &oTargetSRS );
    if( poTransform == NULL )
    {
        // Handle error
        return -1.0;
    }

    // Perform the transformation and measure the time
    auto start = std::chrono::high_resolution_clock::now();
    double x = geodetic.lon; // longitude
    double y = geodetic.lat; // latitude
    if( !poTransform->Transform( 1, &x, &y ) )
    {
        // Handle error
        return -1.0;
    }
    auto finish = std::chrono::high_resolution_clock::now();

    cartesian.x = x;
    cartesian.y = y;

    OCTDestroyCoordinateTransformation( poTransform );

    std::chrono::duration<double> elapsed = finish - start;
    return elapsed.count();
}

// Function to perform the inverse transformation and return the elapsed time
double benchmarkInverseTransform(const XY& cartesian, LatLon& geodetic, OGRSpatialReference& oSourceSRS, OGRSpatialReference& oTargetSRS) {
    // Create coordinate transformation
    OGRCoordinateTransformation *poTransform = OGRCreateCoordinateTransformation( &oTargetSRS, &oSourceSRS );
    if( poTransform == NULL )
    {
        // Handle error
        return -1.0;
    }

    // Perform the transformation and measure the time
    auto start = std::chrono::high_resolution_clock::now();
    double x = cartesian.x; // x-coordinate
    double y = cartesian.y; // y-coordinate
    if( !poTransform->Transform( 1, &x, &y ) )
    {
        // Handle error
        return -1.0;
    }
    auto finish = std::chrono::high_resolution_clock::now();

    geodetic.lat = y;
    geodetic.lon = x;

    OCTDestroyCoordinateTransformation( poTransform );

    std::chrono::duration<double> elapsed = finish - start;
    return elapsed.count();
}