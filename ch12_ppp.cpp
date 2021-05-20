#include <iostream>
#include <vector>
#include <string>
#include <sstream>


//#include "error.h"
#include "Simple_window.h"
#include "Graph.h"


int main()
{
    using namespace Graph_lib;
    
    Point tl(150, 150);
    Simple_window win(tl, 600, 400, "My window");

	Graph_lib::Axis xa{Axis::x, Point{20,300},280,10,"x axis"};
	xa.set_color(Color::green);
	win.attach(xa);

	Image ii{Point{100,50}, "image.jpg"};
	win.attach(ii);


	Function sine{sin, 0, 100, Point{20,150}, 1000, 50, 50};
	sine.set_color(Color::blue);
	win.attach(sine);

	Graph_lib::Polygon poly;
	poly.add(Point{300,200});
	poly.add(Point{350,100});
	poly.add(Point{400,200});

	poly.set_color(Color::red);

	win.attach(poly);

	Graph_lib::Rectangle r{Point{200, 200}, 100, 50};
	r.set_color(Color::red);
	win.attach(r);

	Graph_lib::Text t{Point(150, 150), "Hello, graphical world!"};
	t.set_color(Color::red);
	win.attach(t);


    win.wait_for_button();
}
