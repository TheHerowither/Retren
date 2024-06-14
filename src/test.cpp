#include <iostream>

#include <retren.h>

int main() {
    retren_Init();
    retren_Window window = retren_CreateWindow("C++", 1080, 720);

    while (window.is_open) {
        retren_Update(&window);
    }

    retren_DestroyWindow(window);
    retren_Terminate();
    return 0;
}
