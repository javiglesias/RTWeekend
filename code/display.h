#include "color.h"
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
math::vec3 pixel00LOC;
math::vec3 pixelDeltaU ;
math::vec3 pixelDeltaV ;
float focalLength = 1.f;
math::vec3 cameraCenter(0,0,0);
math::vec3 forward(0,0,-1);
math::vec3 up(0,1,0);
math::vec3 right(1,0,0);
int WIDTH;
int HEIGHT;
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
	float viewportHeigh = 2.0;
	float viewportWidth = viewportHeigh * (float(_w) / _h);

	auto viewportU = math::vec3(viewportWidth, 0, 0);
	auto viewportV = math::vec3(0, -viewportHeigh, 0);

	pixelDeltaU = viewportU / _w;
	pixelDeltaV = viewportV / _h;

	auto viewportUpperLeft = cameraCenter - math::vec3(0, 0, focalLength)
		- viewportU/2 - viewportV/2;
	pixel00LOC = viewportUpperLeft + 0.5 * (pixelDeltaU + pixelDeltaV);
}

inline
void drawFrame()
{
	while(true)
	{
		XNextEvent(display, &event);
		fprintf(stdout, "P3\n%d %d\n255\n", WIDTH, HEIGHT);
		for(long h = 0; h < HEIGHT; h++)
		{
			for(long w = 0; w < WIDTH; w++)
			{
				unsigned long long color;
				//RGB = (R*65535 + G*255 + B)
				auto pixelCenter = pixel00LOC + (w * pixelDeltaU) + (h * pixelDeltaV);
				auto rayDirection = pixelCenter - cameraCenter;
				ray r(cameraCenter, rayDirection);
				sphere sp(math::double3(0, 0, -1), 0.5f);
				color3 pixel = sp.color(r);
				framebuffer[h * HEIGHT + w]= color3(pixel.X(), pixel.Y(), pixel.Z());
				int R = framebuffer[h * HEIGHT + w].X() * 255;
				int G = framebuffer[h * HEIGHT + w].Y() * 255;
				int B = framebuffer[h * HEIGHT + w].Z() * 255;
				color =  (R << 24) | (G << 16) | B;
				fprintf(stdout, "%.f\t%.f \t%.f \n",
					framebuffer[h * HEIGHT + w ].X()  * 255, 
					framebuffer[h * HEIGHT + w].Y()  * 255,
					framebuffer[h * HEIGHT + w].Z() * 255 );
				XSetForeground(display, renderContext, color);
				XDrawPoint(display, window, renderContext, w, h);
				XFlush(display);
			}
		}
	}
}

inline
void CleanFrameBuffer()
{
	XUnmapWindow(display, window);
	XDestroySubwindows(display, window);
	XCloseDisplay(display);
}