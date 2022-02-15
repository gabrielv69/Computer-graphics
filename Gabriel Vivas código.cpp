///librerias
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <learnopengl/shader_s.h>
#include <iostream>


//Declaramos funciones
void framebuffer_size_callback(GLFWwindow* window, int width, int height);//Permite controlar cambios en tamaño de la ventana
void processInput(GLFWwindow* window); //Chequea si hay algun ingreso por teclado 

// Declaramos ancho y largo de la pantalla a mostrar
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

int main()
{
    // glfw: initicializar y configurar
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //Perfil de MACS
#endif

    // glfw window creation
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Gabriel Vivas- Corredor", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window); //Definimos el contexto con el que se va a trabajar, en este caso el deifnido en windows
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);//Definimos el contexto con el que se va a trabajar, en este caso el deifnido en windows

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Establecemos las rutas de vertex y fragment shaders
    Shader ourShader("E:/Universidad/Documents/Computación Gráfica/C2 OGT 222 TG2D Shaders2-20210106/shaders/shader_corredor.vs",
        "E:/Universidad/Documents/Computación Gráfica/C2 OGT 222 TG2D Shaders2-20210106/shaders/shader_corredor.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float Triangle0[] = { //Cabeza 1
        //posiciones        color
     -0.5f, 0.65f, 0.0f,  1.0f, 0.8f, 0.6f, // left  1
      -0.18f, 0.85f, 0.0f, 1.0f, 0.8f, 0.6f,// right 1
      -0.45f, 0.91f, 0.0f,  1.0f, 0.8f, 0.6f // top  1 
    };
    float Triangle1[] = { //Cabeza2
        //posiciones        color
         -0.5f, 0.65f, 0.0f,  1.0f, 0.8f, 0.6f,// left  2
        -0.18f, 0.85f, 0.0f,  1.0f, 0.8f, 0.6f,// right 2
        -0.24f, 0.59f, 0.0f,  1.0f, 0.8f, 0.6f // top  2
    };
    float Triangle2[] = { //triangulo cuerpo 1 
             //posiciones        color
        -0.8f, 0.53f, 0.0f,  0.0f, 0.6f, 0.5f, // left  3
       0.0f, 0.62f, 0.0f,0.0f, 0.6f, 0.5f,  // right 3
       -0.3f, 0.17f, 0.0f,  0.0f, 0.0f, 1.0f   // top  3
    };
    float Triangle3[] = { //triangulo cuerpo 2
        //posiciones        color
       -0.48f, -0.11f, 0.0,  0.0f, 0.6f, 0.5f, // left  4
       0.31f, -0.0f, 0.0f, 0.0f, 0.6f, 0.5f,  // right 4
       -0.18f, 0.35f, 0.0f, 0.0f, 0.0f, 1.0f // top  4
    };
    float Triangle4[] = { // pierna izquierda
         //posiciones           color
         -0.46f, -0.5f, 0.0f, 0.1f, 0.05f, 0.0f, // left  5
        -0.17f, -0.065f, 0.0f, 0.1f, 0.05f, 0.0f,  // right 5
        -0.48f, -0.11f, 0.0, 0.0f, 0.0f, 1.0f  // top  5
    };
    float Triangle5[] = { // pie izquierdo
        //posiciones           color
        -0.77f, -0.71f, 0.0f,   1.0f, 0.0f, 0.0f, // left  6
       -0.54f, -0.775f, 0.0f,  0.0f, 1.0f, 0.0f,// right 6
      -0.46f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top  6
    };
    float Triangle6[] = { //Pierna derecha 1
        //posiciones           color
       -0.09f, -0.055f, 0.0f,  0.1f, 0.05f, 0.0f,// left  7
       0.31f, -0.29f, 0.0f,   0.1f, 0.05f, 0.0f,// right 7
       0.25f, -0.01f, 0.0f, 0.0f, 0.0f, 1.0f    // top  7
    };
    float Triangle7[] = { //Pierna derecha 2
           //posiciones           color
       0.31f, -0.29f, 0.0f,  0.1f, 0.05f, 0.0f,// left  8
       0.59f, -0.24f, 0.0f,  0.1f, 0.05f, 0.0f,// right 8
      0.25f,-0.01f, 0.0f, 0.0f, 0.0f, 1.0f   // top  8
    };
    float Triangle8[] = { //Pie derecho
           //posiciones           color
       0.43f, -0.13f, 0.0f,  1.0f, 0.0f, 0.0f, // left  9
       0.8f, -0.38f, 0.0f,  0.0f, 1.0f, 0.0f,// right 9
       0.79f, -0.1f, 0.0f,  0.0f, 0.0f, 1.0f  // top  9
    };

    unsigned int VBOs[9], VAOs[9];
    glGenVertexArrays(9, VAOs);
    glGenBuffers(9, VBOs);
    for (int i = 0; i < 9; i++) {
        glBindVertexArray(VAOs[i]);
        glBindBuffer(GL_ARRAY_BUFFER, VBOs[i]);
        if (i == 0) { glBufferData(GL_ARRAY_BUFFER, sizeof(Triangle0), Triangle0, GL_STATIC_DRAW); }
        if (i == 1) { glBufferData(GL_ARRAY_BUFFER, sizeof(Triangle1), Triangle1, GL_STATIC_DRAW); }
        if (i == 2) { glBufferData(GL_ARRAY_BUFFER, sizeof(Triangle2), Triangle2, GL_STATIC_DRAW); }
        if (i == 3) { glBufferData(GL_ARRAY_BUFFER, sizeof(Triangle3), Triangle3, GL_STATIC_DRAW); }
        if (i == 4) { glBufferData(GL_ARRAY_BUFFER, sizeof(Triangle4), Triangle4, GL_STATIC_DRAW); }
        if (i == 5) { glBufferData(GL_ARRAY_BUFFER, sizeof(Triangle5), Triangle5, GL_STATIC_DRAW); }
        if (i == 6) { glBufferData(GL_ARRAY_BUFFER, sizeof(Triangle6), Triangle6, GL_STATIC_DRAW); }
        if (i == 7) { glBufferData(GL_ARRAY_BUFFER, sizeof(Triangle7), Triangle7, GL_STATIC_DRAW); }
        if (i == 8) { glBufferData(GL_ARRAY_BUFFER, sizeof(Triangle8), Triangle8, GL_STATIC_DRAW); }
        // position attribute1
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
    }

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window)) {
        
        processInput(window); // procesamiento entradas teclado

        // render
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //Fondo Blanco
        glClear(GL_COLOR_BUFFER_BIT);

        float timeValue = glfwGetTime();//Variable del tiempo
        float value0 = sin(timeValue) / 1.0f ;//Variable de modificacion 
        //std::cout << value0 << std::endl;

        if (value0>0) //Dado que la funcion seno varia entre valores positivo y negativos, 
            //establezco que cambie de direccion cada vez que sean mayores o menores a cero
        {
            // render the triangle
            ourShader.use();

            //Configuracion inicial de la imagen
            ourShader.setInt("xChange", 1);
            ourShader.setInt("yChange", 1);
            ourShader.setInt("zChange", 1);

            //cambios en los colores de la imagen

            //ourShader.setFloat("changeR", value0);
            //ourShader.setFloat("changeG", value0);
            ourShader.setFloat("changeB", value0);

            for (int i = 0; i < 9; i++) {
                ourShader.setFloat("xOffset", -value0);// se mueve a la izquierda
                ourShader.setFloat("yOffset", value0); // se mueve hacia arriba
                glBindVertexArray(VAOs[i]);
                glDrawArrays(GL_TRIANGLES, 0, 3);
            }
        }
        else {
            // render the triangle
            ourShader.use();

            //Configuracion inicial de la imagen
            ourShader.setInt("xChange", -1); //Invertimos la posicion de X, el resto se mantiene
            ourShader.setInt("yChange", 1);
            ourShader.setInt("zChange", 1);

            //cambios en los colores de la imagen

            //ourShader.setFloat("changeR", value0);
            //ourShader.setFloat("changeG", value0);
            ourShader.setFloat("changeB", value0);

            for (int i = 0; i < 9; i++) {
                ourShader.setFloat("xOffset", value0);// se mueve a la derecha
                ourShader.setFloat("yOffset", value0); // se mueve hacia arriba
                //Añadimos los vao a renderizar
                glBindVertexArray(VAOs[i]);
                glDrawArrays(GL_TRIANGLES, 0, 3);
            }

        }

            
    
        //glfw: intercambiar búferes y sondear eventos de E / S
        glfwSwapBuffers(window);
        glfwPollEvents();
        
        
    }

    // Borramos el VAO Y VBO usados
    glDeleteVertexArrays(9, VAOs);
    glDeleteBuffers(9, VBOs);
    // glfw: terminar, borrando todos los recursos GLFW previamente asignados.
    glfwTerminate();
    return 0;
}

// procesamiento de ingresos de teclado 
void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    //Hacemos que con las teclas 1 y 2 cambie a solo aristas o con color
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)// SOLO ARISTAS
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}


//Verifica cambios realizados en la ventana
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}