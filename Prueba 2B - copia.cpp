#include <glad/glad.h>
#include <GLFW/glfw3.h>              //Agregar librerías necesarias para la compilación
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION //Add to use stb_image.h
#include <learnopengl/stb_image.h> //Add to use stb_image.h
#include <learnopengl/shader.h>
#include <learnopengl/camera.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 900;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

//numbertnts
float numbertnts = 5.0f;
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
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "CandyCraft-Vivas-Zambrano", NULL, NULL);
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


    // build and compile our shader zprogram
    // ------------------------------------
    Shader ourShader("E:/Universidad/Documents/Computación Gráfica/Prueba B2/CÓDIGO/shaders/vertex.vs",
        "E:/Universidad/Documents/Computación Gráfica/Prueba B2/CÓDIGO/shaders/fragment.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
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
        // positions          // texture coords

        //Cara inferior -z
    -0.5f, -0.5f, -0.5f,  0.05f, 0.33f,//sup iz
     0.5f, -0.5f, -0.5f,  0.27f, 0.32f, //sup der
     0.5f,  0.5f, -0.5f,  0.27f, 0.68f, //inf der
     0.5f,  0.5f, -0.5f,  0.27f, 0.68f,
    -0.5f,  0.5f, -0.5f,  0.05f, 0.68f,// inferior iz
    -0.5f, -0.5f, -0.5f,  0.05f, 0.33f,

    //Cara superior +z
    -0.5f, -0.5f,  0.5f,  0.08f, 0.67f,//sup iz
     0.5f, -0.5f,  0.5f,  0.08f, 0.42f,//sup der
     0.5f,  0.5f,  0.5f,  0.3f, 0.42f,//inf der
     0.5f,  0.5f,  0.5f,  0.3f, 0.42f,
    -0.5f,  0.5f,  0.5f,  0.3f, 0.67f,// inferior iz
    -0.5f, -0.5f,  0.5f,  0.08f, 0.67f,

    //cara -x
    -0.5f,  0.5f,  0.5f,  0.08f, 0.67f,
    -0.5f,  0.5f, -0.5f,  0.08f, 0.42f,
    -0.5f, -0.5f, -0.5f,  0.3f, 0.42f,
    -0.5f, -0.5f, -0.5f,  0.3f, 0.42f,
    -0.5f, -0.5f,  0.5f,  0.3f, 0.67f,
    -0.5f,  0.5f,  0.5f,   0.08f, 0.67f,

    //cara +x
     0.5f,  0.5f,  0.5f,  0.08f, 0.67f,
     0.5f,  0.5f, -0.5f,  0.08f, 0.42f,
     0.5f, -0.5f, -0.5f,  0.3f, 0.42f,
     0.5f, -0.5f, -0.5f,  0.3f, 0.42f,
     0.5f, -0.5f,  0.5f,  0.3f, 0.67f,
     0.5f,  0.5f,  0.5f,  0.08f, 0.67f,

     //cara -y 
    -0.5f, -0.5f, -0.5f,  0.3f, 0.67f,
     0.5f, -0.5f, -0.5f,  0.51f, 0.67f,
     0.5f, -0.5f,  0.5f,  0.51f, 0.42f,
     0.5f, -0.5f,  0.5f,  0.51f, 0.42f,
    -0.5f, -0.5f,  0.5f,  0.3f, 0.42f,
    -0.5f, -0.5f, -0.5f,  0.3f, 0.67f,
    //cara +y 
    -0.5f,  0.5f, -0.5f,  0.3f, 0.67f,
     0.5f,  0.5f, -0.5f,  0.51f, 0.67f,
     0.5f,  0.5f,  0.5f,  0.51f, 0.93f,
     0.5f,  0.5f,  0.5f,  0.51f, 0.93f,
    -0.5f,  0.5f,  0.5f,  0.3f, 0.93f,
    -0.5f,  0.5f, -0.5f,  0.3f, 0.67f
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


    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);











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
    unsigned char* data = stbi_load("E:/Universidad/Documents/Computación Gráfica/Prueba B2/CÓDIGO/textures/ic.png", &width, &height, &nrChannels, 0);
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
    data = stbi_load("E:/Universidad/Documents/Computación Gráfica/Prueba B2/CÓDIGO/textures/candy.png", &width, &height, &nrChannels, 0);
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
    data = stbi_load("E:/Universidad/Documents/Computación Gráfica/Prueba B2/CÓDIGO/textures/Texture3.jpg", &width, &height, &nrChannels, 0);
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
       // --------------------
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



        //TRABAJANDO CON LAS TEXTURAS
        //TEXTURA 1: 

        // activate shader
        ourShader.use();
        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        ourShader.setInt("texture1", 0);


        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 1.0f, 100.0f);
        ourShader.setMat4("projection", projection);

        // camera/view transformation
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setMat4("view", view);

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

        //TEXTURA PROFE: 

        // activate shader
        ourShader.use();
        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture3);


        for (unsigned int i = 0; i < 2; i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i+6]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            ourShader.setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }



        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);


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

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        numbertnts = numbertnts - 0.01f;// change this value accordingly (might be too slow or too fast based on system hardware)
        if (numbertnts <= 5.0f)
            numbertnts = 5.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        numbertnts = numbertnts + 0.01f;// change this value accordingly (might be too slow or too fast based on system hardware)
        if (numbertnts >= 20.0f)
            numbertnts = 20.0f;
    }



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