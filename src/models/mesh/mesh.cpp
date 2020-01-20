#include <imgui.h>

#include "mesh.h"

#include "../../material/shader.h"

#include <math.h>

#include <iostream>
#include <unordered_map>

#ifndef M_PI
#define M_PI 3.1415926
#endif

void Mesh::initialize(){
    maxX = 0; maxY = 0; maxZ = 0;
    minX = 0; minY = 0; minZ = 0;
}


// calcul le 1-voisinage des sommets
void Mesh::collect_one_ring (std::vector<std::vector<unsigned int> > & one_ring, std::vector<std::vector<unsigned int> > triangles, unsigned int nbVertices) {
    one_ring = std::vector<std::vector<unsigned int>>(triangles.size()*3);

    for(unsigned int i=0; i<triangles.size(); i++){ // pour chaque triangle

        for(unsigned int j=0; j<triangles[i].size(); j++){ // pour chaque sommet dans le triangle

            unsigned int currentV = triangles[i][j];
            one_ring[currentV].push_back(i);
        }
    }

}

bool Mesh::alreadyExist(unsigned int num, std::vector<unsigned int> vec){
    for(unsigned int i=0; i<vec.size(); i++){
        if(vec[i] == num){
            return true;
        }
    }
    return false;
}

void Mesh::update(){
}

void Mesh::compute_vertex_valences (std::vector<int> & valences, std::vector<std::vector<unsigned int>> one_ring, std::vector<std::vector<unsigned int> > triangles) {
    valences = std::vector<int>(one_ring.size());

    std::vector<unsigned int> vecVertex;

    for(unsigned int i=0; i<one_ring.size(); i++){ // pour chaque sommet

        unsigned int current = i;

        vecVertex = std::vector<unsigned int>();
        valences[i] = 0;

        for(unsigned int j=0; j<one_ring[i].size(); j++){ // pour chaque triangle adjacent
            for(unsigned int k=0; k<triangles[one_ring[i][j]].size(); k++){
                unsigned int vert = triangles[one_ring[i][j]][k];
                if(vert != current && !alreadyExist(vert, vecVertex)){
                    vecVertex.push_back(vert);
                    valences[i]++;
                }
            }
        }
    }

}

int Mesh::maxValue(std::vector<int> vec){
    int max = 0;

    for(unsigned int i=0; i<vec.size(); i++){
        if(max < vec[i]){
            max = vec[i];
        }
    }
    return max;
}




void Mesh::computeAllInfo(){
    // pas opti !!!!
    std::vector<std::vector<unsigned int>> triangles;
    triangles.resize(faces.size()/3);
    for(unsigned int i=0; i<triangles.size(); i++){
        triangles[i].resize(3);
        for(unsigned int j=0; j<3; j++){
            triangles[i][j] = faces[3*i +j];
        }
    }

    collect_one_ring (oneRing, triangles, nb_vertices);
    compute_vertex_valences(valences, oneRing, triangles);

    computeCenter();
    computeRadius();

    computeBoundingBox();
    inflateBoundingBox();

    computeSmoothNormals();

    // computing colors as normals
    colors.resize(nb_vertices);
    for(unsigned int i=0;i<nb_vertices;i++) {
        colors[i] = (normals[i]+1.0f)/2.0f;
    }

    computeUVCoord();
    computeTangents();
}

void Mesh::computeAllInfoWithoutNormals(){

        // pas opti !!!!
        std::vector<std::vector<unsigned int>> triangles;
        triangles.resize(faces.size()/3);
        for(unsigned int i=0; i<triangles.size(); i++){
            triangles[i].resize(3);
            for(unsigned int j=0; j<3; j++){
                triangles[i][j] = faces[3*i +j];
            }
        }

        collect_one_ring (oneRing, triangles, nb_vertices);
        compute_vertex_valences(valences, oneRing, triangles);

        computeCenter();
        computeRadius();

        computeBoundingBox();
        inflateBoundingBox();

        // computing colors as normals
        colors.resize(nb_vertices);
        for(unsigned int i=0;i<nb_vertices;i++) {
            colors[i] = (normals[i]+1.0f)/2.0f;
        }

        computeUVCoord();
        computeTangents();
}

void Mesh::displayArray(char node[128], std::vector<glm::vec3> array){
    if (ImGui::TreeNode(node)){

        ImGui::Columns(3, node); // 4-ways, with border
        ImGui::Separator();
        ImGui::Text("X"); ImGui::NextColumn();
        ImGui::Text("Y"); ImGui::NextColumn();
        ImGui::Text("Z"); ImGui::NextColumn();
        ImGui::Separator();
        for(unsigned int i=0; i<array.size(); i++){
            ImGui::Text("%4f",array[i].x); ImGui::NextColumn();
            ImGui::Text("%4f",array[i].y); ImGui::NextColumn();
            ImGui::Text("%4f", array[i].z); ImGui::NextColumn();
        }
        ImGui::Columns(1);
        ImGui::Separator();
        ImGui::TreePop();

    }
}

void Mesh::displayArray(char node[128], std::vector<unsigned int> array){
    if (ImGui::TreeNode(node)){

        ImGui::Columns(3, node); // 4-ways, with border
        ImGui::Separator();
        ImGui::Text("v1"); ImGui::NextColumn();
        ImGui::Text("v2"); ImGui::NextColumn();
        ImGui::Text("v3"); ImGui::NextColumn();
        ImGui::Separator();
        for(unsigned int i=0; i<array.size(); i+=3){
            ImGui::Text("%u",array[3*i]); ImGui::NextColumn();
            ImGui::Text("%u",array[3*i+1]); ImGui::NextColumn();
            ImGui::Text("%u", array[3*i+2]); ImGui::NextColumn();
        }

        ImGui::Columns(1);
        ImGui::Separator();
        ImGui::TreePop();
    }
}


void Mesh::createUI(){
    ImGui::Text("Number vertices: %d", getNBVertices());
    ImGui::Text("Number faces: %d", getNBFaces());

    ImGui::Separator();
    displayArray("Vertices", vertices);

    displayArray("Faces", faces);

    ImGui::Text("Bounding Box");
    ImGui::Text("min: %f, %f, %f", minX, minY, minZ);
    ImGui::Text("max: %f, %f, %f", maxX, maxY, maxZ);


    ImGui::Text("center: %f, %f, %f", center.x, center.y,center.z);
    ImGui::Text("radius: %f", radius);

}


glm::vec3 Mesh::getCenter(){
    return center;
}


///////////////////// COMPUTE NORMAL !!!! /////////////////////

void Mesh::computeNormals(){
    computeSmoothNormals();
}


void Mesh::computeSmoothNormals(){
    std::vector<std::vector<unsigned int>> one_ring;
    std::vector<glm::vec3> triangle_normals;
    std::vector<int> valences;

    std::vector<std::vector<unsigned int>> triangles;
    triangles.resize(getNBFaces());
    for(unsigned int i=0; i<triangles.size(); i++){
        triangles[i] = get_face(i);
    }

    compute_triangle_normals(triangle_normals, triangles, vertices);
    collect_one_ring(one_ring,triangles, vertices.size());
    compute_vertex_valences (valences, one_ring, triangles);

    normals.resize(vertices.size());

    unsigned int i0, i1, i2;
    glm::vec3 p0,p1,p2;

    for(unsigned int i=0; i<normals.size(); i++){ // pour chaque sommet
        glm::vec3 n = glm::vec3(0.);
        float sumalpha = 0;
        for(unsigned int j=0; j<one_ring[i].size(); j++){ // pour chaque triangle dans le voisinage

            // calcul angle
            i0 = triangles[one_ring[i][j]][0]; i1 = triangles[one_ring[i][j]][1]; i2 = triangles[one_ring[i][j]][2];
            p0 = vertices[i0]; p1 = vertices[i1]; p2 = vertices[i2];

            if(i == i1){
                p1 = vertices[i0];
                p0 = vertices[i1];
            } else if(i == i2) {
                p2 = vertices[i0];
                p0 = vertices[i2];
            }

            float alpha = glm::acos(glm::dot(p1-p0, p2-p0)/(glm::length(p1-p0)*glm::length(p2-p0)));

            n += alpha*triangle_normals[one_ring[i][j]];
            sumalpha += alpha;
        }


        n /= sumalpha;
        n /= one_ring[i].size();
        normals[i] = glm::normalize(n);

    }


}

// a partir d'un triangle calcul la normales du triangle puis la renvoie sous forme de vec3
glm::vec3 Mesh::computeNormalOfOneTriangle(std::vector<unsigned int> triangle, std::vector<glm::vec3> indexed_vertices){

    unsigned int i0,i1,i2;
    glm::vec3 p0, p1, p2;

    i0 = triangle[0]; i1 = triangle[1]; i2=triangle[2];

    p0 = indexed_vertices[i0]; p1 = indexed_vertices[i1]; p2 = indexed_vertices[i2];

    glm::vec3 normal = glm::cross(p1-p0, p2-p0)/glm::length(glm::cross(p1-p0, p2-p0));

    return normal;
}

void Mesh::compute_triangle_normals (std::vector<glm::vec3> & triangle_normals, std::vector<std::vector<unsigned int> > triangles, std::vector<glm::vec3> indexed_vertices){

    triangle_normals = std::vector<glm::vec3>(triangles.size());

    for(unsigned int i=0; i<triangles.size(); i++){
        glm::vec3 n = computeNormalOfOneTriangle(triangles[i], indexed_vertices);
        triangle_normals[i] = n;
    }

}







////////////////// COMPUTE TEXTURE COORDINATE ///////////////

void Mesh::computeUVCoord(){
    // computing spherical uv coordinates

    coords.resize(nb_vertices);

    glm::vec3 v1;
    glm::vec3 c;
    float r;

    for(unsigned int i=0;i<nb_vertices;i++) {
        v1 = get_vertex(i);

        // direction between center and current point
        c = v1-center;

        // normalization
        c = glm::normalize(c);

        glm::vec2 coord;
        // elevation & azimuth remapped between 0 and 1
        r = c.z/sqrt(c.x*c.x+c.z*c.z);
        if(r>=1.0f) r = 1.0f;
        if(r<=-1.0f) r = -1.0f;
        coord.x = asin(r);
        if(c.x<0.0) coord.x = M_PI-coord.x;
        coord.x = (coord.x+(M_PI/2.0))/(2.0*M_PI);
        coord.y = acos(c.y)/M_PI;
        coords[i] = coord;
    }
}


////////////////// COMPUTE TANGENTS  ///////////////////////


void Mesh::computeTangents(){

    // TODO

    tangents.resize(nb_vertices);

    for(unsigned int i=0; i<nb_vertices; i++){
        tangents[i] = glm::vec3(0);
    }

}

////////////////// COMPUTE CENTER  ///////////////////////

void Mesh::computeCenter(){
    // computing center
    glm::vec3 c = glm::vec3(0);
    for(unsigned int i=0;i<vertices.size();i++) {
        c = vertices[i];
    }
    center = c/(float)nb_vertices;

}

////////////////// COMPUTE RADIUS  ///////////////////////

void Mesh::computeRadius(){

    radius = 0.0;
    glm::vec3 c;
    float r;
    for(unsigned int i=0;i<nb_vertices;i++) {
      c = vertices[i]-center;

      r = sqrt(c.x*c.x+c.y*c.y+c.z*c.z);
      radius = r>radius ? r : radius;
    }

}

void Mesh::computeColor(){
    colors.resize(nb_vertices);

    for(unsigned int i=0; i<nb_vertices; i++){
        colors[i] = glm::vec3(1,0,0);
    }
}


////// COMPUTE BOUNDING BOX /////

void Mesh::computeBoundingBox(){
    assert(vertices.size() > 0);

    maxX = vertices[0].x; maxY = vertices[0].y; maxZ = vertices[0].z;
    minX = vertices[0].x; minY = vertices[0].y; minZ = vertices[0].z;

    for(unsigned int i=0; i<vertices.size(); i++){
        if(vertices[i].x > maxX){
            maxX = vertices[i].x;
        } else if(vertices[i].x < minX){
            minX = vertices[i].x;
        }
        if(vertices[i].y > maxY){
            maxY = vertices[i].y;
        } else if(vertices[i].y < minY){
            minY = vertices[i].y;
        }
        if(vertices[i].z > maxZ){
            maxZ = vertices[i].z;
        } else if(vertices[i].z < minZ){
            minZ = vertices[i].z;
        }
    }



}

void Mesh::inflateBoundingBox(){
    const float percent = 0.1f;
    maxX += percent*radius; maxY += percent*radius; maxZ += percent*radius;
    minX -= percent*radius; minY -= percent*radius; minZ -= percent*radius;
}


glm::vec3 Mesh::getMin(){
    return glm::vec3(minX, minY, minZ);
}


glm::vec3 Mesh::getMax(){
    return glm::vec3(maxX, maxY, maxZ);
}



void Mesh::drawQuadWithTriangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec3 v4){
    glVertex3f(v1.x, v1.y, v1.z);
    glVertex3f(v2.x, v2.y, v2.z);
    glVertex3f(v4.x, v4.y, v4.z);

    glVertex3f(v2.x, v2.y, v2.z);
    glVertex3f(v3.x, v3.y, v3.z);
    glVertex3f(v4.x, v4.y, v4.z);
}


void Mesh::drawGridForSimplification(glm::vec3 minimum, glm::vec3 maximum, glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projectionMat){
    Shader *shader = new Shader();
    shader->load("../data/shaders/displayBoundingBox.vert","../data/shaders/displayBoundingBox.frag");

    glUseProgram(shader->id());


    glUniformMatrix4fv(glGetUniformLocation(shader->id(),"modelMat"),1,GL_FALSE,&(modelMat[0][0]));
    glUniformMatrix4fv(glGetUniformLocation(shader->id(),"viewMat"),1,GL_FALSE,&(viewMat[0][0]));
    glUniformMatrix4fv(glGetUniformLocation(shader->id(),"projMat"),1,GL_FALSE,&(projectionMat[0][0]));

    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

    glBegin(GL_TRIANGLES);

    // front face
    drawQuadWithTriangle(glm::vec3(minimum.x,maximum.y,maximum.z), glm::vec3(maximum.x,maximum.y,maximum.z), glm::vec3(maximum.x,minimum.y,maximum.z), glm::vec3(minimum.x,minimum.y,maximum.z));
    // back face
    drawQuadWithTriangle(glm::vec3(maximum.x,maximum.y,minimum.z), glm::vec3(minimum.x,maximum.y,minimum.z), glm::vec3(minimum.x,minimum.y,minimum.z), glm::vec3(maximum.x,minimum.y,minimum.z));
    // left face
    drawQuadWithTriangle(glm::vec3(minimum.x,maximum.y,minimum.z), glm::vec3(minimum.x,minimum.y,maximum.z), glm::vec3(minimum.x,minimum.y,maximum.z), glm::vec3(minimum.x,minimum.y,minimum.z));
    // right face
    drawQuadWithTriangle(glm::vec3(maximum.x,maximum.y,maximum.z), glm::vec3(maximum.x,maximum.y,minimum.z), glm::vec3(maximum.x,minimum.y,minimum.z), glm::vec3(maximum.x,minimum.y,maximum.z));
    // bottom face
    drawQuadWithTriangle(glm::vec3(minimum.x,minimum.y,maximum.z), glm::vec3(maximum.x,minimum.y,maximum.z), glm::vec3(maximum.x,minimum.y,minimum.z), glm::vec3(minimum.x,minimum.y,minimum.z));
    // top face
    drawQuadWithTriangle(glm::vec3(minimum.x,maximum.y,minimum.z), glm::vec3(maximum.x,maximum.y,minimum.z), glm::vec3(maximum.x,maximum.y,maximum.z), glm::vec3(minimum.x,maximum.y,maximum.z));

    glEnd();

    glUseProgram(0);

    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
}


// calcul le numero de la cellule en fonction de la resolution
int cellToIndex(int resolution, int i, int j, int k){
    return i + j*resolution + k*resolution*resolution;
}

std::vector<int> indexToCell(int resolution, int index){
    std::vector<int> v;
    v.resize(3);


}



void Mesh::createVAO(){

    buffers = new GLuint[5];

    glGenBuffers(5, buffers);
    glGenVertexArrays(1,&vertexArrayID);

    // create the VBO associated with the grid (the terrain)
    glBindVertexArray(vertexArrayID);

    glBindBuffer(GL_ARRAY_BUFFER,buffers[0]); // vertices
    glBufferData(GL_ARRAY_BUFFER,getNBVertices()*3*sizeof(float),getVertices(),GL_STATIC_DRAW);
    glEnableVertexAttribArray(POSITION_ATTRIB);
    glVertexAttribPointer(POSITION_ATTRIB,3,GL_FLOAT,GL_FALSE,0,(void *)0);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,buffers[1]); // indices
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,getNBFaces()*3*sizeof(unsigned int),getFaces(),GL_STATIC_DRAW);

    /* normals */
    glEnableVertexAttribArray(VERTEX_NORMAL_ATTRIB);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[2]);
    glBufferData(GL_ARRAY_BUFFER, getNBVertices()*3* sizeof(float), getNormals(), GL_STATIC_DRAW); //normals is std::vector<float>
    glVertexAttribPointer(VERTEX_NORMAL_ATTRIB, 3, GL_FLOAT, GL_FALSE, 0, 0);

    /* texture coordinates */
    glEnableVertexAttribArray(VERTEX_UV_ATTRIB);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[3]);
    glBufferData(GL_ARRAY_BUFFER, getNBVertices()*2* sizeof(float), getUVs(), GL_STATIC_DRAW); //normals is std::vector<float>
    glVertexAttribPointer(VERTEX_UV_ATTRIB, 2, GL_FLOAT, GL_FALSE, 0, 0);

    /* colors */
    glEnableVertexAttribArray(VERTEX_UV_ATTRIB);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[4]);
    glBufferData(GL_ARRAY_BUFFER, getNBVertices()*3* sizeof(float), getColors(), GL_STATIC_DRAW); //normals is std::vector<float>
    glVertexAttribPointer(VERTEX_COLOR_ATTRIB, 3, GL_FLOAT, GL_FALSE, 0, 0);
    //indices
    glBindVertexArray(0);
}

void Mesh::deleteVAO(){
    glDeleteBuffers(5,buffers);
    glDeleteVertexArrays(1,&vertexArrayID);
    delete buffers;
}

void Mesh::drawVAO(){
    glBindVertexArray(vertexArrayID);
    glDrawElements(GL_TRIANGLES,3*getNBFaces(),GL_UNSIGNED_INT,(void *)0);
    glBindVertexArray(0);
}