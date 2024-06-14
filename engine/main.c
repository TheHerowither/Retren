#define __RETREN_DEFINE_GLOBAL_VARS
#include <retren.h>
#include <stdio.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define CLOG_IMPLEMENTATION
#include <clog.h>




static void glfwError(int id, const char* description) {
    clog(CLOG_ERROR, "Error %i occured: %s", id, description);
}

void retren_Init() {
#ifdef RETREN_NO_DEBUG
    clog_muted_level = CLOG_TRACE;
#endif
    glfwSetErrorCallback(&glfwError);
    clog_set_fmt("%c[%L]:%r %m");
    if (!glfwInit()) {
        clog(CLOG_FATAL, "Failed to initialize GLFW (Exiting...)");
        exit(1);
    }


    __retren_initialized__ = true;
    clog(CLOG_TRACE, "Initialized retren");
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    retren_Window *win = (retren_Window*)glfwGetWindowUserPointer(window);
    win->width = width;
    win->height = height;

    glViewport(0, 0, width, height);
}

retren_Window retren_CreateWindow(const char *title, retren_uint width, retren_uint height) {
    clog(CLOG_TRACE, "Initializing retren_Window...");
    if (!IS_RETREN_INITIALIZED) {
        clog(CLOG_FATAL, "Retren is not initialized yet (Exiting...)");
        retren_Terminate();
        exit(1);
    }


    clog(CLOG_DEBUG, "Setting up window");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    retren_Window win = (retren_Window) {
        (char *)title,

        width,
        height,

        true,

        glfwCreateWindow(width, height, title, NULL, NULL)
    };
    clog(CLOG_DEBUG, "Window NULL check");
    if (win.__window == NULL) {
        clog(CLOG_FATAL, "Retren failed to create glfwWindow (Exiting...)");
        retren_Terminate();
        exit(1);
    }

    glfwMakeContextCurrent(win.__window);


    glfwSetWindowUserPointer(win.__window, &win);
    glfwSetFramebufferSizeCallback(win.__window, framebuffer_size_callback);

    clog(CLOG_DEBUG, "Initializing GLAD...");
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        clog(CLOG_FATAL, "Failed to initialize GLAD (Exiting...)");
        retren_Terminate();
        exit(1);
    }

    clog(CLOG_TRACE, "Initialized retren_Window");
    return win;
}

void retren_Update(retren_Window *window) {
    window->is_open = !glfwWindowShouldClose(window->__window);
    glfwSwapBuffers(window->__window);
    glfwPollEvents();
}

void retren_DestroyWindow(retren_Window window) {
    glfwDestroyWindow(window.__window);
    clog(CLOG_INFO, "Destroyed retren_Window");
}

void retren_Terminate() {
    clog(CLOG_INFO, "Terminating retren");
    glfwTerminate();
}
