#pragma once
#include "sphere.h"
#include "xServer.h"
typedef vec3 color3;

void RenderPixel(color3 _v)
{
	fprintf(stdout, "%.f \t%.f \t%.f \n",_v.v[0] * 255.f, _v.v[1] * 255.f, 
					_v.v[2] * 255.f);
}

void RenderPPM(int _w)
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
			add_pixel_color(i, j, pixel);
			// RenderPixel(pixel);
		}
	}
}