#include "benchmark.h"
#include <chrono>

double getCurrentTime() {
    auto now = std::chrono::high_resolution_clock::now();
    auto now_ms = std::chrono::time_point_cast<std::chrono::microseconds>(now);
    auto epoch = now_ms.time_since_epoch();
    auto value = std::chrono::duration_cast<std::chrono::microseconds>(epoch);
    return value.count() / 1e6;
}

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
    // double x = geodetic.lon; // longitude
    // double y = geodetic.lat; // latitude
    double x = geodetic.lat;
    double y = geodetic.lon;
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

    // geodetic.lat = y;
    // geodetic.lon = x;
    geodetic.lat = x;
    geodetic.lon = y;

    OCTDestroyCoordinateTransformation( poTransform );

    std::chrono::duration<double> elapsed = finish - start;
    return elapsed.count();
}

double benchmarkTransformGeographicLib(const LatLon& geodetic, XY& cartesian, int& zone) {
    double start = getCurrentTime();

    bool northp;
    double x, y;
    GeographicLib::UTMUPS::Forward(geodetic.lat, geodetic.lon, zone, northp, x, y);

    cartesian.x = x;
    cartesian.y = y;

    return getCurrentTime() - start;
}

double benchmarkInverseTransformGeographicLib(const XY& cartesian, LatLon& geodetic, int& zone) {
    double start = getCurrentTime();

    bool northp;
    double lat, lon;
    GeographicLib::UTMUPS::Reverse(zone, cartesian.x, cartesian.y, northp, lat, lon);

    geodetic.lat = lat;
    geodetic.lon = lon;

    return getCurrentTime() - start;
}