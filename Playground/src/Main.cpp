#include <iostream>

namespace Arcane {
	__declspec(dllimport) void Print();
}

int main(int argc, char* argv[])
{
	Arcane::Print();
	std::cin.get();

	return 0;
}