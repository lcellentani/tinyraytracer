#pragma once

#include "primitive.h"

namespace tinyraytracer
{

class sphere : public primitive {
public:
	sphere() = default;
	sphere(const vec3& c, float r) : mCenter(c) {
		set_radius(r);
	}
	~sphere() = default;

	void set_radius(float r) {
		mRadius = r;
		mSquaredRadius = mRadius * mRadius;
		mInvRadius = 1.0f / mRadius;
	}

	bool raycast(const ray& ray, float minDistance, float maxDistance, ray::hitinfo& hitinfo) override;

private:
	vec3 mCenter;
	float mRadius;

	float mSquaredRadius;
	float mInvRadius;
};

}