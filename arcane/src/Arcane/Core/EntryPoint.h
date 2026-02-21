#pragma once

#ifdef AE_PLAT_WINDOWS

extern Arcane::Application* Arcane::CreateApplication();

int main(int argc, char* argv[])
{
	Arcane::Log::Init();
	AE_CORE_WARN("Initialized Logger!");

	auto app = Arcane::CreateApplication();
	app->Run();

	delete app;
	return 0;
}

#endif