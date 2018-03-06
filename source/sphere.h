#pragma once

#include "primitive.h"
#include "material.h"
#include <memory>

namespace tinyraytracer
{

class sphere : public primitive {
public:
	sphere() = default;
	sphere(const vec3& c, float r, std::unique_ptr<material> m) : mCenter(c), mMaterial(std::move(m)) {
		set_radius(r);
	}
	~sphere() = default;

	void set_radius(float r) {
		mRadius = r;
		mSquaredRadius = mRadius * mRadius;
		mInvRadius = 1.0f / mRadius;
	}

	bool raycast(const ray& r, float minDistance, float maxDistance, rayhit& hit) override;

private:
	vec3 mCenter;
	float mRadius;
	std::unique_ptr<material> mMaterial;

	float mSquaredRadius;
	float mInvRadius;
};

}