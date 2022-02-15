#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/shader.h>
#include <learnopengl/camera.h>

#define STB_IMAGE_IMPLEMENTATION 
#include <learnopengl/stb_image.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

//Exercise 13
//lighting
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

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
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Vivas_Gabriel_2B", NULL, NULL);
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
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    // configure global opengl state
    //Exercise 11 Task 3
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

	//Exercise 13 Task 1
    // build and compile our shader zprogram
    // ------------------------------------
    Shader ourShader("E:/Universidad/Documents/Computaci�n Gr�fica/Prueba B2/C�DIGO/shaders/vertex.vs",
        "E:/Universidad/Documents/Computaci�n Gr�fica/Prueba B2/C�DIGO/shaders/fragment.fs");

	Shader lightCubeShader("E:/Universidad/Documents/Computaci�n Gr�fica/Prueba B2/C�DIGO/shaders/vertex_lightcube.vs", 
        "E:/Universidad/Documents/Computaci�n Gr�fica/Prueba B2/C�DIGO/shaders/fragment_lightcube.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    float vertices[] = {
        // positions          // texture coords
     0.5f,  0.5f,-0.5f,  0.09f, 0.67f,
    -0.5f, 0.5f, -0.5f,  0.30f, 0.67f,
    -0.5f,  0.5f, 0.5f,  0.30f, 0.42f,
    -0.5f,  0.5f, 0.5f,  0.30f, 0.42f,
     0.5f,  0.5f, 0.5f,  0.09f, 0.42f,
     0.5f,  0.5f,-0.5f,  0.09f, 0.67f,


    -0.5f,  0.5f,-0.5f,   0.30f, 0.67f, //1
    -0.5f, -0.5f,-0.5f,   0.51f, 0.67f, //4
    -0.5f, -0.5f, 0.5f,   0.51f, 0.42f, //3
    -0.5f, -0.5f, 0.5f,   0.51f, 0.42f, //3
    -0.5f,  0.5f, 0.5f,   0.30f, 0.42f, //2
    -0.5f,  0.5f,-0.5f,   0.30f, 0.67f, //1

    -0.5f, -0.5f, -0.5f,  0.51f, 0.67f,
     0.5f, -0.5f, -0.5f,  0.72f, 0.67f,
     0.5f, -0.5f,  0.5f,  0.72f, 0.42f,
     0.5f, -0.5f,  0.5f,  0.72f, 0.42f,
    -0.5f, -0.5f,  0.5f,  0.51f, 0.42f,
    -0.5f, -0.5f, -0.5f,  0.51f, 0.67f,

     0.5f,-0.5f,-0.5f,   0.72f, 0.67f,
     0.5f,0.5f, -0.5f,   0.93f, 0.67f,
     0.5f,0.5f,  0.5f,   0.93f, 0.42f,
     0.5f,0.5f,  0.5f,   0.93f, 0.42f,
     0.5f,-0.5f, 0.5f,   0.72f, 0.42f,
     0.5f,-0.5f,-0.5f,   0.72f, 0.67f,

    -0.5f,  0.5f,  0.5f,  0.30f, 0.42f,
    -0.5f, -0.5f,  0.5f,  0.51f, 0.42f,
     0.5f, -0.5f,  0.5f,  0.51f, 0.17f,
     0.5f, -0.5f,  0.5f,  0.51f, 0.17f,
     0.5f,  0.5f,  0.5f,  0.30f, 0.17f,
    -0.5f,  0.5f,  0.5f,  0.30f, 0.42f,

     0.5f,  0.5f, -0.5f,   0.30f, 0.93f,
     0.5f, -0.5f, -0.5f,   0.51f, 0.93f,
    -0.5f, -0.5f, -0.5f,   0.51f, 0.68f,
    -0.5f, -0.5f, -0.5f,   0.51f, 0.68f,
    -0.5f,  0.5f, -0.5f,   0.30f, 0.68f,
     0.5f,  0.5f, -0.5f,   0.30f, 0.93f,
    };



    float vertices2[] = {

     -0.5f, -0.5f, -0.5f,  0.5f, 0.68f,//sup iz
     0.5f, -0.5f, -0.5f,  0.73f, 0.68f, //sup der
     0.5f,  0.5f, -0.5f,  0.73f, 0.94f, //inf der
     0.5f,  0.5f, -0.5f,  0.73f, 0.94f,
    -0.5f,  0.5f, -0.5f,  0.5f, 0.94f,// inferior iz
    -0.5f, -0.5f, -0.5f,  0.5f, 0.68f,

    //Cara superior +z
    -0.5f, -0.5f,  0.5f,  0.5f, 0.06f,//sup iz
     0.5f, -0.5f,  0.5f,  0.73f, 0.06f,//sup der
     0.5f,  0.5f,  0.5f,  0.73f, 0.32f,//inf der
     0.5f,  0.5f,  0.5f,  0.73f, 0.32f,
    -0.5f,  0.5f,  0.5f,  0.5f, 0.32f,// inferior iz
    -0.5f, -0.5f,  0.5f,  0.5f, 0.06f,

    //cara -x no
    -0.5f,  0.5f,  0.5f, 0.5f, 0.32f,
    -0.5f,  0.5f, -0.5f, 0.73f, 0.32f,
    -0.5f, -0.5f, -0.5f,  0.5f, 0.68f, //INF IZ
    -0.5f, -0.5f, -0.5f,  0.5f, 0.68f,//INF IZ
    -0.5f, -0.5f,  0.5f,  0.73f, 0.68f, 
    -0.5f,  0.5f,  0.5f,   0.5f, 0.32f,

    //cara +x no
     0.5f,  0.5f,  0.5f,  0.5f, 0.32f,
     0.5f,  0.5f, -0.5f,  0.73f, 0.32f,
     0.5f, -0.5f, -0.5f,  0.73f, 0.68f,
     0.5f, -0.5f, -0.5f,  0.73f, 0.68f,
     0.5f, -0.5f,  0.5f,  0.5f, 0.68f,
     0.5f,  0.5f,  0.5f,   0.5f, 0.32f,

     //cara -y 
    -0.5f, -0.5f, -0.5f,  0.5f, 0.32f,
     0.5f, -0.5f, -0.5f,  0.73f, 0.32f,
     0.5f, -0.5f,  0.5f,  0.73f, 0.68f,
     0.5f, -0.5f,  0.5f,  0.73f, 0.68f,
    -0.5f, -0.5f,  0.5f,  0.5f, 0.68f,
    -0.5f, -0.5f, -0.5f,  0.5f, 0.32f,
    //cara +y  
    -0.5f,  0.5f, -0.5f,  0.5f, 0.68f,//sup iz
     0.5f,  0.5f, -0.5f,  0.73f, 0.68f,//sup der
     0.5f,  0.5f,  0.5f,  0.73f, 0.32f,//inf der
     0.5f,  0.5f,  0.5f,  0.73f, 0.32f,
    -0.5f,  0.5f,  0.5f,  0.5f, 0.32f,// inferior iz
    -0.5f,  0.5f, -0.5f,  0.5f, 0.68f
    };


    glm::vec3 cubePositions[] = {
    glm::vec3(-4.0f, 4.0f, 0.0f),
    glm::vec3(4.0f, 4.0f, 0.0f),
    glm::vec3(-4.0f, -4.0f, 0.0f),
    glm::vec3(2.0f,-2.0f,0.0f),
    glm::vec3(-2.0f, 2.0f, 0.0f),
    glm::vec3(2.0f, 2.0f, 0.0f),
    glm::vec3(1.3f, -2.0f, -2.5f),
    glm::vec3(-1.5f,  2.0f, 2.5f)
    };

	
	//Exercise 13 Task 1
	unsigned int VBO, VAO, VAO1;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(VAO);
	
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //vao1
    glGenVertexArrays(1, &VAO1);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

	
	// second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    unsigned int lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);
	
	 // we only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need (it's already bound, but we do it again for educational purposes)
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
	

    // load and create a texture 
    // -------------------------
    unsigned int texture1, texture2, texture3, texture4, texture5;
    // texture 1
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    //stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    unsigned char* data = stbi_load("E:/Universidad/Documents/Computaci�n Gr�fica/Prueba B2/C�DIGO/textures/ic.png", &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else { std::cout << "Failed to load texture" << std::endl; }
    stbi_image_free(data);


    //texture 4
    glGenTextures(1, &texture4);
    glBindTexture(GL_TEXTURE_2D, texture4);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    data = stbi_load("E:/Universidad/Documents/Computaci�n Gr�fica/Prueba B2/C�DIGO/textures/candy.png", &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    //texture 3 PROFE
    glGenTextures(1, &texture3);
    glBindTexture(GL_TEXTURE_2D, texture3);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    data = stbi_load("E:/Universidad/Documents/Computaci�n Gr�fica/Prueba B2/C�DIGO/textures/Texture3.jpg", &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);


	
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {

        float movimiento = sin(glfwGetTime()); //Variable de modificacion
        // per-frame time logic
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        float scale = sin(currentFrame);
        float color = sin(currentFrame) / 8.0f + 0.5;

        if (color >= 0) {
            color = color;
        }
        else {
            color = color * (-1);
        }


        // input
        // -----
        processInput(window);        
		
		        // render
        // ------
        glClearColor(0.9f, 0.6f, color, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
       // be sure to activate shader when setting uniforms/drawing objects
        ourShader.use();
        ourShader.setInt("texture1", 0);

        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 1.0f, 100.0f);
        ourShader.setMat4("projection", projection);

        // camera/view transformation
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setMat4("view", view);
        //TEXTURA 1: 

            // activate shader
        ourShader.use();
        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        // render the cube
        glBindVertexArray(VAO);

        for (unsigned int i = 0; i < 3; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);

            if (i == 0) {
                model = glm::rotate(model, glm::radians(180.0f), glm::vec3(scale, scale, scale));
                model = glm::translate(model, cubePositions[i]);
            }
            if (i == 1) {
                model = glm::rotate(model, glm::radians(180.0f), glm::vec3(-scale, -scale, -scale));
                model = glm::translate(model, cubePositions[i]);
            }
            if (i == 2) {
                model = glm::rotate(model, glm::radians(180.0f), glm::vec3(scale, -scale, -scale));
                model = glm::translate(model, cubePositions[i]);
            }

            model = glm::scale(model, glm::vec3(movimiento, movimiento, movimiento));
            ourShader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        //TEXTURA 4: 

        // activate shader
        ourShader.use();
        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture4);
        // render the cube
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        for (unsigned int i = 0; i < 3; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);


            if (i == 0) {
                model = glm::rotate(model, glm::radians(180.0f), glm::vec3(scale, scale, scale));
                model = glm::translate(model, cubePositions[i + 3]);
            }
            if (i == 1) {
                model = glm::rotate(model, glm::radians(180.0f), glm::vec3(-scale, -scale, -scale));
                model = glm::translate(model, cubePositions[i + 3]);
            }
            if (i == 2) {
                model = glm::rotate(model, glm::radians(180.0f), glm::vec3(scale, -scale, -scale));
                model = glm::translate(model, cubePositions[i + 3]);
            }
            ourShader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);

        }
        // render the cube
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //TEXTURA PROFE: 
        glBindVertexArray(VAO1);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        // activate shader
        ourShader.use();
        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture3);
        for (unsigned int i = 0; i < 2; i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i + 6]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            model = glm::translate(model, cubePositions[i + 3]);
            if (i == 0) {
                angle = glfwGetTime() * 50.0f;
                model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
            }
            ourShader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }


        // world transformation
        glm::mat4 model = glm::mat4(1.0f);
        ourShader.setMat4("model", model);



        // also draw the lamp object
        lightCubeShader.use();
       lightCubeShader.setMat4("projection", projection);
        lightCubeShader.setMat4("view", view);
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
        lightCubeShader.setMat4("model", model);

        glBindVertexArray(lightCubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();		
		
	}	
	
	    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteVertexArrays(1, &lightCubeVAO);
    glDeleteBuffers(1, &VBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
	
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
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

    //If I want to stay in ground level (xz plane)
    //camera.Position.y = 0.0f;
	
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