#pragma once

#include <mbgl/style/types.hpp>
#include <mbgl/util/constants.hpp>
#include <mbgl/util/geo.hpp>

#include <array>
#include <vector>
#include <string>
#include <cstdint>

namespace mbgl {

class TileID;

class SourceInfo {
public:
    std::vector<std::string> tiles;
    uint8_t minZoom = 0;
    uint8_t maxZoom = 22;
    std::string attribution;
    LatLng center;
    double zoom = 0;
    LatLngBounds bounds = LatLngBounds::world();

    std::vector<uint8_t> stepZooms;

    uint8_t sourceZoom(uint8_t szoom) const {
        return szoom >= maxZoom ? maxZoom : (stepZooms.empty() ? szoom : stepZooms[szoom]);
    }
};

} // namespace mbgl
