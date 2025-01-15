#pragma once
#include "vector3.h"
#include <X11/Xlib.h>
// #include <xcb/xcb.h>
static vec3* pPixels;
static Display* display;
static Window window;
static Window window_root;
static int window_width = 1;
static int window_height = 1;
static int X_create_window(int width, int height)
{
    window_width = width;
    window_height = height;
    // Status threadStatus = XInitThreads();
    display = XOpenDisplay(NULL);
    int disN = DefaultScreen(display);
    if(display != NULL)
    {
        // XLockDisplay(display);
        unsigned long blackColor = BlackPixel(display, 0);
        unsigned long whiteColor = WhitePixel(display, 0);
        // int connectionN = ConnectionNumber(display);
        // int defaultDetpth = DefaultDepth(display, 0);
        // int screens = ScreenCount(display);

        // fprintf(stderr, "Bc: %ld, Wc: %ld, CNumber %d, depth: %d ", 
        //     blackColor, whiteColor, connectionN, defaultDetpth);
        // XNoOp(display);
        window_root= RootWindow(display, disN);
        window = XCreateSimpleWindow(display, window_root, 
            0, 0, 
            width, height, 
            1, 
            '0x0000ff', '0x00ff00');
        XSelectInput(display, window, ExposureMask | KeyPressMask);
        XMapWindow(display, window);
        XStoreName(display, window, "RTWeekend");
        vec3 pixels [window_width * window_height];
        pPixels = &pixels[0];
        // XUnlockDisplay(display);
    }
}
void window_loop()
{
    Atom WM_DELETE_WINDOW = XInternAtom(display, "WM_DELETE_WINDOW", False); 
    XSetWMProtocols(display, window, &WM_DELETE_WINDOW, 1); 
    XEvent event;
    XGCValues pixelValue;
    FILE* fImage = fopen("image.ppm", "w+");
    fprintf(fImage, "P3\n%d %d\n255\n", window_width, window_height);
    while(1)
    {
        if(XPending(display))
        {
            XNextEvent(display, &event);
            if ((event.type == ClientMessage) && 
                    (event.xclient.data.l[0] == WM_DELETE_WINDOW))
            {
                for (int i = 0; i < window_width; i++)
                {
                    for (int j = 0; j < window_height; j++)
                    {
                    fprintf(fImage, "%.f \t%.f \t%.f \n",pPixels[i*j].v[0] * 255.f, 
                            pPixels[i*j].v[1] * 255.f, 
                            pPixels[i*j].v[2] * 255.f);
                    }
                }
                fclose(fImage);
                break;
            }
        } else {
            for (int i = 0; i < window_width; i++)
            {
                for (int j = 0; j < window_height; j++)
                {
                    int pixelHex = pPixels[i*j].v[0] * 16 * 16 * 16 * 16 +
                        pPixels[i*j].v[1] * 16 * 16 +
                        pPixels[i*j].v[2];
                    pixelValue.foreground = pixelHex;
                    fprintf(stdout, "Pixel %d, %d: %d - %.f \t%.f \t%.f \n",
                        i, j, pixelHex,
                        pPixels[i].v[0] * 255.f, 
                        pPixels[i].v[1] * 255.f, 
                        pPixels[i].v[2] * 255.f);
                    GC pixel_context = XCreateGC(display, window_root, GCForeground, &pixelValue);
                    XFillRectangle(display, window, pixel_context, 
                    i, j, 
                    1, 1);
                    XFlush(display);
                }
            }
        }
    }
    XDestroyWindow(display, window);
    XCloseDisplay(display);
}
void add_pixel_color(int _x, int _y, vec3 _color)
{
    pPixels[_x *_y] = _color;
    // ->v
}