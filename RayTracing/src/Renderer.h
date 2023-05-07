#pragma once

#include "Core/Image.h"

#include <memory>
#include <glm/glm.hpp>

namespace RayTracing {

	class Renderer
	{
	public:
		Renderer() = default;

		std::shared_ptr<Core::Image> GetFinalImage() const { return m_FinalImage; }

		void Resize(uint32_t width, uint32_t height);
		void Render();
	private:
		uint32_t PerPixel(glm::vec2 coord);
	private:
		uint32_t* m_ImageData = nullptr;
		std::shared_ptr<Core::Image> m_FinalImage;
	};

}