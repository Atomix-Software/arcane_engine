#include <Arcane.h>
#include <Arcane/Core/EntryPoint.h>

#include "Layer2D.h"

#include <imgui.h>

using namespace Arcane;

class LayerTest : public Layer
{
public:
	LayerTest(int width, int height) :
		Layer("Test")
	{
		float aspectRatio = (float) width / (float) height;
		camControl = new OrthoCameraController(aspectRatio);
	}

	virtual void OnAttach() override
	{
		// Load Files
		shaderLib.Load("assets/shaders/Texture.glsl");
		shaderLib.Load("assets/shaders/Flat.glsl");

		texture = Texture2D::Create("assets/textures/whoa.png");

		// Setup Code
		vao = VertexArray::Create();

		float vertices[] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Shared<VertexBuffer> vbo = VertexBuffer::Create(vertices, sizeof(vertices));
		vbo->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float2, "a_TexCoord" }
		});

		vao->AddVertexBuffer(vbo);

		uint32_t indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		Shared<IndexBuffer> ebo = IndexBuffer::Create(indices, sizeof(indices));
		vao->SetIndexBuffer(ebo);
	}

	virtual void OnUpdate(Timestep ts) override
	{
		camControl->OnUpdate(ts);

		Renderer::BeginScene(*camControl->GetCamera());

		Renderer::Submit(shaderLib.Get("Flat"), vao, nullptr,    {  0.75f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }, 0.0f, 0.75f);
		Renderer::Submit(shaderLib.Get("Texture"), vao, texture, {  0.75f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }, 0.0f, 0.75f);
		Renderer::Submit(shaderLib.Get("Flat"), vao, nullptr,    { -0.75f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, 0.0f, 0.75f);
		Renderer::Submit(shaderLib.Get("Texture"), vao, texture, { -0.75f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, 0.0f, 0.75f);

		Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		Renderer::SceneData data = Renderer::GetSceneData();

		ImGui::Begin("Render Info");
		ImGui::Text("Shader Count: %d", data.ShaderCount);
		ImGui::Text("Object Count: %d", data.ObjectCount);
		ImGui::End();
	}

	virtual void OnEvent(Event& event)
	{
		camControl->OnEvent(event);
	}

private:
	Shared<Texture2D> texture;
	Shared<VertexArray> vao;

	ShaderLibrary shaderLib;
	OrthoCameraController* camControl;
};

class Playground : public Application
{
public:
	Playground(const WindowProps& props) :
		Application(props)
	{
		//PushLayer(new LayerTest(GetWindow()->GetWidth(), GetWindow()->GetHeight()));
		PushLayer(new Layer2D);
	}

	~Playground()
	{

	}


};

Application* Arcane::CreateApplication()
{
	return new Playground({"Playground App"});
}