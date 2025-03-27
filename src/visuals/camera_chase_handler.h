#pragma once

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/camera2d.hpp>

namespace godot 
{
	class CameraChaseHandler : public Camera2D 
	{
		GDCLASS(CameraChaseHandler, Camera2D)

	protected:
		static void _bind_methods();

	public:
        CameraChaseHandler();
		~CameraChaseHandler();

		void _ready() override;
		void _process(double delta) override;

		Node2D* target_follow = nullptr;

		Vector2 offset;

		bool lock_x = false;

		void set_target_follow(Node2D* new_targetFollow);
		Node2D* get_target_follow() const;

		void set_lock_x(const bool new_lock_x);
		bool get_lock_x() const;
	};
}