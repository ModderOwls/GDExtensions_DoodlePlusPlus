
#include "score_manager.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/file_access.hpp>
#include <godot_cpp/classes/json.hpp>

using namespace godot;

ScoreManager* ScoreManager::instance = nullptr;


ScoreManager::ScoreManager() 
{
	instance = this;
}

ScoreManager::~ScoreManager() { }

void ScoreManager::_ready()
{
	Engine* engine = Engine::get_singleton();

	//Ensure it doesn't run in the editor.
	if (engine->is_editor_hint())
	{
		set_process(false);
		set_physics_process(false);

		return;
	}
	else
	{
		set_process(true);
		set_physics_process(true);
	}

	load_record_time();
}

ScoreManager* ScoreManager::get_instance() 
{
	return instance;
}


void ScoreManager::detect_win() 
{
    if (score >= win_amount) 
    {
		//Pause the game.
		Engine::get_singleton()->set_time_scale(0);

		if (timer_label != nullptr)
		{
			float time = timer_label->get_time();

			if (time < record_time || record_time == 0)
			{
				record_time = time;

				//Save new personal record.
				save_record_time();

				emit_signal("record_changed", record_time);
			}
		}

		emit_signal("score_win", true);
    }
}


void ScoreManager::_bind_methods() 
{
	//Bind methods for other scripts to use.
    ClassDB::bind_method(D_METHOD("add_score", "amount"), &ScoreManager::add_score);
    ClassDB::bind_method(D_METHOD("get_score"), &ScoreManager::get_score);

	ClassDB::bind_method(D_METHOD("get_win_amount"), &ScoreManager::get_win_amount);
	ClassDB::bind_method(D_METHOD("set_win_amount", "new_win_amount"), &ScoreManager::set_win_amount);

	ClassDB::bind_method(D_METHOD("get_timer_label"), &ScoreManager::get_timer_label);
	ClassDB::bind_method(D_METHOD("set_timer_label", "new_timer_label"), &ScoreManager::set_timer_label);

	
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "win_amount"), "set_win_amount", "get_win_amount");
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "timer_label", PROPERTY_HINT_NODE_TYPE, "TimerLabel"), "set_timer_label", "get_timer_label");


	//Add signals for when you win or lose.
    ADD_SIGNAL(MethodInfo("score_win", PropertyInfo(Variant::BOOL, "won")));
    ADD_SIGNAL(MethodInfo("score_changed", PropertyInfo(Variant::INT, "new_score")));
    ADD_SIGNAL(MethodInfo("score_lose", PropertyInfo(Variant::BOOL, "lost")));

    ADD_SIGNAL(MethodInfo("record_changed", PropertyInfo(Variant::FLOAT, "new_record")));
}

void ScoreManager::add_score(int amount) 
{
    score += amount;

    emit_signal("score_changed", score);
    
    detect_win();
}

int ScoreManager::get_score() const { return score; }

//Win amount s(g)etters
void ScoreManager::set_win_amount(const float new_win_amount) { win_amount = new_win_amount; }
float ScoreManager::get_win_amount() const { return win_amount; }

//Timer label s(g)etters
void ScoreManager::set_timer_label(TimerLabel* new_timer_label) { timer_label = new_timer_label; }
TimerLabel* ScoreManager::get_timer_label() const { return timer_label; }


void ScoreManager::save_record_time() 
{
	//Turn it into a dictionary for ease of use.
	Dictionary data;
	data["record_time"] = record_time;

	//Create JSON object.
	JSON* json = memnew(JSON);
	String json_string = json->stringify(data);

	//Write the JSON string to the file.
	Ref<FileAccess> file = FileAccess::open("user://record_time.json", FileAccess::WRITE);
	if (file.is_valid()) 
	{
		file->store_string(json_string);
		file->close();
	}
}
void ScoreManager::load_record_time() 
{
	//Load last record time if it exists.
	Ref<FileAccess> file = FileAccess::open("user://record_time.json", FileAccess::READ);

	if (file.is_valid()) 
	{
		String json_content = file->get_as_text();
		file->close();

		JSON* json = memnew(JSON);
        Error error = json->parse(json_content);

        if (error == OK) 
        {
            Dictionary data = json->get_data();

            if (data.has("record_time")) 
            {
                record_time = data["record_time"];

				emit_signal("record_changed", record_time);
            }
        }
        else 
        {
            print_line("Failed to parse save, it might be corrupted.");
        }
	}
}