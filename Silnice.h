#ifndef SILNICE_H
#define SILNICE_H

#include "Path.h"



//Silnice inherits from Path
class Silnice : public Path {
public:
    Silnice(TerrainMap& map, Point start, Point finish) : Path(map, "Silnice", start, finish) {}
    bool find() override;
};





#endif