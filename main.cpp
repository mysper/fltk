#include "Window.h"
#include "GUI.h"
using namespace Graph_lib;

class Connect_Window : public Graph_lib::Window {
public:
    Connect_Window(int,int,string);
private:
    Button quit;
    Button menuBtn;
    Button connect;
    Menu recent;
    In_box ip;
    In_box port;
    Out_box msg;

    static void cb_quit(Address,Address);
};

Connect_Window::Connect_Window(int w,int h,string t):
    Window(w,h,t),
    quit(Point(x_max()-75,0),75,25,"quit",cb_quit),
    menuBtn(Point(0,0),150,25,"recent",cb_quit),
    connect(Point(120,230),100,25,"Connect",cb_quit),
    recent(Point(0,25),150,25,Menu::Kind::vertical,"recent"),
    ip(Point(120,130),175,25,"IP Address: "),
    port(Point(120,180),75,25,"Port: "),
    msg(Point(120,275),300,75,"Message: ") {


    recent.attach(new Button(Point(0,0),150,25,"recent",cb_quit));
    recent.attach(new Button(Point(0,0),150,25,"recent",cb_quit));
    recent.attach(new Button(Point(0,0),150,25,"recent",cb_quit));
    
    attach(quit);
    attach(menuBtn);
    attach(recent);
    attach(ip);
    attach(port);
    attach(connect);
    attach(msg);

    // recent.hide();
}

void Connect_Window::cb_quit(Address,Address win) {
    reference_to<Connect_Window>(win).hide();
}

int main () {

    Connect_Window win(600,400,"New Window");
    
    return gui_main();
}
