#ifndef PLAYER_H
#define PLAYER_H

#include "../models/meshObject.h"
#include "../models/mesh/meshLoader.h"

class Player : public MeshObject {

public:
    Player(int id, std::string name = "Player", Transform *t = new Transform(), Mesh *m = new MeshLoader("../data/models/sphere.off"), Material *mat = new Lambertian());
    ~Player();

    void update() override;

    void createUI(char *ID);

    inline void setTerrainMesh(Mesh *m){
        terrain = m;
    }

private:

    void stayCloseToTerrain(Mesh *mesh);
    float triangle_area(int x1, int y1, int x2, int y2, int x3, int y3);
    bool isInsideTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int x, int y);

    float distanceFromTerrain = 0.1f;

    float speed = 0.01f;

    float heightFromTerrain = 0.1f;

    Mesh *terrain;

};



#endif