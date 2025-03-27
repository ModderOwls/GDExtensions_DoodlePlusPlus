
#include "timer_label.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;


TimerLabel::TimerLabel()
{
	set_process(false);
	set_physics_process(false);
}

TimerLabel::~TimerLabel() { }

void TimerLabel::_process(double delta)
{
    time += delta;

    update_timer();
}

void TimerLabel::_ready()
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
        if (!auto_start)
        {
            set_process(false);
            set_physics_process(false);

            return;
        }

		set_process(true);
		set_physics_process(true);
	}
}


void TimerLabel::start_timer()
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
}

void TimerLabel::update_timer()
{
    String minutes = String::num_int64(Math::floor(time / 60)).pad_zeros(2);
    String seconds = String::num_int64(Math::floor(fmod(time, 60))).pad_zeros(2);
    String milli = String::num_int64(Math::floor(fmod(time, 1) * 100)).pad_zeros(2);

    set_text(minutes + ":" + seconds + ":" + milli);
}

void TimerLabel::stop_timer()
{
    set_process(false);
    set_physics_process(false);
}


void TimerLabel::_bind_methods() 
{
	//Bind methods for other scripts to use.
	ClassDB::bind_method(D_METHOD("start_timer"), &TimerLabel::start_timer);
	ClassDB::bind_method(D_METHOD("update_timer"), &TimerLabel::update_timer);
	ClassDB::bind_method(D_METHOD("stop_timer"), &TimerLabel::stop_timer);

	ClassDB::bind_method(D_METHOD("set_time", "value"), &TimerLabel::set_time);
	ClassDB::bind_method(D_METHOD("get_time"), &TimerLabel::get_time);

	ClassDB::bind_method(D_METHOD("set_auto_start", "new_auto_start"), &TimerLabel::set_auto_start);
	ClassDB::bind_method(D_METHOD("get_auto_start"), &TimerLabel::get_auto_start);

	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "auto_start"), "set_auto_start", "get_auto_start");
}

void TimerLabel::set_time(const float value)
{
    time = value;

    update_timer();
}
float TimerLabel::get_time() const { return time; }

void TimerLabel::set_auto_start(const bool new_auto_start) { auto_start = new_auto_start; }
bool TimerLabel::get_auto_start() const { return auto_start; }