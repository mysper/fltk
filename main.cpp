#include "Window.h"
using Graph_lib::gui_main;

int main () {

    Graph_lib::Window* win = new Graph_lib::Window(600,400,"New Window");
    
    return gui_main();
}