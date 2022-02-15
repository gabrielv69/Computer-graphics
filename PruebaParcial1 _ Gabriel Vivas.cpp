
//Prueba 1
//Gabriel Vivas

//Con la tecla 2 se ven solo las aristas y con 1 se las pinta






#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";



//Colores
const char* fragmentShader1Source = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.4f, 0.4f, 1.0f);\n" // Rosado Cabeza
"}\n\0";

const char* fragmentShader2Source = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n" //Amarillo
"}\n\0";

const char* fragmentShader3Source = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.3f, 1.0f, 0.42f, 1.0f);\n" //Verde cuerpo
"}\n\0";

const char* fragmentShader4Source = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.53f, 1.0f, 0.3f, 1.0f);\n" //Verde pierna
"}\n\0";


const char* fragmentShader5Source = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.0f, 0.67f, 0.8f, 1.0f);\n" //Celeste
"}\n\0";


const char* fragmentShader6Source = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.5f, 0.4f, 1.0f, 1.0f);\n" //Morado
"}\n\0";


const char* fragmentShader7Source = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.6f, 0.2f, 1.0f);\n" //Naranja
"}\n\0";

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Gabriel Vivas - Prueba - fig. Corredor", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    // build and compile our shader program
    // ------------------------------------
    // we skipped compile log checks this time for readability (if you do encounter issues, add the compile-checks! see previous code samples)
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);//Crear el objeto Vertex Shader como entero 


    //FRAGMENT SHADER

    unsigned int fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER); // cabeza
    unsigned int fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER); // amarillo
    unsigned int fragmentShader3 = glCreateShader(GL_FRAGMENT_SHADER); // verde body
    unsigned int fragmentShader4 = glCreateShader(GL_FRAGMENT_SHADER); // verde
    unsigned int fragmentShader5 = glCreateShader(GL_FRAGMENT_SHADER); // celeste
    unsigned int fragmentShader6 = glCreateShader(GL_FRAGMENT_SHADER); // morado
    unsigned int fragmentShader7 = glCreateShader(GL_FRAGMENT_SHADER); // naranja


    unsigned int shaderProgram1 = glCreateProgram(); // cabeza
    unsigned int shaderProgram2 = glCreateProgram();// amarillo
    unsigned int shaderProgram3  = glCreateProgram(); // verde body
    unsigned int shaderProgram4 = glCreateProgram(); // verde
    unsigned int shaderProgram5 = glCreateProgram();// celeste
    unsigned int shaderProgram6 = glCreateProgram(); // morado
    unsigned int shaderProgram7 = glCreateProgram(); // naranja

    //Shader del Vertex
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    //Shader del Fragment
    glShaderSource(fragmentShader1, 1, &fragmentShader1Source, NULL);
    glCompileShader(fragmentShader1);

    glShaderSource(fragmentShader2, 1, &fragmentShader2Source, NULL);
    glCompileShader(fragmentShader2);

    glShaderSource(fragmentShader3, 1, &fragmentShader3Source, NULL);
    glCompileShader(fragmentShader3);

    glShaderSource(fragmentShader4, 1, &fragmentShader4Source, NULL);
    glCompileShader(fragmentShader4);

    glShaderSource(fragmentShader5, 1, &fragmentShader5Source, NULL);
    glCompileShader(fragmentShader5);

    glShaderSource(fragmentShader6, 1, &fragmentShader6Source, NULL);
    glCompileShader(fragmentShader6);

    glShaderSource(fragmentShader7, 1, &fragmentShader7Source, NULL);
    glCompileShader(fragmentShader7);



    // link the 1 program object
    glAttachShader(shaderProgram1, vertexShader);
    glAttachShader(shaderProgram1, fragmentShader1);
    glLinkProgram(shaderProgram1);
    
    // link the 2 program object
    glAttachShader(shaderProgram2, vertexShader);
    glAttachShader(shaderProgram2, fragmentShader2);
    glLinkProgram(shaderProgram2);

    // link the 3 program object
    glAttachShader(shaderProgram3, vertexShader);
    glAttachShader(shaderProgram3, fragmentShader3);
    glLinkProgram(shaderProgram3);

    // link the 4 program object
    glAttachShader(shaderProgram4, vertexShader);
    glAttachShader(shaderProgram4, fragmentShader4);
    glLinkProgram(shaderProgram4);

    // link the 5 program object
    glAttachShader(shaderProgram5, vertexShader);
    glAttachShader(shaderProgram5, fragmentShader5);
    glLinkProgram(shaderProgram5);

    // link the 6 program object
    glAttachShader(shaderProgram6, vertexShader);
    glAttachShader(shaderProgram6, fragmentShader6);
    glLinkProgram(shaderProgram6);

    // link the 7 program object
    glAttachShader(shaderProgram7, vertexShader);
    glAttachShader(shaderProgram7, fragmentShader7);
    glLinkProgram(shaderProgram7);


    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float firstTriangle[] = { //Cabeza 1
       -0.5f, 0.65f, 0.0f, // left  1
        -0.18f, 0.85f, 0.0f, // right 1
        -0.45f, 0.91f, 0.0f,  // top  1 
    };
    float secondTriangle[] = { //Cabeza2
         -0.5f, 0.65f, 0.0f, // left  2
        -0.18f, 0.85f, 0.0f, // right 2
        -0.24f, 0.59f, 0.0f  // top  2
    };
    float thirdTriangle[] = { //triangulo cuerpo 1 
        -0.8f, 0.53f, 0.0f, // left  3
       0.0f, 0.62f, 0.0f, // right 3
       -0.3f, 0.17f, 0.0f  // top  3
    };
    float fourthTriangle[] = { //triangulo cuerpo 2
       -0.48f, -0.11f, 0.0, // left  4
       0.31f, -0.0f, 0.0f, // right 4
       -0.18f, 0.35f, 0.0f // top  4
    };
    float fiveTriangle[] = { // pierna izquierda
         -0.46f, -0.5f, 0.0f, // left  5
        -0.17f, -0.065f, 0.0f, // right 5
        -0.48f, -0.11f, 0.0  // top  5
    };
    float sixTriangle[] = { // pie izquierdo
        -0.77f, -0.71f, 0.0f, // left  6
       -0.54f, -0.775f, 0.0f, // right 6
      -0.46f, -0.5f, 0.0f  // top  6
    };
    float sevenTriangle[] = { //Pierna derecha 1
       -0.09f, -0.055f, 0.0f, // left  7
       0.31f, -0.29f, 0.0f, // right 7
       0.25f, -0.01f, 0.0f  // top  7
    };
    float eightTriangle[] = { //Pierna derecha 2
       0.31f, -0.29f, 0.0f, // left  8
       0.59f, -0.24f, 0.0f, // right 8
      0.25f,-0.01f, 0.0f  // top  8
    };
    float nineTriangle[] = { //Pie derecho
       0.43f, -0.13f, 0.0f, // left  9
       0.8f, -0.38f, 0.0f, // right 9
       0.79f, -0.1f, 0.0f  // top  9
    };






    unsigned int VBOs[9], VAOs[9];
    glGenVertexArrays(9, VAOs); // we can also generate multiple VAOs or buffers at the same time
    glGenBuffers(9, VBOs);
    // first triangle setup
    // --------------------
    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	// Vertex attributes stay the same
    glEnableVertexAttribArray(0);
    // glBindVertexArray(0); // no need to unbind at all as we directly bind a different VAO the next few lines
    // second triangle setup
    // ---------------------
    glBindVertexArray(VAOs[1]);	// note that we bind to a different VAO now
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);	// and a different VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); // because the vertex data is tightly packed we can also specify 0 as the vertex attribute's stride to let OpenGL figure it out
    glEnableVertexAttribArray(0);
    // glBindVertexArray(0); // not really necessary as well, but beware of calls that could affect VAOs while this one is bound (like binding element buffer objects, or enabling/disabling vertex attributes)
       // third triangle setup
    // ---------------------
    glBindVertexArray(VAOs[2]);	// note that we bind to a different VAO now
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[2]);	// and a different VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(thirdTriangle), thirdTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); // because the vertex data is tightly packed we can also specify 0 as the vertex attribute's stride to let OpenGL figure it out
    glEnableVertexAttribArray(0);
    // fourth triangle setup
 // ---------------------
    glBindVertexArray(VAOs[3]);	// note that we bind to a different VAO now
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[3]);	// and a different VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(fourthTriangle), fourthTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); // because the vertex data is tightly packed we can also specify 0 as the vertex attribute's stride to let OpenGL figure it out
    glEnableVertexAttribArray(0);
    // five triangle setup
// ---------------------
    glBindVertexArray(VAOs[4]);	// note that we bind to a different VAO now
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[4]);	// and a different VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(fiveTriangle), fiveTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); // because the vertex data is tightly packed we can also specify 0 as the vertex attribute's stride to let OpenGL figure it out
    glEnableVertexAttribArray(0);
    // six triangle setup
// ---------------------
    glBindVertexArray(VAOs[5]);	// note that we bind to a different VAO now
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[5]);	// and a different VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(sixTriangle), sixTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); // because the vertex data is tightly packed we can also specify 0 as the vertex attribute's stride to let OpenGL figure it out
    glEnableVertexAttribArray(0);

    // seven triangle setup
  // ---------------------
    glBindVertexArray(VAOs[6]);	// note that we bind to a different VAO now
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[6]);	// and a different VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(sevenTriangle), sevenTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); // because the vertex data is tightly packed we can also specify 0 as the vertex attribute's stride to let OpenGL figure it out
    glEnableVertexAttribArray(0);
    // eight triangle setup
// ---------------------
    glBindVertexArray(VAOs[7]);	// note that we bind to a different VAO now
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[7]);	// and a different VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(eightTriangle), eightTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); // because the vertex data is tightly packed we can also specify 0 as the vertex attribute's stride to let OpenGL figure it out
    glEnableVertexAttribArray(0);
    // nine triangle setup
// ---------------------
    glBindVertexArray(VAOs[8]);	// note that we bind to a different VAO now
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[8]);	// and a different VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(nineTriangle), nineTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); // because the vertex data is tightly packed we can also specify 0 as the vertex attribute's stride to let OpenGL figure it out
    glEnableVertexAttribArray(0);



    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //Fondo Blanco
        glClear(GL_COLOR_BUFFER_BIT);

        // now when we draw the triangle we first use the vertex and orange fragment shader from the first program
        glUseProgram(shaderProgram1);
        // draw the head formado por dos triangulos
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        // this call should output an red triangle
        // then we draw the second triangle using the data from the second VAO
        // when we draw the second triangle we want to use a different shader program so we switch to the shader program with our yellow fragment shader.
       
        //Amarillo
        glUseProgram(shaderProgram2);
        glBindVertexArray(VAOs[2]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

            //Verde cuerpo
        glUseProgram(shaderProgram3);
        glBindVertexArray(VAOs[3]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        //Pierna IZquierda
        glUseProgram(shaderProgram4);
        glBindVertexArray(VAOs[4]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        //Pie Izquierdo
        glUseProgram(shaderProgram5);
        glBindVertexArray(VAOs[5]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        //Pierna Derecha
        glUseProgram(shaderProgram6);
        glBindVertexArray(VAOs[6]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(VAOs[7]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        //Pie Derecho
        glUseProgram(shaderProgram7);
        glBindVertexArray(VAOs[8]);
        glDrawArrays(GL_TRIANGLES, 0, 3);



        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(9, VAOs);
    glDeleteBuffers(9, VBOs);

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
    //Hacemos que con las teclas 1 y 2 cambie a solo aristas o con color

    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)// SOLO ARISTAS
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}