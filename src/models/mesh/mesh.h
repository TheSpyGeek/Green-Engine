
#ifndef MESH_H
#define MESH_H

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
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
#include <array>
#include <cstdio>
#include <iostream>

#include "../../components/component.h"


class Mesh : public Component {

public:

     Mesh();
     virtual ~Mesh();

     virtual void createUI();
     virtual void recreate();

     glm::vec3 getMin();
     glm::vec3 getMax();

     void createVAO();

     void drawVAO();

     void deleteVAO();

     inline void *getFaces(){ return &(m_faces[0]);}
     inline void *getVertices(){ return &(m_vertices[0]);}
     inline void *getNormals(){ return &(m_normals[0]);}
     inline void *getUVs(){ return &(m_coords[0]);}
     inline void *getColors(){ return &(m_colors[0]);}

     inline unsigned int getNBVertices(){ return m_vertices.size();}

     inline unsigned int getNBFaces(){ return getNBVertices()/3; }

     std::vector<unsigned int> get_face(unsigned int i);
     inline glm::vec3 get_vertex(unsigned int i) { return m_vertices[i];}
     inline glm::vec3 get_normal(unsigned int i) { return m_normals[i];}
     inline glm::vec3 get_color(unsigned int i) { return m_colors[i];}
     inline glm::vec2 get_coord(unsigned int i) { return m_coords[i];}

     inline glm::vec3 get_tangent(unsigned int i) { return m_tangents[i];}

     // -- Modificators --
     
     void addTriangle(const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& v3,
                      const glm::vec3& normal, const glm::vec3& color);

     void addQuad    (const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& v3, const glm::vec3& v4,
                      const glm::vec3& normal, const glm::vec3& color);

     void clear();

     static void displayArrayImGui(char node[56], std::vector<glm::vec3> array);

protected:

     float m_maxX, m_maxY, m_maxZ;
     float m_minX, m_minY, m_minZ;

     // data
     std::vector<unsigned int> m_faces;
     std::vector<glm::vec3> m_vertices;
     std::vector<glm::vec3> m_normals;
     std::vector<glm::vec3> m_colors;

     std::vector<glm::vec2> m_coords; // ne sert pas pour l'instant

     std::vector<glm::vec3> m_tangents;
     std::vector<glm::vec3> m_backupVertices;

   
     float          m_radius;
     glm::vec3 m_center;

     void computeAllInfo();
     void computeNormals();
     void computeUVCoord();
     void computeTangents();
     void computeCenter();
     void computeRadius();
     void computeColor();

     void compute_vertex_valences (std::vector<int> & valences, std::vector<std::vector<unsigned int>> one_ring, std::vector<std::vector<unsigned int> > triangles);
     void collect_one_ring (std::vector<std::vector<unsigned int> > & one_ring, std::vector<std::vector<unsigned int> > triangles, unsigned int nbVertices);
     bool alreadyExist(unsigned int num, std::vector<unsigned int> vec);

     void computeSmoothNormals();
     void compute_triangle_normals(std::vector<glm::vec3> & triangle_normals, std::vector<std::vector<unsigned int> > triangles, std::vector<glm::vec3> indexed_vertices);
     glm::vec3 computeNormalOfOneTriangle(std::vector<unsigned int> triangle, std::vector<glm::vec3> indexed_vertices);


     std::vector<std::vector<unsigned int>> m_oneRing;
     // degree de chaque sommet
     std::vector<int> m_valences;

     void computeBoundingBox();
     void inflateBoundingBox();

     GLuint m_vertexArrayID = 0;
     std::array<GLuint, 5> m_buffers;


};



#endif
