#include "scene.h"

#include "../tools/lights/directionnalLight.h"
#include "../tools/cameraProj.h"

#include "../models/meshObject.h"
#include "../models/mesh/meshCube.h"
#include "../models/mesh/meshGrid.h"

#include "../material/simpleMat.h"

#include "../material/textureMaterial.h"

#include "../controlable/player.h"


Scene::Scene(){

    loadDefaultScene();

    MeshObject *obj = new MeshObject(addNewId(), "Cube", new Transform(), new MeshCube(0.5f), new SimpleMat(glm::vec4(1,1,0,1)));
    objectsEngine.push_back(obj);

}

Scene::~Scene(){
    deleteScene();
}

void Scene::deleteScene(){
    for(unsigned int i=0; i<objectsEngine.size(); i++){
        delete objectsEngine[i];
    }
}

Camera *Scene::getCameraRecursive(EngineObject *obj){
    Camera *tmp = NULL;
    if(Camera* c = dynamic_cast<Camera*>(obj)) {
        return c;
    } else {
        if(obj->listOfChildren.size() == 0){
            return NULL;
        } else {
            for(unsigned int i=0; i<obj->listOfChildren.size(); i++){
                tmp = getCameraRecursive(obj->listOfChildren[i]);
                if(tmp != NULL){ return tmp;}
            }
        }
        return NULL;
    }
}

Camera *Scene::getCamera(){
    Camera *tmp = NULL;
    for(unsigned int i=0; i<objectsEngine.size(); i++){
        tmp = getCameraRecursive(objectsEngine[i]);
        if(tmp != NULL){ return tmp;}
    }
    return NULL;
}

Light *Scene::getLight(){
    Light *tmp = NULL;
    for(unsigned int i=0; i<objectsEngine.size(); i++){
        tmp = getLightRecursive(objectsEngine[i]);
        if(tmp != NULL){ return tmp;}
    }
    return NULL;
}

Light *Scene::getLightRecursive(EngineObject *obj){
    Light *tmp = NULL;
    if(Light* l = dynamic_cast<Light*>(obj)) {
        return l;
    } else {
        if(obj->listOfChildren.size() == 0){
            return NULL;
        } else {
            for(unsigned int i=0; i<obj->listOfChildren.size(); i++){
                tmp = getLightRecursive(obj->listOfChildren[i]);
                if(tmp != NULL){ return tmp;}
            }
        }
        return NULL;
    }
}

void Scene::createUIAtID(int indexItem, char *ID){

    for(unsigned int i=0; i<objectsEngine.size(); i++){
        if(objectsEngine[i]->getID() == indexItem){
            objectsEngine[i]->createUI(ID);
            return;
        } else {
            drawUIAtID(objectsEngine[i]->listOfChildren, indexItem, ID);
        }
    }
}

void Scene::drawUIAtID(std::vector<EngineObject*> objs, int indexItem, char *ID){
    for(unsigned int i=0; i<objs.size(); i++){
        if(objs[i]->getID() == indexItem){
            objs[i]->createUI(ID);
            return;
        } else {
            drawUIAtID(objs[i]->listOfChildren, indexItem, ID);
        }
    }
}

void Scene::getAllObjects(std::vector<std::string> & names, std::vector<int> & ids){
    names.resize(objectsEngine.size());
    ids.resize(objectsEngine.size());


    for(unsigned int i=0; i<objectsEngine.size(); i++){
        names[i] = objectsEngine[i]->getName();
        ids[i] = objectsEngine[i]->getID();
    }

}


void Scene::addMeshObject(){
    objectsEngine.push_back(new MeshObject(addNewId()));
}

void Scene::addPlane(){
    objectsEngine.push_back(new MeshObject(addNewId(), "Plane", new Transform(), new MeshGrid()));
}

void Scene::addEngineObject(){
    objectsEngine.push_back(new EngineObject(addNewId()));
}

void Scene::addSphere(){
    objectsEngine.push_back(new MeshObject(addNewId(), "Sphere", new Transform(), new MeshLoader("../data/models/sphere.off")));
}

void Scene::addTerrain(){
    MeshObject *p = new MeshObject(addNewId(), "Terrain", new Transform(glm::vec3(0), glm::vec3(0), glm::vec3(1), glm::vec3(0.5,0,0)), new MeshGrid(128, 3, 0, 0.2, 5), new Lambertian());
    objectsEngine.push_back(p);
}

void Scene::deleteObject(int id){

    for(unsigned int i=0; i<objectsEngine.size(); i++){
        if(objectsEngine[i]->getID() == id){
            delete(objectsEngine[i]);
            objectsEngine.erase(objectsEngine.begin()+i);
            return;
        }
    }
}


int Scene::addNewId(){
    IDObject++;
    return IDObject-1;
}

void Scene::updateObj(EngineObject *obj){
    obj->update();
    for(unsigned int i=0; i<obj->listOfChildren.size(); i++){
        updateObj(obj->listOfChildren[i]);
    }
}

void Scene::update(){
    if(!pause){
        for(unsigned int i=0; i<objectsEngine.size(); i++){
            updateObj(objectsEngine[i]);
        }
    }
}


void Scene::togglePause(){
    pause = !pause;
}


void Scene::loadSolarSystem(){
    pause = false;

    IDObject = 0;


    objectsEngine = std::vector<EngineObject*>();

    Transform *EarthTransform =  new Transform(glm::vec3(0),glm::vec3(-2.5,0,0), glm::vec3(0.5), glm::vec3(0.44,0,0));
    Transform *MoonTransform = new Transform(glm::vec3(0),glm::vec3(0.9,0,0), glm::vec3(0.2), glm::vec3(0));

    MeshObject *Sun = new MeshObject(addNewId(),"Sun", new Transform(), new MeshLoader("../data/models/sphere.off"), new SimpleMat());
    MeshObject *Earth = new MeshObject(addNewId(),"Earth", EarthTransform, new MeshLoader("../data/models/sphere.off"), new Lambertian(glm::vec4(0.,0.,1.,1.)));
    MeshObject *Moon = new MeshObject(addNewId(),"Moon", MoonTransform, new MeshLoader("../data/models/sphere.off"), new Lambertian(glm::vec4(0.1,0.1,0.1,1.0)));

    Sun->addChild(Earth);
    Earth->addChild(Moon);

    objectsEngine.push_back(Sun);


    //// SET ANIMATION OF SOLAR SYSTEM
    Sun->getTransform()->setSameAsParent(true, false);
    Sun->getTransform()->setChildAnimation(false, true, false);


    Earth->getTransform()->setSameAsParent(true, false);
    Earth->getTransform()->setAnimation(false,true,false);
    Earth->getTransform()->setChildAnimation(false,true,false, 0.,-0.05,0.);

    Camera *cam = new CameraProj(addNewId());

    objectsEngine.push_back(cam);

    objectsEngine.push_back(new DirectionnalLight(addNewId(), "Light", glm::vec3(8, 0.0, 1)));

}

void Scene::loadDefaultScene(){
    pause = false;

    IDObject = 0;

    objectsEngine = std::vector<EngineObject*>();

    Camera *camera = new CameraProj(addNewId(), "Camera", glm::vec3(0,0,3));

    objectsEngine.push_back(camera);

    objectsEngine.push_back(new DirectionnalLight(addNewId(), "Light", glm::vec3(0, 2.0, 2)));
}


void Scene::loadTerrainPlayer(){
    pause = false;

    IDObject = 0;


    objectsEngine = std::vector<EngineObject*>();

    MeshObject *p = new MeshObject(addNewId(), "Terrain", new Transform(glm::vec3(0), glm::vec3(0), glm::vec3(1), glm::vec3(0.5,0,0)), new MeshGrid(32, 3, 0, 0.2, 5) ,new Lambertian(glm::vec4(0,0.6,0,1)));
    objectsEngine.push_back(p);


    Player *player = new Player(addNewId(), "Player", new Transform(glm::vec3(0), glm::vec3(0, 0.2, 0), glm::vec3(0.1)), new MeshLoader("../data/models/sphere.off"), new SimpleMat());

    p->addChild(player);

    Camera *camera = new CameraProj(addNewId(), "Camera", glm::vec3(0,1,3));

    objectsEngine.push_back(camera);

    objectsEngine.push_back(new DirectionnalLight(addNewId(), "Light", glm::vec3(0, 2.0, 2)));

}