#include "player.h"

#include <imgui.h>

#include <iostream>

Player::Player(int id, std::string name, Transform *t, Mesh *m, Material *mat){

    setName(name);
    setID(id);
    fullMesh = m;
    currentMesh = fullMesh;
    material = mat;
    transform = t;

    glm::vec3 center = currentMesh->getCenter();
    t->setCenter(center);

    createVAO();

}


Player::~Player(){
    
}

void Player::update(){

    glm::vec3 pos = transform->getPosition();
    if(ImGui::IsKeyPressed('W')){
        pos.z -= speed;
    }
    if(ImGui::IsKeyPressed('S')){
        pos.z += speed;
    }
    if(ImGui::IsKeyPressed('A')){
        pos.x -= speed;
    }
    if(ImGui::IsKeyPressed('D')){
        pos.x += speed;
    }

    transform->setPosition(pos);  
    
    stayCloseToTerrain(terrain);

 
}

float Player::sign(glm::vec2 p1, glm::vec2 p2, glm::vec2 p3) {
    return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

bool Player::isInTriangle(glm::vec2 pt, glm::vec2 v1, glm::vec2 v2, glm::vec2 v3){
    float d1, d2, d3;
    bool has_neg, has_pos;

    d1 = sign(pt, v1, v2);
    d2 = sign(pt, v2, v3);
    d3 = sign(pt, v3, v1);

    has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
    has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

    return !(has_neg && has_pos);
}

float distance(glm::vec2 v1, glm::vec2 v2){
    return sqrt((v1.x-v2.x)*(v1.x-v2.x) + (v1.y-v2.y)*(v1.y-v2.y));
}

void Player::stayCloseToTerrain(Mesh *mesh){

    unsigned int v1, v2, v3;
    bool found = false;


    glm::vec3 p = transform->getPosition();

    for(unsigned int i=0; !found && i<mesh->getNBFaces(); i++){
        std::vector<unsigned int> face = mesh->get_face(i);
        assert(face.size() == 3);
        v1 = face[0];
        v2 = face[1];
        v3 = face[2];

        if(isInTriangle(glm::vec2(p.x, p.z), glm::vec2(mesh->get_vertex(v1).x, mesh->get_vertex(v1).z), glm::vec2(currentMesh->get_vertex(v2).x, currentMesh->get_vertex(v2).z), glm::vec2(currentMesh->get_vertex(v3).x, currentMesh->get_vertex(v3).z))){
            found = true;
        }
        
    }

    // INTERPOLATION DE Y

    float w1 = 1.0f/distance(glm::vec2(mesh->get_vertex(v1).x, mesh->get_vertex(v1).z), glm::vec2(p.x, p.z));
    float w2 = 1.0f/distance(glm::vec2(mesh->get_vertex(v2).x, mesh->get_vertex(v2).z), glm::vec2(p.x, p.z));
    float w3 = 1.0f/distance(glm::vec2(mesh->get_vertex(v3).x, mesh->get_vertex(v3).z), glm::vec2(p.x, p.z));


    float yP = (mesh->get_vertex(v1).y*w1 + mesh->get_vertex(v2).y*w2 + mesh->get_vertex(v3).y*w3)/(w1+w2+w3);
    
    yP += heightFromTerrain;

    // update pos Y
    transform->setPosition(glm::vec3(transform->getPosition().x, yP, transform->getPosition().z));


}




void Player::createUI(char *ID){
    ImGui::BeginChild(ID);
    ImGui::Text(name.c_str()); ImGui::SameLine();
    ImGui::Text("id : %d", getID());
    ImGui::Separator();
    transform->createUI();


    ImGui::Separator();
    ImGui::Text("Player Speed: ");
    ImGui::DragFloat("##speed", &speed, 0.01f);  

    ImGui::Text("Height from terrain : ");
    ImGui::DragFloat("##heightFromTerrain", &heightFromTerrain, 0.01f);

    ImGui::Separator();
    bool node_material = ImGui::TreeNodeEx("Material", 0);
    if(node_material){
        material->createUI();
        ImGui::TreePop();
    }

    ImGui::EndChild();

}