#pragma once

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/input_event.hpp>

namespace godot 
{
	class PlayerPhysics : public Node2D 
	{
		GDCLASS(PlayerPhysics, Node2D)

	private:
		void movement_air();
		void on_floor_hit(Dictionary& ray);

		Dictionary push_raycast(Vector2 from, Vector2 to);

		float input_left = 0;
		float input_right = 0;

		float delta_physics_f;

	protected:
		static void _bind_methods();

	public:
		PlayerPhysics();
		~PlayerPhysics();

		void _ready() override;
		void _physics_process(double delta) override;
		void _unhandled_input(const Ref<InputEvent> &input) override;

		float input_horizontal = 0;

		Vector2 velocity;

		float acceleration = 640;
		float top_speed = 60;
		float gravity = 80;
		float jump_height = 80;
		float drag = 150;

		float height = 8;

		void set_acceleration(const float new_acceleration);
		float get_acceleration() const;

		void set_top_speed(const float new_top_speed);
		float get_top_speed() const;

		void set_gravity(const float new_gravity);
		float get_gravity() const;

		void set_jump_height(const float new_jump_height);
		float get_jump_height() const;

		void set_drag(const float new_drag);
		float get_drag() const;

		void set_height(const float new_height);
		float get_height() const;
	};
}