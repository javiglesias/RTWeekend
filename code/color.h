#pragma once
#include "vector3.h"
#include "sphere.h"

using color3 = math::vec3;

inline 
void RenderPixel(color3 v)
{
	fprintf(stdout, "%.f \t%.f \t%.f \n",v[0] * 255.f, v[1] * 255.f, v[2] * 255.f);
}


inline 
void RenderPPM(int _w)
{
	float aspectRatio = 16.0/9.0;
	unsigned int imageWidth = _w;
	unsigned int imageHeight = imageWidth / aspectRatio;
	imageHeight = imageHeight < 1 ? 1 : imageHeight;

	float viewportHeigh = 12.0;
	float viewportWidth = viewportHeigh * (float(imageWidth) / imageHeight);

	auto viewportU = math::vec3(viewportWidth, 0, 0);
	auto viewportV = math::vec3(0, -viewportHeigh, 0);

	auto pixelDeltaU = viewportU / imageWidth;
	auto pixelDeltaV = viewportV / imageHeight;

	float focalLength = 1.f;
	math::vec3 cameraCenter(0,0,0);
	math::vec3 forward(0,0,-1);
	math::vec3 up(0,1,0);
	math::vec3 right(1,0,0);
	
	auto viewportUpperLeft = cameraCenter - math::vec3(0, 0, focalLength)
		- viewportU/2 - viewportV/2;
	auto pixel00LOC = viewportUpperLeft + 0.5 *
		(pixelDeltaU + pixelDeltaV);

	fprintf(stdout, "P3\n%d %d\n255\n", imageWidth, imageHeight);
	for (int i = 0; i < imageHeight; i++)
	{
		for (int j = 0; j < imageWidth; j++)
		{
			auto pixelCenter = pixel00LOC + (i * pixelDeltaU) + (j * pixelDeltaV);
			auto rayDirection = pixelCenter - cameraCenter;
			ray r(cameraCenter, rayDirection);
			sphere sp(math::double3(0, 0, -1), 0.5f);
			color3 pixel = sp.color(r);
			RenderPixel(pixel);
		}
	}
}