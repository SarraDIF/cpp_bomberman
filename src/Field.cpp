#include "Field.hpp"

Field::Field(irr::IrrlichtDevice *device) : _device(device), _sceneManager(device->getSceneManager())
{
	_sceneManager->loadScene("media/maps/bombermap.irr");
	this->running();
	srand(time(NULL));
	setBoxes();
}

Field::~Field()
{
	_meta->drop();
}

void Field::running()
{
	unsigned int i;
	irr::scene::ISceneNode *node;
	irr::scene::ITriangleSelector *selector;
	irr::core::array<irr::scene::ISceneNode *> nodes;

	_meta = _sceneManager->createMetaTriangleSelector();
	_sceneManager->getSceneNodesFromType(irr::scene::ESNT_CUBE, nodes);
	_sceneManager->addCameraSceneNode(NULL, irr::core::vector3df(0, 450, -200),
									  irr::core::vector3df(0, 0, 0));
	i = 0;
	while (i < nodes.size())
	{
		selector = _sceneManager->createTriangleSelectorFromBoundingBox(nodes[i++]);
		if (selector)
		{
			_meta->addTriangleSelector(selector);
			selector->drop();
		}
	}
}

void Field::setBoxes()
{
	int i = 0;
	int y = 0;
	int x = 0;
	std::string line;
	std::ifstream myfile("../maps/basic.txt");

	if (!myfile.is_open())
		std::cerr << "ERROR OPENING MAP FILE" << std::endl;
	else
	{
		std::getline(myfile, line, '\0');
		myfile.close();
	}
	while (y < 11)
	{
		x = 0;
		while (x < 13)
		{
			if (line[i++] != 'X' && rand() % 2 == 1)
				_boxes.push_back(std::unique_ptr<Box>(new Box(_device,
															  irr::core::vector3df(50.f * (x - 6), 30.f, 50.f * (y - 5) + 50.f))));
			x++;
		}
		y++;
		i++;
	}
}

void Field::resetField()
{
	_boxes.clear();
}