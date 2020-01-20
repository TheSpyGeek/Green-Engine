#ifndef MESHCUBE_H
#define MESHCUBE_H


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

#include "mesh.h"

class MeshCube : public Mesh {

public:

    MeshCube(float w = 1.0f, bool center = true);
    
	void recreate();
	void createUI();
    
    float getVoxelSize(){return m_width;}

    virtual void createVAO() override;
    virtual void drawVAO() override;
    virtual void deleteVAO() override;

private:

	void createMesh(float w);
    void createPositions(float w);

    void createNormals();
    void createm_tangents();
    void createUVs();
    void createColors();

    float m_width;
    bool m_centered;

    

    std::array<GLuint, 4> m_buffersCube;

};


#endif