#include "Window.h"
#include "GUI.h"
#include <fstream>
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

    bool isMenu;
    string ip_port[3];

    static void cb_quit(Address,Address);
    static void cb_menuBtn(Address,Address);
};

Connect_Window::Connect_Window(int w,int h,string t):
    Window(w,h,t),
    quit(Point(x_max()-75,0),75,25,"quit",cb_quit),
    menuBtn(Point(0,0),175,25,"recent list",cb_menuBtn),
    connect(Point(120,230),100,25,"Connect",cb_quit),
    recent(Point(0,25),175,25,Menu::Kind::vertical,"recent"),
    ip(Point(120,130),175,25,"IP Address: "),
    port(Point(120,180),75,25,"Port: "),
    msg(Point(120,275),300,75,"Message: ") {

    fstream fs;
    fs.open("./recents.txt",std::ios::in);
    for (int i=0;i<3;++i) {
        // read line from file
        getline(fs,ip_port[i]);
        // replace the space to ':'
        for (char& i : ip_port[i]) i = (i == ' ')? ':' : i;
        // declare stringstream as ss
        stringstream ss;
        // put each value to ss in order
        ss << i + 1 << ". " << ip_port[i];
        // put button which label is transfer from ss into recent(Menu)
        recent.attach(new Button(Point(0,0),150,25,ss.str(),cb_quit));
    }

    attach(quit);
    attach(menuBtn);
    attach(recent);
    attach(ip);
    attach(port);
    attach(connect);
    attach(msg);

    recent.hide();
    isMenu = false;
}

void Connect_Window::cb_quit(Address,Address win) {
    reference_to<Connect_Window>(win).hide();
}

void Connect_Window::cb_menuBtn(Address,Address _win) {
    Connect_Window& win = reference_to<Connect_Window>(_win);
    if (win.isMenu) {
        win.recent.hide();
    } else {
        win.recent.show();
    }
    win.isMenu = !win.isMenu;
}

int main () {

    Connect_Window win(600,400,"New Window");
    
    return gui_main();
}
