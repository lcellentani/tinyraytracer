#include <iostream>
#include <cstdint>
#include <vector>
#include <memory>
#include <limits>
#include <random>

#include "vec3.h"
#include "ray.h"
#include "camera.h"
#include "sphere.h"

using namespace tinyraytracer;

vec3 color(const ray& r, const std::vector<std::unique_ptr<primitive>>& primitives) {
	ray::hitinfo hitinfo;
	for (auto& primitive : primitives) {
		if (primitive->raycast(r, 0.0f, std::numeric_limits<float>::max(), hitinfo)) {
			auto& normal = hitinfo.normal;
			return 0.5f * vec3(normal.x() + 1.0f, normal.y() + 1.0f, normal.z() + 1.0f);
		}
	}
	vec3 d = r.direction().normalized();
	float t = 0.5f * (d.y() + 1.0f);
	return ((1.0f - t) * vec3(1.0f)) + (t * vec3(0.5f, 0.7f, 1.0f));
}

void main() {
	std::random_device rd;
	std::mt19937 gen(rd());

	int32_t nx = 400;
	int32_t ny = 200;
	int32_t ns = 100;
	std::cout << "P3\n" << nx << " " << ny << "\n255\n";
	vec3 lower_left_corner(-2.0f, -1.0f, -1.0f);
	vec3 horizontal(4.0f, 0.0f, 0.0f);
	vec3 vertical(0.0f, 2.0f, 0.0f);
	vec3 origin(0.0f, 0.0f, 0.0f);
	std::vector<std::unique_ptr<primitive>> primitives;
	primitives.push_back(std::make_unique<sphere>(vec3(0.0f, 0.0f, -1.0f), 0.5f));
	primitives.push_back(std::make_unique<sphere>(vec3(0.0f, -100.5f, -1.0f), 100.0f));
	camera mainCamera;
	for (int32_t j = ny - 1; j >= 0; j--) {
		for (int32_t i = 0; i < nx; i++) {
			vec3 c;
			for (int32_t s = 0; s < ns; s++) {
				float u = float(i + std::generate_canonical<double, 10>(gen)) / float(nx);
				float v = float(j + std::generate_canonical<double, 10>(gen)) / float(ny);
				ray r = mainCamera.get_ray(u, v);
				c += color(r, primitives);
			}
			c /= float(ns);

			int ir = int(255.99f * c.r());
			int ig = int(255.99f * c.g());
			int ib = int(255.99f * c.b());
			std::cout << ir << " " << ig << " " << ib << "\n";
		}
	}
}
