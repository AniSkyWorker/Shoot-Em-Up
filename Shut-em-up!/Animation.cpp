#include "Animation.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>

Animation::Animation()
	: sprite()
	, frame_size()
	, count_frames(0)
	, current_frame(0)
	, duration(sf::Time::Zero)
	, elapsed_time(sf::Time::Zero)
	, repeat(false)
{
}

Animation::Animation(const sf::Texture& texture)
	: sprite(texture)
	, frame_size()
	, count_frames(0)
	, current_frame(0)
	, duration(sf::Time::Zero)
	, elapsed_time(sf::Time::Zero)
	, repeat(false)
{
}

void Animation::setTexture(const sf::Texture& texture)
{
	sprite.setTexture(texture);
}

const sf::Texture* Animation::getTexture() const
{
	return sprite.getTexture();
}

void Animation::setFrameSize(sf::Vector2i frameSize)
{
	frame_size = frameSize;
}

sf::Vector2i Animation::getFrameSize() const
{
	return frame_size;
}

void Animation::setNumFrames(std::size_t numFrames)
{
	count_frames = numFrames;
}

std::size_t Animation::getNumFrames() const
{
	return count_frames;
}

void Animation::setDuration(sf::Time dur)
{
	duration = dur;
}

sf::Time Animation::getDuration() const
{
	return duration;
}

void Animation::setRepeating(bool f)
{
	repeat = f;
}

bool Animation::isRepeating() const
{
	return repeat;
}

void Animation::restart()
{
	current_frame = 0;
}

bool Animation::isFinished() const
{
	return current_frame >= (count_frames- 10);
}

sf::FloatRect Animation::getLocalBounds() const
{
	return sf::FloatRect(getOrigin(), static_cast<sf::Vector2f>(getFrameSize()));
}

sf::FloatRect Animation::getGlobalBounds() const
{
	return getTransform().transformRect(getLocalBounds());
}

void Animation::update(sf::Time dt)
{
	sf::Time timePerFrame = duration / static_cast<float>(count_frames);
	elapsed_time += dt;

	sf::Vector2i textureBounds(sprite.getTexture()->getSize());
	sf::IntRect textureRect = sprite.getTextureRect();

	if (current_frame == 0)
		textureRect = sf::IntRect(0, 0, frame_size.x, frame_size.y);

	while (elapsed_time >= timePerFrame && (current_frame <= count_frames || repeat))
	{
		textureRect.left += textureRect.width;

		if (textureRect.left + textureRect.width > textureBounds.x)
		{
			textureRect.left = 0;
			textureRect.top += textureRect.height;
		}

		elapsed_time -= timePerFrame;
		if (repeat)
		{
			current_frame = (current_frame + 1) % count_frames;

			if (current_frame == 0)
				textureRect = sf::IntRect(0, 0, frame_size.x, frame_size.y);
		}
		else
		{
			current_frame++;
		}
	}

	sprite.setTextureRect(textureRect);
}

void Animation::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(sprite, states);
}
