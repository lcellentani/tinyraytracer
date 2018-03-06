#include "sphere.h"

namespace tinyraytracer
{
	
bool sphere::raycast(const ray& r, float minDistance, float maxDistance, rayhit& hitinfo) {
	vec3 oc = r.origin() - mCenter;
	float a = vec3::dot(r.direction(), r.direction());
	float b = vec3::dot(oc, r.direction());
	float c = vec3::dot(oc, oc) - mSquaredRadius;
	float discriminant = b * b - a * c;
	if (discriminant > 0) {
		float temp = (-b - sqrt(discriminant)) / a;
		if (temp < maxDistance && temp > minDistance) {
			hitinfo.t = temp;
			hitinfo.point = r.point_at_parameter(hitinfo.t);
			hitinfo.normal = (hitinfo.point - mCenter) * mInvRadius;
			hitinfo.normal.normalize();
			hitinfo.material = mMaterial.get();
			return true;
		}
		temp = (-b + sqrt(discriminant)) / a;
		if (temp < maxDistance && temp > minDistance) {
			hitinfo.t = temp;
			hitinfo.point = r.point_at_parameter(hitinfo.t);
			hitinfo.normal = (hitinfo.point - mCenter) * mInvRadius;
			hitinfo.normal.normalize();
			hitinfo.material = mMaterial.get();
			return true;
		}
	}
	return false;
}


} // namespace tinyraytracer