#ifndef MESH_H
#define MESH_H

#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h>    // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>    // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>  // Initialize with gladLoadGL()
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif

#ifndef GLM_H
#define GLM_H
#include <glm/gtx/perpendicular.hpp>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#endif

#include <string>
#include <vector>
#include <stdio.h>

#include "../../components/component.h"

#define POSITION_ATTRIB 0
#define VERTEX_NORMAL_ATTRIB 1
#define VERTEX_UV_ATTRIB 2
#define VERTEX_COLOR_ATTRIB 3


class Mesh : public Component {

public:

     virtual ~Mesh() = default;

     void *getVertices(){return &(vertices[0]);}
     void *getFaces(){return &(faces[0]);}
     void *getNormals(){return &(normals[0]);}
     void *getUVs(){return &(coords[0]);}
     void *getColors(){ return &(colors[0]);}


     unsigned int getNBVertices(){return vertices.size();} 
     unsigned int getNBFaces(){return faces.size()/3;}

     void createUI() override;

     glm::vec3 getCenter();

     glm::vec3 getMin();
     glm::vec3 getMax();


      // DEBUG
      void drawDebug(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projectionMat);
      void drawGridForSimplification(glm::vec3 minimum, glm::vec3 maximum, glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projectionMat);


     void simplify();

     virtual void update();

     void createVAO();
     void drawVAO();
     void deleteVAO();

     static void displayArray(char node[128], std::vector<unsigned int> array);
     static void displayArray(char node[128], std::vector<glm::vec3> array);

protected:

     std::vector<unsigned int> get_face(unsigned int i) {
          std::vector<unsigned int> face = std::vector<unsigned int>(3);
          face[0] = faces[i*3]; face[1] = faces[i*3 +1]; face[2] = faces[i*3+2];
          return face;
     }

     glm::vec3 get_vertex(unsigned int i) {return vertices[i];}
     glm::vec3 get_normal(unsigned int i) {return normals[i];}
     glm::vec3 get_tangent(unsigned int i) {return tangents[i];}
     glm::vec2 get_coord(unsigned int i) {return coords[i];}
     glm::vec3 get_color(unsigned int i) {return colors[i];}
     



     unsigned int  nb_vertices;
     unsigned int  nb_faces;

     float maxX, maxY, maxZ;
     float minX, minY, minZ;

     // data
     std::vector<glm::vec3> vertices;
     std::vector<glm::vec3> normals;
     std::vector<glm::vec3> tangents;
     std::vector<glm::vec3> colors;
     std::vector<glm::vec2> coords;
     std::vector<unsigned int> faces;

     std::vector<glm::vec3> backupVertices;
     std::vector<unsigned int> backupFaces;

     // voisinage
     std::vector<std::vector<unsigned int>> oneRing;
     // degree de chaque sommet
     std::vector<int> valences;

     std::vector<glm::vec3> curvature;
     std::vector<float> trianglesQuality;

     // info
     glm::vec3      center;
     float          radius;

     void initialize();

     void computeTangents();
     void computeCenter();
     void computeRadius();
     void computeUVCoord();
     void computeColor();
     void computeBoundingBox();
     void inflateBoundingBox();

     void computeAllInfo();

     /// COMPUTE VALENCE + ONE RING

     int maxValue(std::vector<int> vec);
     void compute_vertex_valences (std::vector<int> & valences, std::vector<std::vector<unsigned int>> one_ring, std::vector<std::vector<unsigned int> > triangles);
     bool alreadyExist(unsigned int num, std::vector<unsigned int> vec);
     void collect_one_ring (std::vector<std::vector<unsigned int> > & one_ring, std::vector<std::vector<unsigned int> > triangles, unsigned int nbVertices);

     ///// COMPUTE NORMALES

     void computeNormals();
     void computeSmoothNormals();
     void computeNormalsWithAngles();
     void compute_triangle_normals(std::vector<glm::vec3> & triangle_normals, std::vector<std::vector<unsigned int> > triangles, std::vector<glm::vec3> indexed_vertices);
     glm::vec3 computeNormalOfOneTriangle(std::vector<unsigned int> triangle, std::vector<glm::vec3> indexed_vertices);


     void computeAllInfoWithoutNormals();
     void drawQuadWithTriangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec3 v4);

     GLuint *buffers;
     GLuint vertexArrayID;

};



#endif