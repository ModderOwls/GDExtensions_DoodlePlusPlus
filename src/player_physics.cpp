
#include "player_physics.h"
#include <godot_cpp/core/class_db.hpp>

#include <godot_cpp/classes/physics_direct_space_state2d.hpp>
#include <godot_cpp/classes/physics_ray_query_parameters2d.hpp>
#include <godot_cpp/classes/world2d.hpp>

using namespace godot;

PhysicsDirectSpaceState2D* spaceState;
Ref<PhysicsRayQueryParameters2D> query;

uint32_t rayMask = 0b01;

void player_physics::_bind_methods() 
{	
	//Export variables to inspector.
	ClassDB::bind_method(D_METHOD("get_gravity"), &player_physics::get_gravity);
	ClassDB::bind_method(D_METHOD("set_gravity", "new_gravity"), &player_physics::set_gravity);

	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "gravity"), "set_gravity", "get_gravity");

	
	ClassDB::bind_method(D_METHOD("get_moveSpeed"), &player_physics::get_moveSpeed);
	ClassDB::bind_method(D_METHOD("set_moveSpeed", "new_moveSpeed"), &player_physics::set_moveSpeed);

	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "moveSpeed"), "set_moveSpeed", "get_moveSpeed");

	
	ClassDB::bind_method(D_METHOD("get_height"), &player_physics::get_height);
	ClassDB::bind_method(D_METHOD("set_height", "new_height"), &player_physics::set_height);

	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "height"), "set_height", "get_height");
}

player_physics::player_physics() 
{
	deltaPhysF = 0;

	grounded = false;
	velocity = Vector2(0, 0);
}

player_physics::~player_physics() { }

void player_physics::_ready()
{
	Engine *engine = Engine::get_singleton();

	//Set up raycast variables.
	//Assuming it's like C#/.Net, setting this every frame/tick causes garbage.
	spaceState = CanvasItem::get_world_2d()->get_direct_space_state();
	query = PhysicsRayQueryParameters2D::create(Vector2(0, 0), Vector2(0, -1), rayMask);

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

void player_physics::_process(double delta) 
{
	
}

void player_physics::_physics_process(double delta)
{
	deltaPhysF = (float)delta;

	if (grounded) movement_grounded();
	else movement_air();

	//Update physics.
	Node2D::set_global_position(Node2D::get_global_position() + velocity);
}

void player_physics::movement_grounded()
{
	Vector2 globalPosition = Node2D::get_global_position();

	velocity.x = inputHorizontal * moveSpeed;

	//Perform raycast.
	Dictionary ray = push_raycast(globalPosition, globalPosition + Vector2(0, height / 2 + .1f));

	//Detect for a floor.
	if (!ray.is_empty())
	{
		//Make player stick to floor on ramps.
		Node2D::set_global_position((Vector2)ray["position"] + Vector2(0, -1) * height / 2);
	}
	else
	{
		grounded = false;

		print_line("ray lost floor.");
	}
}

void player_physics::movement_air()
{
	Vector2 globalPosition = Node2D::get_global_position();

	velocity.y += gravity * deltaPhysF;

	//Perform raycast.
	Dictionary ray = push_raycast(globalPosition, globalPosition + Vector2(0, height / 2 + .1f));

	//Detect for a floor.
	if (!ray.is_empty())
	{
		grounded = true;

		velocity.y = 0;

		Node2D::set_global_position((Vector2)ray["position"] + Vector2(0, -1) * height / 2);

		print_line("ray hit floor!");
	}
}

void player_physics::_unhandled_input(const Ref<InputEvent> &input)
{
	if (input->is_echo() || !input->is_action_type()) return;

	if (input->is_action("playerRight"))
	{
		inputHorizontal = input->get_action_strength("playerRight");
	}
	else if (input->is_action("playerLeft"))
	{
		inputHorizontal = -input->get_action_strength("playerLeft");
	}

	//delete(&input);
}

Dictionary player_physics::push_raycast(const Vector2 from, const Vector2 to)
{
	query->set_from(from);
	query->set_to(from+to);

	return spaceState->intersect_ray(query); //do raycast thingamajig
}

//Gravity s(g)etters
void player_physics::set_gravity(const float new_gravity) { gravity = new_gravity; }
float player_physics::get_gravity() const { return gravity; }

//MoveSpeed s(g)etters
void player_physics::set_moveSpeed(const float new_moveSpeed) { moveSpeed = new_moveSpeed; }
float player_physics::get_moveSpeed() const { return moveSpeed; }

//Height s(g)etters
void player_physics::set_height(const float new_height) { height = new_height; }
float player_physics::get_height() const { return height; }