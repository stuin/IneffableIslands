#include "Skyrmion/input/MovementSystems.h"
#include "Skyrmion/input/InputHandler.h"
#include "Skyrmion/input/TouchscreenInput.hpp"
#include "Skyrmion/input/Settings.h"

#include "indexes.h"

class PlayerBase : public Node {
private:
	FrameTimer timer;

public:
	int direction = DOWN;
	int variant = 0;

	PlayerBase(Layer layer, int _variant) : Node(layer, Vector2i(16,24)), timer(4, 0.2) {
		variant = _variant;

		setTexture(TEXTURE_PLAYER);
		setTextureVecRect(16 * direction, 24*(1+variant*4));
	}

	//Update animation frame
	void updateAnimation(double time, Vector2f movement) {
		if(movement != Vector2f(0,0)) {
		//if(distance(movement) > 0.1) {
			direction = topDownDirection(movement);

			if(timer.next(time) == 3)
				setTextureVecRect(16 * direction, 24*(2+variant*4));
			else
				setTextureVecRect(16 * direction, 24*(timer.frame+1+variant*4));
		} else {
			timer.frame = 1;
			timer.time = 0;
			setTextureVecRect(16 * direction, 24*(2+variant*4));
		}
	}
};

class Player : public PlayerBase {
private:
	Indexer *collisionMap;

	DirectionHandler input;
	TouchscreenJoystick joystick;

	Vector2f lastSent;

public:
	Player(Indexer *_collisionMap) : PlayerBase(PLAYER, Settings::getInt("/playervariant")), collisionMap(_collisionMap),
	input("/movement", INPUT, this), joystick(TEXTURE_JOYSTICK, Settings::getInt("/movement/joystick"), TOUCHSCREENINPUT) {

	}

	void update(double time) {
		Vector2f movement = input.getMovement(time * 60);
		//setPosition(topDownMovement(this, movement, collisionMap));
		setPosition(getPosition()+movement);

		if(UpdateList::getNetworkId() && UpdateList::isNetworkTick() && distance(getPosition(), lastSent) > 0.001) {
			send();
		}

		updateAnimation(time, movement);
	}

	void send() {
		UpdateList::sendNetworkEvent(Event(EVENT_NETWORK_POSITION, false, UpdateList::getNetworkId(), getPosition()));
		lastSent = getPosition();
	}
};

class OtherPlayer : public PlayerBase {
private:
	Vector2f target;

public:
	int id = 0;

	OtherPlayer() : PlayerBase(OTHERPLAYERS, 0) {
		setHidden();
		UpdateList::addListener(this, EVENT_NETWORK_POSITION);
	}

	void setup(int _id, int _variant) {
		setHidden();
		id = _id;
		variant = _variant;
		std::cout << "Setup player id " << id << "\n";
	}

	void update(double time) {
		updateAnimation(time, target-getPosition());
		setPosition(target);
	}

	void recieveEvent(Event event) {
		if(id != 0 && event.code == id) {
			target = event.vector();
			setHidden(false);
		}
	}
};

#define MAX_PLAYERS 4
class MultiPlayer : public Node {
	OtherPlayer players[MAX_PLAYERS];
	Player *self;

public:

	MultiPlayer(Player *_self) : Node(INPUT), self(_self) {
		UpdateList::addListener(this, EVENT_NETWORK_CONNECT_SERVER);
		UpdateList::addListener(this, EVENT_NETWORK_CONNECT_CLIENT);

		UpdateList::addNode(this);
		for(int i = 0; i < MAX_PLAYERS; i++)
			UpdateList::addNode(&players[i]);
	}

	void recieveEvent(Event event) {
		if(event.type == EVENT_NETWORK_CONNECT_SERVER && !event.down) {
			UpdateList::sendNetworkEvent(Event(
				EVENT_NETWORK_CONNECT_CLIENT, false, UpdateList::getNetworkId(), Settings::getInt("/playervariant"), 0), true);
			self->send();
		} else if(event.type == EVENT_NETWORK_CONNECT_SERVER && event.down) {
			for(int i = 0; i < MAX_PLAYERS; i++)
				players[i].setup(0, 0);
		} else if(event.type == EVENT_NETWORK_CONNECT_CLIENT && !event.down) {
			if(players[event.code-1].id == 0) {
				players[event.code-1].setup(event.code, event.x);
				UpdateList::sendNetworkEvent(Event(
					EVENT_NETWORK_CONNECT_CLIENT, false, UpdateList::getNetworkId(), Settings::getInt("/playervariant"), 0), true);
				self->send();
			}
		} else if(event.type == EVENT_NETWORK_CONNECT_CLIENT && event.down) {
		}
	}
};

void initializePlayer(Indexer *collisionMap) {
	//Player
	Player player(collisionMap);
	player.setPosition(Vector2f(16*16, 16*16));
	UpdateList::addNode(&player);
	UpdateList::setCamera(&player, Vector2f(450, 250));

	//Other players
	MultiPlayer multi(&player);

	std::cout << "Added players\n";

	UpdateList::startEngine();
}