#include "scene.h"


#include "tools/lights/directionnalLight.h"
#include "models/meshObject.h"

Scene::Scene(){


    objectsEngine = std::vector<EngineObject*>();

    objectsEngine.push_back(new MeshObject("Object Loaded", "exampleModels/monkey.off", glm::vec3(-2.28, 0.0,0.0)));

    Camera *cam = new CameraProj();

    objectsEngine.push_back(cam);


    objectsEngine.push_back(new DirectionnalLight());

}

Scene::~Scene(){
    deleteScene();
}

void Scene::deleteScene(){
    for(unsigned int i=0; i<objectsEngine.size(); i++){
        delete objectsEngine[i];
    }
}

Camera *Scene::getCamera(){
    for(unsigned int i=0; i<objectsEngine.size(); i++){
        if(Camera* c = dynamic_cast<Camera*>(objectsEngine[i])) {
        // old was safely casted to NewType
            return c;
        }
    }
    return NULL;
}

Light *Scene::getLight(){
    for(unsigned int i=0; i<objectsEngine.size(); i++){
        if(Light* l = dynamic_cast<Light*>(objectsEngine[i])) {
        // old was safely casted to NewType
            return l;
        }
    }
    return NULL;
}

void Scene::createUIAtID(int indexItem, char *ID){
    if(indexItem >= 0 && indexItem < (int)objectsEngine.size()){
        objectsEngine[indexItem]->createUI(ID);
    }
}

std::vector<std::string> Scene::getNameOfAllObjects(){
    std::vector<std::string> list = std::vector<std::string>();

    for(unsigned int i=0; i<objectsEngine.size(); i++){
        list.push_back(objectsEngine[i]->getName());
    }

    return list;
}