#include "Renderer.h"

#include "Random.h"

namespace Utils {

	static uint32_t ConvertToRGBA(const glm::vec4& color)
	{
		uint8_t r = (uint8_t)(color.r * 255.0f);
		uint8_t g = (uint8_t)(color.g * 255.0f);
		uint8_t b = (uint8_t)(color.b * 255.0f);
		uint8_t a = (uint8_t)(color.a * 255.0f);

		uint32_t res = (a << 24) | (b << 16) | (g << 8) | r;
		return res;
	}

}

namespace RayTracing {
	
	void Renderer::Resize(uint32_t width, uint32_t height)
	{
		if (!m_FinalImage)
		{
			m_FinalImage = std::make_shared<Core::Image>(width, height, Core::ImageFormat::RGBA);
		}
		else if (width != m_FinalImage->GetWidth() || height != m_FinalImage->GetHeight())
		{
			m_FinalImage->Resize(width, height);
		}
		delete[] m_ImageData;
		m_ImageData = new uint32_t[width * height];
	}

	void Renderer::Render()
	{
		for (uint32_t y = 0; y < m_FinalImage->GetHeight(); y++)
		{
			for (uint32_t x = 0; x < m_FinalImage->GetWidth(); x++)
			{
				glm::vec2 coord{ (float)x / (float)m_FinalImage->GetWidth(), (float)y / (float)m_FinalImage->GetHeight()};
				coord = coord * 2.0f - 1.0f;
				glm::vec4 color = PerPixel(coord);
				color = glm::clamp(color, glm::vec4(0.0f), glm::vec4(1.0f));
				m_ImageData[x + y * m_FinalImage->GetWidth()] = Utils::ConvertToRGBA(color);
			}
		}
		m_FinalImage->SetData(m_ImageData);
	}

	glm::vec4 Renderer::PerPixel(glm::vec2 coord)
	{
		glm::vec3 rayOrigin(0.0f, 0.0f, 1.0f);
		glm::vec3 rayDirection(coord.x, coord.y, -1.0f);
		float radius = 0.5f;

		float a = glm::dot(rayDirection, rayDirection);
		float b = 2.0f * glm::dot(rayOrigin, rayDirection);
		float c = glm::dot(rayOrigin, rayOrigin) - radius * radius;

		float discriminant = b * b - 4.0f * a * c;
		if (discriminant < 0)
			return glm::vec4(0, 0, 0, 1);

		float closestT = (-b - glm::sqrt(discriminant)) / (2.0f * a);
		float t2 = (-b + glm::sqrt(discriminant)) / (2.0f * a);

		glm::vec3 hitPoint = rayOrigin + rayDirection * closestT;
		glm::vec3 normal = glm::normalize(hitPoint);

		glm::vec3 lightDirection = glm::normalize(glm::vec3(-1, -1, -1));
		float cosTheta = glm::dot(normal, -lightDirection);
		float lightIntensity = glm::max(cosTheta, 0.0f);

		glm::vec3 sphereColor(0.0f, 1.0f, 1.0f);
		sphereColor *= lightIntensity;
		return glm::vec4(sphereColor, 1.0f);
	}
}