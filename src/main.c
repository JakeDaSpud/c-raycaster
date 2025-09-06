#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

/*
Build command
    g++ src/main.c -Ilibs/include -Llibs/lib -lglfw3 -lglew32 -lopengl32 -lgdi32 -o bin/raycaster.exe
*/

float px, py; // Player position
int playerMoveDistance = 5;

void drawPlayer()
{
    glColor3f(1, 1, 0);
    glPointSize(8);
    glBegin(GL_POINTS);
    glVertex2i(px, py);
    glEnd();
}

void display(GLFWwindow* const window)
{
    glClear(GL_COLOR_BUFFER_BIT); // Clear the screen

    drawPlayer(); // Draw the Player

    // Swap front and back buffers
    glfwSwapBuffers(window);
}

void buttons(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_A && action == GLFW_PRESS) { px -= playerMoveDistance; }
    if (key == GLFW_KEY_D && action == GLFW_PRESS) { px += playerMoveDistance; }
    if (key == GLFW_KEY_W && action == GLFW_PRESS) { py -= playerMoveDistance; }
    if (key == GLFW_KEY_S && action == GLFW_PRESS) { py += playerMoveDistance; }
    //glutPostRedisplay();
}

void init(GLFWwindow* window)
{
    // Set clear colour rgba
    glClearColor(0.3, 0.3, 0.3, 0);

    glMatrixMode(GL_PROJECTION); // So the top half of the screen gets rendered too
    glOrtho(0, 1024, 512, 0, -1, 1);
    //gluOrtho2D(0,1024,512,0); // Can't find this in my version

    glfwSetKeyCallback(window, buttons);

    // Set Player position
    px = 300;
    py = 300;
}

int main()
{
    // Initiialise GLFW
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialise GLFW\n");
        return -1;
    }

    // Create a windowed mode window and OpenGL context
    // glfwCreateWindow(pixel width, pixel height, window title, targeted monitor, shared context with another window)
    GLFWwindow* window = glfwCreateWindow(1024, 512, "Jake's Raycaster", NULL, NULL);
    if (!window) {
        fprintf(stderr, "Failed to create window\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Setting up GLEW now, after GLFW is done

    // Initialise GLEW (must be done after context is current)
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        fprintf(stderr, "Failed to initialise GLEW\n");
        return -1;
    };

    // ----- Real Code Underneath, no more setup -----
    
    init(window);

    // Main Render Loop
    while (!glfwWindowShouldClose(window)) {

        display(window);
        

        // Poll for and process events
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
