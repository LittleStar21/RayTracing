#include "Renderer.h"

#include "Random.h"

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
		for (uint32_t i = 0; i < m_FinalImage->GetHeight(); i++)
		{
			for (uint32_t j = 0; j < m_FinalImage->GetWidth(); j++)
			{
				glm::vec2 coord{ (float)j / m_FinalImage->GetWidth(), (float)i / m_FinalImage->GetHeight()};
				m_ImageData[i * m_FinalImage->GetWidth() + j] = PerPixel(coord);
			}
		}
		m_FinalImage->SetData(m_ImageData);
	}

	uint32_t Renderer::PerPixel(glm::vec2 coord)
	{
		uint8_t r = (uint8_t)(coord.x * 255.0f);
		uint8_t g = (uint8_t)(coord.y * 255.0f);
		return 0xff000000 | (g << 8) | r;
	}
}