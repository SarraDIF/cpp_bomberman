#include "Character.hpp"

Character::Character(EventManager const &receiver, irr::IrrlichtDevice *device,
					 irr::core::vector3df const &pos, Field &map, std::string const &pathTexture)
	: _receiver(receiver), _device(device), _map(map), _dead(false), _pathTexture(pathTexture)
{
	_model = _device->getSceneManager()->addAnimatedMeshSceneNode(_device->getSceneManager()->getMesh("media/models/player.md2"));
	if (!_model)
		throw std::runtime_error("Failed to create a new character.");
	_model->setMaterialTexture(0, device->getVideoDriver()->getTexture(_pathTexture.c_str()));
	_model->setMD2Animation(irr::scene::EMAT_STAND);
	_model->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	_model->setPosition(pos);
	_model->setName("Player");
	_speed = 15.f;
	_then = _device->getTimer()->getTime();
	_maxBomb = 1;
	_bombTimer = 2000;
	_bombPower = 1;
	_selector = _device->getSceneManager()->createOctreeTriangleSelector(_model->getMesh(), _model, 128);
	_model->setTriangleSelector(_selector);
}

Character::~Character()
{
	_selector->drop();
	_model->removeAnimators();
	_device->getSceneManager()->addToDeletionQueue(_model);
}

irr::scene::IAnimatedMeshSceneNode *Character::getModel(void)
{
	return (_model);
}

void Character::assignCollision(irr::scene::IAnimatedMeshSceneNode *model)
{
	irr::scene::ISceneNodeAnimator *anim;

	anim = _device->getSceneManager()->createCollisionResponseAnimator(_selector, model, irr::core::vector3df(10, 10, 10),
																	   irr::core::vector3df(0, 0, 0), irr::core::vector3df(0, 0, 0));
	model->addAnimator(anim);
	anim->drop();
	_collisionTab.push_back({model, anim});
}

void Character::moveUp(void)
{
	irr::core::vector3df pos;

	pos = _model->getPosition();
	if (_moveDirection != UP)
	{
		_model->setMD2Animation(irr::scene::EMAT_RUN);
		_model->setRotation(irr::core::vector3df(0.0, 270.0, 0.0));
		_moveDirection = UP;
	}
	pos.Z += _speed * _frameDeltaTime;
	_model->setPosition(pos);
}

void Character::moveDown(void)
{
	irr::core::vector3df pos;

	pos = _model->getPosition();
	if (_moveDirection != BACK)
	{
		_model->setMD2Animation(irr::scene::EMAT_RUN);
		_model->setRotation(irr::core::vector3df(0.0, 90.0, 0.0));
		_moveDirection = BACK;
	}
	pos.Z -= _speed * _frameDeltaTime;
	_model->setPosition(pos);
}

void Character::moveRight(void)
{
	irr::core::vector3df pos;

	pos = _model->getPosition();
	if (_moveDirection != RIGHT)
	{
		_model->setMD2Animation(irr::scene::EMAT_RUN);
		_model->setRotation(irr::core::vector3df(0.0, 0.0, 0.0));
		_moveDirection = RIGHT;
	}
	pos.X += _speed * _frameDeltaTime;
	_model->setPosition(pos);
}

void Character::moveLeft(void)
{
	irr::core::vector3df pos;

	pos = _model->getPosition();
	if (_moveDirection != LEFT)
	{
		_model->setMD2Animation(irr::scene::EMAT_RUN);
		_model->setRotation(irr::core::vector3df(0.0, 180.0, 0.0));
		_moveDirection = LEFT;
	}
	pos.X -= _speed * _frameDeltaTime;
	_model->setPosition(pos);
}