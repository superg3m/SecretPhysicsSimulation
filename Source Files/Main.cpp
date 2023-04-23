#include <Headers/main.h>

struct Buffers
{
	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;
};

// Time Variables
float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main()
{
	GLFWwindow* window = createWindow();

	// Shaders
	Shader circleShader;
	circleShader.addShader(ShaderTypes::VERTEX, "./Shaders/Vertex/basic_lighting.vert");
	circleShader.addShader(ShaderTypes::FRAGMENT, "./Shaders/Fragment/basic_lighting.frag");
	circleShader.linkShaderProgram();

	// Generate Circle Vertices
	
	Buffers circleBuffers {0, 0, 0};
	
	genBuffers(circleBuffers.VBO, circleBuffers.VAO);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// update the uniform color
		float timeValue = static_cast<float>(glfwGetTime());
		deltaTime = timeValue - lastFrame;
		lastFrame = timeValue;

		circleShader.use();

		circleShader.setFloat("time", timeValue);

		drawVertices(circleBuffers.VAO, 6);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

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

	//up.setRenderProperty(RenderProperties::WIRE_FRAME, true); ONLY IN 3D

	/*
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO &io = ImGui::GetIO(); (void)io;

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330 core");
	*/

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
	glViewport(0, 0, width, height);

	return;
}

void genBuffers(unsigned int& VBO, unsigned int& VAO)
{
	float vertices[] = {
		//  X     Y     Z      R      G      B
		//   POSITIONS             COLOR
		+0.5f, +0.5f, +0.0f, +0.0f, +0.0f, +1.0f, // top right
		-0.5f, +0.5f, +0.0f, +1.0f, +0.0f, +0.0f, // top left
		-0.5f, -0.5f, +0.0f, +0.0f, +1.0f, +0.0f, // bottom left 

		+0.5f, +0.5f, +0.0f, +0.0f, +0.0f, +1.0f, // top right
		-0.5f, -0.5f, +0.0f, +0.0f, +1.0f, +0.0f, // bottom left
		+0.5f, -0.5f, +0.0f, +1.0f, +0.0f, +0.0f, // bottom right
	};

	//VBO vertex buffer object, deals with verticies

	glGenBuffers(1, &VBO);

	//EBO element buffer object, deals with indices

	glGenVertexArrays(1, &VAO);
	// 1. bind Vertex Array Object
	glBindVertexArray(VAO);
	// 2. copy our vertices array in a vertex buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3. copy our index array in a element buffer for OpenGL to use
	// 
	// 4. then set the vertex attributes pointers
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	return;
}

void drawVertices(unsigned int& VAO, int verts)
{
	glBindVertexArray(VAO);

	glDrawArrays(GL_TRIANGLES, 0, verts);

	glBindVertexArray(0);

	return;
}

void generateCircleVertices(glm::vec3 centerPoint, float radius)
{

}