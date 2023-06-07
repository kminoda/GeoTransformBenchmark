#include "benchmark.h"
#include <iostream>
#include <iomanip>

int getUTMZone(double longitude) {
    return static_cast<int>((longitude + 180) / 6) + 1;
}

int main() {
    // Define the geodetic coordinates for transformation
    LatLon geodetic {35.6092, 139.7303}; // Change this to your desired coordinates
    XY cartesian;
    double timeTaken;
    LatLon geodeticInverse {0.0, 0.0};
    std::cout << "==========================================" << "\n";
    std::cout << "Original lat: " << std::setprecision(4) << std::fixed << geodetic.lat << ", lon: " << geodetic.lon << "\n";
    std::cout << "==========================================" << "\n";

    // Define the source and target spatial references
    OGRSpatialReference oSourceSRS, oTargetSRS;
    oSourceSRS.SetWellKnownGeogCS( "WGS84" );

    // Mercator
    oTargetSRS.SetMercator(geodetic.lat, geodetic.lon, 1.0, 0.0, 0.0);
    timeTaken = benchmarkTransform(geodetic, cartesian, oSourceSRS, oTargetSRS);
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

    // UTM
    // Note: the second parameter is a boolean for North (true) or South (false) hemisphere
    std::cout << getUTMZone(geodetic.lon) << std::endl;
    oTargetSRS.SetUTM(getUTMZone(geodetic.lon), true);
    timeTaken = benchmarkTransform(geodetic, cartesian, oSourceSRS, oTargetSRS);
    // std::cout << "UTM transform: " << timeTaken << " s\n";
    std::cout << "GDAL UTM x: " << std::setprecision(4) << std::fixed << cartesian.x << ", y: " << cartesian.y << "\n";

    // Inverse UTM transformation
    // Reset geodeticInverse
    geodeticInverse = {0.0, 0.0};
    timeTaken = benchmarkInverseTransform(cartesian, geodeticInverse, oSourceSRS, oTargetSRS);
    // std::cout << "Inverse UTM transform: " << timeTaken << " s\n";
    std::cout << "GDAL UTM inverse lat: " << std::setprecision(4) << std::fixed << geodeticInverse.lat << ", lon: " << geodeticInverse.lon << "\n";
    std::cout << "==========================================" << "\n";

    // GeographicLib UTM
    int utm_zone;
    timeTaken = benchmarkTransformGeographicLib(geodetic, cartesian, utm_zone);
    // std::cout << "GeographicLib UTM transform: " << timeTaken << " s\n";
    std::cout << "GeographicLib UTM x: " << std::setprecision(4) << std::fixed << cartesian.x << ", y: " << cartesian.y << "\n";

    // Inverse GeographicLib UTM transformation
    geodeticInverse = {0.0, 0.0};
    timeTaken = benchmarkInverseTransformGeographicLib(cartesian, geodeticInverse, utm_zone);
    // std::cout << "Inverse GeographicLib UTM transform: " << timeTaken << " s\n";
    std::cout << "GeographicLib UTM inverse lat: " << std::setprecision(4) << std::fixed << geodeticInverse.lat << ", lon: " << geodeticInverse.lon << "\n";

    return 0;
}