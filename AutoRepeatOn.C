#include<stdlib.h>
#include<iostream>
#include<X11/Xlib.h>
using namespace std;
int main ()
 {Display* display;
  if (!(display=XOpenDisplay(NULL)))
    cout<<"Could not open display."<<endl;
  else
   {XAutoRepeatOn(display);
    XCloseDisplay(display);
   }
  return 0;
 }
