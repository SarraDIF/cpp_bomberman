#include "Game.hpp"


Game::Game(int const &width, int const &height, irr::IrrlichtDevice *device,
		   irr::video::IVideoDriver *driver, EventManager &receiver,
		   Field &map, int const &nbPlayers, irr::scene::ISceneManager *sceneManager)
	: _width(width), _height(height), _device(device), _driver(driver),
	  _receiver(receiver), _map(map), _sceneManager(sceneManager)
{
	_player = new Character(_receiver, _device, SpawnPosition[0], _map, "./media/textures/player.bmp");
}

Game::~Game()
{
	delete (_player);
}

void Game::running()
{
	if (_receiver.IsKeyDown(irr::KEY_KEY_Q))
		_player->moveLeft();
	if (_receiver.IsKeyDown(irr::KEY_KEY_D))
		_player->moveRight();
	if (_receiver.IsKeyDown(irr::KEY_KEY_Z))
		_player->moveDown();
	if (_receiver.IsKeyDown(irr::KEY_KEY_S))
		_player->moveUp();
}

irr::core::vector3df const Game::SpawnPosition[] =
	{
		irr::core::vector3df(-300.f, 30.f, 300.f),
		irr::core::vector3df(300.f, 30.f, -200.f),
		irr::core::vector3df(-300.f, 30.f, -200.f),
		irr::core::vector3df(300.f, 30.f, 300.f)
	};