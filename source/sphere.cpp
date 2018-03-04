#include "sphere.h"

namespace tinyraytracer
{
	
bool sphere::raycast(const ray& ray, float minDistance, float maxDistance, ray::hitinfo& hitinfo) {
	vec3 oc = ray.origin() - mCenter;
	float a = vec3::dot(ray.direction(), ray.direction());
	float b = vec3::dot(oc, ray.direction());
	float c = vec3::dot(oc, oc) - mSquaredRadius;
	float discriminant = b * b - a * c;
	if (discriminant > 0) {
		float temp = (-b - sqrt(discriminant)) / a;
		if (temp < maxDistance && temp > minDistance) {
			hitinfo.t = temp;
			hitinfo.point = ray.point_at_parameter(hitinfo.t);
			hitinfo.normal = (hitinfo.point - mCenter) * mInvRadius;
			hitinfo.normal.normalize();
			return true;
		}
		temp = (-b + sqrt(discriminant)) / a;
		if (temp < maxDistance && temp > minDistance) {
			hitinfo.t = temp;
			hitinfo.point = ray.point_at_parameter(hitinfo.t);
			hitinfo.normal = (hitinfo.point - mCenter) * mInvRadius;
			hitinfo.normal.normalize();
			return true;
		}
	}
	return false;
}


} // namespace tinyraytracer