#pragma once

#include "ray.h"

struct sphere : public hittable
{
	sphere(math::double3 _center, double _radius) : center(_center), radius(_radius) {}
	bool hit(ray& _r, double _ray_min, double _ray_max, hitInfo& info_) override
	{
		math::vec3 centerSphere = center - _r.getOrigin();
		auto a = _r.getDirection().length_sq();//dot(_r.getDirection(), _r.getDirection());
		auto h = dot(_r.getDirection(), centerSphere);
		auto b = -2.0 * h;
		auto c = centerSphere.length_sq() - radius * radius;
		auto discriminant = h*h - a*c;
		if(discriminant < 0)
			return false;
		
		info_.t = (h - std::sqrt(discriminant)) / a;
		info_.mPoint = _r.at(info_.t);
		info_.mNormal = (info_.mPoint - center) / radius;
		return true;
	}

	math::vec3 color(ray _r)
	{
		hitInfo info;
		if(hit(_r, 1, 1, info))
		{
			math::vec3 normal = unit_vector(_r.at(info.t) - math::vec3(0.f, 0.f, -1.f));
			return 0.5 * math::vec3(normal.X() + 1, normal.Y() + 1, normal.Z() + 1);
		}
		// not hit
		math::vec3 unitDirection = unit_vector(_r.getDirection());
		auto alpha = 0.5 * (unitDirection.Y() + 1.f);
		return (1.0-alpha) * math::vec3(1.f) + alpha * math::vec3(0.2f, 0.7f, 1.f);
	}
	math::double3 center{0, 0, -1};
	double radius{.5f};
};
