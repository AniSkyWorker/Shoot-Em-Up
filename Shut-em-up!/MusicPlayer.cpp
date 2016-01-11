#include "MusicPlayer.h"

MusicPlayer::MusicPlayer()
	:music()
	,file_names()
	,volume(100.f)
{
	file_names[Music::MissionTheme] = "Media/Music/MenuTheme.ogg";
	file_names[Music::MenuTheme] = "Media/Music/MissionTheme.ogg";
}

void MusicPlayer::play(Music::ID theme)
{
	std::string filename = file_names[theme];

	if (!music.openFromFile(filename))
		throw std::runtime_error("Music " + filename + " could not be loaded.");

	music.setVolume(volume);
	music.setLoop(true);
	music.play();
}

void MusicPlayer::stop()
{
	music.stop();
}

void MusicPlayer::setVolume(float vol)
{
	volume = vol;
}

void MusicPlayer::setPaused(bool paused)
{
	if (paused)
		music.pause();
	else
		music.play();
}

