
#include "platform_manager.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;


PlatformManager::PlatformManager() 
{
	engine = nullptr;

	ignore_space = nullptr;
	collider = nullptr;

	last_position = Vector2(0, 0);
	next_platform = 0;
}

PlatformManager::~PlatformManager() { }


void PlatformManager::_ready()
{
	engine = Engine::get_singleton();

	//Ensure it doesn't run in the editor.
	if (engine->is_editor_hint())
	{
		set_process(false);
		set_physics_process(false);

		return;
	}
	else
	{
		set_process(true);
		set_physics_process(true);
	}

	//Odd name, but this means platforms with this as their parent wont follow the manager's transform/space.
	ignore_space = memnew(Node);
	add_child(ignore_space);

	collider = memnew(StaticBody2D);
	ignore_space->add_child(collider);

	rng.instantiate();
	
	last_position = get_position();

	for (int i = 0; i < spawn_initial; ++i)
	{
		Node2D* newNode = create_platform();

		if (newNode != nullptr)
		{
			pool_platforms.push_back(newNode);
		}
	}
}

void PlatformManager::_physics_process(double delta)
{
	next_platform += last_position.y - get_global_position().y;

	while (next_platform - spawn_rate > 0)
	{
		next_platform -= spawn_rate;

		Node2D* newPlatform = get_platform();

		newPlatform->set_global_position(get_global_position() + Vector2(1, 0) * rng->randf_range(-spawn_width, spawn_width));

		active_platforms.push_back(newPlatform);
	}

	for (int i = 0; i < active_platforms.size(); ++i)
	{
		float offset = get_position().y * 2;

		//Despawn platforms if below the screen.
		if (active_platforms[i]->get_global_position().y > get_global_position().y - offset + 30)
		{
			Node2D* platform = active_platforms[i];

			active_platforms.erase(active_platforms.begin() + i);

			return_platform(platform);
		}
	}

	last_position = get_global_position();
}


Node2D* PlatformManager::create_platform()
{
	if (!platform_prefab.is_valid())
	{
		print_error("Attach a platform prefab to the platform manager!");

		return nullptr;
	}

	Node2D* platform = Object::cast_to<Node2D>(platform_prefab->instantiate());

	//If platform doesn't contain a node2D, return.
	if (!platform)
	{
		print_error("Platform prefab on platform manager isn't a Node2D!");

		return nullptr;
	}

	//Ensure it is out of view.
	add_child(platform);
	platform->set_position(Vector2(0, 100));
	platform->set_visible(false);

	return platform;
}

Node2D* PlatformManager::get_platform()
{
	if (pool_platforms.size() == 0)
	{
		//Create new platform if no pooled ones are left.
		Node2D* platform = create_platform();

		//Set it's parent to ignore space.
		platform->get_parent()->remove_child(platform);
		collider->add_child(platform);

		platform->set_visible(true);

		return platform;
	}
	else
	{
		//Grab the platform at the back.
		Node2D* back = pool_platforms.back();
		pool_platforms.pop_back();

		//Set it's parent to ignore space.
		back->get_parent()->remove_child(back);
		collider->add_child(back);

		back->set_visible(true);

		return back;
	}
}

void PlatformManager::return_platform(Node2D* platform)
{
	//Set its parent to the manager again.
	platform->get_parent()->remove_child(platform);
	add_child(platform);

	//Ensure it is out of view.
	platform->set_position(Vector2(0, 100));
	platform->set_visible(false);
	
	//Put it back in the pool
	pool_platforms.push_back(platform);
}


void PlatformManager::_bind_methods() 
{	
	//Export variables to inspector.
	ClassDB::bind_method(D_METHOD("get_platform_prefab"), &PlatformManager::get_platform_prefab);
	ClassDB::bind_method(D_METHOD("set_platform_prefab", "new_platform_prefab"), &PlatformManager::set_platform_prefab);
	
	ClassDB::bind_method(D_METHOD("get_spawn_width"), &PlatformManager::get_spawn_width);
	ClassDB::bind_method(D_METHOD("set_spawn_width", "new_spawn_width"), &PlatformManager::set_spawn_width);
	
	ClassDB::bind_method(D_METHOD("get_spawn_initial"), &PlatformManager::get_spawn_initial);
	ClassDB::bind_method(D_METHOD("set_spawn_initial", "new_spawn_initial"), &PlatformManager::set_spawn_initial);
	
	ClassDB::bind_method(D_METHOD("get_spawn_rate"), &PlatformManager::get_spawn_rate);
	ClassDB::bind_method(D_METHOD("set_spawn_rate", "new_spawn_rate"), &PlatformManager::set_spawn_rate);

	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "platform_prefab", PROPERTY_HINT_RESOURCE_TYPE, "PackedScene"), "set_platform_prefab", "get_platform_prefab");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "spawn_width"), "set_spawn_width", "get_spawn_width");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "spawn_initial"), "set_spawn_initial", "get_spawn_initial");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "spawn_rate"), "set_spawn_rate", "get_spawn_rate");
}

//Platform prefab s(g)etters
void PlatformManager::set_platform_prefab(Ref<PackedScene> new_platform_prefab) { platform_prefab = new_platform_prefab; }
Ref<PackedScene> PlatformManager::get_platform_prefab() const { return platform_prefab; }

//Spawn width s(g)etters
void PlatformManager::set_spawn_width(const float new_spawn_width) { spawn_width = new_spawn_width; }
float PlatformManager::get_spawn_width() const { return spawn_width; }

//Spawn initial s(g)etters
void PlatformManager::set_spawn_initial(const float new_spawn_initial) { spawn_initial = new_spawn_initial; }
float PlatformManager::get_spawn_initial() const { return spawn_initial; }

//Spawn rate s(g)etters
void PlatformManager::set_spawn_rate(const float new_spawn_rate) { spawn_rate = new_spawn_rate; }
float PlatformManager::get_spawn_rate() const { return spawn_rate; }