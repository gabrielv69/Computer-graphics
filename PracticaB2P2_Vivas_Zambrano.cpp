#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/shader.h> 
#include <learnopengl/camera.h>
#include <learnopengl/model.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

unsigned int loadTexture(const char* path);

//linterna
int on = 1;
//contadorEscalasFaroles
int escala = 0;
//contadorEscalasBarrotes
int escala2 = 0;

// settings
const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 1000;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 20.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

int main()
{
	// glfw: initialize and configure
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "B2P2 Vivas-Zambrano Parque Nocturno", NULL, NULL);
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

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
	stbi_set_flip_vertically_on_load(true);

	// configure global opengl state
	glEnable(GL_DEPTH_TEST);

	// build and compile our shader zprogram
	Shader cubosShader("E:/ProyectoGraficas/shaders/vertex_cubos.vs", "E:/ProyectoGraficas/shaders/fragment_cubos.fs");
	Shader lucesShader("E:/ProyectoGraficas/shaders/vertex_luces.vs", "E:/ProyectoGraficas/shaders/fragment_luces.fs");
	Shader colorShader("E:/ProyectoGraficas/shaders/vertex_colors.vs", "E:/ProyectoGraficas/shaders/fragment_colors.fs");
	//Modelo shader
	Shader modelShader("E:/ProyectoGraficas/shaders/vertex_modelo2.vs", "E:/ProyectoGraficas/shaders/fragment_modelo1.fs");
		// load models
	stbi_set_flip_vertically_on_load(false);
	Model ourModel1("E:/ProyectoGraficas/modelos/bird(gltf)/bird(gltf)/untitled.obj");
	Model ourModel2("E:/ProyectoGraficas/modelos/shiba(gltf)/untitled.obj");
	stbi_set_flip_vertically_on_load(true);
	Model ourModel3("E:/ProyectoGraficas/modelos/white_flower(gltf)/untitled.obj");
	Model ourModel4("E:/ProyectoGraficas/modelos/flower(gltf)/untitled.obj");
	Model ourModel5("E:/ProyectoGraficas/modelos/bench4(gltf)/untitled.obj");
	Model ourModel6("E:/ProyectoGraficas/modelos/butterfly/output.obj");
	Model ourModel7("E:/ProyectoGraficas/modelos/old_tree(gltf)/untitled.obj");

 // set up vertex data (and buffer(s)) and configure vertex attributes
	float vertices[] = {
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
	};


	//POSICIONES CERCAS
	glm::vec3 posicionesCERCAS[] = {
		//derecha horizontal
	glm::vec3(14.7f, -9.0f, 0.0f),
	glm::vec3(14.7f, -8.3f, 0.0f),
	//izquierda horizontal
	glm::vec3(-14.7f, -9.0f, 0.0f),
	glm::vec3(-14.7f, -8.3f, 0.0f),
	//entrada horizontal DERECHA 
	glm::vec3(8.7f, -9.0f, 14.5f),
	glm::vec3(8.7f, -8.3f, 14.5f),
	//entrada horizontal izquierda
	glm::vec3(-8.7f, -9.0f, 14.5f),
	glm::vec3(-8.7f, -8.3f, 14.5f),
	//fondo horizontal Derecha
	glm::vec3(8.7f, -9.0f, -14.5f),
	glm::vec3(8.7f, -8.3f, -14.5f),
	//fondo horizontal Ìzquierda
	glm::vec3(-8.7f, -9.0f, -14.5f),
	glm::vec3(-8.7f, -8.3f, -14.5f)

	};

	glm::vec3 FarolPositions[] = {
		//FAROL1 CERCA
	   glm::vec3(3.0f, -5.0f, 13.0f), //Cuerpo
	   glm::vec3(2.1f, 0.1f, 13.0f), //Parte superior --horizontal (corta) 
	   glm::vec3(1.0f, -0.3f, 13.0f), //Parte superior --vertical (corta)
	   glm::vec3(1.0f, -0.8f, 13.0f), //Parte superior --plana (base de la lámpara)
	   //FAROL2
	   glm::vec3(3.0f, -5.0f, -13.0f),
	   glm::vec3(2.1f, 0.1f, -13.0f),
	   glm::vec3(1.0f, -0.3f, -13.0f),
	   glm::vec3(1.0f, -0.8f, -13.0f),
	   //FAROLMEDIO
	   glm::vec3(-2.9f, -5.0f, 0.0f),
	   glm::vec3(-3.8f, 0.1f, 0.0f),
	   glm::vec3(-4.9f, -0.3f, 0.0f),
	   glm::vec3(-4.9f, -0.8f, 0.0f),
	   //FAROL2 INVERTIDO
	   glm::vec3(-3.2f, -5.0f, 13.0f),
	   glm::vec3(-4.1f, 0.1f, 13.0f),
	   glm::vec3(-5.2f, -0.3f, 13.0f),
	   glm::vec3(-5.2f, -0.8f, 13.0f),
	   //FAROL1 cerca INVERTIDO
	   glm::vec3(-3.2f, -5.0f, -13.0f),
	   glm::vec3(-4.1f, 0.1f, -13.0f),
	   glm::vec3(-5.2f, -0.3f, -13.0f),
	   glm::vec3(-5.2f, -0.8f, -13.0f),
	   //FAROLMEDIO INVERTIDO
	   glm::vec3(2.7f, -5.0f, 0.0f),
	   glm::vec3(1.8f, 0.1f, 0.0f),
	   glm::vec3(0.7f, -0.3f, 0.0f),
	   glm::vec3(0.7f, -0.8f, 0.0f),

	};

	glm::vec3 FarolLucesPositions[] = {
		//FAROL1 CERCA
	   glm::vec3(1.0f, -1.1f, 13.0f),//Cubo de luz
	   //FAROL2
	   glm::vec3(1.0f, -1.1f, -13.0f),
	   //FAROLMEDIO
	   glm::vec3(-4.9f, -1.1f, 0.0f),
	   //FAROL2 INVERTIDO
	   glm::vec3(-5.2f, -1.1f, 13.0f),
	   //FAROL1 cerca INVERTIDO
	   glm::vec3(-5.2f, -1.1f, -13.0f),
	   //FAROLMEDIO INVERTIDO
	   glm::vec3(0.7f, -1.1f, 0.0f),

	   //luces 2
			   //FAROL2 INVERTIDO
		glm::vec3(5.2f, -1.1f, 13.0f),
		//FAROL1 cerca INVERTIDO
		glm::vec3(5.2f, -1.1f, -13.0f),
		//FAROLMEDIO INVERTIDO
		glm::vec3(-0.7f, -1.1f, 0.0f)

	};

	glm::vec3 FarolEscalas[] = {
	   glm::vec3(0.2f, 10.0f, 0.2f),//Cuerpo
	   glm::vec3(2.0f, 0.2f, 0.2f),//Parte superior --horizontal (corta)
	   glm::vec3(0.2f, 1.0f, 0.2f), //Parte superior --vertical (corta)
	   glm::vec3(1.0f, 0.2f, 1.0f) //Parte superior --plana (base de la lámpara)

	};
	//Posiciones de las flores blancas
	glm::vec3 flores[] = {
		glm::vec3(12.5f, -9.8f,  13.0f), //Parte derecha
		glm::vec3(12.5f, -9.8f,  6.5f),
		glm::vec3(12.5f, -9.8f,  0.0f),
		glm::vec3(12.5f, -9.8f, -6.5f),
		glm::vec3(12.5f, -9.8f, -13.0f),

		glm::vec3(10.5f, -9.8f,  9.75f),
		glm::vec3(10.5f, -9.8f,  3.25f),
		glm::vec3(10.5f, -9.8f, -3.25f),
		glm::vec3(10.5f, -9.8f, -9.75f),

		glm::vec3(8.5f, -9.8f,  13.0f),
		glm::vec3(8.5f, -9.8f,  6.5f),
		glm::vec3(8.5f, -9.8f,  0.0f),
		glm::vec3(8.5f, -9.8f, -6.5f),
		glm::vec3(8.5f, -9.8f, -13.0f),

		glm::vec3(6.5f, -9.8f,  9.75f),
		glm::vec3(6.5f, -9.8f,  4.85f),
		glm::vec3(6.5f, -9.8f, -4.85f),
		glm::vec3(6.5f, -9.8f, -9.75f),

		glm::vec3(4.5f, -9.8f,  13.0f),
		glm::vec3(4.5f, -9.8f,  6.5f),
		glm::vec3(4.5f, -9.8f, -6.5f),
		glm::vec3(4.5f, -9.8f, -13.0f),

		glm::vec3(-12.5f, -9.8f,  6.5f),//Parte izquierda
		glm::vec3(-12.5f, -9.8f,  0.0f),
		glm::vec3(-12.5f, -9.8f, -6.5f),
		glm::vec3(-12.5f, -9.8f, -13.0f),

		glm::vec3(-10.5f, -9.8f,  9.75f),
		glm::vec3(-10.5f, -9.8f,  3.25f),
		glm::vec3(-10.5f, -9.8f, -3.25f),
		glm::vec3(-10.5f, -9.8f, -9.75f),

		glm::vec3(-8.5f, -9.8f,  13.0f),
		glm::vec3(-8.5f, -9.8f,  6.5f),
		glm::vec3(-8.5f, -9.8f,  0.0f),
		glm::vec3(-8.5f, -9.8f, -6.5f),
		glm::vec3(-8.5f, -9.8f, -13.0f),

		glm::vec3(-6.5f, -9.8f,  9.75f),
		glm::vec3(-6.5f, -9.8f,  4.85f),
		glm::vec3(-6.5f, -9.8f, -4.85f),
		glm::vec3(-6.5f, -9.8f, -9.75f),

		glm::vec3(-4.5f, -9.8f,  13.0f),
		glm::vec3(-4.5f, -9.8f,  6.5f),
		glm::vec3(-4.5f, -9.8f,  0.0f),
		glm::vec3(-4.5f, -9.8f, -6.5f),
		glm::vec3(-4.5f, -9.8f, -13.0f)
	};

	glm::vec3 BarrotesPositions[] = {
		//puerta inferior izquierda
			glm::vec3(-2.7f, -7.68f, 14.5f), //base superior
			glm::vec3(-2.7f, -9.68f, 14.5f),//base inferior
			glm::vec3(-2.7f, -8.68f, 14.5f),//base superior
			glm::vec3(-2.7f, -7.5f, 14.5f), //rombo
			//puerta inferior derecha 
			glm::vec3(2.7f, -7.68f, 14.5f),
			glm::vec3(2.7f, -9.68f, 14.5f),
			glm::vec3(2.7f, -8.68f, 14.5f),
			glm::vec3(2.7f, -7.5f, 14.5f),
			//puerta superior  derecha
			glm::vec3(2.7f, -7.68f, -14.5f),
			glm::vec3(2.7f, -9.68f, -14.5f),
			glm::vec3(2.7f, -8.68f, -14.5f),
			glm::vec3(2.7f, -7.5f, -14.5f),
			//puerta superior  izquierda
			 glm::vec3(-2.7f, -7.68f, -14.5f),
			 glm::vec3(-2.7f, -9.68f, -14.5f),
			 glm::vec3(-2.7f, -8.68f, -14.5f),
			 glm::vec3(-2.7f, -7.5f, -14.5f),
			 //derecha inferior
			glm::vec3(14.7f, -7.68f, 14.5f),
			glm::vec3(14.7f, -9.68f, 14.5f),
			glm::vec3(14.7f, -8.68f, 14.5f),
			glm::vec3(14.7f, -7.5f, 14.5f),
			//derecha superior
			glm::vec3(14.7f, -7.68f, -14.5f),
			glm::vec3(14.7f, -9.68f, -14.5f),
			glm::vec3(14.7f, -8.68f,-14.5f),
			glm::vec3(14.7f, -7.5f, -14.5f),
			//izquierda inferior
			glm::vec3(-14.7f, -7.68f, 14.5f),
			glm::vec3(-14.7f, -9.68f, 14.5f),
			glm::vec3(-14.7f, -8.68f, 14.5f),
			glm::vec3(-14.7f, -7.5f, 14.5f),
			//izquierda superior
			glm::vec3(-14.7f, -7.68f, -14.5f),
			glm::vec3(-14.7f, -9.68f, -14.5f),
			glm::vec3(-14.7f, -8.68f, -14.5f),
			glm::vec3(-14.7f, -7.5f, -14.5f)
	};

	glm::vec3 BarrotesEscalas[] = {
		//puerta inferior izquierda
		glm::vec3(0.5f, 0.2f, 0.5f),//base superior
		glm::vec3(0.5f, 0.3f, 0.5f),//base inferior
		glm::vec3(0.35f, 2.0f, 0.35f), //base superior
		glm::vec3(0.3f, 0.3f, 0.3f), //rombo

	};

	//Configuración posiciones Estrellas
	glm::vec3 estrellaspositions[200];
	for (int i = 0; i < 200; i++) {
		if (i % 2 == 0) {
			estrellaspositions[i] = glm::vec3(((rand() % 14) + 1) - (0.075 * i), 9.0f, ((rand() % 13) + 1) - (0.04 * i));
		}
		if (i % 3 == 0) {
			estrellaspositions[i] = glm::vec3(((rand() % 15) + 1) - (0.06 * i), 9.0f, ((rand() % 15) + 1) + (0.05 * i));
		}
		if (i % 5 == 0) {
			estrellaspositions[i] = glm::vec3(((rand() % 14) + 1) - (0.033 * i), 9.0f, ((rand() % 14) + 1) - (0.066 * i));
		}
		if (i % 7 == 0) {
			estrellaspositions[i] = glm::vec3(((rand() % 14) + 1) + (0.019 * i), 9.0f, ((rand() % 15) + 1) - (0.015 * i));
		}
	}

	// first, configure the cube's VAO (and VBO)
	unsigned int VBO, cubeVAO;
	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(cubeVAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
	unsigned int lightCubeVAO;
	glGenVertexArrays(1, &lightCubeVAO);
	glBindVertexArray(lightCubeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// note that we update the lamp's position attribute's stride to reflect the updated buffer data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// load textures (we now use a utility function to keep the code more organized)
	   //hierba
	unsigned int diffuseMap = loadTexture("E:/ProyectoGraficas/textures/hierba2.jpg");
	unsigned int specularMap = loadTexture("E:/ProyectoGraficas/textures/hierba2_specular.jpg");

	//Lamp
	unsigned int diffuseMap1 = loadTexture("E:/ProyectoGraficas/textures/lampa.jpg");
	unsigned int specularMap1 = loadTexture("E:/ProyectoGraficas/textures/lampa_specular.jpg");
	unsigned int emissionMap1 = loadTexture("E:/ProyectoGraficas/textures/lampa_emission.jpg");

	//camino interior
	unsigned int diffuseMap2 = loadTexture("E:/ProyectoGraficas/textures/camino.jpg");
	unsigned int specularMap2 = loadTexture("E:/ProyectoGraficas/textures/camino_specular.jpg");
	//calle
	unsigned int diffuseMap3 = loadTexture("E:/ProyectoGraficas/textures/calle.jpg");
	unsigned int specularMap3 = loadTexture("E:/ProyectoGraficas/textures/calle_specular.jpg");
	//reja
	unsigned int diffuseMap4 = loadTexture("E:/ProyectoGraficas/textures/metal.jpg");
	unsigned int specularMap4 = loadTexture("E:/ProyectoGraficas/textures/metal_specular.jpg");

	//cafe
	unsigned int diffuseMap5 = loadTexture("E:/ProyectoGraficas/textures/brown.jpg");
	unsigned int specularMap5 = loadTexture("E:/ProyectoGraficas/textures/brown_specular.jpg");

	// shader configuration
	cubosShader.use();
	cubosShader.setInt("material.diffuse", 0);
	cubosShader.setInt("material.specular", 1);
	cubosShader.setInt("material.emission", 2);


	const char* numSpot[6] = { "1", "2","3", "4","5" ,"6" };
	string spotstring = "spotLights[";
	string pointstring = "pointLights[";
	string position = "].position";
	string direction = "].direction";
	string ambient = "].ambient";
	string diffuse = "].diffuse";
	string specular = "].specular";
	string constant = "].constant";
	string linear = "].linear";
	string quadratic = "].quadratic";
	string cutOff = "].cutOff";
	string outerCutOff = "].outerCutOff";

	// render loop
	while (!glfwWindowShouldClose(window))
	{
		// per-frame time logic
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		float seno = sin(currentFrame);

		// input
		processInput(window);
		if (seno > 0.04) {
			glClearColor(0.04f, 0.04f, seno * 0.1, 1.0f);
		}


		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		//Estrella Fugaz
		// be sure to activate shader when setting uniforms/drawing objects
		colorShader.use();
		colorShader.setVec3("objectColor", 0.7f, 0.9f, 1.0f);
		colorShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);

		// view/projection transformations
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		colorShader.setMat4("projection", projection);
		colorShader.setMat4("view", view);

		// Movimiento de la estrella
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(sin(currentFrame)*15, 13.0f, sin(currentFrame) * 15));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		colorShader.setMat4("model", model);

		// render the cube
		glBindVertexArray(cubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);


		// be sure to activate shader when setting uniforms/drawing objects
		cubosShader.use();
		cubosShader.setVec3("viewPos", camera.Position);
		cubosShader.setFloat("material.shininess", 32.0f);

		// directional light
		cubosShader.setVec3("dirLight.direction", -0.2f, 15.0f, -0.3f);
		cubosShader.setVec3("dirLight.ambient", 0.1f, 0.1f, 0.1f);
		cubosShader.setVec3("dirLight.diffuse", 0.3f, 0.3f, 0.3f);
		cubosShader.setVec3("dirLight.specular", 0.4f, 0.4f, 0.4f);

		//POINT LIGHTS
		for (int i = 0; i < 20; i++) {
			cubosShader.setVec3(pointstring + std::to_string(i) + position, estrellaspositions[i]);
			cubosShader.setVec3(pointstring + std::to_string(i) + ambient, 0.03f, 0.03f, 0.03f);
			cubosShader.setVec3(pointstring + std::to_string(i) + diffuse, 0.6f, 0.6f, 0.6f);
			cubosShader.setVec3(pointstring + std::to_string(i) + specular, 1.0f, 1.0f, 1.0f);
			cubosShader.setFloat(pointstring + std::to_string(i) + constant, 1.0f);
			cubosShader.setFloat(pointstring + std::to_string(i) + linear, 1.2f);
			cubosShader.setFloat(pointstring + std::to_string(i) + quadratic, 0.032);
		}

		// FlashLight
		cubosShader.setVec3("spotLights[0].position", camera.Position);
		cubosShader.setVec3("spotLights[0].direction", camera.Front);
		cubosShader.setVec3("spotLights[0].ambient", 0.0f, 0.0f, 0.0f);

		if (on % 2 == 0) {
			cubosShader.setVec3("spotLights[0].diffuse", 0.0f, 0.0f, 0.0f);
			cubosShader.setVec3("spotLights[0].specular", 0.0f, 0.0f, 0.0f);
		}
		else {
			cubosShader.setVec3("spotLights[0].diffuse", 1.0f, 1.0f, 1.0f);
			cubosShader.setVec3("spotLights[0].specular", 1.0f, 1.0f, 1.0f);
		}
		cubosShader.setFloat("spotLights[0].constant", 0.5f); //aumenta intensidad al disminuir 
		cubosShader.setFloat("spotLights[0].linear", 0.05); //AGRANDA tamanio al disminuir
		cubosShader.setFloat("spotLights[0].quadratic", 0.032);
		cubosShader.setFloat("spotLights[0].cutOff", glm::cos(glm::radians(12.5f)));
		cubosShader.setFloat("spotLights[0].outerCutOff", glm::cos(glm::radians(15.0f)));


		//SPOTLIGHT FAROLES
		for (int i = 0; i < 6; i++) {
			if (i > 2) {
				cubosShader.setVec3(spotstring + numSpot[i] + position, FarolLucesPositions[i + 3]);
			}
			else {
				cubosShader.setVec3(spotstring + numSpot[i] + position, FarolLucesPositions[i]);
			}
			cubosShader.setVec3(spotstring + numSpot[i] + direction, glm::vec3(0.0f, -1.0f, 0.0f));
			cubosShader.setVec3(spotstring + numSpot[i] + ambient, 0.0f, 0.0f, 0.0f);
			cubosShader.setVec3(spotstring + numSpot[i] + diffuse, 1.0f, 1.0f, 1.0f);
			cubosShader.setVec3(spotstring + numSpot[i] + specular, 1.0f, 1.0f, 1.0f);
			cubosShader.setFloat(spotstring + numSpot[i] + constant, 0.1f); //aumenta intensidad al disminuir 
			cubosShader.setFloat(spotstring + numSpot[i] + linear, 0.05); //AGRANDA tamanio al disminuir
			cubosShader.setFloat(spotstring + numSpot[i] + quadratic, 0.032);
			cubosShader.setFloat(spotstring + numSpot[i] + cutOff, glm::cos(glm::radians(12.5f)));
			cubosShader.setFloat(spotstring + numSpot[i] + outerCutOff, glm::cos(glm::radians(15.0f)));
		}



		// view/projection transformations
		projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		view = camera.GetViewMatrix();
		cubosShader.setMat4("projection", projection);
		cubosShader.setMat4("view", view);

		// world transformation
		model = glm::mat4(1.0f);
		cubosShader.setMat4("model", model);

		//Faroles PALOS
		cubosShader.use();
		// bind diffuse map
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseMap4);
		// bind specular map
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specularMap4);
		glBindVertexArray(cubeVAO);
		for (unsigned int i = 0; i < 24; i++)
		{
			if (i % 4 == 0) {
				escala = 0;
			}
			model = glm::mat4(1.0f);
			if (i > 11) {
				model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			}
			model = glm::translate(model, FarolPositions[i]);
			model = glm::scale(model, FarolEscalas[escala]);
			cubosShader.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			escala++;
		}

		//fAROL LUCES
		// bind diffuse map
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseMap1);
		// bind specular map
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specularMap1);
		// bind emission map
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, emissionMap1);
		for (unsigned int i = 0; i < 6; i++) {
			glm::mat4 model = glm::mat4(1.0f);
			if (i > 2) {
				model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			}
			model = glm::translate(model, FarolLucesPositions[i]);
			model = glm::scale(model, glm::vec3(0.7f, 0.7f, 0.7f));
			cubosShader.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		glBindTexture(GL_TEXTURE_2D, 0);

		//HIERBA
		// bind diffuse map
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseMap);
		// bind specular map
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specularMap);
		glBindVertexArray(cubeVAO);
		//calculate the model matrix for each object and pass it to the shader before drawing
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f, 0.5f, 30.0f));
		cubosShader.setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);


		//CUBO EXTERIOR
		// bind diffuse map
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseMap3);
		// bind specular map
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specularMap3);
		glBindVertexArray(cubeVAO);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -10.1f, 0.0f));
		model = glm::scale(model, glm::vec3(33.0f, 0.5f, 33.0f));
		cubosShader.setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//CAMINO
		cubosShader.use();
		// bind diffuse map
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseMap2);
		// bind specular map
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specularMap2);
		for (unsigned int i = 0; i < 6; i++) {
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(0.0f, -9.96f, 12.5f - (i * 5.0)));
			model = glm::scale(model, glm::vec3(5.0f, 0.5f, 5.0f));
			cubosShader.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		//BARROTES
		cubosShader.use();
		// bind diffuse map
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseMap5);
		// bind specular map
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specularMap5);
		for (unsigned int i = 0; i < 32; i++)
		{
			if (i % 4 == 0) {
				escala2 = 0;
			}
			model = glm::mat4(1.0f);
			model = glm::translate(model, BarrotesPositions[i]);
			model = glm::scale(model, BarrotesEscalas[escala2]);
			cubosShader.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			escala2++;
		}

		//CERCA
		cubosShader.use();
		// bind diffuse map
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseMap4);
		// bind specular map
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specularMap4);

		//fondo vertical
		for (unsigned int i = 0; i < 30; i++) {
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(-14.7f + i, -9.0f, 14.5f));
			model = glm::scale(model, glm::vec3(0.07f, 3.0f, 0.07f));
			cubosShader.setMat4("model", model);
			if (i != 12 && i != 13 && i != 14 && i != 15 && i != 16 && i != 17) {
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}

			//cerca vertical
			model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(-14.7f + i, -9.0f, -14.5f));
			model = glm::scale(model, glm::vec3(0.07f, 3.0f, 0.07f));
			cubosShader.setMat4("model", model);
			if (i != 12 && i != 13 && i != 14 && i != 15 && i != 16 && i != 17) {
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}

			model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(-14.7f, -9.0f, -14.5f + i));
			model = glm::scale(model, glm::vec3(0.07f, 3.0f, 0.07f));
			cubosShader.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);

			model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(14.7f, -9.0f, -14.5f + i));
			model = glm::scale(model, glm::vec3(0.07f, 3.0f, 0.07f));
			cubosShader.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		//Cercas Horizontales
		for (unsigned int i = 0; i < 12; i++) {
			model = glm::mat4(1.0f);
			model = glm::translate(model, posicionesCERCAS[i]);
			if (i > 3) {
				model = glm::scale(model, glm::vec3(12.0f, 0.07f, 0.07f));
			}
			else {
				model = glm::scale(model, glm::vec3(0.07f, 0.07f, 29.3f));
			}
			cubosShader.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		//ESTRELLAS
		lucesShader.use();
		lucesShader.setMat4("projection", projection);
		lucesShader.setMat4("view", view);

		// we now draw as many light bulbs as we have point lights.
		glBindVertexArray(lightCubeVAO);
		for (unsigned int i = 0; i < 200; i++)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model, estrellaspositions[i]);
			model = glm::scale(model, glm::vec3((sin(currentFrame)/2+0.5)*0.05f)); // Make it a smaller cube
			lucesShader.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		//MODELOS
				// don't forget to enable shader before setting uniforms
		modelShader.use();
		modelShader.setVec3("viewPos", camera.Position);
		modelShader.setFloat("material.shininess", 0.6f);

		// directional light
		modelShader.setVec3("dirLight.direction", -0.2f, 15.0f, -0.3f);
		modelShader.setVec3("dirLight.ambient", 0.1f, 0.1f, 0.1f);
		modelShader.setVec3("dirLight.diffuse", 0.3f, 0.3f, 0.3f);
		modelShader.setVec3("dirLight.specular", 0.4f, 0.4f, 0.4f);

		//POINT LIGHTS
		for (int i = 0; i < 200; i++) {
			modelShader.setVec3(pointstring + std::to_string(i) + position, estrellaspositions[i]);
			modelShader.setVec3(pointstring + std::to_string(i) + ambient, 1.00f, 1.00f, 1.00f);
			modelShader.setVec3(pointstring + std::to_string(i) + diffuse, 0.6f, 0.6f, 0.6f);
			modelShader.setVec3(pointstring + std::to_string(i) + specular, 1.0f, 1.0f, 1.0f);
			modelShader.setFloat(pointstring + std::to_string(i) + constant, 2.0f);
			modelShader.setFloat(pointstring + std::to_string(i) + linear, 1.2f);
			modelShader.setFloat(pointstring + std::to_string(i) + quadratic, 0.032);
		}

		// FlashLight
		modelShader.setVec3("spotLights[0].position", camera.Position);
		modelShader.setVec3("spotLights[0].direction", camera.Front);
		modelShader.setVec3("spotLights[0].ambient", 0.0f, 0.0f, 0.0f);

		if (on % 2 == 0) {
			modelShader.setVec3("spotLights[0].diffuse", 0.0f, 0.0f, 0.0f);
			modelShader.setVec3("spotLights[0].specular", 0.0f, 0.0f, 0.0f);
		}
		else {
			modelShader.setVec3("spotLights[0].diffuse", 1.0f, 1.0f, 1.0f);
			modelShader.setVec3("spotLights[0].specular", 1.0f, 1.0f, 1.0f);
		}
		modelShader.setFloat("spotLights[0].constant", 1.0f); //aumenta intensidad al disminuir 
		modelShader.setFloat("spotLights[0].linear", 0.09); //AGRANDA tamanio al disminuir
		modelShader.setFloat("spotLights[0].quadratic", 0.032);
		modelShader.setFloat("spotLights[0].cutOff", glm::cos(glm::radians(12.5f)));
		modelShader.setFloat("spotLights[0].outerCutOff", glm::cos(glm::radians(15.0f)));


		//SPOTLIGHT FAROLES
		for (int i = 0; i < 6; i++) {
			if (i > 2) {
				modelShader.setVec3(spotstring + numSpot[i] + position, FarolLucesPositions[i + 3]);
			}
			else {
				modelShader.setVec3(spotstring + numSpot[i] + position, FarolLucesPositions[i]);
			}
			modelShader.setVec3(spotstring + numSpot[i] + direction, glm::vec3(0.0f, -1.0f, 0.0f));
			modelShader.setVec3(spotstring + numSpot[i] + ambient, 0.0f, 0.0f, 0.0f);
			modelShader.setVec3(spotstring + numSpot[i] + diffuse, 1.0f, 1.0f, 1.0f);
			modelShader.setVec3(spotstring + numSpot[i] + specular, 1.0f, 1.0f, 1.0f);
			modelShader.setFloat(spotstring + numSpot[i] + constant, 0.5f); //aumenta intensidad al disminuir 
			modelShader.setFloat(spotstring + numSpot[i] + linear, 0.1); //AGRANDA tamanio al disminuir
			modelShader.setFloat(spotstring + numSpot[i] + quadratic, 0.032);
			modelShader.setFloat(spotstring + numSpot[i] + cutOff, glm::cos(glm::radians(12.5f)));
			modelShader.setFloat(spotstring + numSpot[i] + outerCutOff, glm::cos(glm::radians(15.0f)));
		}


		// view/projection transformations
		projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		view = camera.GetViewMatrix();
		modelShader.setMat4("projection", projection);
		modelShader.setMat4("view", view);

		//2: Perrito
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-8.0f, -8.75f, 4.0f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit oo big for our scene, so scale it down
		model = glm::rotate(model, glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		modelShader.setMat4("model", model);
		ourModel2.Draw(modelShader);


		//LUCES 
		modelShader.use();
		modelShader.setVec3("viewPos", camera.Position);
		modelShader.setFloat("material.shininess", 32.0f);
		////1: Pajarito
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(4.5f, -7.1f, -3.1f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
		modelShader.setMat4("model", model);
		ourModel1.Draw(modelShader);

		//3:Flor Blanca
		for (int i = 0; i < size(flores); i++) {
			model = glm::mat4(1.0f);
			model = glm::translate(model, flores[i]); // translate it down so it's at the center of the scene
			model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.02f));	// it's a bit oo big for our scene, so scale it down
			modelShader.setMat4("model", model);
			ourModel3.Draw(modelShader);
		}
		//Flor naranja
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-12.0f, -9.8f, 12.0f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(0.03f, 0.03f, 0.03f));	// it's a bit oo big for our scene, so scale it down
		modelShader.setMat4("model", model);
		ourModel4.Draw(modelShader);

		//6: Mariposa
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(sin(currentFrame) * 14, -6.0f + cos(currentFrame) * 3, cos(currentFrame) * 14)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(0.008f, 0.008f, 0.008f));	// it's a bit too big for our scene, so scale it down
		modelShader.setMat4("model", model);
		ourModel6.Draw(modelShader);

		//7: Árbol
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-12.0f, -9.8f, -10.0f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(1.2f, 1.2f, 1.2f));	// it's a bit too big for our scene, so scale it down
		modelShader.setMat4("model", model);
		ourModel7.Draw(modelShader);

		//LUCES PARA BANCO
		// directional light
		modelShader.use();
		modelShader.setVec3("viewPos", camera.Position);
		modelShader.setFloat("material.shininess", 78.125f);

		modelShader.setVec3("dirLight.direction", -0.2f, 15.0f, -0.3f);
		modelShader.setVec3("dirLight.ambient", 0.19225f, 0.19225f, 0.19225f);
		modelShader.setVec3("dirLight.diffuse", 0.50754f, 0.50754f, 0.50754f);
		modelShader.setVec3("dirLight.specular", 0.508273f, 0.508273f, 0.508273f);

		//5: Banco
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(5.0f, -9.5f, 0.0f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(0.8f, 0.8f, 0.8f));	// it's a bit too big for our scene, so scale it down
		modelShader.setMat4("model", model);
		ourModel5.Draw(modelShader);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	// optional: de-allocate all resources once they've outlived their purpose:
	glDeleteVertexArrays(1, &cubeVAO);
	glDeleteVertexArrays(1, &lightCubeVAO);
	glDeleteBuffers(1, &VBO);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
		on = 1;
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
		on = 2;
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

//Exercise 14 Task 2
// utility function for loading a 2D texture from file
// ---------------------------------------------------
unsigned int loadTexture(char const* path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
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

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
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