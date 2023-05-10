#include <Headers/main.h>

struct Buffers
{
	unsigned int VBO;
	unsigned int VAO;
};

// Time Variables
float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main()
{
	GLFWwindow* window = createWindow();

	Shader circleShader;
	circleShader.addShader(ShaderTypes::VERTEX, "./Shaders/Vertex/basic_lighting.vert");
	circleShader.addShader(ShaderTypes::FRAGMENT, "./Shaders/Fragment/basic_lighting.frag");
	circleShader.linkShaderProgram();

	const int num_segments = 360;
	const float radius = 0.25;
	
	// Set the viewport
	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
	glViewport(0, 0, screenWidth, screenHeight);

	std::vector<std::vector<int>> map = 
	{
		{1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 1, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 1, 0, 0, 0, 1},
		{1, 1, 0, 1, 1, 0, 0, 0, 1},
		{1, 1, 0, 1, 1, 0, 0, 0, 1},
		{1, 0, 0, 0, 1, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 1, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1},
	};

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// update the uniform color
		float timeValue = static_cast<float>(glfwGetTime());
		deltaTime = timeValue - lastFrame;
		lastFrame = timeValue;

		
		circleShader.use();
		//circleShader.setFloat("time", timeValue);
		// Draw a grid of squares
		float size = 1.75f;
		float xOffset = 0.0f;
		float yOffset = 0.0f;
		drawGrid(map, size, -0.9f, 0.9f, xOffset, yOffset);
		
		//draw_filled_circle(glm::vec2 (sin(timeValue) * 0.5, cos(timeValue) * 0.5), num_segments, sin(timeValue) * 0.5);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}

#pragma region OpenGL Methods
	void mouse_callback(GLFWwindow* window, double xpos, double ypos)
	{
		//float xoffset = 0;
		//float yoffset = 0;
		//if (use_mouse) {
		//    glfwSetCursorPos(window, SCR_WIDTH / 2, SCR_HEIGHT / 2);

		//    xoffset = xpos - (SCR_WIDTH / 2);
		//    yoffset = (SCR_HEIGHT / 2) - ypos;
		//    /*float lastX = xpos;
		//    float lastY = ypos;*/

		//    float sensitivity = 0.5f;
		//    xoffset *= sensitivity;
		//    yoffset *= sensitivity;

		//    camera.ProcessMouseMovement(xoffset, yoffset);
		//}

		return;
	}

	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
	{
		//camera.ProcessMouseScroll(static_cast<float>(yoffset));

		return;
	}

	GLFWwindow* createWindow()
	{
		glfwInit(); //initialize glfw
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		#endif

		GLFWwindow* result = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Physics Engine", NULL, NULL);

		if (result == NULL) {
			std::cerr << "GLFW Initialization Failed" << std::endl;

			exit(1);
		}

		glfwConfig(result);

		if (glfwRawMouseMotionSupported()) {
			glfwSetInputMode(result, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
		}

		return result;
	}

	void glfwConfig(GLFWwindow* window)
	{
		glfwMakeContextCurrent(window);
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
		glfwSetCursorPosCallback(window, mouse_callback);
		glfwSetScrollCallback(window, scroll_callback);
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		glfwSwapInterval(0); // vsync off

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cerr << "Failed to initialize GLAD" << std::endl;

			exit(1);
		}
		return;
	}

	void processInput(GLFWwindow* window)
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, true);
		}

		return;
	}

	void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		// Set the viewport to cover the entire new window size
		glViewport(0, 0, width, height);

		return;
	}
	void configureBufferAttributes(const unsigned int& position, const unsigned  int& color, const unsigned int& texture, const unsigned int& normal, const unsigned int& number_of_elements_per_line)
	{
		// TODO: redo this method better
		int offset = 0;
		if (position != NULL)
		{
			// Position attribute
			glVertexAttribPointer(0, position, GL_FLOAT, GL_FALSE, number_of_elements_per_line * sizeof(float), (void*)(offset * sizeof(float)));
			glEnableVertexAttribArray(0);
			offset += position;
		}
		if (color != NULL)
		{
			// Color attributoffset
			glVertexAttribPointer(1, color, GL_FLOAT, GL_FALSE, number_of_elements_per_line * sizeof(float), (void*)(offset * sizeof(float)));
			glEnableVertexAttribArray(1);
			offset += color;
		}
		if (texture != NULL)
		{
			// Texture Attribute
			glVertexAttribPointer(2, texture, GL_FLOAT, GL_FALSE, number_of_elements_per_line * sizeof(float), (void*)(offset * sizeof(float)));
			glEnableVertexAttribArray(2);
			offset += texture;
		}
		if (normal != NULL)
		{
			// Normal Attribute
			glVertexAttribPointer(3, normal, GL_FLOAT, GL_FALSE, number_of_elements_per_line * sizeof(float), (void*)(offset * sizeof(float)));
			glEnableVertexAttribArray(3);
			offset += normal;
		}
	}
#pragma endregion

#pragma region Draw Methods
	void drawVertices(unsigned int& VAO, int verts)
	{
		glBindVertexArray(VAO);

		glDrawArrays(GL_TRIANGLES, 0, verts);

		glBindVertexArray(0);

		return;
	}

	void draw_filled_circle(glm::vec2 center, int num_segments, float radius)
	{
		std::vector<float> vertices;
		generate_circle_vertices(center, vertices, num_segments, radius);

		// Bind buffers
		GLuint VBO;
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

		GLuint VAO;
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// Draw triangles to fill the circle
		glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.size() / 2);

		// Cleanup
		glDeleteBuffers(1, &VBO);
		glDeleteVertexArrays(1, &VAO);
		return;
	}

	void generate_circle_vertices(glm::vec2 center, std::vector<float>& vertices, int num_segments, float radius) {
		vertices.clear();
		float theta = TAU / static_cast<float>(num_segments);
		float cos_theta = cosf(theta);
		float sin_theta = sinf(theta);
		float x = radius; // start at (radius, 0)
		float y = 0.0f;
		for (int i = 0; i < num_segments; ++i) {
			// add the vertex (x, y) to the list of vertices
			vertices.push_back(center.x + x);
			vertices.push_back(center.y + y);

			// apply the rotation matrix to (x, y)
			float new_x = cos_theta * x - sin_theta * y;
			float new_y = sin_theta * x + cos_theta * y;
			x = new_x;
			y = new_y;
		}
		// add the last vertex (which is the same as the first one)
		vertices.push_back(center.x + radius);
		vertices.push_back(center.y);
	}

	void drawSquare(float x, float y, float size)
	{
		// Calculate the positions of the vertices
		float vertices[] = {
			x - (size / 2.0f), y - (size / 2.0f),
			x + (size / 2.0f), y - (size / 2.0f),
			x + (size / 2.0f), y + (size / 2.0f),
			x - (size / 2.0f), y + (size / 2.0f)
		};

		// Create a vertex array object (VAO) and bind it
		unsigned int VAO;
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		// Create a buffer for the vertices
		unsigned int VBO;
		glGenBuffers(1, &VBO);

		// Bind the buffer and copy the vertices into it
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// Set up the vertex attributes
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// Draw the square
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

		// Clean up
		glDeleteBuffers(1, &VBO);
		glDeleteVertexArrays(1, &VAO);
	}

	void drawGrid(std::vector<std::vector<int>>& map, float size, float topLeftStartX, float topLeftStartY, float xOffset, float yOffset)
	{
		float squareSize = size / static_cast<float>(map.size()); // Calculate the size of each square

		for (int i = 0; i < map.size(); i++) {
			for (int j = 0; j < map.at(i).size(); j++) {
				if (map.at(i).at(j) == 1) {
					float x = topLeftStartX + (2.0f * j / static_cast<float>(map.at(i).size()));
					float y = topLeftStartY + (-2.0f * i / static_cast<float>(map.size()));

					// Apply the xOffset as the spacing offset
					float xOffsetWithSpacing = xOffset * j;
					float yOffsetWithSpacing = yOffset * i;

					drawSquare(x + xOffsetWithSpacing, y + yOffsetWithSpacing, squareSize); // Pass squareSize as the size parameter
				}
			}
		}
	}

#pragma endregion
