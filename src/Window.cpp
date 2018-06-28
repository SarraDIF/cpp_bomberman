#include "Window.hpp"

Window::Window(int const &width, int const &height) : _height(height), _width(width), _receiver()
{
	bool GameOver = false;

	_device = irr::createDevice(irr::video::EDT_OPENGL,
								irr::core::dimension2d<irr::u32>(_width, _height), 32, false, true, false, &_receiver);
	_device->setWindowCaption(L"Bombermoon");
	_device->setEventReceiver(&_receiver);
	_receiver.resetKeysArrays();

	_device->getCursorControl()->setVisible(true);
	_gui = _device->getGUIEnvironment();
	_driver = _device->getVideoDriver();
	_sceneManager = _device->getSceneManager();
	_map = new Field(_device);
	_game = new Game(_width, _height, _device, _driver, _receiver, *_map, 1, _sceneManager);
	_receiver.resetKeysArrays();

	while (_device->run() && !GameOver)
	{
		_driver->beginScene(true, true, irr::video::SColor(0, 0, 0, 0));
		_map->running();
		_game->running();
		_sceneManager->drawAll();
		_driver->endScene();
		if (_receiver.IsKeyDown(irr::KEY_ESCAPE) /* || GetAsyncKeyState('K') */)
			break;
		_receiver.resetKeysArrays();
	}
}

Window::~Window()
{
	_device->getSceneManager()->clear();
	_device->drop();
}