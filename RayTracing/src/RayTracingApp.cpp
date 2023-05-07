#include "Core/Application.h"
#include "Core/EntryPoint.h"
#include "Core/Image.h"

#include "Renderer.h"

class RayTracingLayer : public Core::Layer
{
public:
	virtual void OnRender() override
	{
		ImGui::Begin("Settings");
		ImGui::Text("FPS: %.2f", ImGui::GetIO().Framerate);
		ImGui::End();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("Viewport");

		m_ViewportWidth = ImGui::GetContentRegionAvail().x;
		m_ViewportHeight = ImGui::GetContentRegionAvail().y;
		
		std::shared_ptr<Core::Image> image = m_Renderer.GetFinalImage();
		if (image)
			ImGui::Image(image->GetDescriptorSet(), {(float)image->GetWidth(), (float)image->GetHeight()}, ImVec2(0, 1), ImVec2(1, 0));
		ImGui::End();
		ImGui::PopStyleVar();

		Render();
	}
private:
	void Render()
	{
		m_Renderer.Resize(m_ViewportWidth, m_ViewportHeight);
		m_Renderer.Render();
	}
private:
	uint32_t m_ViewportWidth = 0;
	uint32_t m_ViewportHeight = 0;

	RayTracing::Renderer m_Renderer;
};

Core::Application *Core::CreateApplication(int argc, char **argv)
{
	Core::ApplicationSpecification spec;
	spec.Name = "Ray Tracing";

	Core::Application *app = new Core::Application(spec);
	app->PushLayer<RayTracingLayer>();
	app->SetMenubarCallback([app]()
							{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Quit"))
			{
				app->Close();
			}
			ImGui::EndMenu();
		} });
	return app;
}