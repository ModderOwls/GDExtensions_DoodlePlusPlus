#pragma once

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/audio_stream_player.hpp>
#include <godot_cpp/classes/audio_stream.hpp>
#include <godot_cpp/variant/dictionary.hpp>
#include <godot_cpp/variant/string.hpp>

namespace godot 
{
	class SoundManager : public Node 
	{
		GDCLASS(SoundManager, Node)

		private:
            static SoundManager* instance;

			AudioStreamPlayer* music_player;
			AudioStreamPlayer* sound_effect_player;

			Dictionary sound_library;
			Ref<AudioStream> music;

		protected:
			static void _bind_methods();

		public:
            SoundManager();
			~SoundManager();

			void _ready() override;

			static SoundManager* get_instance();

			void play_sound(const String& sound_name);
			void add_sound(const String& sound_name, const Ref<AudioStream>& sound);

			void SoundManager::set_sounds(const Dictionary& new_sounds);
			Dictionary SoundManager::get_sounds() const;

			void SoundManager::set_music(const Ref<AudioStream>& new_music);
			Ref<AudioStream> SoundManager::get_music() const;
	};
}