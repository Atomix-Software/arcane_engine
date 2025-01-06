#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace Arcane
{
	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);

		inline const glm::mat4& GetView() const { return m_View; }
		inline const glm::mat4& GetProjection() const { return m_Projection; }
		inline const glm::mat4& GetProjectionView() const { return GetProjection() * GetView(); }

		inline const glm::vec3& GetPosition() const { return m_Position; }
		inline float GetRotation() const { return m_Rotation; }

		inline void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateView(); }
		inline void SetRotation(float rotation) { m_Rotation = rotation; RecalculateView(); }

	private:
		void RecalculateView();

	private:
		glm::mat4 m_Projection;
		glm::mat4 m_View;

		glm::vec3 m_Position;
		float m_Rotation = 0.0f;
	};
}