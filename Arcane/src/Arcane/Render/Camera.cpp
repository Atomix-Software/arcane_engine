#include <arcpch.h>

#include "Camera.h"

namespace Arcane
{
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top) :
		m_Projection(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_View(), m_Position()
	{
		RecalculateView();
	}

	void OrthographicCamera::RecalculateView()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
			glm::rotate(glm::mat4(1.0f), m_Rotation, glm::vec3(0, 0, 1));

		m_View = glm::inverse(transform);
	}
}