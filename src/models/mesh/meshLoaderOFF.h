#ifndef MESHLOADEROFF_H
#define MESHLOADEROFF_H

#include "mesh.h"


class MeshLoaderOFF : public Mesh {
public:
    MeshLoaderOFF(char *filename);
    ~MeshLoaderOFF();

    void createUI() override;

protected:
    void cleanup();

    void readOFFfile(char *filename);

    char m_filename[1024];

};


#endif