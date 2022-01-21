#pragma once

#ifndef MATERIAL_H
#define MATERIAL_H

#include "rtweekend.h"

struct hit_record;

class material 
{
	public:
		virtual bool scatter(
			const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
		) const = 0;

};

class lambertian : public material 
{
	public: 
		lambertian(const color& a) : m_albedo(a) {}

		virtual bool scatter(
			const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
		) const override 
		{
			auto scatter_direction = rec.normal + random_unit_vector();

			// Catch degenerate scatter direction
			if (scatter_direction.near_zero())
				scatter_direction = rec.normal;

			scattered = ray(rec.p, scatter_direction);
			attenuation = m_albedo;
			return true;
		}

	public: 
		color m_albedo;
};

class metal : public material
{
	public: 
		metal(const color& a) : m_albedo(a) {}

		virtual bool scatter(
			const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
		) const override 
		{
			vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
			scattered = ray(rec.p, reflected);
			attenuation = m_albedo;
			return (dot(scattered.direction(), rec.normal) > 0);
		}

	public: 
		color m_albedo;
};
#endif
