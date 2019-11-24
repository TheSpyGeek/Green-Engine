#ifndef PLAYER_H
#define PLAYER_H

#include "../models/meshObject.h"
#include "../models/mesh/meshLoader.h"

#include "../tools/camera.h"

class Player : public MeshObject {

public:
    Player(int id, std::string name = "Player", Transform *t = new Transform(), Mesh *m = new MeshLoader("../data/models/sphere.off"), Material *mat = new Lambertian());
    ~Player();

    void update() override;

    void createUI(char *ID);

    inline void setTransformWorldAndCamera(Transform *trans, Camera *c){
        world = trans;
        cam = c;
    }

    inline void setTerrainMesh(Mesh *m){
        terrain = m;
    }

private:

    void stayCloseToTerrain(Mesh *mesh);

    float sign(glm::vec2 p1, glm::vec2 p2, glm::vec2 p3);
    bool isInTriangle(glm::vec2 pt, glm::vec2 v1, glm::vec2 v2, glm::vec2 v3);

    float computeDistanceFromTheCamera();

    float distanceFromTerrain = 0.1f;

    float speed = 0.01f;

    float heightFromTerrain = 0.1f;

    Mesh *terrain;

    Transform *world = NULL;
    Camera *cam = NULL;


};



#endif