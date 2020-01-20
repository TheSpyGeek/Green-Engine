#include <imgui.h>


#include <math.h>


#define POSITION_ATTRIB 0
#define VERTEX_NORMAL_ATTRIB 1
#define VERTEX_UV_ATTRIB 2
#define VERTEX_COLOR_ATTRIB 3

#include "mesh.h"

#include "../../material/shader.h"

#include <math.h>

#include <iostream>
#include <unordered_map>

#ifndef M_PI
#define M_PI 3.1415926
#endif

Mesh::Mesh() {
    setName("Mesh");
}

Mesh::~Mesh() 
{
    deleteVAO();
}

void Mesh::displayArrayImGui(char node[56], std::vector<glm::vec3> array){
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
            ImGui::Text("%4f",array[i].z); ImGui::NextColumn();
        }

        ImGui::Columns(1);
        ImGui::Separator();
        ImGui::TreePop();

    }
}

void Mesh::createUI(){
    if (ImGui::TreeNode("Mesh")){
        ImGui::Text("Number vertices: %d", getNBVertices());
        ImGui::Text("Number faces: %d", getNBFaces());

        ImGui::Separator();
        displayArrayImGui("Vertices", m_vertices);
        

        ImGui::Text("Bounding Box");
        ImGui::Text("min: %f, %f, %f", m_minX, m_minY, m_minZ);
        ImGui::Text("max: %f, %f, %f", m_maxX, m_maxY, m_maxZ);


        ImGui::Text("radius: %f", m_radius);
        ImGui::TreePop();
    }

}

////// COMPUTE BOUNDING BOX /////

void Mesh::computeBoundingBox(){
    assert(m_vertices.size() > 0);

    m_maxX = m_vertices[0].x; m_maxY = m_vertices[0].y; m_maxZ = m_vertices[0].z;
    m_minX = m_vertices[0].x; m_minY = m_vertices[0].y; m_minZ = m_vertices[0].z;

    for(unsigned int i=0; i<m_vertices.size(); i++){
        if(m_vertices[i].x > m_maxX){
            m_maxX = m_vertices[i].x;
        } else if(m_vertices[i].x < m_minX){
            m_minX = m_vertices[i].x;
        }
        if(m_vertices[i].y > m_maxY){
            m_maxY = m_vertices[i].y;
        } else if(m_vertices[i].y < m_minY){
            m_minY = m_vertices[i].y;
        }
        if(m_vertices[i].z > m_maxZ){
            m_maxZ = m_vertices[i].z;
        } else if(m_vertices[i].z < m_minZ){
            m_minZ = m_vertices[i].z;
        }
    }
}

void Mesh::recreate(){
    createVAO();
}

void Mesh::inflateBoundingBox(){
    const float percent = 0.1f;
    m_maxX += percent*m_radius; m_maxY += percent*m_radius; m_maxZ += percent*m_radius;
    m_minX -= percent*m_radius; m_minY -= percent*m_radius; m_minZ -= percent*m_radius;
}


glm::vec3 Mesh::getMin(){
    return glm::vec3(m_minX, m_minY, m_minZ);
}


glm::vec3 Mesh::getMax(){
    return glm::vec3(m_maxX, m_maxY, m_maxZ);
}


void Mesh::createVAO(){

    glGenBuffers(m_buffers.size(), m_buffers.data());
    glGenVertexArrays(1,&m_vertexArrayID);

    // create the VBO associated with the grid (the terrain)
    glBindVertexArray(m_vertexArrayID);

    glBindBuffer(GL_ARRAY_BUFFER,m_buffers[0]); // vertices
    glBufferData(GL_ARRAY_BUFFER,getNBVertices()*3*sizeof(float),getVertices(),GL_STATIC_DRAW);
    glEnableVertexAttribArray(POSITION_ATTRIB);
    glVertexAttribPointer(POSITION_ATTRIB,3,GL_FLOAT,GL_FALSE,0,(void *)0);



    // m_normals
    glEnableVertexAttribArray(VERTEX_NORMAL_ATTRIB);
    glBindBuffer(GL_ARRAY_BUFFER, m_buffers[1]);
    glBufferData(GL_ARRAY_BUFFER, getNBVertices()*3* sizeof(float), getNormals(), GL_STATIC_DRAW); //m_normals is std::vector<float>
    glVertexAttribPointer(VERTEX_NORMAL_ATTRIB, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // texture coordinates
    glEnableVertexAttribArray(VERTEX_UV_ATTRIB);
    glBindBuffer(GL_ARRAY_BUFFER, m_buffers[2]);
    glBufferData(GL_ARRAY_BUFFER, getNBVertices()*2* sizeof(float), getUVs(), GL_STATIC_DRAW); //m_normals is std::vector<float>
    glVertexAttribPointer(VERTEX_UV_ATTRIB, 2, GL_FLOAT, GL_FALSE, 0, 0);

    // m_colors
    glEnableVertexAttribArray(VERTEX_COLOR_ATTRIB);
    glBindBuffer(GL_ARRAY_BUFFER, m_buffers[3]);
    glBufferData(GL_ARRAY_BUFFER, getNBVertices()*3* sizeof(float), getColors(), GL_STATIC_DRAW); //m_normals is std::vector<float>
    glVertexAttribPointer(VERTEX_COLOR_ATTRIB, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_buffers[4]); // indices
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,getNBFaces()*3*sizeof(unsigned int),getFaces(),GL_STATIC_DRAW);

    glBindVertexArray(0);
}


void Mesh::drawVAO(){

    glBindVertexArray(m_vertexArrayID);
    // glDrawArrays(GL_TRIANGLES,0,getNBVertices());
    glDrawElements(GL_TRIANGLES,3*getNBFaces(),GL_UNSIGNED_INT,(void *)0);
    glBindVertexArray(0);

}

void Mesh::deleteVAO(){
    if (m_vertexArrayID != 0){
        glDeleteBuffers(m_buffers.size(), m_buffers.data());
        glDeleteVertexArrays(1,&m_vertexArrayID);
    }
}


// -- Add Method --

void Mesh::addTriangle(const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& v3,
                 const glm::vec3& normal, const glm::vec3& color) {

    m_vertices.push_back(v1);
    m_vertices.push_back(v2);
    m_vertices.push_back(v3);

    m_normals.push_back(normal);
    m_normals.push_back(normal);
    m_normals.push_back(normal);

    m_colors.push_back(color);
    m_colors.push_back(color);
    m_colors.push_back(color);

    // Coord bidon pour ne pas faire bugger l'affichage

    m_coords.push_back(glm::vec3(0, 0, 0));
    m_coords.push_back(glm::vec3(0, 0, 0));
    m_coords.push_back(glm::vec3(0, 0, 0));
}

void Mesh::addQuad    (const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& v3, const glm::vec3& v4,
                 const glm::vec3& normal, const glm::vec3& color) {

    this->addTriangle(v1, v2, v3, normal, color);
    this->addTriangle(v2, v4, v3, normal, color);
}

void Mesh::clear() {

     m_vertices.clear();
     m_normals.clear();
     m_colors.clear();
     
     m_coords.clear();

     m_tangents.clear();
     m_backupVertices.clear();
}


void Mesh::computeAllInfo(){

    // pas opti !!!!
    std::vector<std::vector<unsigned int>> triangles;
    triangles.resize(m_faces.size()/3);
    for(unsigned int i=0; i<triangles.size(); i++){
        triangles[i].resize(3);
        for(unsigned int j=0; j<3; j++){
            triangles[i][j] = m_faces[3*i +j];
        }
    }

    collect_one_ring (m_oneRing, triangles, getNBVertices());
    compute_vertex_valences(m_valences, m_oneRing, triangles);

    computeCenter();
    computeRadius();

    computeBoundingBox();
    inflateBoundingBox();


    // vertices = smoothing(vertices, triangles,oneRing, nbSmoothingIteration, type_smoothing, curvature,trianglesQuality);

    // computeNormals();
    m_normals.resize(getNBVertices());
    computeSmoothNormals();
    printf("Nb normals : %u\n", m_normals.size());
    /*for(unsigned int i=0; i<m_normals.size(); i++){
        m_normals[i] = glm::vec3(1);
    }*/

    // computing colors as normals
    m_colors.resize(getNBVertices());
    for(unsigned int i=0;i<getNBVertices();i++) {
        m_colors[i] = (m_normals[i]+1.0f)/2.0f;
    }

    computeUVCoord();


    computeTangents();

}






////////////////// COMPUTE TEXTURE COORDINATE ///////////////

void Mesh::computeUVCoord(){
    // computing spherical uv coordinates

    m_coords.resize(getNBVertices());

    glm::vec3 v1;
    glm::vec3 c;
    float r;


    for(unsigned int i=0;i<getNBVertices();i++) {
      v1 = get_vertex(i);

      // direction between center and current point
      c = v1-m_center;

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
      m_coords[i] = coord;
    }
}


void Mesh::computeTangents(){

    // TODO

    m_tangents.resize(getNBVertices());

    for(unsigned int i=0; i<getNBVertices(); i++){
        m_tangents[i] = glm::vec3(0);
    }

}

void Mesh::computeCenter(){
    // computing center
    glm::vec3 c = glm::vec3(0);
    for(unsigned int i=0;i<getNBVertices();i++) {
        c = m_vertices[i];
    }
    m_center = c/(float)getNBVertices();

}

void Mesh::computeRadius(){

    m_radius = 0.0;
    glm::vec3 c;
    float r;
    for(unsigned int i=0;i<getNBVertices();i++) {
      c = m_vertices[i]-m_center;

      r = sqrt(c.x*c.x+c.y*c.y+c.z*c.z);
      m_radius = r>m_radius ? r : m_radius;
    }

}

void Mesh::computeColor(){
    m_colors.resize(getNBVertices());

    for(unsigned int i=0; i<getNBVertices(); i++){
        m_colors[i] = glm::vec3(1,0,0);
    }
}

std::vector<unsigned int> Mesh::get_face(unsigned int i) {
    std::vector<unsigned int> face = std::vector<unsigned int>(3);
    face[0] = m_faces[i*3]; face[1] = m_faces[i*3 +1]; face[2] = m_faces[i*3+2];
    return face;
}

void Mesh::computeNormals(){
    std::vector<glm::vec3> nf;

    glm::vec3 normal;

    glm::vec3 v1, v2, v3;
    glm::vec3 v12;
    glm::vec3 v13;
    std::vector<unsigned int> f;
    float norm;
    glm::vec3 nv;

    // computing normals per faces
    nf.resize(getNBFaces()*3);
    for(unsigned int i=0;i<getNBFaces();++i) {
        f = get_face(i);

        // the three vertices of the current face
        v1 = get_vertex(f[0]);
        v2 = get_vertex(f[1]);
        v3 = get_vertex(f[2]);

        // the two vectors of the current face
        v12 = v2-v1;
        v13 = v3-v1;

        // cross product
        normal = glm::cross(v12,v13);

        // normalization
        normal = glm::normalize(normal);
        nf[i] = normal;
    }

    // computing normals per vertex
    /*for(unsigned int i=0;i<normalV.size();++i) {
        // initialization
        normals[3*i  ] = 0.0;
        normals[3*i+1] = 0.0;
        normals[3*i+2] = 0.0;
        nv[i] = 0.0;
    }*/
    std::vector<float> normalV;
    normalV.resize(getNBVertices());
    m_normals.resize(getNBVertices());
    for(unsigned int i=0;i<getNBVertices();++i) {
        // face normals average
        f = get_face(i);
        //n = &(nf[3*i]);

        m_normals[f[0]] += nf[i]; normalV[f[0]] ++;
        m_normals[f[1]] += nf[i]; normalV[f[1]] ++;
        m_normals[f[2]] += nf[i]; normalV[f[2]] ++;

/*        normals[3*f[0]  ] += nf[3*i  ];
        normals[3*f[0]+1] += nf[3*i+1];
        normals[3*f[0]+2] += nf[3*i+2];
        nv[f[0]] ++;

        normals[3*f[1]  ] += nf[3*i  ];
        normals[3*f[1]+1] += nf[3*i+1];
        normals[3*f[1]+2] += nf[3*i+2];
        nv[f[1]] ++;

        normals[3*f[2]  ] += nf[3*i  ];
        normals[3*f[2]+1] += nf[3*i+1];
        normals[3*f[2]+2] += nf[3*i+2];
        nv[f[2]] ++;*/
    }

    for(unsigned int i=0;i<getNBVertices();++i) {
        // normalization
        m_normals[i] /= (float)normalV[i];
    }


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


// calcul le 1-voisinage des sommets
void Mesh::collect_one_ring (std::vector<std::vector<unsigned int> > & one_ring, std::vector<std::vector<unsigned int> > triangles, unsigned int nbVertices) {
    one_ring = std::vector<std::vector<unsigned int>>(nbVertices);

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




void Mesh::computeSmoothNormals(){
    std::vector<std::vector<unsigned int>> one_ring;
    std::vector<glm::vec3> triangle_normals;
    std::vector<int> valences;

    std::vector<std::vector<unsigned int>> triangles;
    triangles.resize(getNBFaces());
    for(unsigned int i=0; i<triangles.size(); i++){
        triangles[i] = get_face(i);
    }

    compute_triangle_normals(triangle_normals, triangles, m_vertices);
    collect_one_ring(one_ring,triangles, m_vertices.size());
    compute_vertex_valences (valences, one_ring, triangles);

    m_normals.resize(getNBVertices());

    unsigned int i0, i1, i2;
    glm::vec3 p0,p1,p2;

    for(unsigned int i=0; i<m_normals.size(); i++){ // pour chaque sommet
        glm::vec3 n = glm::vec3(0.);
        float sumalpha = 0;
        for(unsigned int j=0; j<one_ring[i].size(); j++){ // pour chaque triangle dans le voisinage

            // calcul angle
            i0 = triangles[one_ring[i][j]][0]; i1 = triangles[one_ring[i][j]][1]; i2 = triangles[one_ring[i][j]][2];
            p0 = m_vertices[i0]; p1 = m_vertices[i1]; p2 = m_vertices[i2];

            if(i == i1){
                p1 = m_vertices[i0];
                p0 = m_vertices[i1];
            } else if(i == i2) {
                p2 = m_vertices[i0];
                p0 = m_vertices[i2];
            }

            float alpha = glm::acos(glm::dot(p1-p0, p2-p0)/(glm::length(p1-p0)*glm::length(p2-p0)));

            n += alpha*triangle_normals[one_ring[i][j]];
            sumalpha += alpha;
        }


        n /= sumalpha;
        if(one_ring[i].size() == 0){
            m_normals[i] = glm::vec3(1.0);
        } else {
            n /= one_ring[i].size();
            m_normals[i] = glm::normalize(n);
        }
            

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