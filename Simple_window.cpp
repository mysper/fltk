#include "Simple_window.h"

bool Simple_window::wait_for_button()
// modified event loop:
// handle all events (as per default), quit when button_pushed becomes true
// this allows graphics without control inversion
{
    show();
    button_pushed = false;
#if 1
    // Simpler handler
    while (!button_pushed) Fl::wait();
    Fl::redraw();
#else
    // To handle the case where the user presses the X button in the window frame
    // to kill the application, change the condition to 0 to enable this branch.
    Fl::run();
#endif
    return button_pushed;
}

//------------------------------------------------------------------------------

void Simple_window::cb_next(Address, Address pw)
// call Simple_window::next() for the window located at pw
{  
    reference_to<Simple_window>(pw).next();    
}

//------------------------------------------------------------------------------

void Simple_window::next()
{
    button_pushed = true;
    hide();
}

//------------------------------------------------------------------------------
