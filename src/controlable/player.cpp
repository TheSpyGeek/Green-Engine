#include "player.h"

#include <imgui.h>

#include <iostream>

Player::Player(int id, std::string name, Transform *t, Mesh *m, Material *mat){

    setName(name);
    setID(id);
    mesh = m;
    material = mat;
    transform = t;

    glm::vec3 center = mesh->getCenter();
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
}


void stayCloseToTerrain(Mesh *mesh){

}

// code from https://www.geeksforgeeks.org/check-whether-a-given-point-lies-inside-a-triangle-or-not/

float Player::triangle_area(int x1, int y1, int x2, int y2, int x3, int y3) {
   return abs((x1*(y2-y3) + x2*(y3-y1)+ x3*(y1-y2))/2.0); 
} 
  
/* A function to check whether point P(x, y) lies inside the triangle formed  
   by A(x1, y1), B(x2, y2) and C(x3, y3) */ 
bool Player::isInsideTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int x, int y){    
   /* Calculate area of triangle ABC */
   float A = triangle_area (x1, y1, x2, y2, x3, y3); 
  
   /* Calculate area of triangle PBC */   
   float A1 = triangle_area (x, y, x2, y2, x3, y3); 
  
   /* Calculate area of triangle PAC */   
   float A2 = triangle_area (x1, y1, x, y, x3, y3); 
  
   /* Calculate area of triangle PAB */    
   float A3 = triangle_area (x1, y1, x2, y2, x, y); 
    
   /* Check if sum of A1, A2 and A3 is same as A */ 
   return (A == A1 + A2 + A3); 
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

    ImGui::Separator();
    bool node_material = ImGui::TreeNodeEx("Material", 0);
    if(node_material){
        material->createUI();
        ImGui::TreePop();
    }

    ImGui::EndChild();

}