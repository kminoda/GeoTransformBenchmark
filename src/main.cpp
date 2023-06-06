#include "benchmark.h"
#include <iostream>

int main() {
    // Define the geodetic coordinates for transformation
    LatLon geodetic {45.0, -72.0}; // Change this to your desired coordinates
    XY cartesian;

    // Define the source and target spatial references
    OGRSpatialReference oSourceSRS, oTargetSRS;
    oSourceSRS.SetWellKnownGeogCS( "WGS84" );

    // Mercator
    oTargetSRS.SetMercator(geodetic.lat, geodetic.lon, 1.0, 0.0, 0.0);
    double timeTaken = benchmarkTransform(geodetic, cartesian, oSourceSRS, oTargetSRS);
    std::cout << "Mercator transform: " << timeTaken << " s\n";

    // Transverse Mercator
    oTargetSRS.SetTM(geodetic.lat, geodetic.lon, 1.0, 0.0, 0.0);
    timeTaken = benchmarkTransform(geodetic, cartesian, oSourceSRS, oTargetSRS);
    std::cout << "Transverse Mercator transform: " << timeTaken << " s\n";

    // Stereographic
    oTargetSRS.SetStereographic(geodetic.lat, geodetic.lon, 1.0, 0.0, 0.0);
    timeTaken = benchmarkTransform(geodetic, cartesian, oSourceSRS, oTargetSRS);
    std::cout << "Stereographic transform: " << timeTaken << " s\n";

    // Inverse Stereographic transformation
    LatLon geodeticInverse;
    timeTaken = benchmarkInverseTransform(cartesian, geodeticInverse, oSourceSRS, oTargetSRS);
    std::cout << "Inverse Stereographic transform: " << timeTaken << " s\n";

    // Oblique Stereographic
    oTargetSRS.SetOS(geodetic.lat, geodetic.lon, 1.0, 0.0, 0.0);
    timeTaken = benchmarkTransform(geodetic, cartesian, oSourceSRS, oTargetSRS);
    std::cout << "Oblique Stereographic transform: " << timeTaken << " s\n";

    // Inverse Oblique Stereographic transformation
    // Reset geodeticInverse
    geodeticInverse = {0.0, 0.0};
    timeTaken = benchmarkInverseTransform(cartesian, geodeticInverse, oSourceSRS, oTargetSRS);
    std::cout << "Inverse Oblique Stereographic transform: " << timeTaken << " s\n";

    // Inverse transformation (example with Transverse Mercator)
    // Reset geodeticInverse
    geodeticInverse = {0.0, 0.0};
    oTargetSRS.SetTM(geodetic.lat, geodetic.lon, 1.0, 0.0, 0.0);
    timeTaken = benchmarkInverseTransform(cartesian, geodeticInverse, oSourceSRS, oTargetSRS);
    std::cout << "Inverse Transverse Mercator transform: " << timeTaken << " s\n";

    return 0;
}