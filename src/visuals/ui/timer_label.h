#pragma once

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/label.hpp>

namespace godot 
{
	class TimerLabel : public Label
	{
		GDCLASS(TimerLabel, Label)

        private:
            double time;

		protected:
			static void _bind_methods();

		public:
            TimerLabel();
			~TimerLabel();

			void _process(double delta) override;
			void _ready() override;

            bool auto_start = false;
            
            void start_timer();
            void update_timer();
            void restart_timer();
            void stop_timer();

            void set_time(const float value);
            float get_time() const;

            void set_auto_start(const bool new_auto_start);
            bool get_auto_start() const;
	};
}