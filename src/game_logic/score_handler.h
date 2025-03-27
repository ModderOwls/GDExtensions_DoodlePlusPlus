#pragma once

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/node.hpp>

namespace godot 
{
	class ScoreHandler : public Node 
	{
		GDCLASS(ScoreHandler, Node)

		private:
			static ScoreHandler* instance;

            int score;

		protected:
			static void _bind_methods();

		public:
            ScoreHandler();
			~ScoreHandler();

			void _ready() override;

			static ScoreHandler* get_instance();

            void add_score(int amount);
            int get_score() const;
        
            void check_win();
	};
}