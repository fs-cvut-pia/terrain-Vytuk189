#ifndef ZELEZNICE_H
#define ZELEZNICE_H

#include "Path.h"

//Zeleznice inherits from Path
class Zeleznice : public Path {
public:
    Zeleznice(TerrainMap& map, Point start, Point finish) : Path(map, "Zeleznice", start, finish) {}
    bool find() override;
};

#endif
