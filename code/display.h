#include "vector3.h"
#include <X11/X.h>
#include <X11/Xlib.h>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <unistd.h>

using color3 = math::vec3;

color3* framebuffer;
unsigned int WIDTH;
unsigned int HEIGHT;
Display * display;
Window window;
XEvent event;
GC renderContext;

inline
void InitFrameBuffer(unsigned int _w, unsigned int _h)
{
	WIDTH = _w;
	HEIGHT = _h;
	framebuffer = (color3*)malloc(sizeof(color3) * _w * _h);
	display = XOpenDisplay(NULL);
	if(display == NULL)
	{
		fprintf(stderr, "Display Error");
		exit(-2);
	}
	window = XCreateSimpleWindow(display, DefaultRootWindow(display),0, 0, _w, _h, 1,
		XBlackPixel(display, 0), XWhitePixel(display, 0));
	XStoreName(display, window, "Hello, Sailor");
	if(XMapWindow(display, window) == BadWindow)
	{
		fprintf(stderr, "Map Window Error");
		exit(-3);
	}
	XSelectInput(display, window, ExposureMask);
	renderContext = XCreateGC(display, window,0, NULL);
}

inline
void drawFrame()
{
	while(true)
	{
		XNextEvent(display, &event);
		if(event.type == Expose)
		{
			XDrawString(display, window, renderContext, 10,10, "Hello, Sailor", 20);
		}
		for(int h = 0; h < HEIGHT; h++)
			{
				for(int w = 0; w < WIDTH; w++)
				{
					unsigned long long color;
					//RGB = (R*65535 + G*255 + B)
					// fprintf(stderr, "pixel: %ld\n",(unsigned long) (h * HEIGHT + w));
					color = framebuffer[h * HEIGHT + w].X() * 255 * 65535
								+ framebuffer[h * HEIGHT + w].Y() * 255 * 256
								+ framebuffer[h * HEIGHT + w].Z() * 255;
					fprintf(stdout, "%.f\t%.f \t%.f \n",
						framebuffer[h * HEIGHT + w ].X()  * 255, 
						framebuffer[h * HEIGHT + w].Y()  * 255,
						framebuffer[h * HEIGHT + w].Z() * 255 );
					XSetForeground(display, renderContext, color);
					XDrawPoint(display, window, renderContext, w, h);
				}
			}
		XFlush(display);
	}
}

inline
void CleanFrameBuffer()
{
	XUnmapWindow(display, window);
	XDestroySubwindows(display, window);
	XCloseDisplay(display);
}