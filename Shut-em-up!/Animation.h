#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>


struct Animation : public sf::Drawable, public sf::Transformable
{
	Animation();
	Animation(const sf::Texture& texture);

	void setTexture(const sf::Texture& texture);
	const sf::Texture* getTexture() const;

	void setFrameSize(sf::Vector2i mFrameSize);
	sf::Vector2i getFrameSize() const;

	void setNumFrames(std::size_t numFrames);
	std::size_t getNumFrames() const;

	void setDuration(sf::Time duration);
	sf::Time getDuration() const;

	void setRepeating(bool flag);
	bool isRepeating() const;

	void restart();
	bool isFinished() const;

	sf::FloatRect getLocalBounds() const;
	sf::FloatRect getGlobalBounds() const;

	void update(sf::Time dt);


	void draw(sf::RenderTarget& target, sf::RenderStates states) const;


	sf::Sprite sprite;
	sf::Vector2i frame_size;
	std::size_t count_frames;
	std::size_t current_frame;
	sf::Time duration;
	sf::Time elapsed_time;
	bool repeat;
};
