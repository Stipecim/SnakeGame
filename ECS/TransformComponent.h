#pragma once
#include "ECS.h"
#include "../Vector2D.h"

struct TransformComponent : public Component {
public:
	Vector2D position;
	Vector2D velocity;

	// border game scene 
	int width = 640;
	int height = 512;
	//------------------

	int speed = 1;

	TransformComponent() {
		position.x = 0.0f;
		position.y = 0.0f;
	}
	TransformComponent(int x, int y) {
		position.x = x;
		position.y = y;
	}
	void init() override {
		if (entity->getName() == "snake") {
			velocity.x = 32;
			velocity.y = 0;
		}
	}
	void update() override {
		if (entity->getName() == "snake") {
			position.x += velocity.x * speed;
			position.y += velocity.y * speed;
		}
		
	}

	bool isInit() override {
		return true;
	}
	
};