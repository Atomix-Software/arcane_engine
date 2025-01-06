#include <Arcane.h>

#include <imgui.h>

using namespace Arcane;

class ExampleLayer : public Layer
{
public:
	ExampleLayer() :
		Layer("Example"), camera(-1.6f, 1.6f, -0.9f, 0.9f) {}

	virtual void OnAttach() override
	{
		std::string vertSrc = R"(
			#version 330 core

			layout(location=0) in vec3 a_Position;

			uniform mat4 u_ProjectionView;
			
			void main()
			{
				gl_Position = u_ProjectionView * vec4(a_Position, 1);
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
		glm::vec3 camPos = camera.GetPosition();
		float rotation = camera.GetRotation();

		float speed = 2.5f * (1.0f / 60.0f);

		if (Input::IsKeyPressed(Key::W))
			camPos.y += speed;
		else if (Input::IsKeyPressed(Key::S))
			camPos.y -= speed;

		if (Input::IsKeyPressed(Key::A))
			camPos.x -= speed;
		else if (Input::IsKeyPressed(Key::D))
			camPos.x += speed;

		if (Input::IsKeyPressed(Key::Q))
			rotation += speed;
		else if (Input::IsKeyPressed(Key::E))
			rotation -= speed;

		camera.SetPosition(camPos);
		camera.SetRotation(rotation);

		Renderer::BeginScene(camera);

		Renderer::Submit(shader, vao);

		Renderer::EndScene();
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

	OrthographicCamera camera;
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