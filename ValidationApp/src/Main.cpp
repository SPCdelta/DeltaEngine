#include "ValidationApp.hpp"
#include "Engine/MemLeakDetection/MemLeakDetection.hpp"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	_CrtDumpMemoryLeaks();

	ValidationApp app{};
	app.Run();
}