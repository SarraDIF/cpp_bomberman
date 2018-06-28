#include "EventManager.hpp"

EventManager::EventManager()
{
	for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
		KeyIsDown[i] = false;
	for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
		KeyIsPressed[i] = false;
	resetKeysArrays();
}

EventManager::~EventManager()
{
}

bool EventManager::OnEvent(const irr::SEvent &event)
{
	switch (event.EventType)
	{
	case irr::EET_KEY_INPUT_EVENT:
	{
		KeyDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
		break;
	}
	default:
		break;
	}
	return (false);
}


bool EventManager::IsKeyDown(irr::EKEY_CODE const keyCode) const
{
	return (KeyDown[keyCode]);
}

/* bool EventManager::isKeyUp(irr::EKEY_CODE const keyCode) const
{
	return !KeyDown[keyCode];
}
 */

/* bool EventManager::IsKeyPressed(irr::EKEY_CODE keyCode) const
{
	return (KeyIsPressed[keyCode]);
}

bool EventManager::IsKeyDown(irr::EKEY_CODE keyCode) const
{
	return (KeyDown[keyCode]);
}
 */
void EventManager::resetKeysArrays(void)
{
	for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
		KeyIsDown[i] = false;
	for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
		KeyIsPressed[i] = false;
}