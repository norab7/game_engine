#pragma once

struct AABB;

class I_AABB {

public:
	virtual ~I_AABB() = default;
	virtual AABB get_AABB() const = 0;
};
