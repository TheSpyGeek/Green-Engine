#include "meshNonIndexed.h"


void MeshNonIndexed::createVAO() {
    glGenBuffers(m_buffersNonIndexed.size(), m_buffersNonIndexed.data());
    glGenVertexArrays(1,&m_vertexArrayID);

    // create the VBO associated with the grid (the terrain)
    glBindVertexArray(m_vertexArrayID);

    glBindBuffer(GL_ARRAY_BUFFER,m_buffersNonIndexed[0]); // vertices
    glBufferData(GL_ARRAY_BUFFER,getNBVertices()*3*sizeof(float),getVertices(),GL_STATIC_DRAW);
    glEnableVertexAttribArray(VERTEX_POSITION_ATTRIB);
    glVertexAttribPointer(VERTEX_POSITION_ATTRIB,3,GL_FLOAT,GL_FALSE,0,(void *)0);

    // m_normals
    glEnableVertexAttribArray(VERTEX_NORMAL_ATTRIB);
    glBindBuffer(GL_ARRAY_BUFFER, m_buffersNonIndexed[1]);
    glBufferData(GL_ARRAY_BUFFER, getNBVertices()*3* sizeof(float), getNormals(), GL_STATIC_DRAW); //m_normals is std::vector<float>
    glVertexAttribPointer(VERTEX_NORMAL_ATTRIB, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // texture coordinates
    glEnableVertexAttribArray(VERTEX_UV_ATTRIB);
    glBindBuffer(GL_ARRAY_BUFFER, m_buffersNonIndexed[2]);
    glBufferData(GL_ARRAY_BUFFER, getNBVertices()*2* sizeof(float), getUVs(), GL_STATIC_DRAW); //m_normals is std::vector<float>
    glVertexAttribPointer(VERTEX_UV_ATTRIB, 2, GL_FLOAT, GL_FALSE, 0, 0);

    // m_colors
    glEnableVertexAttribArray(VERTEX_COLOR_ATTRIB);
    glBindBuffer(GL_ARRAY_BUFFER, m_buffersNonIndexed[3]);
    glBufferData(GL_ARRAY_BUFFER, getNBVertices()*3* sizeof(float), getColors(), GL_STATIC_DRAW); //m_normals is std::vector<float>
    glVertexAttribPointer(VERTEX_COLOR_ATTRIB, 3, GL_FLOAT, GL_FALSE, 0, 0);
    

    glBindVertexArray(0);
}

void MeshNonIndexed::drawVAO() {
    glBindVertexArray(m_vertexArrayID);
    glDrawArrays(GL_TRIANGLES,0,getNBVertices());
    glBindVertexArray(0);
}

void MeshNonIndexed::deleteVAO() {
    if (m_vertexArrayID != 0){
        glDeleteBuffers(m_buffersNonIndexed.size(), m_buffersNonIndexed.data());
        glDeleteVertexArrays(1,&m_vertexArrayID);
    }
}
