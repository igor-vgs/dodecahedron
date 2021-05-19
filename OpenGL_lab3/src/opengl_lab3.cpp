#include <GLFW/glfw3.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <random>
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

GLfloat rotationAboutX = 0;
GLfloat rotationAboutY = 0;
GLfloat rotationAboutZ = 0;
GLfloat cameraAboutX = 0;
GLfloat cameraAboutY = 0;
GLfloat cameraAboutZ = 0;
GLfloat distance = 1;
GLboolean skeleton = 0;

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE || key == GLFW_KEY_ENTER) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    if (key == GLFW_KEY_A) {
        skeleton = 1;
    }
    if (key == GLFW_KEY_D) {
        skeleton = 0;
    }
    const GLfloat rotationAngle = 5;
    const GLfloat zoom = 0.5f;

    // actions are GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        switch (key) {
        case GLFW_KEY_UP:
            rotationAboutX -= rotationAngle;
            break;
        case GLFW_KEY_DOWN:
            rotationAboutX += rotationAngle;
            break;
        case GLFW_KEY_RIGHT:
            rotationAboutY += rotationAngle;
            break;
        case GLFW_KEY_LEFT:
            rotationAboutY -= rotationAngle;
            break;
        case GLFW_KEY_W:
            distance += zoom;
            break;
        case GLFW_KEY_S:
            distance -= zoom;
            break;
        case GLFW_KEY_Q:
            rotationAboutZ += rotationAngle;
            break;
        case GLFW_KEY_E:
            rotationAboutZ -= rotationAngle;
            break;
        }
    }
};
struct Point {
    GLfloat x;
    GLfloat y;
    GLfloat z;
};

Point colors12[12];
Point dodecahedron[4][5];

void drawPoint(int h, int w) {
    float teta;
    float phi;


    if (h == 0 || h == 3) {
        teta = asinf(2 / (float)(sqrt(3) * (1 + sqrt(5)) * sin(M_PI / 5)));
    }
    else {
        teta = asinf(1 / (float)(sqrt(3) * sin(M_PI / 5)));
    }
    if(h >= 2) {
        teta = (float)M_PI - teta;
    }
    phi = 2 * (float)M_PI * (2 * w + h / 2) / 10;
    dodecahedron[h][w] = {
        100 * sin(teta) * cos(phi),
        100 * sin(teta) * sin(phi),
        100 * cos(teta),
    };
    //std::cout << dodecahedron[h][w].x << " " << dodecahedron[h][w].y << " " << dodecahedron[h][w].z << std::endl;
    glVertex3d(dodecahedron[h][w].x, dodecahedron[h][w].y, dodecahedron[h][w].z);
}

void drawDodecahedron() {

    glBegin(GL_POLYGON);   
    glColor3f(colors12[0].x, colors12[0].y, colors12[0].z);
    for(int i = 0; i < 5; i++ ){
        drawPoint(0 , i%5);
    }
    glEnd();

    for (int i = 0; i < 5; i++) {
        glBegin(GL_POLYGON);
        glColor3f(colors12[i+1].x, colors12[i+1].y, colors12[i+1].z);
        drawPoint(0, i);
        drawPoint(0, (i + 1) % 5);
        drawPoint(1, (i + 1) % 5);
        drawPoint(2, i);
        drawPoint(1, i);

        glEnd();
    }

    for (int i = 0; i < 5; i++) {
         glBegin(GL_POLYGON);
         glColor3f(colors12[i + 6].x, colors12[i + 6].y, colors12[i + 6].z);
         drawPoint(3, (i + 1) % 5);
         drawPoint(3, i);
         drawPoint(2, i);
         drawPoint(1, (i + 1) % 5);
         drawPoint(2, (i + 1) % 5);

         glEnd();
    }

     glBegin(GL_POLYGON);
     glColor3f(colors12[11].x, colors12[11].y, colors12[11].z);
     for (int i = 0; i < 5; i++) {

         drawPoint(3, i % 5);
     }
     glEnd();

     //std::cout << dodecahedron[3][4].x << " " << dodecahedron[3][4].y << " " << dodecahedron[3][4].z << std::endl;
}

void drawCube(GLfloat x0, GLfloat y0, GLfloat z0, GLfloat edgeLength) {
    GLfloat halfSideLength = edgeLength / 2;

    GLfloat vertices[] =
    {
        // front face
        x0 - halfSideLength, y0 + halfSideLength, z0 + halfSideLength, // top left
        x0 + halfSideLength, y0 + halfSideLength, z0 + halfSideLength, // top right
        x0 + halfSideLength, y0 - halfSideLength, z0 + halfSideLength, // bottom right
        x0 - halfSideLength, y0 - halfSideLength, z0 + halfSideLength, // bottom left

        // back face
        x0 - halfSideLength, y0 + halfSideLength, z0 - halfSideLength, // top left
        x0 + halfSideLength, y0 + halfSideLength, z0 - halfSideLength, // top right
        x0 + halfSideLength, y0 - halfSideLength, z0 - halfSideLength, // bottom right
        x0 - halfSideLength, y0 - halfSideLength, z0 - halfSideLength, // bottom left

        // left face
        x0 - halfSideLength, y0 + halfSideLength, z0 + halfSideLength, // top left
        x0 - halfSideLength, y0 + halfSideLength, z0 - halfSideLength, // top right
        x0 - halfSideLength, y0 - halfSideLength, z0 - halfSideLength, // bottom right
        x0 - halfSideLength, y0 - halfSideLength, z0 + halfSideLength, // bottom left

        // right face
        x0 + halfSideLength, y0 + halfSideLength, z0 + halfSideLength, // top left
        x0 + halfSideLength, y0 + halfSideLength, z0 - halfSideLength, // top right
        x0 + halfSideLength, y0 - halfSideLength, z0 - halfSideLength, // bottom right
        x0 + halfSideLength, y0 - halfSideLength, z0 + halfSideLength, // bottom left

        // top face
        x0 - halfSideLength, y0 + halfSideLength, z0 + halfSideLength, // top left
        x0 - halfSideLength, y0 + halfSideLength, z0 - halfSideLength, // top right
        x0 + halfSideLength, y0 + halfSideLength, z0 - halfSideLength, // bottom right
        x0 + halfSideLength, y0 + halfSideLength, z0 + halfSideLength, // bottom left

        // top face
        x0 - halfSideLength, y0 - halfSideLength, z0 + halfSideLength, // top left
        x0 - halfSideLength, y0 - halfSideLength, z0 - halfSideLength, // top right
        x0 + halfSideLength, y0 - halfSideLength, z0 - halfSideLength, // bottom right
        x0 + halfSideLength, y0 - halfSideLength, z0 + halfSideLength  // bottom left
    };

    GLfloat color[] =
    {
        255, 0, 0,
        255, 0, 0,
        255, 0, 0,
        255, 0, 0,

        0, 255, 0,
        0, 255, 0,
        0, 255, 0,
        0, 255, 0,

        0, 0, 255,
        0, 0, 255,
        0, 0, 255,
        0, 0, 255,

        122.5, 122.5, 0,
        122.5, 122.5, 0,
        122.5, 122.5, 0,
        122.5, 122.5, 0,

        122.5, 0, 122.5,
        122.5, 0, 122.5,
        122.5, 0, 122.5,
        122.5, 0, 122.5,

        0, 122.5, 122.5,
        0, 122.5, 122.5,
        0, 122.5, 122.5,
        0, 122.5, 122.5,
    };
    if (skeleton) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, color);
    glDrawArrays(GL_QUADS, 0, 24);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
};

int main(void)
{
    GLFWwindow* window;

    // Initialize the library 
    if (!glfwInit())
        return -1;

    // Create a windowed mode window and its OpenGL context 
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current 
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, keyCallback);
    GLfloat x0 = SCREEN_WIDTH / 2;
    GLfloat y0 = SCREEN_HEIGHT / 2;

    glEnable(GL_DEPTH_TEST);
    
    std::random_device rd;  
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0.0, 1.0);
    for (int i = 0; i < 12; i++) {
        float r = dis(gen);
        float g = dis(gen);
        float b = dis(gen);
        colors12[i] = { r, g, b };
    }

    // Loop until the user closes the window 
    while (!glfwWindowShouldClose(window))
    {
        // Render here 
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Фронтальный вид. Ось Z смотрит на нас. Находится в левой нижней части экрана. 
        glViewport(0, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-SCREEN_WIDTH / 2, SCREEN_WIDTH / 2, -SCREEN_HEIGHT / 2, SCREEN_HEIGHT / 2, 0, 1000);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glTranslatef(0, 0, -500);

        glRotatef(rotationAboutX, 1, 0, 0);
        glRotatef(rotationAboutY, 0, 1, 0);
        glRotatef(rotationAboutZ, 0, 0, 1);
        glScalef(distance, distance, distance);
        drawDodecahedron();
        //drawCube(0, 0, 0, 100);
        glLoadIdentity();

        // Вид сверху. Ось Y смотрит на нас. Находится в левой верхней части экрана 
        glViewport(0, SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-SCREEN_WIDTH / 2, SCREEN_WIDTH / 2, -SCREEN_HEIGHT / 2, SCREEN_HEIGHT / 2, 0, 1000);
        glRotatef(90, 1, 0, 0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glTranslatef(0, -500, 0);

        glRotatef(rotationAboutX, 1, 0, 0);
        glRotatef(rotationAboutY, 0, 1, 0);
        glRotatef(rotationAboutZ, 0, 0, 1);
        glScalef(distance, distance, distance);
        //drawCube(0, 0, 0, 100);
        drawDodecahedron();
        glLoadIdentity();

        // Вид сбоку. Ось X смотрит на нас. Находится в правой верхней части экрана 
        glViewport(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-SCREEN_WIDTH / 2, SCREEN_WIDTH / 2, -SCREEN_HEIGHT / 2, SCREEN_HEIGHT / 2, 0, 1000);
        glRotatef(-90, 0, 1, 0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glTranslatef(-500, 0, 0);

        glRotatef(rotationAboutX, 1, 0, 0);
        glRotatef(rotationAboutY, 0, 1, 0);
        glRotatef(rotationAboutZ, 0, 0, 1);
        glScalef(distance, distance, distance);
        //drawCube(0, 0, 0, 100);
        drawDodecahedron();
        glLoadIdentity();

        // Куб в стандартной ориентации. 
        glViewport(SCREEN_WIDTH / 2, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-SCREEN_WIDTH / 2, SCREEN_WIDTH / 2, -SCREEN_HEIGHT / 2, SCREEN_HEIGHT / 2, 0, 1000);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glTranslatef(0, 0, -500);
        drawCube(0, 0, 0, 100);
        glLoadIdentity();

        // Swap front and back buffers 
        glfwSwapBuffers(window);

        // Poll for and process events 
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

/*#include <GLFW/glfw3.h>

using namespace std;

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

struct Point{
    float x;
    float y;
    float z;
};

struct Color {
    float r;
    float g;
    float b;
};

struct Figure {
    []Color colors;
    Point startPoint;
    Point angle;
    float scale;
    int polygonMode;
    float projections;
    int** viewPorts;
};

struct Dodecahedron {
    Figure figure;
    Point* points;
    Color *colors;
};

void drawPoint(Point *p) {
    glVertex3f(p->x,p->y,p->z);
}

void setColor(Color *c) {
    glColor3f(c->r, c->g, c->b);
}

void init(Figure *f) {
    f->viewPorts[3][4] = {
        
        {0, SCREEN_HEIGHT/2, SCREEN_WIDTH/2, SCREEN_HEIGHT / 2},
        {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2},
        {SCREEN_WIDTH / 2, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2},
    };

    f->projections = {
        { //Z
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, -1, 0,
            0, 0, 0, 1,
        },
        { //X
            0, 0, -1, 0,
            0, 1, 0, 0,
            -1, 0, 0, 0,
            0, 0, 0, 1,
        },
        { //Y
            1, 0, 0, 0,
            0, 0, -1, 0,
            0, -1, 0, 0,
            0, 0, 0, 1,
        },
    }
}


int main(void) {
    
}*/