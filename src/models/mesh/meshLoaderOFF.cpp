#include "meshLoaderOFF.h"



#include <imgui.h>

#include <iostream>

#include <math.h>


MeshLoaderOFF::MeshLoaderOFF(char *filename) {
    setName("Mesh Loader OFF");

    sprintf(m_filename, "%s", filename);
    readOFFfile(filename);

    computeAllInfo();

    createVAO();
}



/*
void MeshLoaderOFF::recreate(){

    if(strcmp(currentFilename, backupFilename) == 0){ // meme fichier
        cleanup();
        vertices = backupVertices;
        faces = backupFaces;
        nb_vertices = backupVertices.size();
        nb_faces = backupFaces.size()/3;
    } else {
        if(fopen(currentFilename,"r") == NULL) {
          
    initialize();  return;
        }
        cleanup();
        readOFFfile(currentFilename);
        sprintf(backupFilename, "%s", currentFilename);
        backupVertices = vertices;
        backupFaces = faces;
        nb_vertices = backupVertices.size();
        nb_faces = backupFaces.size()/3;
    }

    computeAllInfo();


}*/





/// Read vertices and faces from the file "filename" at the format OFF
void MeshLoaderOFF::readOFFfile(char *filename){

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

    nb_vertices = nbVertices;
    nb_faces = nbFaces;


    vertices.resize(nbVertices);
    faces.resize(nbFaces*3);

    glm::vec3 vertex = glm::vec3(0);

    // reading vertices
    for(i=0;i<getNBVertices();i++) {

        error = fscanf(file,"%f %f %f\n",&(vertex.x),&(vertex.y),&(vertex.z));
        if(error==EOF) {
            printf("Unable to read vertices of %s\n",filename);
        // MeshLoader_delete(MeshLoader);
        // return NULL;
        }
        vertices[i] = vertex;
    }


    // reading faces
    j = 0;
    for(i=0;i<getNBFaces();i++) {
        error = fscanf(file,"%d %d %d %d\n",&tmp,&(faces[j]),&(faces[j+1]),&(faces[j+2]));
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

void MeshLoaderOFF::createUI(){

    ImGui::InputText("##fileMeshLoader", m_filename, IM_ARRAYSIZE(m_filename));
    // this->Mesh::createUI();

    ImGui::Text("Nombre de normals: %u", normals.size());
    //isplayArrayImGui("Normals", m_normals);

}

void MeshLoaderOFF::cleanup(){

}

MeshLoaderOFF::~MeshLoaderOFF() {
    cleanup();
}
