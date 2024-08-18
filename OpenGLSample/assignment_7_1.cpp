////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Name: Assignment 7-1 Computational Graphics & Visualizations Project                                       //
// Author: Michael Gagujas                                                                                    //
// Date: 02/24/2024                                                                                           //
// Description: Using OpenGL to create a realistic 3D Scene of a 2D photo                                     //
// 
// Credits:
//     Battersby, Brian. (2022). MeshesExample. Retrieved from https://learn.snhu.edu/d2l/common/viewFile.d2lfile/Database/MTMxNDMxNDM2/Meshes%20Example.zip?ou=1460943
//     Gray, Scott. (2024). TutorialCylinder.cpp[Source code]. Retrieved from https://learn.snhu.edu/d2l/common/viewFile.d2lfile/Database/MTMwOTI5MDU2/TutorialCylinder.cpp?ou=1460943
//     SNHU-CS. (2023). CS-330/tut_06_03.cpp[Source code].GitHub. https://github.com/SNHU-CS/CS-330
//     
//     **Photo attributions in Textures.cpp above their file name                                             //
//                                                                                                            //
// Camera Controls:                                                                                           //
// W/A/S/D/Q/E - Move Forward/Back/Left/Right/Down/Up                                                         //
// Mouse scroll wheel - Raise/Lower camera movement speed                                                     //
//                                                                                                            //
// Light Controls:                                                                                            //
//     1/2     - 1 selects left point light, 2 selects right point light                                      //
// I/J/K/L/U/O - Move Forward/Back/Left/Right/Down/Up                                                         //
//                                                                                                            //
// Toggle Buttons:                                                                                            //
//      P      - Toggle between perspective/orthographic                                                      //
//      F      - Toggle flashlight on/off                                                                     //
//      B      - Toggle skybox                                                                                //
//     ESC     - Closes window                                                                                //
//                                                                                                            //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "camera.h"
#include "MeshCreator.h"
#include "Textures.h"
#include "SceneObjects.h"

#include <iostream>
using namespace::std;

// Unnamed namespace
namespace
{
	// Window settings
	const unsigned int SCR_WIDTH = 800;
	const unsigned int SCR_HEIGHT = 600;

	// Meshes data
	MeshCreator gMesh;

	// Textures data
	Textures gTexture;

	// Creates objects for scene
	SceneObjects builder;

	// Camera
	Camera camera(glm::vec3(0.0f, 2.8f, 4.8f));
	float lastX = SCR_WIDTH / 2.0f;
	float lastY = SCR_HEIGHT / 2.0f;
	bool firstMouse = true;

	// Timing
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	// Positions of the point lights
	glm::vec3 pointLightPositions[] = {
		glm::vec3(-2.0f, 1.1f, 1.0f),
		glm::vec3(2.0f, 2.2f, 1.7f),
	};

	// Default status values
	int lightNumber = 1;
	bool showPerspective = true;
	bool showFlashlight = true;
	bool showSkybox = false;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
void moveLight(string direction, float time);
void toggleEvent(GLFWwindow* window, int key, int scancode, int action, int mods);


int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "7-1 Michael Gagujas", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetKeyCallback(window, toggleEvent);


	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	// build and compile our shader zprogram
	// ------------------------------------
	Shader lightingShader("../OpenGLSample/shaderfiles/6.multiple_lights.vs", "../OpenGLSample/shaderfiles/6.multiple_lights.fs");
	Shader lightCubeShader("../OpenGLSample/shaderfiles/6.light_cube.vs", "../OpenGLSample/shaderfiles/6.light_cube.fs");
	Shader skyboxShader("../OpenGLSample/shaderfiles/skybox.vs", "../OpenGLSample/shaderfiles/skybox.fs");

	// Create meshes
	gMesh.createMeshes();

	// Load textures
	gTexture.createTextures();

	// shader configuration
	// --------------------
	lightingShader.use();
	lightingShader.setInt("material.diffuse", 0);
	lightingShader.setInt("material.specular", 1);
	lightingShader.setInt("textureOverlay", 2);

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// per-frame time logic
		// --------------------
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// be sure to activate shader when setting uniforms/drawing objects
		lightingShader.use();
		lightingShader.setVec3("viewPos", camera.Position);

		// default shininess, rough materials
		lightingShader.setFloat("material.shininess", 2.0f);

		// set default texture scale
		glm::vec2 gUVScale(1.0f, 1.0f);
		lightingShader.setVec2("uvScale", gUVScale);

		/*
		   Here we set all the uniforms for the 3/4 types of lights we have. We have to set them manually and index
		   the proper PointLight struct in the array to set each uniform variable. This can be done more code-friendly
		   by defining light types as classes and set their values in there, or by using a more efficient uniform approach
		   by using 'Uniform buffer objects', but that is something we'll discuss in the 'Advanced GLSL' tutorial.
		*/
		// directional light
		lightingShader.setVec3("dirLight.direction", -3.0f, -10.0f, 10.0f);
		lightingShader.setVec3("dirLight.ambient", 0.15f, 0.15f, 0.15f);
		lightingShader.setVec3("dirLight.diffuse", 0.2f, 0.2f, 0.2f);
		lightingShader.setVec3("dirLight.specular", 0.1f, 0.1f, 0.1f);
		// point light 1, orange light at 70%
		lightingShader.setVec3("pointLights[0].position", pointLightPositions[0]);
		lightingShader.setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
		lightingShader.setVec3("pointLights[0].diffuse", 1.0f, 0.5f, 0.0f);
		lightingShader.setVec3("pointLights[0].specular", 1.0f, 0.5f, 0.0f);
		lightingShader.setFloat("pointLights[0].constant", 1.0f);
		lightingShader.setFloat("pointLights[0].linear", 0.09);
		lightingShader.setFloat("pointLights[0].quadratic", 0.032);
		// multiplies ambient, diffuse, and specular light by intensity strength
		lightingShader.setFloat("pointLights[0].intensity", 0.7f); // 70%
		// point light 2, whitish-yellow at 100%
		lightingShader.setVec3("pointLights[1].position", pointLightPositions[1]);
		lightingShader.setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
		lightingShader.setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.7f);
		lightingShader.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
		lightingShader.setFloat("pointLights[1].constant", 1.0f);
		lightingShader.setFloat("pointLights[1].linear", 0.09);
		lightingShader.setFloat("pointLights[1].quadratic", 0.032);
		// multiplies ambient, diffuse, and specular light by intensity strength
		lightingShader.setFloat("pointLights[1].intensity", 1.0f); // 100%
		// spotLight
		lightingShader.setVec3("spotLight.position", camera.Position);
		lightingShader.setVec3("spotLight.direction", camera.Front);
		lightingShader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
		if (showFlashlight) {
			lightingShader.setVec3("spotLight.diffuse", 0.7f, 0.7f, 0.7f);
			lightingShader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
		}
		else {
			lightingShader.setVec3("spotLight.diffuse", 0.0f, 0.0f, 0.0f);
			lightingShader.setVec3("spotLight.specular", 0.0f, 0.0f, 0.0f);
		}
		lightingShader.setFloat("spotLight.constant", 1.0f);
		lightingShader.setFloat("spotLight.linear", 0.09);
		lightingShader.setFloat("spotLight.quadratic", 0.032);
		lightingShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
		lightingShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
		

		// View/projection transformations
		glm::mat4 projection;
		if (showPerspective) {
			projection = glm::perspective(glm::radians(60.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		}
		else {
			projection = glm::ortho(-5.0f, 5.0f, -5.0f, 5.0f, 0.1f, 100.0f);
		}
		glm::mat4 view = camera.GetViewMatrix();
		lightingShader.setMat4("projection", projection);
		lightingShader.setMat4("view", view);

		// World transformation
		glm::mat4 model = glm::mat4(1.0f);
		lightingShader.setMat4("model", model);


		// Draw the lamp object(s)
		lightCubeShader.use();
		lightCubeShader.setMat4("projection", projection);
		lightCubeShader.setMat4("view", view);
		// Draw as many light bulbs as we have point lights.
		glBindVertexArray(gMesh.gCubeMesh.vao);
		for (unsigned int i = 0; i < 2; i++)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model, pointLightPositions[i]);
			model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
			lightCubeShader.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, gMesh.gCubeMesh.nVertices);
		}

		// Deactivate the Vertex Array Object
		glBindVertexArray(0);

		// Draw scene objects and environment
		lightingShader.use();
		Transform transformData;
		builder.createScene(gMesh, gTexture, lightingShader, transformData);

		// Example for reusing scene objects multiple times
		// creates another fire flower cup on the grass to the right of desk
		// ------------------------------------------------------
		//Transform transformData1;
		//transformData1.scale = glm::scale(glm::vec3(1.0f, 1.0f, 1.0f));
		//transformData1.rotation = glm::rotate(glm::radians(-40.0f), glm::vec3(0.0f, 1.0f, 0.0f)) *
		//	glm::rotate(glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 1.0f));
		//transformData1.translation = glm::translate(glm::vec3(5.5f, -1.7f, -3.5f));
		//builder.renderFireFlower(gMesh, gTexture, lightingShader, transformData1);

		// Display skybox
		if (showSkybox) {
			unsigned int cubemapTexture = gTexture.loadSkyBox();
			glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
			skyboxShader.use();

			view = glm::mat4(glm::mat3(camera.GetViewMatrix()));
			view = glm::rotate(view, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // Rotate the view matrix by 180 degrees around the y-axis
			skyboxShader.setMat4("projection", projection);
			skyboxShader.setMat4("view", view);
			glBindVertexArray(gMesh.gSkyboxMesh.vao);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
			model = glm::mat4(1.0f);
			skyboxShader.setMat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, gMesh.gSkyboxMesh.nVertices);

			glDepthFunc(GL_LESS); // set depth function back to default

			// Deactivate the Vertex Array Object
			glBindVertexArray(0);

			glDeleteTextures(1, &cubemapTexture);
		}


		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	// De-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	
	// Release meshes data
	gMesh.destroyMeshes();

	// Release textures
	gTexture.destroyTextures();


	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	// Camera movement
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		camera.ProcessKeyboard(DOWN, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		camera.ProcessKeyboard(UP, deltaTime);

	// Point light selection
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		lightNumber = 1;
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		lightNumber = 2;

	// Animate point lights
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
		moveLight("forward", deltaTime);
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
		moveLight("backward", deltaTime);
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
		moveLight("left", deltaTime);
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		moveLight("right", deltaTime);
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
		moveLight("down", deltaTime);
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
		moveLight("up", deltaTime);

}

// Toggles perspective and ortho projection, or toggles flashlight
void toggleEvent(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_P && action == GLFW_PRESS) {
		showPerspective = !showPerspective;
	}
	if (key == GLFW_KEY_F && action == GLFW_PRESS) {
		showFlashlight = !showFlashlight;
	}
	if (key == GLFW_KEY_B && action == GLFW_PRESS) {
		showSkybox = !showSkybox;
	}
}

// Processes input received from any keyboard-like input system.
void moveLight(string direction, float time)
{
	glm::vec3& light = (lightNumber == 1) ? pointLightPositions[0] : pointLightPositions[1];

	float speed = 1.0f * time;
	if (direction == "forward")
		light.z -= speed; // Move forward
	if (direction == "backward")
		light.z += speed; // Move backward
	if (direction == "left")
		light.x -= speed; // Move left
	if (direction == "right")
		light.x += speed; // Move right
	if (direction == "down")
		light.y -= speed; // Move down
	if (direction == "up")
		light.y += speed; // Move up
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}
