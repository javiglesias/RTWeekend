#pragma once

#include "vector3.h"
#include "math_utils.h"

struct ray
{
	math::double3 mOrigin;
	math::vec3 mDirection;
	ray() {}
	ray(const math::double3& _origin, const math::vec3& _direction) :
		mOrigin(_origin), mDirection(_direction) {}
	const math::double3& getOrigin() const { return mOrigin; }
	const math::vec3& getDirection() const { return mDirection;}

	math::double3 at(double _c) const 
	{
		return mOrigin + _c * mDirection;
	}
};

struct hitInfo
{
	math::double3 mPoint;
	math::vec3 mNormal;
	double t;
};

struct hittable
{
	virtual ~hittable() = default;
	virtual bool hit(ray& _r, double _ray_min, double _ray_max, hitInfo& info_) = 0;
};
