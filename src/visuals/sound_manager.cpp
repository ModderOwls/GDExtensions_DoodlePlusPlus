
#include "sound_manager.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/audio_server.hpp>

using namespace godot;

SoundManager* SoundManager::instance = nullptr;


SoundManager::SoundManager() 
{
	music_player = nullptr;
	sound_effect_player = nullptr;

	instance = this;
}

SoundManager::~SoundManager() { }

void SoundManager::_ready()
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

	music_player = memnew(AudioStreamPlayer);
	sound_effect_player = memnew(AudioStreamPlayer);

	music_player->set_bus("Music");
	sound_effect_player->set_bus("SoundEffects");

	add_child(music_player);
	add_child(sound_effect_player);

	if (!music.is_valid()) return;

	music_player->set_stream(music);
	music_player->play();
}

SoundManager* SoundManager::get_instance() 
{
	return instance;
}

void SoundManager::play_sound(const String& sound_name)
{
	if (sound_library.has(sound_name))
	{
		Ref<AudioStream> sound = sound_library[sound_name];
		
		if (!sound.is_valid())
		{
			print_error("Audio playback went wrong! Ensure the dictionary key and value types are correct.");
		}

		sound_effect_player->set_stream(sound);
		sound_effect_player->play();
	}
	else
	{
		print_error("Could not find sound effect: " + sound_name);
	}
}

void SoundManager::add_sound(const String& sound_name, const Ref<AudioStream>& sound)
{
	if (sound.is_valid())
	{
		sound_library[sound_name] = sound;
	}
	else
	{
		print_error("The sound you added was considered invalid.");
	}
}


void SoundManager::_bind_methods() 
{
	//Bind methods for other scripts to use.
	ClassDB::bind_method(D_METHOD("add_sound", "sound_name", "sound"), &SoundManager::add_sound);
	ClassDB::bind_method(D_METHOD("play_sound", "sound_name"), &SoundManager::play_sound);

	ClassDB::bind_method(D_METHOD("get_sounds"), &SoundManager::get_sounds);
	ClassDB::bind_method(D_METHOD("set_sounds", "new_sounds"), &SoundManager::set_sounds);

	ClassDB::bind_method(D_METHOD("get_music"), &SoundManager::get_music);
	ClassDB::bind_method(D_METHOD("set_music", "new_music"), &SoundManager::set_music);

	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "music"), "set_music", "get_music");
	ADD_PROPERTY(PropertyInfo(Variant::DICTIONARY, "sound_library"), "set_sounds", "get_sounds");
}

//Sounds s(g)etters
void SoundManager::set_sounds(const Dictionary& new_sounds) { sound_library = new_sounds; }
Dictionary SoundManager::get_sounds() const { return sound_library; }

//Music s(g)etters
void SoundManager::set_music(const Ref<AudioStream>& new_music) { music = new_music; }
Ref<AudioStream> SoundManager::get_music() const { return music; }