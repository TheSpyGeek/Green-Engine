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

private:

    float distanceFromTerrain = 0.1f;

    float speed = 0.01f;

};



#endif