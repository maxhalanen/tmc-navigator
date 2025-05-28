#include "TileConversion.h"
#include <math.h>

double lon2tile(double lon, int zoom) {
    return (lon + 180.0) / 360.0 * (1 << zoom);
}

double lat2tile(double lat, int zoom) {
    double lat_rad = lat * M_PI / 180.0;
    return (1.0 - log(tan(lat_rad) + 1.0 / cos(lat_rad)) / M_PI) / 2.0 * (1 << zoom);
}


