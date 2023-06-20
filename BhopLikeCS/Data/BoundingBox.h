#pragma once

#include <glm/glm.hpp>

struct BoundingBox
{
	glm::vec3 min;
	glm::vec3 max;

	inline constexpr static BoundingBox FromTwoPoints(const glm::vec3& firstPoint, const glm::vec3& secondPoint)
	{
		BoundingBox boundingBox;
		boundingBox.min = glm::min(firstPoint, secondPoint);
		boundingBox.max = glm::max(firstPoint, secondPoint);

		return boundingBox;
	}

	inline constexpr static BoundingBox FromTwoBoundingBoxes(const BoundingBox& firstBox, const BoundingBox& secondBox)
	{
		return BoundingBox::FromTwoPoints(glm::min(firstBox.min, secondBox.min), glm::max(firstBox.max, secondBox.max));
	}

	inline constexpr static BoundingBox FromPlayer(const glm::vec3& position, const float halfSize, const float height)
	{
		BoundingBox boundingBox;
		boundingBox.min = glm::vec3(position.x - halfSize, position.y - halfSize, position.z);
		boundingBox.max = glm::vec3(position.x + halfSize, position.y + halfSize, position.z + height);

		return boundingBox;
	}

	constexpr BoundingBox() = default;

	inline bool IntersectWithBox(const BoundingBox& boundingBox)
	{
		return this->min.x <= boundingBox.max.x && this->max.x >= boundingBox.min.x &&
			   this->min.y <= boundingBox.max.y && this->max.y >= boundingBox.min.y &&
			   this->min.z <= boundingBox.max.z && this->max.z >= boundingBox.min.z;
	}

	inline constexpr BoundingBox& operator=(const BoundingBox& boundingBox)
	{
		this->min = boundingBox.min;
		this->max = boundingBox.max;

		return *this;
	}
};
