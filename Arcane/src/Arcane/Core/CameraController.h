#pragma once

#include "Arcane/Core/Timestep.h"

#include "Arcane/Events/ApplicationEvent.h"
#include "Arcane/Events/MouseEvent.h"

#include "Arcane/Render/Camera.h"

namespace Arcane
{
	class ARC_API OrthoCameraController
	{
	public:
		OrthoCameraController(float aspectRatio, float zoom = 1.0f);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& event);

		void OnResize(float width, float height);

		inline const Shared<OrthographicCamera>& GetCamera() { return m_Camera; }
		inline const glm::vec3& GetPosition() const { return m_Position; }

		inline const float GetRotation() const { return m_Rotation; }
		
		inline const float GetAspectRatio() const { return m_AspectRatio; }
		inline const float GetSpeed() const { return m_Speed; }

		inline void SetSpeed(float speed) { m_Speed = speed; }

	private:
		bool OnWindowResized(WindowResizeEvent& event);
		bool OnMouseScrolled(MouseScrolledEvent& event);

	private:
		glm::vec3 m_Position;
		float m_Rotation;
		float m_AspectRatio, m_Speed;

		Shared<OrthographicCamera> m_Camera;

	};
}