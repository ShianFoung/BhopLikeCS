#pragma once

#include <glm/glm.hpp>

struct BoundingBox
{
	glm::vec3 min;
	glm::vec3 max;
	glm::vec3 size;
	glm::vec3 halfSize;
	glm::vec3 center;

	inline static BoundingBox FromTwoPoints(const glm::vec3& firstPoint, const glm::vec3& secondPoint)
	{
		BoundingBox boundingBox;
		boundingBox.min = glm::min(firstPoint, secondPoint);
		boundingBox.max = glm::max(firstPoint, secondPoint);
		boundingBox.size = boundingBox.max - boundingBox.min;
		boundingBox.halfSize = boundingBox.size * 0.5f;
		boundingBox.center = boundingBox.min + boundingBox.halfSize;

		return boundingBox;
	}

	inline constexpr BoundingBox& operator=(const BoundingBox& boundingBox)
	{
		this->min = boundingBox.min;
		this->max = boundingBox.max;
		this->size = boundingBox.size;
		this->halfSize = boundingBox.halfSize;
		this->center = boundingBox.center;

		return *this;
	}
};
