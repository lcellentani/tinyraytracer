#pragma once

#include "vec3.h"
#include "ray.h"

namespace tinyraytracer
{

class camera {
public:
	camera()
		: mOrigin(0.0f, 0.0f, 0.0f)
		, mBottomLeftCorner(-2.0f, -1.0f, -1.0f)
		, mHorizontal(4.0f, 0.0f, 0.0f)
		, mVertical(0.0f, 2.0f, 0.0f) {
	}

	void set_origin(const vec3& origin) {
		mOrigin = origin;
	}

	void set_horizontal(const vec3& horizontal) {
		mHorizontal = horizontal;
	}

	void set_vertical(const vec3& vertical) {
		mVertical = vertical;
	}

	ray get_ray(float u, float v) {
		return ray(mOrigin, mBottomLeftCorner + u * mHorizontal + v * mVertical - mOrigin);
	}

private:
	vec3 mOrigin;
	vec3 mBottomLeftCorner;
	vec3 mHorizontal;
	vec3 mVertical;
};

} // namespace tinyraytracer