#pragma once

#include "material.h"
#include "util.h"

namespace tinyraytracer
{

class lambertian : public material {
public:
	lambertian(const vec3& a) : mAlbedo(a) {};

	bool scatter(const ray& r, const rayhit& hit, vec3& attenuation, ray& scattered) const override {
		(void)r;
		vec3 target = hit.point + hit.normal + util::random_in_unit_sphere();
		scattered = ray(hit.point, target - hit.point);
		attenuation = mAlbedo;
		return true;
	}

private:
	vec3 mAlbedo;
};

} // namespace tinyraytracer