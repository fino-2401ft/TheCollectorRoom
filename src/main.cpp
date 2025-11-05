#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <chrono>
#include <iostream>
#include <cstdio>
#include <cmath>
#include "../include/Room.h"
#include "../include/Camera.h"
#include "../include/Geometry.h"

Room room;
Camera cam;
bool keysDown[1024] = {0};
double lastX = 400, lastY = 300;
bool firstMouse = true;
int collected = 0;
bool gameWon = false;

void framebuffer_size_callback(GLFWwindow *window, int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float aspect = (float)w / (float)h;
    float fovy = 60.0f;
    float near = 0.1f;
    float t = tanf(fovy * 3.1415926f / 180.0f * 0.5f) * near;
    float r = t * aspect;
    glFrustum(-r, r, -t, t, near, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

void cursor_pos_callback(GLFWwindow *window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    float dx = (float)(xpos - lastX);
    float dy = (float)(lastY - ypos);
    lastX = xpos;
    lastY = ypos;
    cam.processMouse(dx, dy);
}

void key_callback(GLFWwindow *window, int key, int sc, int action, int mods)
{
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            keysDown[key] = true;
        else if (action == GLFW_RELEASE)
            keysDown[key] = false;
    }
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (key == GLFW_KEY_F && action == GLFW_PRESS)
    {
        Item *it = room.getNearbyItem(cam.pos, 2.0f);
        if (it)
        {
            it->collected = true;
            collected++;
            std::cout << "Collected: " << collected << " / 5\n";
        }
        else if (collected >= 5 && room.isNearDoor(cam.pos, 2.0f) && !room.doorOpen)
        {
            room.openDoor();
            gameWon = true;
            std::cout << "Congratulations! You've collected all keys and opened the door!\n";
        }
    }
}

int main()
{
    if (!glfwInit())
    {
        std::cerr << "GLFW init failed\n";
        return -1;
    }
    GLFWwindow *window = glfwCreateWindow(1280, 720, "The Collector Room", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, cursor_pos_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    // Light from window (right wall, position around window area)
    float lightpos[] = {9.0f, 3.0f, -3.5f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
    float ambient[] = {0.3f, 0.3f, 0.35f, 1.0f};
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    float diffuse[] = {0.8f, 0.85f, 0.9f, 1.0f};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);

    room.setupScene();

    auto lastTime = std::chrono::high_resolution_clock::now();
    while (!glfwWindowShouldClose(window))
    {
        auto now = std::chrono::high_resolution_clock::now();
        float dt = std::chrono::duration<float>(now - lastTime).count();
        lastTime = now;

        // keyboard movement
        if (keysDown[GLFW_KEY_W])
            cam.processKeyboard(0, dt);
        if (keysDown[GLFW_KEY_S])
            cam.processKeyboard(1, dt);
        if (keysDown[GLFW_KEY_D])
            cam.processKeyboard(2, dt);
        if (keysDown[GLFW_KEY_A])
            cam.processKeyboard(3, dt);

        // update animations
        for (auto o : room.objects)
            o->update(dt);
        for (auto it : room.items)
            it->update(dt);

        glClearColor(0.2f, 0.2f, 0.25f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        int w, h;
        glfwGetFramebufferSize(window, &w, &h);
        framebuffer_size_callback(window, w, h);

        cam.applyView();
        room.draw();

        // HUD
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        glOrtho(0, w, 0, h, -1, 1);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();
        char buf[64];
        sprintf(buf, "Collected: %d / 5", collected);
        float col[3] = {1.0f, 1.0f, 1.0f};
        drawText2D(buf, 10.0f, (float)h - 30.0f, 1.0f, col, w, h);
        
        // Show interaction prompts
        if (room.getNearbyItem(cam.pos, 2.0f))
        {
            drawText2D("Press F to collect", w / 2.0f - 80.0f, h / 2.0f, 1.2f, col, w, h);
        }
        else if (collected >= 5 && room.isNearDoor(cam.pos, 2.0f) && !room.doorOpen)
        {
            drawText2D("Press F to open door", w / 2.0f - 90.0f, h / 2.0f, 1.2f, col, w, h);
        }
        
        // Victory message
        if (gameWon)
        {
            float winCol[3] = {1.0f, 1.0f, 0.0f};
            drawText2D("Congratulations! You've collected all items!", w / 2.0f - 200.0f, h / 2.0f + 50.0f, 1.5f, winCol, w, h);
        }
        glPopMatrix();
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
