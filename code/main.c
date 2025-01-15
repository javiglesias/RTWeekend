#include "xServer.h"
#include "color.h"
#include <stdlib.h>

int main(int argc, char** argv)
{
	int resolution = 400;
	if(argc > 1) 
		resolution = atoi(argv[1]);
	// char* wayland_display = getenv("WAYLAND_DISPLAY");
    // if(wayland_display != NULL)
    // {
	// 	return wayland_display_connect();
	// } else
	X_create_window(resolution, resolution);
	RenderPPM(resolution);
	window_loop();
}