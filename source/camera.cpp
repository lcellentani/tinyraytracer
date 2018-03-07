#include "camera.h"
#include "util.h"
#include <cmath>

namespace tinyraytracer
{

camera::camera(const vec3& lookfrom, const vec3& lookat, const vec3& up, float fovy, float aspect, float aperture, float focusDistance) {
	mLensRadius = aperture * 0.5f;
	float theta = fovy * float(util::pi()) / 180.0f;
	float half_height = std::tan(theta * 0.5f);
	float half_width = aspect * half_height;
	mOrigin = lookfrom;
	mDepth = (lookfrom - lookat).normalized();
	mRight = vec3::cross(up, mDepth).normalized();
	mUp = vec3::cross(mDepth, mRight);
	mBottomLeftCorner = mOrigin - (half_width * mRight * focusDistance) - (half_height * mUp * focusDistance) - (focusDistance * mDepth);
	mHorizontal = 2.0f * half_width * mRight * focusDistance;
	mVertical = 2.0f * half_height * mUp * focusDistance;
}

ray camera::get_ray(float s, float t) {
	vec3 rd = mLensRadius * util::random_in_unit_sphere();
	vec3 offset = mRight * rd.x() + mUp * rd.y();
	return ray(mOrigin + offset, mBottomLeftCorner + s * mHorizontal + t * mVertical - mOrigin - offset);
}

} // namespace tinyraytracer