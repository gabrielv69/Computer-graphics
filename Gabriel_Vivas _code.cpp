//Gabriel Vivas

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <learnopengl/shader_s.h>
#define STB_IMAGE_IMPLEMENTATION 
#include <learnopengl/stb_image.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 1600;
const unsigned int SCR_HEIGHT = 900;

float scale= 0.5f;
float numbercats = 0.0f;

int main(){
    // glfw: initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    // glfw window creation
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Fondo Pantalla - Gabriel Vivas", NULL, NULL);
    if (window == NULL){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1; }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1; }

    // build and compile our shader program
    Shader ourShader("E:/Universidad/Documents/Computación Gráfica/Tarea B2T1_Vivas_Zambrano/Gabriel_Vivas/shaders/vertex_shaderB2T1.vs", 
        "E:/Universidad/Documents/Computación Gráfica/Tarea B2T1_Vivas_Zambrano/Gabriel_Vivas/shaders/fragment_shaderB2T1.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        // positions                color                             texture coords
         0.2f,  0.2f, 0.0f,     1.0f, 0.6f, 0.2f,    1.0f, 1.0f, // top right
         0.2f, -0.2f, 0.0f,     0.0f, 0.2f, 1.0f,   1.0f, 0.0f, // bottom right
        -0.2f, -0.2f, 0.0f,     1.0f, 0.6f, 0.2f,    0.0f, 0.0f, // bottom left
        -0.2f,  0.2f, 0.0f,     0.0f, 1.0f, 0.2f,    0.0f, 1.0f  // top left 
    };
    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    // load and create textures
    unsigned int texture1;
    // texture 1
    // ---------
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
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    unsigned char* data = stbi_load("E:/Universidad/Documents/Computación Gráfica/Tarea B2T1_Vivas_Zambrano/Gabriel_Vivas/textures/cat.png", 
        &width, &height, &nrChannels, 0);   
    if (data)
    {
        // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else{
        std::cout << "Failed to load texture" << std::endl; }

    stbi_image_free(data);


    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    ourShader.use(); 
    ourShader.setInt("texture1", 0);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        float timeValue = glfwGetTime();//Variable del tiempo
        float visible = sin(timeValue) / 4.0f + 0.4f; //Variable de modificacion
        float movimiento = sin(timeValue); //Variable de modificacion

        processInput(window);// input
        // render
        glClearColor(0.6f, 1.0f, 1.0f, 1.0f); //Fondo Blanco
        glClear(GL_COLOR_BUFFER_BIT);

        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        //visibilidad del color e imagen
        ourShader.setFloat("visible", visible);


        //figura1
        glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        transform = glm::translate(transform, glm::vec3(movimiento, movimiento, 0.0f));
        transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
        // render container
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        //Figura2
        transform = glm::mat4(1.0f); //RESET THE TRANSFORMATION MATRIX
        transform = glm::translate(transform, glm::vec3(-movimiento, movimiento, 0.0f));
        transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    
        //Figura3
        transform = glm::mat4(1.0f); //RESET THE TRANSFORMATION MATRIX
        transform = glm::translate(transform, glm::vec3(movimiento, 0.0f, 0.0f));
        transform = glm::scale(transform, glm::vec3(scale, scale, scale));
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &transform[0][0]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
       
        //Figura4
        transform = glm::mat4(1.0f); //RESET THE TRANSFORMATION MATRIX
        transform = glm::translate(transform, glm::vec3(0.0f, movimiento, 0.0f));
        transform = glm::scale(transform, glm::vec3(scale, scale, scale));
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &transform[0][0]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        //Figura5
        transform = glm::mat4(1.0f); //RESET THE TRANSFORMATION MATRIX
        transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        transform = glm::translate(transform, glm::vec3(0.0f, 0.5f, 0.0f));
        transform = glm::scale(transform, glm::vec3(0.5f, 0.5f, 0.5f));
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &transform[0][0]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

   
        for (int i = 0; i < numbercats; i++) {

            transform = glm::mat4(1.0f); //RESET THE TRANSFORMATION MATRIX
            transform = glm::rotate(transform, (float)glfwGetTime()*i, glm::vec3(0.0f, 0.0f, 1.0f));
            transform = glm::translate(transform, glm::vec3(i*0.1, i*0.1, 0.0f));
            transform = glm::scale(transform, glm::vec3(0.5f, 0.5f, 0.5f));
            glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &transform[0][0]);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }
        


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow *window){
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        scale = scale + 0.001f; // change this value accordingly (might be too slow or too fast based on system hardware)
        if (scale >= 2.0f)
            scale = 2.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        scale = scale - 0.001f;// change this value accordingly (might be too slow or too fast based on system hardware)
        if (scale <= 0.0f)
            scale = 0.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        numbercats = numbercats  - 0.01f;// change this value accordingly (might be too slow or too fast based on system hardware)
        if (numbercats <= 0.0f)
            numbercats = 0.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        numbercats = numbercats + 0.01f;// change this value accordingly (might be too slow or too fast based on system hardware)
        if (numbercats >= 10.0f)
            numbercats = 10.0f;
    }

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);}