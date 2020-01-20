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
#include <array>

#include "../../components/component.h"

#define VERTEX_POSITION_ATTRIB 0
#define VERTEX_NORMAL_ATTRIB 1
#define VERTEX_UV_ATTRIB 2
#define VERTEX_COLOR_ATTRIB 3


class Mesh : public Component {

public:

     virtual ~Mesh() = default;

     void *getVertices(){return &(m_vertices[0]);}
     void *getFaces(){return &(m_faces[0]);}
     void *getNormals(){return &(m_normals[0]);}
     void *getUVs(){return &(m_coords[0]);}
     void *getColors(){ return &(m_colors[0]);}


     unsigned int getNBVertices(){return m_vertices.size();} 
     unsigned int getNBFaces(){return m_faces.size()/3;}

     void createUI() override;

     glm::vec3 getCenter(){return m_center;}


     glm::vec3 getMin(){return m_min;}
     glm::vec3 getMax(){return m_max;}


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
          face[0] = m_faces[i*3]; face[1] = m_faces[i*3 +1]; face[2] = m_faces[i*3+2];
          return face;
     }

     glm::vec3 get_vertex(unsigned int i) {return m_vertices[i];}
     glm::vec3 get_normal(unsigned int i) {return m_normals[i];}
     glm::vec3 get_tangent(unsigned int i) {return m_tangents[i];}
     glm::vec2 get_coord(unsigned int i) {return m_coords[i];}
     glm::vec3 get_color(unsigned int i) {return m_colors[i];}
     

     glm::vec3 m_max, m_min;

     // data
     std::vector<glm::vec3> m_vertices;
     std::vector<glm::vec3> m_normals;
     std::vector<glm::vec3> m_tangents;
     std::vector<glm::vec3> m_colors;
     std::vector<glm::vec2> m_coords;
     std::vector<unsigned int> m_faces;


     // voisinage
     std::vector<std::vector<unsigned int>> m_oneRing;
     // degree de chaque sommet
     std::vector<int> m_valences;

     //std::vector<glm::vec3> curvature;
     //std::vector<float> trianglesQuality;

     // info
     glm::vec3      m_center;
     float          m_radius;

     void initialize();

     void computeTangents();
     void computeCenter();
     void computeRadius();
     void computeUVCoord();
     void computeColor();
     void computeBoundingBox();
     void inflateBoundingBox();

     void computeAllInfo();

     void cleanup();

     /// COMPUTE VALENCE + ONE RING

     int maxValue(std::vector<int> vec);
     void compute_vertex_valences (std::vector<int> & valences, std::vector<std::vector<unsigned int>> one_ring, std::vector<std::vector<unsigned int> > triangles);
     bool alreadyExist(unsigned int num, std::vector<unsigned int> vec);
     void collect_one_ring (std::vector<std::vector<unsigned int> > & one_ring, std::vector<std::vector<unsigned int> > triangles, unsigned int nbVertices);

     ///// COMPUTE NORMALS

     void computeNormals();
     void computeSmoothNormals();
     void computeNormalsWithAngles();
     void compute_triangle_normals(std::vector<glm::vec3> & triangle_normals, std::vector<std::vector<unsigned int> > triangles, std::vector<glm::vec3> indexed_vertices);
     glm::vec3 computeNormalOfOneTriangle(std::vector<unsigned int> triangle, std::vector<glm::vec3> indexed_vertices);


     void computeAllInfoWithoutNormals();
     void drawQuadWithTriangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec3 v4);

     std::array<GLuint, 5> m_buffers;
     GLuint m_vertexArrayID = 0;

};



#endif