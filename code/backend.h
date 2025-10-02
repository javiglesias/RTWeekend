#pragma once
#include "math_utils.h"
#include "xServer.h"
#include "color.h"
#include <time.h>

typedef struct
{
    device pd;
}backend;
static backend render_backend;

typedef struct{
    vec3 camera_position;
} game_data;
static game_data g_data;

void backend_init(i2d _windows_resulution)
{
    render_backend.pd = X_create_window(_windows_resulution.v[0], _windows_resulution.v[1]);
}

void clean_devices()
{
    clean_device(render_backend.pd);
}

void RenderPPM(int _w, device pd)
{
	float aspectRatio = 16.0/9.0;
	unsigned int imageWidth = _w;
	unsigned int imageHeight = imageWidth / aspectRatio;
	imageHeight = imageHeight < 1 ? 1 : imageHeight;

	float viewportHeigh = 2.0;
	float viewportWidth = viewportHeigh * ((float)imageWidth / imageHeight);

	vec3 viewportU = {viewportWidth, 0, 0};
	vec3 viewportV = {0, -viewportHeigh, 0};

	vec3 pixelDeltaU = {viewportU.v[0] / imageWidth,viewportU.v[1] / imageWidth,
						viewportU.v[2] / imageWidth};
	vec3 pixelDeltaV = {viewportV.v[0] / imageHeight, viewportV.v[1] / imageHeight,
						viewportV.v[2] / imageHeight};

	float focalLength = 1.f;
	vec3 cameraCenter = {0,0,0};
	vec3 forward = {0,0,-1};
	vec3 up = {0,1,0};
	vec3 right = {1,0,0};
	vec3 focalVec = {0, 0, focalLength};
	vec3 viewportUpperLeft = substract(
		substract(
			substract(cameraCenter, focalVec) , 
			division(viewportU,2)),
		division(viewportV, 2));
	vec3 pixel00LOC = cross(
		constant_sum(0.5, viewportUpperLeft),
		sum(pixelDeltaU, pixelDeltaV));
	for (int i = 0; i < imageHeight; i++)
	{
		for (int j = 0; j < imageWidth; j++)
		{
			vec3 pixelCenter = sum(
				pixel00LOC,
				sum(
					constant_product(j, pixelDeltaU), 
					constant_product(i, pixelDeltaV)
				)
			);
			vec3 rayDirection = substract(pixelCenter, cameraCenter);
			ray r;
			r.mOrigin = cameraCenter;
			r.mDirection = rayDirection;
			double3 minus1 = {0, 0, -1};			
			sphere sp = {minus1, 0.5};
			color3 pixel = color(sp, r);
			add_pixel_color(i, j, pixel, pd);
		}
	}
}

void process_logic()
{

}

void clean_background(vec3 _color)
{
    clean_screen(render_backend.pd);
}

void backend_loop()
{
    vec3 color;
    RenderPPM(render_backend.pd.window_width, render_backend.pd);
    present(render_backend.pd);

}