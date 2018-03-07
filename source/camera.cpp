#include "camera.h"
#include "util.h"

namespace tinyraytracer
{

camera::camera(const vec3& lookfrom, const vec3& lookat, const vec3& up, float fovy, float aspect) {
	float theta = fovy * float(util::pi()) / 180.0f;
	float half_height = tan(theta * 0.5f);
	float half_width = aspect * half_height;
	mOrigin = lookfrom;
	vec3 w = (lookfrom - lookat).normalized();
	vec3 u = vec3::cross(up, w).normalized();
	vec3 v = vec3::cross(w, u);
	mBottomLeftCorner = mOrigin - half_width * u - half_height * v - w;
	mHorizontal = 2.0f * half_width * u;
	mVertical = 2.0f * half_height * v;
}

} // namespace tinyraytracer