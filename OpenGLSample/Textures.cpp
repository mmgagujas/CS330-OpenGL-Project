//////////////////////////////////////////////////////////////////////////////////////////////
// Name: Textures.cpp                                                                       //
// Author: Michael Gagujas                                                                  //
//                                                                                          //
// Description: Manages different textures that are applied to a variety of 3D objects.     //
//                                                                                          //   
// Photo attributions are above their file name                                             //
//////////////////////////////////////////////////////////////////////////////////////////////

#include "Textures.h"
using namespace std; // Standard namespace
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


// Images are loaded with Y axis going down, but OpenGL's Y axis goes up, so let's flip it
void Textures::flipImageVertically(unsigned char* image, int width, int height, int channels)
{
    for (int j = 0; j < height / 2; ++j)
    {
        int index1 = j * width * channels;
        int index2 = (height - 1 - j) * width * channels;

        for (int i = width * channels; i > 0; --i)
        {
            unsigned char tmp = image[index1];
            image[index1] = image[index2];
            image[index2] = tmp;
            ++index1;
            ++index2;
        }
    }
}

/*Generate and load the texture*/
unsigned int Textures::loadTexture(char const* path, GLuint wrapMode)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        flipImageVertically(data, width, height, nrComponents);
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

// Assign textures
void Textures::createTextures() {

    // Rawpixel.com. (n.d.). Vertical Wooden Slats Texture Background. Retrieved from https://www.rawpixel.com/image/13176502/photo-image-background-texture-pattern
    gTextureFence = loadTexture("../OpenGLSample/resources/textures/fence.jpg", GL_REPEAT);
    // Rawpixel.com. (n.d.). Free Green Grass Field. Retrieved from https://www.rawpixel.com/image/5911993/image-background-wallpaper-texture
    gTextureGrass = loadTexture("../OpenGLSample/resources/textures/grass.jpg", GL_REPEAT);
    // KaiPhotographer. (n.d). Seamless Texture Wood. Vecteezy. Retrieved from https://www.vecteezy.com/photo/3498716-seamless-texture-wood-old-oak-or-modern-wood-texture
    gTextureDesk = loadTexture("../OpenGLSample/resources/textures/desk.jpg", GL_REPEAT);
    // Denamorado. (n.d.). Brown Rusty Stone Metal Surface. FreePik. Retrieved from https://www.freepik.com/free-photo/empty-brown-rusty-stone-metal-surface-texture_6029183.htm#query=rusty%20metal%20texture&position=19&from_view=keyword&track=ais&uuid=016c81ac-8c79-4587-b8c7-3133403cbe20
    gTextureHammerHead = loadTexture("../OpenGLSample/resources/textures/hammerHead.jpg", GL_REPEAT);
    // hhh316. (n.d.). Seamless Metal Rust 02 Texture. DeviantArt. Retrieved from https://www.deviantart.com/hhh316/art/Seamless-metal-rust-02-texture-164163192
    gSpecularHammerHead = loadTexture("../OpenGLSample/resources/textures/specularHammer.jpg", GL_REPEAT);
    // SimoonMurray. (n.d.). Metal Scratched. DeviantArt. Retrieved from https://www.deviantart.com/simoonmurray/art/Metal-Scratched-Texture-149542845
    gTextureWood = loadTexture("../OpenGLSample/resources/textures/wood.jpg", GL_REPEAT);
    // PhotosPublicDomain. (n.d.). Bumpy Green Plastic Texture. Retrieved from https://www.photos-public-domain.com/2013/11/06/bumpy-green-plastic-texture/
    gTextureGreen = loadTexture("../OpenGLSample/resources/textures/green.jpg", GL_REPEAT);
    // Lifeforstock. (n.d.). Free Photo Gray Wall Textures. Freepik. Retrieved from https://www.freepik.com/free-photo/gray-wall-textures-background_3753132.htm#query=gray&position=4&from_view=search&track=sph&uuid=283eb317-83fa-4a7b-8c67-025ea6e795c5
    gTextureClear = loadTexture("../OpenGLSample/resources/textures/clear.jpg", GL_REPEAT);
    // No attribution required. Retrieved from https://pxhere.com/en/photo/1115674
    gTextureOrange = loadTexture("../OpenGLSample/resources/textures/orange.jpg", GL_REPEAT);
    // Hasan, M. (n.d.). Concrete Wall Yellow Color For Texture Background. Retrieved from https://www.vecteezy.com/vector-art/16596770-concrete-wall-yellow-color-for-texture-background-abstract-yellow-grunge-background-with-growing-effect-yellow-color-painting-background-vector-illustration
    gTextureYellow = loadTexture("../OpenGLSample/resources/textures/yellow.jpg", GL_REPEAT);
    gTextureEyes = loadTexture("../OpenGLSample/resources/textures/eyes.png", GL_REPEAT);
    gTextureQuestion = loadTexture("../OpenGLSample/resources/textures/questionMark.png", GL_REPEAT);
    // KaiPhotographer. (n.d). Gold Background Texture. Vecteezy. Retrieved from https://www.vecteezy.com/photo/3498769-gold-background-texture
    gTextureBrass = loadTexture("../OpenGLSample/resources/textures/brass.jpg", GL_MIRRORED_REPEAT);
    // Rawpixel.com. (n.d.). PNG Snowflake Backgrounds Shape. Retrieved from https://www.rawpixel.com/image/12752198/png-snowflake-backgrounds-shape-blue-generated-image-rawpixel
    gTextureSnowflakes = loadTexture("../OpenGLSample/resources/textures/snowflakes.png", GL_REPEAT);
    gTextureLeaf = loadTexture("../OpenGLSample/resources/textures/bucketLeaf.png", GL_MIRRORED_REPEAT);
    gTextureLeaf2 = loadTexture("../OpenGLSample/resources/textures/bucketLeaf2.png", GL_MIRRORED_REPEAT);
    gTexture4Panel = loadTexture("../OpenGLSample/resources/textures/4Panel.png", GL_REPEAT);
    gTextureDrinkFront = loadTexture("../OpenGLSample/resources/textures/drinkFront.png", GL_REPEAT);
    gTextureDrinkTop = loadTexture("../OpenGLSample/resources/textures/drinkTop.png", GL_REPEAT);
    // Rawpixel.com. (n.d.). Free Photo Glass Background with Frosted Pattern. Freepik. Retrieved from https://www.freepik.com/free-photo/glass-background-with-frosted-pattern_19075756.htm#query=smooth%20plastic%20texture&position=2&from_view=keyword&track=ais&uuid=86683cdd-bdd0-47e7-a250-21d13e106a77
    gSpecularPlastic = loadTexture("../OpenGLSample/resources/textures/specularPlastic.jpg", GL_REPEAT);
    // Rawpixel.com. (n.d.). Silver Gradient Backgrounds Reflection Abstract. Retrieved from https://www.rawpixel.com/image/13176471/image-background-abstract-texture
    gSpecularMetal = loadTexture("../OpenGLSample/resources/textures/specularMetal.jpg", GL_REPEAT);
    // Rawpixel.com. (n.d.). Silver Gradient Backgrounds Reflection Abstract. Retrieved from https://www.rawpixel.com/image/13176471/image-background-abstract-texture
    gTextureBrick = loadTexture("../OpenGLSample/resources/textures/brick.png", GL_REPEAT);

};

// Destroys all textures
void Textures::destroyTextures()
{
    // Release textures
    UDestroyTexture(gTextureFence);
    UDestroyTexture(gTextureGrass);
    UDestroyTexture(gTextureDesk);
    UDestroyTexture(gTextureHammerHead);
    UDestroyTexture(gSpecularHammerHead);
    UDestroyTexture(gTextureWood);
    UDestroyTexture(gTextureGreen);
    UDestroyTexture(gTextureClear);
    UDestroyTexture(gTextureOrange);
    UDestroyTexture(gTextureYellow);
    UDestroyTexture(gTextureEyes);
    UDestroyTexture(gTextureQuestion);
    UDestroyTexture(gTextureBrass);
    UDestroyTexture(gTextureSnowflakes);
    UDestroyTexture(gTextureLeaf);
    UDestroyTexture(gTextureLeaf2);
    UDestroyTexture(gTexture4Panel);
    UDestroyTexture(gTextureDrinkFront);
    UDestroyTexture(gTextureDrinkTop);
    UDestroyTexture(gSpecularPlastic);
    UDestroyTexture(gSpecularMetal);
    UDestroyTexture(gTextureBrick);
}

// Destroys a texture
void Textures::UDestroyTexture(GLuint textureId)
{
    glDeleteTextures(1, &textureId);
}

// Loads cubemap/skybox
unsigned int Textures::loadSkyBox()
{
    // Credit to Terrell, Rye. (2015, November 17). Free WebGL Space Skybox Generator. Retrieved from https://tools.wwwtyro.net/space-3d/index.html#animationSpeed=1&fov=80&nebulae=true&pointStars=true&resolution=1024&seed=idccbn8mkm0&stars=true&sun=true
    vector<std::string> faces = {
        "../OpenGLSample/resources/skybox/right.jpg",
        "../OpenGLSample/resources/skybox/left.jpg",
        "../OpenGLSample/resources/skybox/top.jpg",
        "../OpenGLSample/resources/skybox/bottom.jpg",
        "../OpenGLSample/resources/skybox/front.jpg",
        "../OpenGLSample/resources/skybox/back.jpg"
    };
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
            );
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}