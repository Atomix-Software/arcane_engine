#include <Arcane.h>

#include <imgui.h>

using namespace Arcane;

class ExampleLayer : public Layer
{
public:
	ExampleLayer() :
		Layer("Example") {}

	virtual void OnAttach() override
	{
		std::string vertSrc = R"(
			#version 330 core

			layout(location=0) in vec3 a_Position;
			
			void main()
			{
				gl_Position = vec4(a_Position, 1);
			}
		)";

		std::string fragSrc = R"(
			#version 330 core
			
			layout(location=0) out vec4 a_FragColor;

			void main()
			{
				a_FragColor = vec4(1, 0, 0, 1);
			}
		)";

		shader.reset(new Shader(vertSrc, fragSrc));

		vao = VertexArray::Create();

		float vertices[] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};

		std::shared_ptr<VertexBuffer> vbo = VertexBuffer::Create(vertices, sizeof(vertices));

		vbo->SetLayout({
			{ ShaderDataType::Float3, "a_Position" }
		});

		vao->AddVertexBuffer(vbo);

		uint32_t indices[] = {
			0, 1, 2
		};

		std::shared_ptr<IndexBuffer> ebo = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
		vao->SetIndexBuffer(ebo);
	}

	virtual void OnUpdate() override
	{
		shader->Bind();
		Renderer::Submit(vao);
	}

	virtual void OnImGuiRender() override
	{

	}

	virtual void OnEvent(Event& event)
	{

	}

private:
	std::shared_ptr<Shader> shader;
	std::shared_ptr<VertexArray> vao;
};

class Playground : public Application
{
public:
	Playground()
	{
		PushLayer(new ExampleLayer());
	}

	~Playground()
	{

	}


};

Application* Arcane::CreateApplication()
{
	return new Playground();
}