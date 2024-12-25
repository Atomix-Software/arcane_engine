#pragma once

#ifdef ARC_PLATFORM_WINDOWS

extern Arcane::Application* Arcane::CreateApplication();

int main(int argc, char* argv[])
{
	auto app = Arcane::CreateApplication();
	app->Run();
	delete app;

	return 0;
}

#endif