#pragma once

#include "ray.h"

struct sphere
{
	double3 center;
	double radius;
};

typedef struct sphere sphere;

int hit(sphere _s, ray _r, double _ray_min, double _ray_max, hitInfo info_)
{
	vec3 centerSphere = substract(_s.center, _r.mOrigin);
	double a = length(_r.mDirection);//dot(_r.getDirection(), _r.getDirection());
	double h = dot(_r.mDirection, centerSphere);
	double b = -2.0 * h;
	double c = length(centerSphere) - _s.radius * _s.radius;
	double discriminant = h*h - a*c;
	if(discriminant < 0)
		return 0;
	
	info_.t = (h - discriminant) / a;
	info_.mPoint = point_at(_r, info_.t);
	info_.mNormal = division(substract(info_.mPoint, _s.center), _s.radius);
	return 1;
}

vec3 color(sphere _s, ray _r)
{
	hitInfo info;
	if(hit(_s, _r, 1, 1, info))
	{
		vec3 minus1 = {0.f, 0.f, -1.f};
		vec3 normal = unit_vector(
			substract(
				point_at(_r, info.t), 
				minus1
			)
		);
		vec3 plus1 = {normal.v[0] + 1, normal.v[1] + 1, normal.v[2] + 1};
		return constant_product(0.5, plus1);
	}
	// not hit
	vec3 unitDirection = unit_vector(_r.mDirection);
	vec3 one = {1.0, 1.0, 1.0};
	double alpha = 0.5 * (unitDirection.v[1] + 1.f);
	vec3 rgb_ref = {0.2, 0.7, 1.0};
	return cross(constant_sum(
		alpha, 
		constant_product(
			(1.0-alpha), 
			one)),
			rgb_ref
		);
}