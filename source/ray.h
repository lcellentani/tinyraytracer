#pragma once

#include "vec3.h"

namespace tinyraytracer
{


class ray {
public:
	struct hitinfo {
		float t;
		vec3 point;
		vec3 normal;
	};
public:
	ray() = default;
	ray(const vec3& o, const vec3& d) : mOrigin(o), mDirection(d) {}

	vec3 origin() const { return mOrigin; }
	vec3 direction() const { return mDirection; }

	vec3 point_at_parameter(float t) const {
		return mOrigin + t * mDirection;
	}

private:
	vec3 mOrigin;
	vec3 mDirection;
};

} // namespace tinyraytracer