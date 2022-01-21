#pragma once 

#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable 
{
	public: 
		sphere() {}
		sphere(point3 cen, double r, shared_ptr<material> m) 
			: m_center(cen), m_radius(r), m_mat_ptr(m) {};

		virtual bool hit(
			const ray& r, double t_min, double t_max, hit_record& rec) const override;

	public: 
		point3 m_center;
		double m_radius;
		shared_ptr<material> m_mat_ptr;
};

bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const 
{
	vec3 oc = r.origin() - m_center;
	auto a = r.direction().length_squared();
	auto half_b = dot(oc, r.direction());
	auto c = oc.length_squared() - m_radius * m_radius;
	
	auto discriminant = half_b * half_b - a * c;
	if (discriminant < 0) return false;
	auto sqrtd = sqrt(discriminant);

	// Find the nearest root that lies in the acceptatble range.
	auto root = (-half_b - sqrtd) / a;
	if (root < t_min || t_max < root) 
	{
		root = (-half_b + sqrtd) / a;
		if(root < t_min || t_max < root)
			return false;
	}

	rec.t = root;
	rec.p = r.at(rec.t);
	rec.normal = (rec.p - m_center) / m_radius;
	vec3 outward_normal = (rec.p - m_center) / m_radius;
	rec.set_face_normal(r, outward_normal);
	rec.mat_ptr = m_mat_ptr;

	return true;
}

#endif
