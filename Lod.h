#ifndef LOD_H
#define LOD_H

#include "Path.h"



//Lod inherits from Path
class Lod : public Path {
public:
    Lod(TerrainMap& map, Point start, Point finish) : Path(map, "Lod", start, finish) {}
    bool find() override;
};





#endif