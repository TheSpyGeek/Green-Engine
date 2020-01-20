#ifndef MESHLOADEROFF_H
#define MESHLOADEROFF_H

#include "mesh.h"


class MeshLoaderOFF : public Mesh {
public:
    MeshLoaderOFF(char *filename);
    ~MeshLoaderOFF();

    void createUI() override;

    void recreate(char *filename);
    void create();

protected:

    void readOFFfile(char *filename);

    char m_filename[1024];

    std::string m_errorMessage = "";
};


#endif