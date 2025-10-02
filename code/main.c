#include "backend.h"
#include "math_utils.h"
#include "xServer.h"
#include <stdlib.h>

int main(int argc, char** argv)
{
	int n_game_windows = 1;
	i2d resolution;

	if(argc > 1) 
		n_game_windows = atoi(argv[2]);

		resolution.v[0] = resolution.v[1]= 400;

	backend_init(resolution);
	time_t start_time = time(NULL);
    while (!should_window_close(render_backend.pd))
	{
        time_t end_time = time(NULL);
        if( end_time - start_time >= 2)
        {
			fprintf(stderr, "end: %ld",(end_time - start_time));
			backend_loop();
	    	start_time = time(NULL);
        }
	}
}