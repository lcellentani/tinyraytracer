#pragma once

#include "vec3.h"
#include "ray.h"

namespace tinyraytracer
{

class camera {
public:
	camera(const vec3& lookfrom, const vec3& lookat, const vec3& up, float fovy, float aspect, float aperture, float focusDistance);

	void set_origin(const vec3& origin) {
		mOrigin = origin;
	}

	void set_horizontal(const vec3& horizontal) {
		mHorizontal = horizontal;
	}

	void set_vertical(const vec3& vertical) {
		mVertical = vertical;
	}

	ray get_ray(float s, float t);

private:
	vec3 mOrigin;
	vec3 mBottomLeftCorner;
	vec3 mHorizontal;
	vec3 mVertical;
	vec3 mRight;
	vec3 mUp;
	vec3 mDepth;
	float mLensRadius;
};

} // namespace tinyraytracer