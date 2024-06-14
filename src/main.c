#include <retren.h>
#include <signal.h>




retren_Window window;
void quit(int dummy) {
    (void)dummy;
    window.is_open = false;
}

int main(void) {
    signal(SIGINT, quit);

    retren_Init();

    window = retren_CreateWindow("Test window", 1080, 720);

    while (window.is_open) {
        retren_Update(&window);
    }

    retren_DestroyWindow(window);
    retren_Terminate();
    return 0;
}
