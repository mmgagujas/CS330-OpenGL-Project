//////////////////////////////////////////////////////////////////////////////////////////////
// Name: SceneObjects.cpp                                                                   //
// Author: Michael Gagujas                                                                  //
//                                                                                          //
// Description: Transforms and renders different 3D objects for a scene while               //
// applying textures that tile, overlap, and blend. Scene objects are reusable              //
// by passing in global transformation data.                                                //
//////////////////////////////////////////////////////////////////////////////////////////////

#include "SceneObjects.h"

// Creates the ball-peen hammer
void SceneObjects::renderHammer(MeshCreator gMesh, Textures gTexture, Shader lightingShader, Transform transformData) {
    
    lightingShader.setFloat("material.shininess", 4.0f);
    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gTexture.gTextureHammerHead);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, gTexture.gSpecularHammerHead);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, 0);

    // Activate the VBOs contained within the mesh's VAO
    glBindVertexArray(gMesh.gCylinderMesh.vao);

    // First cylinder, connects hammer handle to headd
    // Scales the object
    glm::mat4 scale = glm::scale(glm::vec3(1.175f, 0.15f, 1.15f));
    // Rotates object along x axis
    glm::mat4 rotation = glm::rotate(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    // Translates object
    glm::mat4 translation = glm::translate(glm::vec3(1.75f, 0.96f, 1.0f));
    // Model matrix: transformations are applied right-to-left order
    glm::mat4 model = transformData.translation * transformData.rotation * transformData.scale * translation * rotation * scale;

	lightingShader.setMat4("model", model);

    // Draws the triangles
    glDrawElements(GL_TRIANGLES, gMesh.gCylinderMesh.nIndices, GL_UNSIGNED_SHORT, NULL);

    lightingShader.setFloat("material.shininess", 2.0f);
    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gTexture.gTextureWood);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, 0);

    // Second cylinder, hammer handle
    scale = glm::scale(glm::vec3(0.7f, 1.7f, 0.4f));
    rotation = glm::rotate(glm::radians(281.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    translation = glm::translate(glm::vec3(-0.55f, 0.497f, 1.0f));
    // Model matrix: transformations are applied right-to-left order
    model = transformData.translation * transformData.rotation * transformData.scale * translation * rotation * scale;	lightingShader.setMat4("model", model);
    // Draws the triangles
    glDrawElements(GL_TRIANGLES, gMesh.gCylinderMesh.nIndices, GL_UNSIGNED_SHORT, NULL);

    lightingShader.setFloat("material.shininess", 4.0f);
    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gTexture.gTextureHammerHead);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, gTexture.gSpecularHammerHead);

    // Third cylinder, hammer head
    scale = glm::scale(glm::vec3(0.98f, 0.25f, 0.98f));
    rotation = glm::rotate(glm::radians(8.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    translation = glm::translate(glm::vec3(1.87f, 0.282f, 1.0f));
    // Model matrix: transformations are applied right-to-left order
    model = transformData.translation * transformData.rotation * transformData.scale * translation * rotation * scale;	lightingShader.setMat4("model", model);
    // Draws the triangles
    glDrawElements(GL_TRIANGLES, gMesh.gCylinderMesh.nIndices, GL_UNSIGNED_SHORT, NULL);

    // Deactivate the Vertex Array Object
    glBindVertexArray(0);

    lightingShader.setFloat("material.shininess", 2.0f);
    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gTexture.gTextureWood);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, 0);

    // Activate the VBOs contained within the mesh's VAO
    glBindVertexArray(gMesh.gPyramidMesh.vao);

    // First pyramid, connects hammer handle to neck
    scale = glm::scale(glm::vec3(0.8f, 0.6f, 0.4f));
    rotation = glm::rotate(glm::radians(100.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    translation = glm::translate(glm::vec3(1.0f, 0.81f, 1.0f));
    // Model matrix: transformations are applied right-to-left order
    model = transformData.translation * transformData.rotation * transformData.scale * translation * rotation * scale;	lightingShader.setMat4("model", model);
    // Draws the triangles
    glDrawArrays(GL_TRIANGLES, 0, gMesh.gPyramidMesh.nVertices);

    // Second pyramid, connects hammer neck to handle
    scale = glm::scale(glm::vec3(0.8f, 0.6f, 0.4f));
    rotation = glm::rotate(glm::radians(280.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    translation = glm::translate(glm::vec3(1.59f, 0.915f, 1.0f));
    // Model matrix: transformations are applied right-to-left order
    model = transformData.translation * transformData.rotation * transformData.scale * translation * rotation * scale;	lightingShader.setMat4("model", model);
    // Draws the triangles
    glDrawArrays(GL_TRIANGLES, 0, gMesh.gPyramidMesh.nVertices);

    // Deactivate the Vertex Array Object
    glBindVertexArray(0);

    lightingShader.setFloat("material.shininess", 4.0f);
    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gTexture.gTextureHammerHead);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, gTexture.gSpecularHammerHead);

    // Activate the VBOs contained within the mesh's VAO
    glBindVertexArray(gMesh.gCubeMesh.vao);

    // First cube, connects hammer's head with center
    scale = glm::scale(glm::vec3(0.39f, 0.9f, 0.27f));
    rotation = glm::rotate(glm::radians(8.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    translation = glm::translate(glm::vec3(1.82f, 0.6f, 1.0f));
    // Model matrix: transformations are applied right-to-left order
    model = transformData.translation * transformData.rotation * transformData.scale * translation * rotation * scale;	lightingShader.setMat4("model", model);
    // Draws the triangles
    glDrawArrays(GL_TRIANGLES, 0, gMesh.gCubeMesh.nVertices);

    // Second cube, connects hammer's peen with center
    scale = glm::scale(glm::vec3(0.28f, 0.4f, 0.28f));
    rotation = glm::rotate(glm::radians(8.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    translation = glm::translate(glm::vec3(1.74f, 1.2f, 1.0f));
    // Model matrix: transformations are applied right-to-left order
    model = transformData.translation * transformData.rotation * transformData.scale * translation * rotation * scale;	lightingShader.setMat4("model", model);
    // Draws the triangles
    glDrawArrays(GL_TRIANGLES, 0, gMesh.gCubeMesh.nVertices);

    // Deactivate the Vertex Array Object
    glBindVertexArray(0);


    // Activate the VBOs contained within the mesh's VAO
    glBindVertexArray(gMesh.gSphereMesh.vao);

    // First sphere, hammer peen
    scale = glm::scale(glm::vec3(0.25f, 0.25f, 0.25f));
    rotation = glm::rotate(glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    translation = glm::translate(glm::vec3(1.7f, 1.53f, 1.0f));
    // Model matrix: transformations are applied right-to-left order
    model = transformData.translation * transformData.rotation * transformData.scale * translation * rotation * scale;	lightingShader.setMat4("model", model);
    // Draws the triangles
    glDrawElements(GL_TRIANGLES, gMesh.gSphereMesh.nIndices, GL_UNSIGNED_SHORT, NULL);

    // Deactivate the Vertex Array Object
    glBindVertexArray(0);
}


// Creates the fire flower souvenir cup
void SceneObjects::renderFireFlower(MeshCreator gMesh, Textures gTexture, Shader lightingShader, Transform transformData) {

    // Activate the VBOs contained within the mesh's VAO
    glBindVertexArray(gMesh.gCubeMesh.vao);

    lightingShader.setFloat("material.shininess", 8.0f);
    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gTexture.gTextureQuestion);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, gTexture.gSpecularPlastic);

    // First cube, base
    glm::mat4 scale = glm::scale(glm::vec3(1.1f, 1.1f, 1.1f));
    glm::mat4 rotation = glm::rotate(glm::radians(40.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 translation = glm::translate(glm::vec3(-0.1f, 0.56f, -1.2f));
    // Model matrix: transformations are applied right-to-left order
    glm::mat4 model = transformData.translation * transformData.rotation * transformData.scale * translation * rotation * scale;	lightingShader.setMat4("model", model);
	lightingShader.setMat4("model", model);
    // Draws the triangles
    glDrawArrays(GL_TRIANGLES, 0, gMesh.gCubeMesh.nVertices);

    // Deactivate the Vertex Array Object
    glBindVertexArray(0);


    // Activate the VBOs contained within the mesh's VAO
    glBindVertexArray(gMesh.gCylinderMesh.vao);

    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gTexture.gTextureClear);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, 0);

    // First cylinder, straw
    scale = glm::scale(glm::vec3(0.19f, 0.7f, 0.19f));
    rotation = glm::rotate(glm::radians(-2.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    translation = glm::translate(glm::vec3(0.22f, 1.6f, -1.42f));
    // Model matrix: transformations are applied right-to-left order
    model = transformData.translation * transformData.rotation * transformData.scale * translation * rotation * scale;	lightingShader.setMat4("model", model);
	lightingShader.setMat4("model", model);
    // Draws the triangles
    glDrawElements(GL_TRIANGLES, gMesh.gCylinderMesh.nIndices, GL_UNSIGNED_SHORT, NULL);

    lightingShader.setFloat("material.shininess", 64.0f);
    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gTexture.gTextureGreen);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, gTexture.gSpecularPlastic);

    // Second cylinder, flower stem bottom
    scale = glm::scale(glm::vec3(0.18f, 0.3f, 0.18f));
    rotation = glm::rotate(glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    translation = glm::translate(glm::vec3(-0.15f, 1.2f, -1.13f));
    // Model matrix: transformations are applied right-to-left order
    model = transformData.translation * transformData.rotation * transformData.scale * translation * rotation * scale;	lightingShader.setMat4("model", model);
	lightingShader.setMat4("model", model);
    // Draws the triangles
    glDrawElements(GL_TRIANGLES, gMesh.gCylinderMesh.nIndices, GL_UNSIGNED_SHORT, NULL);

    // Third cylinder, flower stem top
    scale = glm::scale(glm::vec3(0.175f, 0.15f, 0.175f));
    rotation = glm::rotate(glm::radians(25.0f), glm::vec3(1.0f, 0.0f, 0.0f))
        * glm::rotate(glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    translation = glm::translate(glm::vec3(-0.225f, 1.59f, -1.075f));
    // Model matrix: transformations are applied right-to-left order
    model = transformData.translation * transformData.rotation * transformData.scale * translation * rotation * scale;	lightingShader.setMat4("model", model);
	lightingShader.setMat4("model", model);
    // Draws the triangles
    glDrawElements(GL_TRIANGLES, gMesh.gCylinderMesh.nIndices, GL_UNSIGNED_SHORT, NULL);

    // Fourth cylinder, connect stem to flower
    scale = glm::scale(glm::vec3(0.175f, 0.24f, 0.175f));
    rotation = glm::rotate(glm::radians(35.0f), glm::vec3(0.0f, 1.0f, 0.0f))
        * glm::rotate(glm::radians(80.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    translation = glm::translate(glm::vec3(-0.475f, 1.72f, -0.9f));
    // Model matrix: transformations are applied right-to-left order
    model = transformData.translation * transformData.rotation * transformData.scale * translation * rotation * scale;	lightingShader.setMat4("model", model);
	lightingShader.setMat4("model", model);
    // Draws the triangles
    glDrawElements(GL_TRIANGLES, gMesh.gCylinderMesh.nIndices, GL_UNSIGNED_SHORT, NULL);

    lightingShader.setFloat("material.shininess", 26.0f);
    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gTexture.gTextureOrange);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, gTexture.gSpecularPlastic);

    // Fifth cylinder, straw cap
    scale = glm::scale(glm::vec3(0.24f, 0.07f, 0.24f));
    rotation = glm::rotate(glm::radians(-2.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    translation = glm::translate(glm::vec3(0.245f, 2.3f, -1.42f));
    // Model matrix: transformations are applied right-to-left order
    model = transformData.translation * transformData.rotation * transformData.scale * translation * rotation * scale;	lightingShader.setMat4("model", model);
    lightingShader.setMat4("model", model);
    // Draws the triangles
    glDrawElements(GL_TRIANGLES, gMesh.gCylinderMesh.nIndices, GL_UNSIGNED_SHORT, NULL);

    // Sixth cylinder, straw cap connector
    scale = glm::scale(glm::vec3(0.24f, 0.01f, 0.24f));
    rotation = glm::rotate(glm::radians(-2.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    translation = glm::translate(glm::vec3(0.24f, 2.15f, -1.42f));
    // Model matrix: transformations are applied right-to-left order
    model = transformData.translation * transformData.rotation * transformData.scale * translation * rotation * scale;	lightingShader.setMat4("model", model);
    lightingShader.setMat4("model", model);
    // Draws the triangles
    glDrawElements(GL_TRIANGLES, gMesh.gCylinderMesh.nIndices, GL_UNSIGNED_SHORT, NULL);

    // Deactivate the Vertex Array Object
    glBindVertexArray(0);


    // Activate the VBOs contained within the mesh's VAO
    glBindVertexArray(gMesh.gTorusMesh.vao);


    lightingShader.setFloat("material.shininess", 26.0f);
    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gTexture.gTextureOrange);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, gTexture.gSpecularPlastic);

    // First torus, outer flower ring
    scale = glm::scale(glm::vec3(0.35f, 0.275f, 0.35f));
    rotation = glm::rotate(glm::radians(-50.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    translation = glm::translate(glm::vec3(-0.7f, 1.75f, -0.75f));
    // Model matrix: transformations are applied right-to-left order
    model = transformData.translation * transformData.rotation * transformData.scale * translation * rotation * scale;	lightingShader.setMat4("model", model);
	lightingShader.setMat4("model", model);
    // Draws the triangles
    glDrawArrays(GL_TRIANGLES, 0, gMesh.gTorusMesh.nVertices);

    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gTexture.gTextureYellow);

    // Second torus, inner flower ring
    scale = glm::scale(glm::vec3(0.275f, 0.18f, 0.4f));
    rotation = glm::rotate(glm::radians(-50.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    translation = glm::translate(glm::vec3(-0.7f, 1.75f, -0.75f));
    // Model matrix: transformations are applied right-to-left order
    model = transformData.translation * transformData.rotation * transformData.scale * translation * rotation * scale;	lightingShader.setMat4("model", model);
	lightingShader.setMat4("model", model);
    // Draws the triangles
    glDrawArrays(GL_TRIANGLES, 0, gMesh.gTorusMesh.nVertices);

    // Deactivate the Vertex Array Object
    glBindVertexArray(0);

    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gTexture.gTextureEyes);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, 0);


    // Activate the VBOs contained within the mesh's VAO
    glBindVertexArray(gMesh.gSphereMesh.vao);

    // First sphere, flower face
    scale = glm::scale(glm::vec3(0.15f, 0.15f, 0.25f));
    rotation = glm::rotate(glm::radians(40.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    translation = glm::translate(glm::vec3(-0.7f, 1.75f, -0.75f));
    // Model matrix: transformations are applied right-to-left order
    model = transformData.translation * transformData.rotation * transformData.scale * translation * rotation * scale;	lightingShader.setMat4("model", model);
	lightingShader.setMat4("model", model);
    // Draws the triangles
    glDrawElements(GL_TRIANGLES, gMesh.gSphereMesh.nIndices, GL_UNSIGNED_SHORT, NULL);

    // Deactivate the Vertex Array Object
    glBindVertexArray(0);

    
}


// Creates the popcorn music bucket
void SceneObjects::renderBucket(MeshCreator gMesh, Textures gTexture, Shader lightingShader, Transform transformData) {

    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gTexture.gTexture4Panel);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, gTexture.gTextureSnowflakes);

    // Activate the VBOs contained within the mesh's VAO
    glBindVertexArray(gMesh.gCylinderMesh.vao);

    // First cylinder, inside cylinder
    glm::mat4 scale = glm::scale(glm::vec3(3.0f, 0.8f, 3.0f));
    glm::mat4 rotation = glm::rotate(glm::radians(60.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 translation = glm::translate(glm::vec3(1.82f, 1.3f, -1.3f));
    // Model matrix: transformations are applied right-to-left order
    glm::mat4 model = transformData.translation * transformData.rotation * transformData.scale * translation * rotation * scale;	lightingShader.setMat4("model", model);
	lightingShader.setMat4("model", model);
    // Draws the triangles
    glDrawElements(GL_TRIANGLES, gMesh.gCylinderMesh.nIndices, GL_UNSIGNED_SHORT, NULL);

    lightingShader.setFloat("material.shininess", 64.0f);
    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gTexture.gTextureLeaf2);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, gTexture.gSpecularMetal);
    lightingShader.setVec2("uvScale", glm::vec2(4.0f, 1.0f));
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, 0);

    // Second cylinder, bottom of bucket
    scale = glm::scale(glm::vec3(3.45f, 0.25f, 3.45f));
    rotation = glm::rotate(glm::radians(105.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    translation = glm::translate(glm::vec3(1.8f, 0.26f, -1.3f));
    // Model matrix: transformations are applied right-to-left order
    model = transformData.translation * transformData.rotation * transformData.scale * translation * rotation * scale;	lightingShader.setMat4("model", model);
	lightingShader.setMat4("model", model);
    // Draws the triangles
    glDrawElements(GL_TRIANGLES, gMesh.gCylinderMesh.nIndices, GL_UNSIGNED_SHORT, NULL);

    // Third cylinder, top of bucket
    scale = glm::scale(glm::vec3(3.45f, 0.25f, 3.45f));
    rotation = glm::rotate(glm::radians(105.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    translation = glm::translate(glm::vec3(1.8f, 2.2f, -1.3f));
    // Model matrix: transformations are applied right-to-left order
    model = transformData.translation * transformData.rotation * transformData.scale * translation * rotation * scale;	lightingShader.setMat4("model", model);
	lightingShader.setMat4("model", model);
    // Draws the triangles
    glDrawElements(GL_TRIANGLES, gMesh.gCylinderMesh.nIndices, GL_UNSIGNED_SHORT, NULL);

    lightingShader.setVec2("uvScale", glm::vec2(1.0f, 1.0f));

    lightingShader.setFloat("material.shininess", 32.0f);
    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gTexture.gTextureBrass);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, gTexture.gSpecularMetal);

    // Fourth cylinder, left mickey ear
    scale = glm::scale(glm::vec3(0.4f, 0.02f, 0.4f));
    rotation = glm::rotate(glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f)) * 
        glm::rotate(glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f)) *
        glm::rotate(glm::radians(-135.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    translation = glm::translate(glm::vec3(1.68f, 2.85f, -1.38f));
    // Model matrix: transformations are applied right-to-left order
    model = transformData.translation * transformData.rotation * transformData.scale * translation * rotation * scale;	lightingShader.setMat4("model", model);
	lightingShader.setMat4("model", model);
    // Draws the triangles
    glDrawElements(GL_TRIANGLES, gMesh.gCylinderMesh.nIndices, GL_UNSIGNED_SHORT, NULL);

    // Fifth cylinder, right mickey ear
    scale = glm::scale(glm::vec3(0.4f, 0.02f, 0.4f));
    rotation = glm::rotate(glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f)) * 
        glm::rotate(glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f)) *
        glm::rotate(glm::radians(135.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    translation = glm::translate(glm::vec3(1.91f, 2.85f, -1.18f));
    // Model matrix: transformations are applied right-to-left order
    model = transformData.translation * transformData.rotation * transformData.scale * translation * rotation * scale;	lightingShader.setMat4("model", model);
	lightingShader.setMat4("model", model);
    // Draws the triangles
    glDrawElements(GL_TRIANGLES, gMesh.gCylinderMesh.nIndices, GL_UNSIGNED_SHORT, NULL);

    // Deactivate the Vertex Array Object
    glBindVertexArray(0);

    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gTexture.gTextureBrass);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, gTexture.gSpecularMetal);

    // Activate the VBOs contained within the mesh's VAO
    glBindVertexArray(gMesh.gSphereMesh.vao);

    // First sphere, mickey head
    scale = glm::scale(glm::vec3(0.15f, 0.15f, 0.15f));
    rotation = glm::rotate(glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f)) *
        glm::rotate(glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    translation = glm::translate(glm::vec3(1.8f, 2.69f, -1.3f));
    // Model matrix: transformations are applied right-to-left order
    model = transformData.translation * transformData.rotation * transformData.scale * translation * rotation * scale;	lightingShader.setMat4("model", model);
	lightingShader.setMat4("model", model);
    // Draws the triangles
    glDrawElements(GL_TRIANGLES, gMesh.gSphereMesh.nIndices, GL_UNSIGNED_SHORT, NULL);

    // Deactivate the Vertex Array Object
    glBindVertexArray(0);


    // Activate the VBOs contained within the mesh's VAO
    glBindVertexArray(gMesh.gPlaneMesh.vao);

    lightingShader.setFloat("material.shininess", 64.0f);
    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gTexture.gTextureLeaf);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, gTexture.gSpecularMetal);
    lightingShader.setVec2("uvScale", glm::vec2(1.0f, 1.5f));


    // First plane, front scene divider
    scale = glm::scale(glm::vec3(0.475f, 1.1f, 1.5f));
    rotation = glm::rotate(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f))
        * glm::rotate(glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    translation = glm::translate(glm::vec3(1.42f, 1.21f, -0.575f));
    // Model matrix: transformations are applied right-to-left order
    model = transformData.translation * transformData.rotation * transformData.scale * translation * rotation * scale;	lightingShader.setMat4("model", model);
	lightingShader.setMat4("model", model);
    // Draws the triangles
    glDrawElements(GL_TRIANGLES, gMesh.gPlaneMesh.nIndices, GL_UNSIGNED_SHORT, NULL);

    // Second plane, left scene divider
    scale = glm::scale(glm::vec3(0.475f, 1.1f, 1.5f));
    rotation = glm::rotate(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f))
        * glm::rotate(glm::radians(120.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    translation = glm::translate(glm::vec3(1.095f, 1.21f, -1.72f));
    // Model matrix: transformations are applied right-to-left order
    model = transformData.translation * transformData.rotation * transformData.scale * translation * rotation * scale;	lightingShader.setMat4("model", model);
	lightingShader.setMat4("model", model);
    // Draws the triangles
    glDrawElements(GL_TRIANGLES, gMesh.gPlaneMesh.nIndices, GL_UNSIGNED_SHORT, NULL);

    // Third plane, back scene divider
    scale = glm::scale(glm::vec3(0.475f, 1.1f, 1.5f));
    rotation = glm::rotate(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f))
        * glm::rotate(glm::radians(210.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    translation = glm::translate(glm::vec3(2.22f, 1.21f, -2.01f));
    // Model matrix: transformations are applied right-to-left order
    model = transformData.translation * transformData.rotation * transformData.scale * translation * rotation * scale;	lightingShader.setMat4("model", model);
	lightingShader.setMat4("model", model);
    // Draws the triangles
    glDrawElements(GL_TRIANGLES, gMesh.gPlaneMesh.nIndices, GL_UNSIGNED_SHORT, NULL);

    // Fourth plane, right scene divider
    scale = glm::scale(glm::vec3(0.475f, 1.1f, 1.5f));
    rotation = glm::rotate(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f))
        * glm::rotate(glm::radians(300.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    translation = glm::translate(glm::vec3(2.53f, 1.21f, -0.9f));
    // Model matrix: transformations are applied right-to-left order
    model = transformData.translation * transformData.rotation * transformData.scale * translation * rotation * scale;	lightingShader.setMat4("model", model);
	lightingShader.setMat4("model", model);
    // Draws the triangles
    glDrawElements(GL_TRIANGLES, gMesh.gPlaneMesh.nIndices, GL_UNSIGNED_SHORT, NULL);

    // Deactivate the Vertex Array Object
    glBindVertexArray(0);

    //// reset gUVScale
    lightingShader.setVec2("uvScale", glm::vec2(1.0f, 1.0f));


    // Activate the VBOs contained within the mesh's VAO
    glBindVertexArray(gMesh.gConeMesh.vao);

    lightingShader.setFloat("material.shininess", 64.0f);
    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gTexture.gTextureLeaf);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, gTexture.gSpecularMetal);

    // first cone, lid
    scale = glm::scale(glm::vec3(0.86f, 0.22f, 0.86f));
    rotation = glm::rotate(glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    translation = glm::translate(glm::vec3(1.8f, 2.505f, -1.3f));
    // Model matrix: transformations are applied right-to-left order
    model = transformData.translation * transformData.rotation * transformData.scale * translation * rotation * scale;	lightingShader.setMat4("model", model);
	lightingShader.setMat4("model", model);
    // Draws the triangles
    glDrawElements(GL_TRIANGLES, gMesh.gConeMesh.nIndices, GL_UNSIGNED_SHORT, NULL);

    // Deactivate the Vertex Array Object
    glBindVertexArray(0);
}


// Creates the Japanese drink box
void SceneObjects::renderDrinkBox(MeshCreator gMesh, Textures gTexture, Shader lightingShader, Transform transformData) {
    
    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gTexture.gTextureDrinkFront);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, 0);

    // Activate the VBOs contained within the mesh's VAO
    glBindVertexArray(gMesh.gFrustumPyramidMesh.vao);

    // First frustum pyramid, drink box
    glm::mat4 scale = glm::scale(glm::vec3(1.35f, 1.35f, 1.35f));
    glm::mat4 rotation = glm::rotate(glm::radians(26.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 translation = glm::translate(glm::vec3(-1.875f, 0.676f, -1.0f));
    // Model matrix: transformations are applied right-to-left order
    glm::mat4 model = transformData.translation * transformData.rotation * transformData.scale * translation * rotation * scale;
	lightingShader.setMat4("model", model);
    // Draws the triangles
    glDrawArrays(GL_TRIANGLES, 0, gMesh.gFrustumPyramidMesh.nVertices);

    // Deactivate the Vertex Array Object
    glBindVertexArray(0);


    // Activate the VBOs contained within the mesh's VAO
    glBindVertexArray(gMesh.gPlaneMesh.vao);

    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gTexture.gTextureDrinkTop);

    // First plane, drink box lid
    scale = glm::scale(glm::vec3(0.535f, 1.0f, 0.535f));
    rotation = glm::rotate(glm::radians(26.0f), glm::vec3(0.0f, 1.0f, 0.0f))
        * glm::rotate(glm::radians(-2.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    translation = glm::translate(glm::vec3(-1.88f, 1.7f, -1.0f));
    // Model matrix: transformations are applied right-to-left order
    model = transformData.translation * transformData.rotation * transformData.scale * translation * rotation * scale;
	lightingShader.setMat4("model", model);
    // Draws the triangles
    glDrawElements(GL_TRIANGLES, gMesh.gPlaneMesh.nIndices, GL_UNSIGNED_SHORT, NULL);

    // Deactivate the Vertex Array Object
    glBindVertexArray(0);
}

void SceneObjects::renderRoom(MeshCreator gMesh, Textures gTexture, Shader lightingShader, Transform transformData) {

    // Activate the VBOs contained within the mesh's VAO
    glBindVertexArray(gMesh.gPlaneMesh.vao);

    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gTexture.gTextureGrass);

    // Render floor for 3D scene
    // 1. Scales the object
    glm::mat4 scale = glm::scale(glm::vec3(24.0f, 1.0f, 34.5f));
    // 2. Rotates shape
    glm::mat4 rotation = glm::rotate(glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    // 3. Translates object

    glm::mat4 translation = glm::translate(glm::vec3(0.0f, -3.0f, -6.0f));
    // Transformations are applied right-to-left order
    glm::mat4 model = transformData.translation * transformData.rotation * transformData.scale * translation * rotation * scale;	lightingShader.setMat4("model", model);
	lightingShader.setMat4("model", model);

    // Draws the triangles
    glDrawElements(GL_TRIANGLES, gMesh.gPlaneMesh.nIndices, GL_UNSIGNED_SHORT, NULL);

    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gTexture.gTextureFence);
    lightingShader.setVec2("uvScale", glm::vec2(2.0f, 1.0f));

    // Render Left Wall
    scale = glm::scale(glm::vec3(34.55f, 1.0f, 6.0f));
    rotation = glm::rotate(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)) *
        glm::rotate(glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    translation = glm::translate(glm::vec3(-12.0f, 0.0f, -6.0f));
    // Model matrix: transformations are applied right-to-left order
    model = transformData.translation * transformData.rotation * transformData.scale * translation * rotation * scale;	lightingShader.setMat4("model", model);
	lightingShader.setMat4("model", model);
    // Draws the triangles
    glDrawElements(GL_TRIANGLES, gMesh.gPlaneMesh.nIndices, GL_UNSIGNED_SHORT, NULL);
    
    // Render Right Wall
    scale = glm::scale(glm::vec3(34.55f, 1.0f, 6.0f));
    rotation = glm::rotate(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)) *
        glm::rotate(glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    translation = glm::translate(glm::vec3(12.0f, 0.0f, -6.0f));
    // Model matrix: transformations are applied right-to-left order
    model = transformData.translation * transformData.rotation * transformData.scale * translation * rotation * scale;	lightingShader.setMat4("model", model);
	lightingShader.setMat4("model", model);
    // Draws the triangles
    glDrawElements(GL_TRIANGLES, gMesh.gPlaneMesh.nIndices, GL_UNSIGNED_SHORT, NULL);

    // Render Back Wall
    scale = glm::scale(glm::vec3(24.0f, 1.0f, 6.0f));
    rotation = glm::rotate(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    translation = glm::translate(glm::vec3(0.0f, 0.0f, -23.25f));
    // Model matrix: transformations are applied right-to-left order
    model = transformData.translation * transformData.rotation * transformData.scale * translation * rotation * scale;	lightingShader.setMat4("model", model);
	lightingShader.setMat4("model", model);
    // Draws the triangles
    glDrawElements(GL_TRIANGLES, gMesh.gPlaneMesh.nIndices, GL_UNSIGNED_SHORT, NULL);
    
    // Render Front Wall (Behind default camera)
    scale = glm::scale(glm::vec3(24.0f, 1.0f, 6.0f));
    rotation = glm::rotate(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)) *
        glm::rotate(glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    translation = glm::translate(glm::vec3(0.0f, 0.0f, 11.25f));
    // Model matrix: transformations are applied right-to-left order
    model = transformData.translation * transformData.rotation * transformData.scale * translation * rotation * scale;	lightingShader.setMat4("model", model);
	lightingShader.setMat4("model", model);
    // Draws the triangles
    glDrawElements(GL_TRIANGLES, gMesh.gPlaneMesh.nIndices, GL_UNSIGNED_SHORT, NULL);

    lightingShader.setFloat("material.shininess", 32.0f);
    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gTexture.gTextureDesk);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, gTexture.gSpecularPlastic);
    lightingShader.setVec2("uvScale", glm::vec2(1.0f, 1.0f));

    // Plane on top of desk
    scale = glm::scale(glm::vec3(5.5f, 1.0f, 4.5f));
    rotation = glm::rotate(glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    translation = glm::translate(glm::vec3(0.0f, 0.0f, 0.0f));
    // Model matrix: transformations are applied right-to-left order
    model = transformData.translation * transformData.rotation * transformData.scale * translation * rotation * scale;	lightingShader.setMat4("model", model);
    lightingShader.setMat4("model", model);
    glDrawElements(GL_TRIANGLES, gMesh.gPlaneMesh.nIndices, GL_UNSIGNED_SHORT, NULL);

    // Deactivate the Vertex Array Object
    glBindVertexArray(0);

    // Activate the VBOs contained within the mesh's VAO
    glBindVertexArray(gMesh.gCubeMesh.vao);

    // First cube, Top of Desk
    scale = glm::scale(glm::vec3(5.5f, 0.3f, 4.5f));
    rotation = glm::rotate(glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    translation = glm::translate(glm::vec3(0.0f, -0.15f, 0.0f));
    // Model matrix: transformations are applied right-to-left order
    model = transformData.translation * transformData.rotation * transformData.scale * translation * rotation * scale;	lightingShader.setMat4("model", model);
    lightingShader.setMat4("model", model);
    // Draws the triangles
    glDrawArrays(GL_TRIANGLES, 0, gMesh.gCubeMesh.nVertices);

    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gTexture.gTextureBrick);

    lightingShader.setVec2("uvScale", glm::vec2(0.5f, 0.5f));

    // Second cube, Desk body
    scale = glm::scale(glm::vec3(5.0f, 2.7f, 4.0f));
    rotation = glm::rotate(glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    translation = glm::translate(glm::vec3(0.0f, -1.65f, 0.0f));
    // Model matrix: transformations are applied right-to-left order
    model = transformData.translation * transformData.rotation * transformData.scale * translation * rotation * scale;	lightingShader.setMat4("model", model);
    lightingShader.setMat4("model", model);
    // Draws the triangles
    glDrawArrays(GL_TRIANGLES, 0, gMesh.gCubeMesh.nVertices);

    // Deactivate the Vertex Array Object
    glBindVertexArray(0);

    // reset UV scale
    lightingShader.setVec2("uvScale", glm::vec2(1.0f, 1.0f));

}