#pragma once

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/static_body2d.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>

namespace godot 
{
	class PlatformManager : public Node2D 
	{
		GDCLASS(PlatformManager, Node2D)

		private:
			Engine *engine;

			Node* ignore_space;
			StaticBody2D* collider;

			Node2D* create_platform();

			Vector2 last_position;
			float next_platform;

		protected:
			static void _bind_methods();

		public:
            PlatformManager();
			~PlatformManager();

			void _ready() override;
			void _physics_process(double delta) override;

			Node2D* get_platform();
			void return_platform(Node2D* platform);

			float spawn_width = 30;
			float spawn_initial = 10;
			float spawn_rate = 30;

			std::vector<Node2D*> pool_platforms;
			std::vector<Node2D*> active_platforms;
			Ref<PackedScene> platform_prefab = nullptr;

			Ref<RandomNumberGenerator> rng;

			void set_platform_prefab(Ref<PackedScene> new_platform_prefab);
			Ref<PackedScene> get_platform_prefab() const;

			void set_spawn_width(const float new_spawn_width);
			float get_spawn_width() const;

			void set_spawn_initial(const float new_spawn_amount);
			float get_spawn_initial() const;

			void set_spawn_rate(const float new_spawn_rate);
			float get_spawn_rate() const;
	};
}