#pragma once

#include <Headers/utility.h>
#include <Headers/shader.h>

// Prototypes
GLFWwindow* createWindow();
void glfwConfig(GLFWwindow* window);
void processInput(GLFWwindow* window);
void drawVertices(unsigned int& VAO, int verts);
void draw_filled_circle(glm::vec2 center, int num_segments, float radius);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void generate_circle_vertices(glm::vec2 centerPoint, std::vector<float> &vertices, int num_segments, float radius);
void configureBufferAttributes(const unsigned int& position, const unsigned  int& color, const unsigned int& texture, const unsigned int& normal, const unsigned int& number_of_elements_per_line);




// Defining External Variables
const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 800;

const double PI = 3.1415926535;
const double TAU = 6.2831853071;