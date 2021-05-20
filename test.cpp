#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Graph.h"
#include "GUI.h"
#include "Window.h"

using namespace Graph_lib;
using namespace std;

struct IO_box : Widget{
     IO_box(Point xy, int w, int h, const string& title)
     :Widget(xy,w,h,title,0) {}

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

//------------------------------------------------------------------------------

struct Lines_window : Graph_lib::Window {
    Lines_window(Point xy, int w, int h, const string& title );
    Open_polyline lines;
private:
    Button next_button;        // add (next_x,next_y) to lines
    Button quit_button;
    IO_box next_ip;
    IO_box next_port;
    Out_box mes_out;
    Menu rec_menu;
    Button menu_button;
    



    string ipname[4]={"","","",""};

    void fileread();
    void filewrite();

    bool isVisible = false;
    
    void hide_menu(){rec_menu.hide(); menu_button.show();}
    void menu_pressed(){menu_button.hide();rec_menu.show();}
    
    
    static void cb_menu1(Address, Address);
    void menu1();   
   static void cb_menu2(Address, Address);
    void menu2();   
    static void cb_menu3(Address, Address);
    void menu3();

    static void cb_menu(Address, Address);
    void menu();   
    static void cb_next(Address, Address);     
    void next();
    static void cb_quit(Address, Address);
    void quit();
};

//------------------------------------------------------------------------------

Lines_window::Lines_window(Point xy, int w, int h, const string& title)
:Window(xy,w,h,title),
    next_button(Point(100,200), 70,25, "Connect", cb_next),
    quit_button(Point(x_max()-70,0), 70, 20, "Quit", cb_quit),
    next_ip(Point(100,120), 105, 20, "IP Address:"),
    next_port(Point(100,160), 45, 20, "Port:"),
    mes_out(Point(100,240), 300, 80, "Message:n"),
    rec_menu(Point(15,10),180,30,Menu::Kind::vertical,"rec"),
    menu_button(Point(15,10), 180, 25, "recent menu", cb_menu)
{
    
    
    //add button to menu
    fileread();
    rec_menu.attach(new Button(Point(50,50),70,20,ipname[0],cb_menu1));
    rec_menu.attach(new Button(Point(50,50),70,20,ipname[1],cb_menu2));
    rec_menu.attach(new Button(Point(50,50),70,20,ipname[2],cb_menu3));
 

    attach(next_button);
    attach(quit_button);
    attach(next_ip);
    attach(next_port);
    attach(mes_out);
    attach(rec_menu);
    rec_menu.hide();
    attach(menu_button);
}

void Lines_window::fileread(){
    fstream file;
    file.open("Recent.txt",std::ios::in);
    for(int i=0; i < 3;++i){
	string li;
	std::getline(file,li);
        ipname[i] = li;
	}
    file.close();
    }

void Lines_window::filewrite(){
    
    stringstream ss;
    
    mes_out.put(ss.str());
    }

//------------------------------------------------------------------------------

void Lines_window::cb_quit(Address, Address pw)    // "the usual"
{  
       reference_to<Lines_window>(pw).quit();
} 

//------------------------------------------------------------------------------

void Lines_window::quit()
{
    hide();        // curious FLTK idiom for delete window
}

//------------------------------------------------------------------------------

void Lines_window::cb_next(Address, Address pw)     // "the usual"
{  
    reference_to<Lines_window>(pw).next();
} 

//-------------------------------------------------------------------------------
void Lines_window::next()
{
    string x = next_ip.get_string();
    string y = next_port.get_string();

    stringstream ss;
    if(x == "" && y == ""){
	ss << "Please enter both IP address and port.";
	mes_out.put(ss.str());
    }
    else{
        ss << "Trying to connect to " << x << ':' << y;
        mes_out.put(ss.str());
    }
}

//-------------------------------------------------------------------------------

void Lines_window::cb_menu(Address, Address pw)     // "the usual"
 {  
    reference_to<Lines_window>(pw).menu();                                  
     }
void Lines_window::menu(){
    if(isVisible)
	hide_menu();
    else
	menu_pressed();    

    isVisible = !isVisible;
}


void Lines_window::cb_menu1(Address, Address pw)     // "the usual"
 {  
    reference_to<Lines_window>(pw).menu1();                                  
     }
void Lines_window::menu1(){
    next_ip.put(ipname[0]);
    
    menu();

    string temp = ipname[0];
    for (char& c : temp){
	if (c == ':') c = ' '; //':' replace to ' '
    }
        stringstream ss{temp};
	ss >> temp;
	this->next_ip.put(temp);
	ss >> temp;
	this->next_port.put(temp);
	this->mes_out.put("You clicked recent connections #1");    
}


void Lines_window::cb_menu2(Address, Address pw)     // "the usual"
 {  
    reference_to<Lines_window>(pw).menu2();                                  
     }
void Lines_window::menu2(){
    next_ip.put(ipname[1]);
    
    menu();

    string temp = ipname[1];
    for (char& c : temp){
	if (c == ':') c = ' '; //':' replace to ' '
    }
        stringstream ss{temp};
	ss >> temp;
	this->next_ip.put(temp);
	ss >> temp;
	this->next_port.put(temp);
	this->mes_out.put("You clicked recent connections #2");    
}

void Lines_window::cb_menu3(Address, Address pw)     // "the usual"
 {  
    reference_to<Lines_window>(pw).menu3();                                  
     }
void Lines_window::menu3(){
    next_ip.put(ipname[2]);
    
    menu();

    string temp = ipname[2];
    for (char& c : temp){
	if (c == ':') c = ' '; //':' replace to ' '
    }
        stringstream ss{temp};
	ss >> temp;
	this->next_ip.put(temp);
	ss >> temp;
	this->next_port.put(temp);
	this->mes_out.put("You clicked recent connections #3");    
}
//------------------------------------------------------------------------------

int main()
try {
    Lines_window win(Point(100,100),600,400,"mud_lab_01");
    return gui_main();
}
catch(exception& e) {
    cerr << "exception: " << e.what() << '\n';
    return 1;
}
catch (...) {
    cerr << "Some exception\n";
    return 2;
}

//------------------------------------------------------------------------------
