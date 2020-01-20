#include "meshLoaderOFF.h"



#include <imgui.h>

#include <iostream>

#include <math.h>


MeshLoaderOFF::MeshLoaderOFF(char *filename) {
    setName("Mesh Loader OFF");

    sprintf(m_filename, "%s", filename);
    create();
}

void MeshLoaderOFF::create() {
    readOFFfile(m_filename);

    computeAllInfo();

    createVAO();
}



void MeshLoaderOFF::recreate(char *filename) {

    FILE *file;
    if((file=fopen(filename,"r"))==NULL) {
        m_errorMessage = "Unable to read ";
        //printf("Unable to read %s\n",filename);
        return;
    }
    cleanup();
    sprintf(m_filename, "%s", filename);
    create();
    computeAllInfo();
    m_errorMessage = "";
}





/// Read vertices and faces from the file "filename" at the format OFF
void MeshLoaderOFF::readOFFfile(char *filename) {

    unsigned int tmp;
    unsigned int i,j;

    FILE *file;
    int   error;

    if((file=fopen(filename,"r"))==NULL) {
      printf("Unable to read %s\n",filename);
    }

    int nbVertices, nbFaces;
    error = fscanf(file,"OFF\n%d %d %d\n",&(nbVertices),&(nbFaces),&tmp);
    if(error==EOF) {
      printf("Unable to read %s\n",filename);
    }

    m_vertices.resize(nbVertices);
    m_faces.resize(nbFaces*3);

    glm::vec3 vertex = glm::vec3(0);

    // reading vertices
    for(i=0;i<getNBVertices();i++) {

        error = fscanf(file,"%f %f %f\n",&(vertex.x),&(vertex.y),&(vertex.z));
        if(error==EOF) {
            printf("Unable to read vertices of %s\n",filename);
        }
        m_vertices[i] = vertex;
    }


    // reading faces
    j = 0;
    for(i=0;i<getNBFaces();i++) {
        error = fscanf(file,"%d %d %d %d\n",&tmp,&(m_faces[j]),&(m_faces[j+1]),&(m_faces[j+2]));
        if(error==EOF) {
            printf("Unable to read faces of %s\n",filename);
        }

        if(tmp!=3) {
          printf("Error : face %d is not a triangle (%d polygonal face!)\n",i/3,tmp);
        }
        j += 3;
    }

    fclose(file);
}

void MeshLoaderOFF::createUI() {

    ImGui::InputText("##fileMeshLoader", m_filename, IM_ARRAYSIZE(m_filename));

    if(ImGui::Button("Recreate")){
        recreate(m_filename);
    }
    if(!m_errorMessage.empty()){
        ImGui::TextColored(ImVec4(1,0,0,1),"%s: %s", m_errorMessage.c_str(), m_filename);
    }
}


MeshLoaderOFF::~MeshLoaderOFF() {
    cleanup();
}

