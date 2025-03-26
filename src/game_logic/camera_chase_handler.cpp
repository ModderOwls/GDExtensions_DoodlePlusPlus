
#include "camera_chase_handler.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;


CameraChaseHandler::CameraChaseHandler() 
{
	offset = Vector2(0, 0);
}

CameraChaseHandler::~CameraChaseHandler() { }


void CameraChaseHandler::_ready()
{
	Engine* engine = Engine::get_singleton();

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

void CameraChaseHandler::_process(double delta)
{
	if (target_follow == nullptr) return;

	Vector2 target_position = target_follow->get_global_position() + offset;
	Vector2 position = get_global_position() + offset;

	if (lock_x) target_position.x = offset.x;

	//Ensure it never goes lower than the target.
	if (target_position.y > position.y)
	{
		target_position.y = position.y;
	}

	set_position(target_position);
}


void CameraChaseHandler::_bind_methods() 
{	
	//Export variables to inspector.
	ClassDB::bind_method(D_METHOD("get_target_follow"), &CameraChaseHandler::get_target_follow);
	ClassDB::bind_method(D_METHOD("set_target_follow", "new_target_follow"), &CameraChaseHandler::set_target_follow);

	ClassDB::bind_method(D_METHOD("get_lock_x"), &CameraChaseHandler::get_lock_x);
	ClassDB::bind_method(D_METHOD("set_lock_x", "new_lock_x"), &CameraChaseHandler::set_lock_x);


	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "target_follow", PROPERTY_HINT_NODE_TYPE, "Node2D"), "set_target_follow", "get_target_follow");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "lock_x"), "set_lock_x", "get_lock_x");
}

//Target s(g)etters
void CameraChaseHandler::set_target_follow(Node2D* new_target_follow) { target_follow = new_target_follow; }
Node2D* CameraChaseHandler::get_target_follow() const { return target_follow; }

//Lock x s(g)etters
void CameraChaseHandler::set_lock_x(const bool new_lock_x) { lock_x = new_lock_x; }
bool CameraChaseHandler::get_lock_x() const { return lock_x; }