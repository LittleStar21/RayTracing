#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace RayTracing {

	class Camera
	{
	public:
		Camera(float verticalFOV, float nearClip, float farClip);

		void OnUpdate(float ts);
		void Resize(uint32_t width, uint32_t height);

		const glm::mat4& GetView() const { return m_View; }
		const glm::mat4& GetProjection() const { return m_Projection; }
		const glm::mat4& GetInverseView() const { return m_InverseView; }
		const glm::mat4& GetInverseProjection() const { return m_InverseProjection; }

		const glm::vec3& GetPosition() const { return m_Position; }
		const glm::vec3& GetForwardDirection() const { return m_ForwardDirection; }

		const std::vector<glm::vec3>& GetRayDirections() const { return m_RayDirections; }

		float GetRotationSpeed();
	private:
		void RecalculateView();
		void RecalculateProjection();
		void RecalculateRayDirections();
	private:
		float m_VerticalFOV = 45.0f;
		float m_NearClip = 0.1f;
		float m_FarClip = 100.0f;

		glm::mat4 m_View{ 1.0f };
		glm::mat4 m_Projection{ 1.0f };
		glm::mat4 m_InverseView{ 1.0f };
		glm::mat4 m_InverseProjection{ 1.0f };

		glm::vec3 m_Position{ 0.0f, 0.0f, 1.0f };
		glm::vec3 m_ForwardDirection{ 0.0f, 0.0f, 0.0f };

		std::vector<glm::vec3> m_RayDirections;

		glm::vec2 m_LastMousePosition{ 0.0f, 0.0f };
		uint32_t m_ViewportWidth = 0;
		uint32_t m_ViewportHeight = 0;
	};

}