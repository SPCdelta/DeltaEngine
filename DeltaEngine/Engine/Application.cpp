#include "Application.hpp"

bool Application::_isRunning = true;

Application::Application(int unitPixelSize)
	: _window("Meow!", 1280, 720)
{
	// Init SDL2
	if (Rendering::Initialize(Rendering::INIT_VIDEO | Rendering::INIT_AUDIO) < 0)
	{
		std::cerr << "Failed to initialize the SDL2 library" << std::endl;
	}

	// Init SDL2 image 
	if (!(Rendering::InitializeImage(Rendering::INIT_PNG) & Rendering::INIT_PNG))
	{
		std::cerr << "Failed to initialize the SDL2_image library" << std::endl;
	}

	// Init SDL2_ttf
	if (TTF_Init() < 0)
	{
		std::cerr << "Failed to initialize the SDL2_ttf library" << std::endl;
	}

	ChangeScene.Register([this](const std::string& sceneName) 
	{ 
		LoadScene(sceneName); 
	});

	_window.SetUnitPixelSize(unitPixelSize);
}


Application::~Application()
{
	delete _fpsText;
	Stop();
}

void Application::Run()
{

#ifndef _DEBUG

	try
	{
#endif	// _DEBUG
	
		InitDebug();
		Uint32 previousTime = Rendering::GetTicks();
	
		while (!_window.ShouldWindowClose())
		{
			// DeltaTIme
			Uint32 currentTime = Rendering::GetTicks();
			Time::SetDeltaTime((static_cast<float>(currentTime - previousTime) / 1000.0f));
			previousTime = currentTime;

			// 
			Rendering::RenderClear(_window.GetRenderer());
			_window.RenderViewport(255, 255, 255, 255);

			Rendering::PollEvent(_windowEvent);

			if (!Application::_isRunning || _windowEvent.type == Rendering::QUIT)
				return;



			// Update Window
			_window.Update();

			// Scene UpdateLoop
			std::shared_ptr<Scene> currentScene = _sceneManager.GetCurrent();
			currentScene->Update();

			Debug();

			// Render all
			Rendering::RenderPresent(_window.GetRenderer());

			// Framerate
			Rendering::Delay(1000 / 60);
		}
#ifndef _DEBUG
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what();
	}
#endif	// _DEBUG

}

void Application::LoadScene(const std::string& sceneName)
{
	_sceneManager.Load(sceneName);
	std::shared_ptr<Scene> currentScene = _sceneManager.GetCurrent();
	currentScene->_changeSceneEvent.Register([this](const std::string& name) { ChangeScene.Dispatch(name); });
	currentScene->_inputfacade = &_inputFacade;
	currentScene->_windowEvent = &_windowEvent;
	currentScene->SetWindow(_window);
	currentScene->Start();
}

void Application::InitDebug()
{
	_fpsText = new Ui::Text("FPS: ", "knight", 48, textColor);

	InputManager::onKeyPressed(Key::KEY_L, [this](Input& e) { _renderFps = !_renderFps; });
}
void Application::Debug()
{
	if (_fpsTimer >= 1.0f)
	{
		std::string fps = "FPS: " + std::to_string(static_cast<int>((1.0f / Time::GetDeltaTime())));
		_fpsText->SetText(fps);
		_fpsTimer = 0.0f;
	}
	else
	{
		_fpsTimer += Time::GetDeltaTime();
	}

	if (_renderFps)
	{
		_fpsText->Render(_window.GetRenderer(), _textTransform);
	}
}
