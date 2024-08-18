//////////////////////////////////////////////////////////////////////////////////////////////
// Name: Textures.h                                                                         //
// Author: Michael Gagujas                                                                  //
//                                                                                          //
// Description: Manages different textures that are applied to a variety of 3D objects.     //
//                                                                                          //   
// Photo attributions are above their file name in Textures.cpp                             //
//////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <iostream>
#include <glad/glad.h>
#include <vector>

using namespace std;

// Generate, load, hold, and destroy textures that can be applied to 3D objects
class Textures
{
public:
    GLuint gTextureFence;
    GLuint gTextureGrass;
    GLuint gTextureDesk;
    GLuint gTextureHammerHead;
    GLuint gSpecularHammerHead;
    GLuint gTextureWood;
    GLuint gTextureGreen;
    GLuint gTextureClear;
    GLuint gTextureOrange;
    GLuint gTextureYellow;
    GLuint gTextureEyes;
    GLuint gTextureQuestion;
    GLuint gTextureBrass;
    GLuint gTextureSnowflakes;
    GLuint gTextureLeaf;
    GLuint gTextureLeaf2;
    GLuint gTexture4Panel;
    GLuint gTextureDrinkFront;
    GLuint gTextureDrinkTop;
    GLuint gSpecularLow;
    GLuint gSpecularPlastic;
    GLuint gSpecularMetal;
    GLuint gTextureBrick;

    void createTextures();
    void destroyTextures();
    unsigned int loadSkyBox();

private:
    void flipImageVertically(unsigned char* image, int width, int height, int channels);
    unsigned int loadTexture(const char* filename, GLuint wrapMode);
    void UDestroyTexture(GLuint textureId);
};