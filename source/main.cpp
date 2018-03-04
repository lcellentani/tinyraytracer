#include <iostream>
#include <cstdint>
#include <vector>
#include <memory>
#include <limits>

#include "vec3.h"
#include "ray.h"
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
	int32_t nx = 200;
	int32_t ny = 100;
	std::cout << "P3\n" << nx << " " << ny << "\n255\n";
	vec3 lower_left_corner(-2.0f, -1.0f, -1.0f);
	vec3 horizontal(4.0f, 0.0f, 0.0f);
	vec3 vertical(0.0f, 2.0f, 0.0f);
	vec3 origin(0.0f, 0.0f, 0.0f);
	std::vector<std::unique_ptr<primitive>> primitives;
	primitives.push_back(std::make_unique<sphere>(vec3(0.0f, 0.0f, -1.0f), 0.5f));
	primitives.push_back(std::make_unique<sphere>(vec3(0.0f, -100.5f, -1.0f), 100.0f));
	for (int32_t j = ny - 1; j >= 0; j--) {
		for (int32_t i = 0; i < nx; i++) {
			float u = (float)i / (float)nx;
			float v = (float)j / (float)ny;
			ray r(origin, lower_left_corner + u * horizontal + v * vertical);
			vec3 c = color(r, primitives);

			int ir = int(255.99f * c.r());
			int ig = int(255.99f * c.g());
			int ib = int(255.99f * c.b());
			std::cout << ir << " " << ig << " " << ib << "\n";
		}
	}
}
