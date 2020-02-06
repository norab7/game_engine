#pragma once

namespace _Process_AABB {
	class Process_AABB {

	public:
		virtual ~Process_AABB() = default;
		virtual void get_AABB() = 0;
	};
}