#ifndef LETADLO_H
#define LETADLO_H

#include "Path.h"


// Letadlo inherits from path
class Letadlo : public Path {
public:
    Letadlo(TerrainMap& map, Point start, Point finish) : Path(map, "Letadlo", start, finish) {}
    bool find() override;
};





#endif