#pragma once

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/static_body2d.hpp>

namespace godot 
{
	class PlatformManager : public StaticBody2D 
	{
		GDCLASS(PlatformManager, StaticBody2D)

		private:
			Vector2 lastPosition;

			Engine *engine;

		protected:
			static void _bind_methods();

		public:
            PlatformManager();
			~PlatformManager();

			void _ready() override;
			void _process(double delta) override;
			void _physics_process(double delta) override;

			PackedScene* platform_prefab;

			void set_platform_prefab(PackedScene* new_physicsNode);
			PackedScene* get_platform_prefab() const;
	};
}