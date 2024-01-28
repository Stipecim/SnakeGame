#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>
#include <iostream>
/*	Entity Component System */



class Component;
class Entity;

using ComponentTypeID = std::size_t;


inline ComponentTypeID getUniqueComponentTypeID() {
	static ComponentTypeID lastID = 0u;
	return lastID++;
}
template <typename T>
inline ComponentTypeID getComponentTypeID() {
	static_assert (std::is_base_of<Component, T>::value, "This type is not derived class of Component");
	static const ComponentTypeID TypeID = getUniqueComponentTypeID();
	return TypeID;
}

constexpr std::size_t MAX_ENTITY = 10;
constexpr std::size_t MAX_COMPONENTS = 32;

using ComponentList = std::array<Component*, MAX_COMPONENTS>;
using ComponentBitset = std::bitset<MAX_COMPONENTS>;



class Component {
public:

	Component() {};
	Entity* entity;

	virtual bool isInit() { return true; };
	virtual void init() {}
	virtual void update() {}
	virtual void draw() {}

	virtual ~Component() {}


};

class Entity {
public:
	Entity() = default;
	~Entity() = default;

	template<typename T, typename... TArgs>
	inline T& addComponent(TArgs&&... args) {
		T* comp = new T(std::forward<TArgs>(args)...);
		std::unique_ptr<Component> uptr{ comp };
		components.emplace_back(std::move(uptr));

		if (comp->isInit()) {
			
			compList[getComponentTypeID<T>()] = comp;
			compBitset[getComponentTypeID<T>()] = true;
			comp->entity = this;
			comp->init();
			return *comp;
		}

		return *static_cast<T*>(nullptr);
	}


	template<typename T>
	inline T& getComponent() const {
		Component* ptr(compList[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}


	template<typename T>
	inline bool hasComponent() const {
		return compBitset[getComponentTypeID<T>()];
	}


	inline bool isActive() const {
		return active;
	}

	inline void destroy() {
		active = false;
	}


	inline void draw() {
		for (auto& c: components) {
			c->draw();
		}
	}
	inline void update() {
		for (auto& c : components) {
			c->update();
		}
	}

	void setName(std::string name) {
		this->name = name;
	}
	std::string getName() {
		return name;
	}
private:
	bool active = true;
	ComponentList compList;
	ComponentBitset compBitset;
	std::vector<std::unique_ptr<Component>> components;
	std::string name;
public:
	
};


class EntityManager {
public:
	EntityManager() = default;
	~EntityManager() = default;

	void draw() {
		for (auto& e : entities) e->draw();
	}

	void update() {
		for (auto& e : entities) e->update();
	}

	void refresh() {
		entities.erase(std::remove_if(std::begin(entities), std::end(entities),
			[](const std::unique_ptr<Entity>& mEntity)
			{
				return !mEntity->isActive();
			}),	
				std::end(entities));
	}
	Entity& addEntity() {
		Entity* e = new Entity();
		std::unique_ptr<Entity> uptr{ e };
		entities.emplace_back(std::move(uptr));
		return *e;
	}

private:
	std::vector<std::unique_ptr<Entity>> entities;
};