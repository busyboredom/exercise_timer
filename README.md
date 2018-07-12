This is the alarm I use to remind me to get up and exercise overy half hour. 

Runs just fine on Ubuntu 18.04.

It turns my primary monitor bright orange for 5 seconds every half hour. It is
very difficult to ignore. 

Compile with: 

> g++ timer.cpp -lX11 -o timer

Run with:

> ./timer

Alternatively, have it run in the background with:

> ./timer &
