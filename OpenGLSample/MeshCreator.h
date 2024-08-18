//////////////////////////////////////////////////////////////////////////////////////////////
// Name: MeshCreator.h                                                                      //
// Author: Michael Gagujas                                                                  //
//                                                                                          //
// Description: Creates and manages different types of 3D meshes for defining the           //
// shape of a 3D object                                                                     //
//////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <glad/glad.h>

// Creates mesh for various 3D shapes like primitives and a frustum pyramid
class MeshCreator
{
    // Stores the GL data relative to a given mesh
    struct GLMesh
    {
        GLuint vao;         // Handle for the vertex array object
        GLuint vbos[2];     // Handles for the vertex buffer objects
        GLuint nVertices;	// Number of vertices for the mesh
        GLuint nIndices;    // Number of indices of the mesh
    };

public:
    GLMesh gPlaneMesh;
    GLMesh gPyramidMesh;
    GLMesh gFrustumPyramidMesh;
    GLMesh gCylinderMesh;
    GLMesh gCubeMesh;
    GLMesh gSphereMesh;
    GLMesh gTorusMesh;
    GLMesh gConeMesh;
    GLMesh gSkyboxMesh;


    void createMeshes();
    void destroyMeshes();

private:
    void makePlaneMesh(GLMesh& mesh);
    void makePyramidMesh(GLMesh& mesh);
    void makeFrustumPyramidMesh(GLMesh& mesh);
    void makePrism(GLfloat verts[], GLushort indices[], int numSides, float radius, float halfLen);
    void makeCylinderMesh(GLMesh& mesh);
    void makeCubeMesh(GLMesh& mesh);
    void makeSphereMesh(GLMesh& mesh);
    void makeTorusMesh(GLMesh& mesh);
    void makeConeMesh(GLMesh& mesh);
    void destroyMesh(GLMesh& mesh);
    void makeSkyboxMesh(GLMesh& mesh);
};