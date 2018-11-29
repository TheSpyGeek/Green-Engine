#include <imgui.h>

#include "directionnalLight.h"

DirectionnalLight::DirectionnalLight(std::string name, glm::vec3 l){
    setName(name);
    light = l;
}



glm::vec3 DirectionnalLight::getLight(){
    return light;
}

void DirectionnalLight::createUI(char *ID){
    const float lowestValue = -1000.0f;
    const float highestValue = 1000.0f;
    const char *format = "%.3f";

    ImGui::BeginChild(ID);
    ImGui::Text(name.c_str());
    ImGui::Separator();


    ImGui::PushItemWidth(-1);

    ImGui::Text("Direction: "); ImGui::SameLine();
    ImGui::DragFloat3("directionLight", &light[0], 0.01f, lowestValue, highestValue, format);


    ImGui::PopItemWidth();

    ImGui::EndChild();
}