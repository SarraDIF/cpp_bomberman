#include "Box.hpp"

Box::Box(irr::IrrlichtDevice *device, irr::core::vector3df const &pos)
	: _sceneManager(device->getSceneManager()), _pos(pos), _driver(device->getVideoDriver())
{
	_box = _sceneManager->addCubeSceneNode(50.f, NULL, -1, pos);
	_box->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	_box->setMaterialTexture(0, _driver->getTexture("media/textures/wood.png"));
	_selector = _sceneManager->createOctreeTriangleSelector(_box->getMesh(), _box, 128);
	_box->setTriangleSelector(_selector);
}

Box::~Box()
{
	std::for_each(_collisionTab.begin(), _collisionTab.end(),
				  [](auto &collision) {collision.first->removeAnimator(collision.second);});
	_selector->drop();
	_sceneManager->addToDeletionQueue(_box);
}

void Box::assignCollision(irr::scene::IAnimatedMeshSceneNode *model)
{
	irr::scene::ISceneNodeAnimator *anim;

	anim = _sceneManager->createCollisionResponseAnimator(_selector, model,
														  irr::core::vector3df(10, 10, 10),
														  irr::core::vector3df(0.f, 0.f, 0.f),
														  irr::core::vector3df(0.f, 0.f, 0.f));
	model->addAnimator(anim);
	anim->drop();
	_collisionTab.push_back({model, anim});
}

irr::core::vector3df const &Box::getPosition() const
{
	return (_pos);
}