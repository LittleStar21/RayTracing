#pragma once

#include "Core/Image.h"

#include "Camera.h"
#include "Ray.h"

#include <memory>
#include <glm/glm.hpp>

namespace RayTracing {

	class Renderer
	{
	public:
		Renderer() = default;

		std::shared_ptr<Core::Image> GetFinalImage() const { return m_FinalImage; }

		void Resize(uint32_t width, uint32_t height);
		void Render(const Camera& camera);
	private:
		glm::vec4 TraceRay(const Ray& ray);
	private:
		uint32_t* m_ImageData = nullptr;
		std::shared_ptr<Core::Image> m_FinalImage;
	};

}