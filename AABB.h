#pragma once

namespace _AABB {
	class AABB {
		// Calculate Heuristic for positioning in tree format
		float get_surface_area();
	public:
		float minx, miny, minz, maxx, maxy, maxz, surface_area;

		AABB();
		AABB(float minx, float miny, float minz, float maxx, float maxy, float maxz);

		bool overlaps(const AABB& obj) const;
		bool contains(const AABB& obj) const;

		AABB merge(const AABB& obj) const;
		AABB intersection(const AABB& obj) const;

		float get_width();
		float get_height();
		float get_depth();
	};
}