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
			#version 410 core

			layout(location=0) in vec3 a_Position;

			uniform mat4 u_ProjectionView;
			
			void main()
			{
				gl_Position = u_ProjectionView * vec4(a_Position, 1.0);
			}
		)";

		std::string fragSrc = R"(
			#version 410 core
			
			layout(location=0) out vec4 a_FragColor;

			void main()
			{
				a_FragColor = vec4(1, 0, 0, 1);
			}
		)";

		shader = Shared<Shader>(new Shader(vertSrc, fragSrc));

		vao = VertexArray::Create();

		float vertices[] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		Shared<VertexBuffer> vbo = VertexBuffer::Create(vertices, sizeof(vertices));
		vbo->SetLayout({
			{ ShaderDataType::Float3, "a_Position" }
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
		glm::vec3 camPos = camera.GetPosition();
		float rotation = camera.GetRotation();
		float speed = 2.5f * ts;

		if (Input::IsKeyPressed(Key::W))
			camPos.y += speed;
		else if (Input::IsKeyPressed(Key::S))
			camPos.y -= speed;

		if (Input::IsKeyPressed(Key::A))
			camPos.x -= speed;
		else if (Input::IsKeyPressed(Key::D))
			camPos.x += speed;

		if (Input::IsKeyPressed(Key::Q))
			rotation += speed * 15.f;
		else if (Input::IsKeyPressed(Key::E))
			rotation -= speed * 15.f;

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
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<KeyPressedEvent>(ARC_BIND_EVENT_FN(ExampleLayer::OnKeyPressed));
	}

	bool OnKeyPressed(KeyPressedEvent& event)
	{

		return false;
	}

private:
	Shared<Shader> shader;
	Shared<VertexArray> vao;

	OrthographicCamera camera;
};

class Playground : public Application
{
public:
	Playground() :
		Application()
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