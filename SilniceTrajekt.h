#ifndef SILNICETRAJEKT_H
#define SILNICETRAJEKT_H

#include "Path.h"

//SilniceTrajekt inherits from Path
class SilniceTrajekt : public Path {
public:
    SilniceTrajekt(TerrainMap& map, Point start, Point finish) : Path(map, "SilniceTrajekt", start, finish) {}
    bool find() override;
};

#endif
