
#include "../imgui/imgui.h"
#include "../impl/imgui_impl_glfw.h"
#include "../impl/imgui_impl_opengl3.h"


#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h>    // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>    // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>  // Initialize with gladLoadGL()
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif

#include "meshLoader.h"

#include "meshObject.h"

#include <iostream>

#include "../material/lambertian.h"


MeshObject::MeshObject(std::string n, const char *filename, vec3 position, vec3 scale, vec3 rotation){
    transform = new Transform(position, scale, rotation);

    Mesh *m = new Mesh("exampleModels/head.off");

    vertices = std::vector<float>(m->vertices, m->vertices + sizeof(m->vertices) / sizeof(m->vertices) );
    triangles = std::vector<int>(m->faces, m->faces + sizeof(m->faces) / sizeof(m->faces) );
    normals = std::vector<float>(m->normals, m->normals + sizeof(m->normals) / sizeof(m->normals) );
    // triangles;
    // normals;

    printf("creation done\n");

    createVAO();

    material = new Lambertian();

    name = n;

    delete m;
}


MeshObject::~MeshObject(){
    deleteVAO();
    delete transform;
    delete material;
}




int *MeshObject::getTriangles(){
    return &triangles[0];
}

float *MeshObject::getVertices(){
    return &vertices[0];
}

int MeshObject::nbVertices(){
    return vertices.size()/3;
}

int MeshObject::nbTriangles(){
    return triangles.size()/3;
}



void MeshObject::draw(glm::mat4 viewMat, glm::mat4 projectionMat, glm::vec3 light){

    glUseProgram(material->shaderID());

    setUniform(viewMat, projectionMat, light);

    glBindVertexArray(vertexArrayID);
    glDrawElements(GL_TRIANGLES,3*nbTriangles(),GL_UNSIGNED_INT,(void *)0);
    glBindVertexArray(0);

    glUseProgram(0);
}

void MeshObject::createVAO(){

    buffers = new GLuint[2];

    glGenBuffers(2, buffers);
    glGenVertexArrays(1,&vertexArrayID);

    // create the VBO associated with the grid (the terrain)
    glBindVertexArray(vertexArrayID);
    glBindBuffer(GL_ARRAY_BUFFER,buffers[0]); // vertices
    glBufferData(GL_ARRAY_BUFFER,nbVertices()*3*sizeof(float),getVertices(),GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void *)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,buffers[1]); // indices
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,nbTriangles()*3*sizeof(int),getTriangles(),GL_STATIC_DRAW);
}

void MeshObject::deleteVAO(){
    glDeleteBuffers(2,buffers);
    glDeleteVertexArrays(1,&vertexArrayID);
}

void MeshObject::setUniform(glm::mat4 viewMat, glm::mat4 projectionMat, glm::vec3 light){

    glm::mat4 modelMat = transform->getMat4();


    // send the transformation matrix
    material->callUniform(modelMat, viewMat, projectionMat, light);

}


void MeshObject::createUI(char *ID){
    ImGui::BeginChild(ID);
    ImGui::Text(name.c_str());
    ImGui::Separator();

    transform->createUI();
    ImGui::Separator();
    material->createUI();
    ImGui::Separator();

    ImGui::EndChild();
}