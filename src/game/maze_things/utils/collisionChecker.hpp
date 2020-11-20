#pragma once

#include <glm/glm.hpp>

static bool coll(glm::vec4 left, glm::vec4 right)
{
	if (left[2] < right[0] || right[2] < left[0]) return false;
	if (left[3] < right[1] || right[3] < left[1]) return false;

	return true;
};