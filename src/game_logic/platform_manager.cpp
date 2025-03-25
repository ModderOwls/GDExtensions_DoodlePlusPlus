
#include "platform_manager.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;


PlatformManager::PlatformManager() 
{
    lastPosition = Vector2(0, 0);

	engine = nullptr;
    platform_prefab = nullptr;
}

PlatformManager::~PlatformManager() { }


void PlatformManager::_bind_methods() 
{	
	//Export variables to inspector.
	ClassDB::bind_method(D_METHOD("get_platform_prefab"), &PlatformManager::get_platform_prefab);
	ClassDB::bind_method(D_METHOD("set_platform_prefab", "new_platform_prefab"), &PlatformManager::set_platform_prefab);

	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "platform_prefab", PROPERTY_HINT_NODE_TYPE, "Node2D"), "set_platform_prefab", "get_platform_prefab");
}


void PlatformManager::_ready()
{
	engine = Engine::get_singleton();

	//Ensure it doesn't run in the editor.
	if (engine->is_editor_hint())
	{
		set_process(false);
		set_physics_process(false);
	}
	else
	{
		set_process(true);
		set_physics_process(true);
	}
}

void PlatformManager::_process(double delta)
{
}

void PlatformManager::_physics_process(double delta)
{
}


//Physics node s(g)etters
void PlatformManager::set_platform_prefab(PackedScene* new_platform_prefab) { platform_prefab = new_platform_prefab; }
PackedScene* PlatformManager::get_platform_prefab() const { return platform_prefab; }