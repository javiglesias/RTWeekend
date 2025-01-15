#pragma once

#include "vector3.h"
#include "math_utils.h"

struct ray
{
	double3 mOrigin;
	vec3 mDirection;
};
typedef struct ray ray;
double3 point_at(ray _r, double _c) 
{
	vec3 rvec = constant_product(_c, _r.mDirection);
	double3 r = cross(_r.mOrigin, rvec);
	return r;
}

struct hitInfo
{
	double3 mPoint;
	vec3 mNormal;
	double t;
};
typedef struct hitInfo hitInfo;
