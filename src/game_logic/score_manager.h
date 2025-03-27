#pragma once

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/node.hpp>
#include "../visuals/ui/timer_label.h"

namespace godot 
{
	class ScoreManager : public Node 
	{
		GDCLASS(ScoreManager, Node)

		private:
			static ScoreManager* instance;

            float score = 0;

			float win_amount = 100;
			float record_time = 0;

			TimerLabel* timer_label = nullptr;

		protected:
			static void _bind_methods();

		public:
            ScoreManager();
			~ScoreManager();

			void _ready() override;

			static ScoreManager* get_instance();
        
            void detect_win();
			void restart();
			void death();

            void add_score(const float amount);
            int get_score() const;

			void set_win_amount(const float new_win_amount);
			float get_win_amount() const;

			void set_timer_label(TimerLabel* new_timer_label);
			TimerLabel* get_timer_label() const;

			void load_record_time();
			void save_record_time();
	};
}