//  This is the x11 render backend, it is called "server" because its a server xD
#pragma once
#include "vector3.h"
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdlib.h>
#include <memory.h>

typedef struct 
{
    vec3 color;
} pixel;
typedef struct 
{
    Window window;
    Window window_root;
    Display* display;
    pixel* pPixels;
    int window_width;
    int window_height;
    int should_close_window;
} device;

XGCValues* pixelValues;
GC pixel_context;

void take_screenshot(device _pd);

static device X_create_window(int width, int height)
{
    device pd;
    pd.window_width = width;
    pd.window_height = height;
    // Status threadStatus = XInitThreads();
    pd.display = XOpenDisplay(NULL);
    int disN = DefaultScreen(pd.display);
    if(pd.display != NULL)
    {
        pixelValues = (XGCValues*)malloc(pd.window_height * pd.window_width * sizeof(XGCValues));
        memset(pixelValues, 0xff, pd.window_height * pd.window_width * sizeof(XGCValues));
        XLockDisplay(pd.display);
        XNoOp(pd.display);
        int AttributeValueMask = CWBackPixel;
        XSetWindowAttributes WindowAttributes = {};
        WindowAttributes.background_pixel = 0x0000ff;
        pd.window_root= XDefaultRootWindow(pd.display);
        pd.window = XCreateWindow(pd.display, pd.window_root, 
            0, 0, 
            width, height, 
            0, CopyFromParent, CopyFromParent, CopyFromParent,
            AttributeValueMask, &WindowAttributes);

        XSelectInput(pd.display, pd.window, ExposureMask | KeyPressMask);
        XMapWindow  (pd.display, pd.window);
        XStoreName  (pd.display, pd.window, "RTWeekend");
        pixel pixels [pd.window_width *pd.window_height];
        pd.pPixels = pixels;
        pd.should_close_window = 0;
        pixel_context = XCreateGC(pd.display, pd.window_root, GCForeground, pixelValues);
        XUnlockDisplay(pd.display);
    }
    return pd;
}
void present(device pd)
{
    // if(XPending(pd.display))
    // {
        XEvent event;
        XNextEvent(pd.display, &event);
        if (event.type == KeyPress)
        {
            XKeyPressedEvent* key_event = (XKeyPressedEvent*) &event;
            if(key_event->keycode == XKeysymToKeycode(pd.display, XK_F1))
                take_screenshot(pd);
            if(key_event->keycode == XKeysymToKeycode(pd.display, XK_Escape))
            {
                XDestroyWindow(pd.display, pd.window);
                pd.should_close_window = 1;
            }
        }
    // }
    for (int i = 0; i < pd.window_width; i++)
    {
        for (int j = 0; j < pd.window_height; j++)
        {
            int pixelHex = pd.pPixels[i*j].color.v[0] * 16 * 16 * 16 * 16 +
                pd.pPixels[i*j].color.v[1] * 16 * 16 +
                pd.pPixels[i*j].color.v[2];
            pixelValues[i*j].foreground = pixelHex;
            XFillRectangle(pd.display, pd.window, pixel_context, i, j, 1, 1);
        }
    }
    XChangeGC(pd.display, pixel_context, GCForeground, pixelValues);
    XFlush(pd.display);
    // }
}

void add_pixel_color(int _x, int _y, vec3 _color, device pd)
{
    pd.pPixels[_x *_y].color = _color;
    // ->v
}
void take_screenshot(device _pd)
{
    FILE* fImage = fopen("image.ppm", "w+");
    fprintf(fImage, "P3\n%d %d\n255\n", _pd.window_width, _pd.window_height);
    for (int i = 0; i < _pd.window_width; i++)
    {
        for (int j = 0; j < _pd.window_height; j++)
        {
            fprintf(fImage, "%.f \t%.f \t%.f \n",_pd.pPixels[i*j].color.v[0] * 255.f, 
                _pd.pPixels[i*j].color.v[1] * 255.f, 
                _pd.pPixels[i*j].color.v[2] * 255.f);
            }
    }
    fclose(fImage);
}

int should_window_close(device _pd)
{
    return _pd.should_close_window;
}
void clean_screen(device _pd)
{
    XClearWindow(_pd.display, _pd.window);
}

void clean_device (device pd)
{
    XDestroyWindow(pd.display, pd.window);
    XCloseDisplay(pd.display);
}