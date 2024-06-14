#ifndef _RETREN_INCLUDE
#define _RETREN_INCLUDE
#include <stdbool.h>

#if defined(__cplusplus)
extern "C" {
#endif


typedef unsigned int retren_uint;
extern bool __retren_initialized__;

#ifdef __RETREN_DEFINE_GLOBAL_VARS
bool __retren_initialized__ = false;
#endif //__RETREN_DEFINE_GLOBAL_VARS

#define IS_RETREN_INITIALIZED __retren_initialized__

typedef struct retren_Window {
    char *title;

    retren_uint width;
    retren_uint height;

    bool is_open;

    void *__window;
} retren_Window;

retren_Window retren_CreateWindow(const char *title, retren_uint width, retren_uint height);
void retren_DestroyWindow(retren_Window window);
void retren_Update(retren_Window *window);

void retren_Init();
void retren_Terminate();

#if defined(__cplusplus)
}
#endif
#endif //_RETREN_INCLUDE
