#pragma once

#include <Headers/utility.h>
#include <Headers/shader.h>

// Prototypes
GLFWwindow* createWindow();
void glfwConfig(GLFWwindow* window);
void processInput(GLFWwindow* window);
void drawVertices(unsigned int& VAO, int verts);
void genBuffers(unsigned int& VBO, unsigned int& VAO);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);




// Defining External Variables
const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

const double PI = 3.1415926535;
const double TAU = 6.2831853071;