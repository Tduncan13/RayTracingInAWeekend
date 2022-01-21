#pragma once 

#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray 
{
	public: 
		ray() {}
		ray(const point3& origin, const vec3& direction)
			: m_orig(origin), m_dir(direction) 
		{}

		point3 origin() const { return m_orig; }
		point3 direction() const { return m_dir; }

		point3 at(double t) const 
		{
			return m_orig + t * m_dir;
		}

	public: 
		point3 m_orig;
		vec3 m_dir;
};

#endif
