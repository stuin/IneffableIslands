#include "Skyrmion/input/MovementSystems.h"
#include "Skyrmion/input/InputHandler.h"
#include "Skyrmion/input/TouchscreenInput.hpp"
#include "Skyrmion/input/Settings.h"

class Player : public Node {
	Indexer *collisionMap;
	DirectionHandler input;
	TouchscreenJoystick joystick;

public:
	Player(Indexer *_collisionMap) : Node(PLAYER), collisionMap(_collisionMap),
	input("/movement", INPUT, this), joystick(TEXTURE_JOYSTICK, Settings::getInt("/movement/joystick"), TOUCHSCREENINPUT) {

	}

	void update(double time) {
		//setPosition(topDownMovement(this, input.getMovement(time * 48), collisionMap));
		setPosition(getPosition()+input.getMovement(time * 60));
	}
};