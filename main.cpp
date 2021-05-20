#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
using std::vector;
using std::string;
using std::fstream;
using std::getline;
using std::stringstream;
using std::endl;
#include "Window.h"
#include "Graph.h"
#include "Guii.h"
using namespace Graph_lib;

//define IO_Box
struct IO_box : Widget {
    IO_box(Point xy, int w, int h, const string& s)
        :Widget(xy, w, h, s, 0) { }
    string get_string();
    void put(const string&);

    void attach(Graph_lib::Window& win);
};
string IO_box::get_string() {
    Fl_Input& pi = reference_to<Fl_Input>(pw);
    return string(pi.value());
}
void IO_box::put(const string& s) {
    reference_to<Fl_Output>(pw).value(s.c_str());
}
void IO_box::attach(Graph_lib::Window& win) {
    pw = new Fl_Input(loc.x, loc.y, width, height, label.c_str());
    own = &win;
}

class myWindow : Graph_lib::Window {
public:
    myWindow(Point point, int width, int height, const string& title);
private:
    //varible
    bool menuVisible;
    vector<string> IPString;
    //user interface items
    Button Quit;
    Button Connect;
    Button Recent;
    IO_box IP;
    IO_box Port;
    Out_box Meg;
    Menu IPMenu;
    //file operator, define in line 92~109
    void fileReader();
    void fileWriter();
    //item callback function, define in line 110~127
    static void cbQuit(Address, Address);
    static void cbConnect(Address, Address);
    static void cbRecent(Address, Address);
    static void cbMenu1(Address, Address);
    static void cbMenu2(Address, Address);
    static void cbMenu3(Address, Address);
    //user interface operator, define in line 182~184
    void quit();
    void connect();
    void swapRecent();
    void menu1();
    void menu2();
    void menu3();
};

myWindow::myWindow(Point point, int width, int height, const string& title):
    menuVisible(false),
    Window(point, width, height, title),
    Quit(Point(x_max() - 70, 0), 70, 25, "Quit", cbQuit),
    Connect(Point(125, 250), 85, 25, "Connect", cbConnect),
    Recent(Point(0, 0), 175, 25, "Recent Connections", cbRecent),
    IP(Point(125, 150), 300, 25, "IP Address: "),
    Port(Point(125, 200), 75, 25, "Port: "),
    Meg(Point(125, 295), 450, 150, "Message: "),
    IPMenu(Point(0,25),175,25, Menu::Kind::vertical,"Recent Connetions") {

    fileReader();
    IPMenu.attach(new Button(Point(0,25),175, 25, IPString[2], cbMenu3));
    IPMenu.attach(new Button(Point(0,25),175, 25, IPString[1], cbMenu2));
    IPMenu.attach(new Button(Point(0,25),175, 25, IPString[0], cbMenu1));

    attach(Quit);
    attach(Connect);
    attach(Recent);
    attach(IP);
    attach(Port);
    attach(Meg);
    attach(IPMenu);

    IPMenu.hide();
}
void myWindow::fileReader() {
    fstream file;
    file.open("Recent.txt", std::ios::in);
    for (int i = 0;i < 3;++i) {
        string line;
        std::getline(file, line);
        IPString.push_back(line);
    }
    file.close();
}
void myWindow::fileWriter() {
    fstream file;
    file.open("Recent.txt", std::ios::trunc | std::ios::out);
    for (int i = 3;i > 0;--i) {
        file << IPString[IPString.size() - i] << std::endl;
    }
    file.close();
}
void myWindow::cbQuit(Address, Address pt) {
    static_cast<myWindow*>(pt)->quit();
}
void myWindow::cbConnect(Address, Address pt) {
    static_cast<myWindow*>(pt)->connect();
}
void myWindow::cbRecent(Address, Address pt) {
    static_cast<myWindow*>(pt)->swapRecent();
}
void myWindow::cbMenu1(Address, Address pt) {
    static_cast<myWindow*>(pt)->menu1();
}
void myWindow::cbMenu2(Address, Address pt) {
    static_cast<myWindow*>(pt)->menu2();
}
void myWindow::cbMenu3(Address, Address pt) {
    static_cast<myWindow*>(pt)->menu3();
}
void myWindow::quit() {
    this->fileWriter();
    this->hide();
}
void myWindow::connect() {
    string IP = this->IP.get_string();
    string Port = this->Port.get_string();
    if (IP == "" || Port == "") {
        this->Meg.put("Please enter the correct IP or Port.");
        return;
    }
    string Addr = IP + ":" + Port;
    this->Meg.put("Try to connnect to " + Addr);
    for (string ss : IPString)
        if (ss == Addr) return;
    IPString.push_back(Addr);
    this->fileWriter();
}
void myWindow::swapRecent() {
    if (this->menuVisible) this->IPMenu.hide();
    else this->IPMenu.show();

    this->menuVisible = !this->menuVisible;
}
void myWindow::menu1() {
    string temp = IPString[0];
    for (char& c : temp)
        if (c == ':') c = ' ';
    stringstream ss{ temp };
    ss >> temp;
    this->IP.put(temp);
    ss >> temp;
    this->Port.put(temp);
    this->Meg.put("You clicked recent connections #3");
}
void myWindow::menu2() {
    string temp = IPString[1];
    for (char& c : temp)
        if (c == ':') c = ' ';
    stringstream ss{ temp };
    ss >> temp;
    this->IP.put(temp);
    ss >> temp;
    this->Port.put(temp);
    this->Meg.put("You clicked recent connections #2");
}
void myWindow::menu3() {
    string temp = IPString[2];
    for (char& c : temp)
        if (c == ':') c = ' ';
    stringstream ss{ temp };
    ss >> temp;
    this->IP.put(temp);
    ss >> temp;
    this->Port.put(temp);
    this->Meg.put("You clicked recent connections #1");
}
int main() {
    myWindow win(Point(100, 100), 650, 500, "lines");
    Fl::redraw();
    return gui_main();

}