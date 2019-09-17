#pragma once
class Entity
{
	Entity();
	~Entity() {};
public:
	static Entity* Instance() {
		static Entity s_Instace;
		return &s_Instace;
	}
};

#define ENTITY Entity::Instance()
