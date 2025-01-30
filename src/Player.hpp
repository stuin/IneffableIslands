#include "Skyrmion/input/MovementSystems.h"
#include "Skyrmion/input/InputHandler.h"

class Player : public Node {
	Indexer *collisionMap;
	DirectionHandler input;

public:
	Player(Indexer *_collisionMap) : Node(PLAYER), collisionMap(_collisionMap),
	input("/movement", INPUT, TEXTURE_JOYSTICK, this) {

	}

	void update(double time) {
		//setPosition(topDownMovement(this, input.getMovement(time * 48), collisionMap));
		setPosition(getPosition()+input.getMovement(time * 60));
	}
};