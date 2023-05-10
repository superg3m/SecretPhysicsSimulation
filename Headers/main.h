#pragma once

#include <Headers/utility.h>
#include <Headers/shader.h>

// Prototypes
#pragma region OpenGL Methods
GLFWwindow* createWindow();
void glfwConfig(GLFWwindow* window);
void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void configureBufferAttributes(const unsigned int& position, const unsigned  int& color, const unsigned int& texture, const unsigned int& normal, const unsigned int& number_of_elements_per_line);
#pragma endregion

#pragma region Draw Methods
void drawVertices(unsigned int& VAO, int verts);
void draw_filled_circle(glm::vec2 center, int num_segments, float radius);
void generate_circle_vertices(glm::vec2 centerPoint, std::vector<float> &vertices, int num_segments, float radius);
void drawSquare(float x, float y, float squareSize);
void drawGrid(std::vector<std::vector<int>> &map, float size, float topLeftStartX, float topLeftStartY, float xOffset, float yOffset);
#pragma endregion



// Defining External Variables
const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 800;
const double PI = 3.1415926535;
const double TAU = 6.2831853071;

