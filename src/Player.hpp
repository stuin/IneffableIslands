#include "Skyrmion/input/MovementSystems.h"

class Player : public Node {
	Indexer *collisionMap;
	DirectionHandler input;

public:
	Player(Indexer *_collisionMap) : Node(PLAYER), collisionMap(_collisionMap),
	input("/movement", INPUT, this) {

	}

	void update(double time) {
		//setPosition(topDownMovement(this, input.getMovement(time * 48), collisionMap));
		setPosition(getPosition()+input.getMovement(time * 60));
	}
};