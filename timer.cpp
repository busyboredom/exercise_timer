// An exercise timer that turns the primary monitor international orange for 5
// seconds every half hour. 

#include <X11/X.h>
#include <X11/Xlib.h>
#include <strings.h>
#include <memory.h>
#include <stdlib.h>
#include <stdio.h>
#include <chrono>
#include <thread>

void visual_alarm(int time){  
  // Creates a fullscreen orange window that lasts for "time" seconds
  XColor color;
  Colormap colormap;
  char international_orange[] = "#FF4F00";

  Display* dis = XOpenDisplay(NULL);
  colormap = DefaultColormap(dis, 0);
  XParseColor(dis, colormap, international_orange, &color);
  XAllocColor(dis, colormap, &color);
  
  Window win = XCreateSimpleWindow(dis, RootWindow(dis, 0), 0, 0, 10, 10, 0, 
      BlackPixel (dis, 0), color.pixel);  // The last argument is the window's
                                          // Color

  Atom wm_state = XInternAtom(dis, "_NET_WM_STATE", False);
  Atom fullscreen = XInternAtom(dis, "_NET_WM_STATE_FULLSCREEN", False);

  XEvent xev;
  memset(&xev, 0, sizeof(xev));
  xev.type = ClientMessage;
  xev.xclient.window = win;
  xev.xclient.message_type = wm_state;
  xev.xclient.format = 32;
  xev.xclient.data.l[0] = 1;
  xev.xclient.data.l[1] = fullscreen;
  xev.xclient.data.l[2] = 0;

  XMapWindow(dis, win);

  XSendEvent (dis, DefaultRootWindow(dis), False,
                  SubstructureRedirectMask | SubstructureNotifyMask, &xev);

  XFlush(dis);
  //Sleep "time" seconds, and then it'll close
  std::this_thread::sleep_for(std::chrono::seconds(time));
  XCloseDisplay(dis);

}

int main(){
  // Sets off a visual timer every 30 minutes
  while(true){
    visual_alarm(1); // This is so you can see it working right away, without
                     // giving up your monitor to it for 5s. 
    std::this_thread::sleep_for(std::chrono::minutes(30));
    visual_alarm(4);
  }
  return 0;
}
