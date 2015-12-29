#include "Button.h"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>


namespace GUI
{

	Button::Button(const FontHolder& fonts, const TextureHolder& textures)
		:callback()
		,norm_texture(textures.get(Textures::ButtonNormal))
		,select_texture(textures.get(Textures::ButtonSelected))
		,press_texture(textures.get(Textures::ButtonPressed))
		,sprite()
		,text("", fonts.get(Fonts::Main), 16)
		,is_toggle(false)
	{
		sprite.setTexture(norm_texture);

		sf::FloatRect bounds = sprite.getLocalBounds();
		text.setPosition(bounds.width / 2.f, bounds.height / 2.f);
	}

	void Button::setCallback(Callback back)
	{
		callback = std::move(back);
	}

	void Button::setText(const std::string& txt)
	{
		text.setString(txt);
		text.setOrigin(text.getGlobalBounds().width / 2.f, text.getGlobalBounds().height / 2.f);
	}

	void Button::setToggle(bool flag)
	{
		is_toggle = flag;
	}

	bool Button::isSelectable() const
	{
		return true;
	}

	void Button::select()
	{
		Component::select();
		sprite.setTexture(select_texture);
	}

	void Button::deselect()
	{
		Component::deselect();
		sprite.setTexture(norm_texture);
	}

	void Button::activate()
	{
		Component::activate();

		if (is_toggle)
			sprite.setTexture(press_texture);

		if (callback)
			callback();

		if (!is_toggle)
			deactivate();
	}

	void Button::deactivate()
	{
		Component::deactivate();

		if (is_toggle)
		{
			if (isSelected())
				sprite.setTexture(select_texture);
			else
				sprite.setTexture(norm_texture);
		}
	}

	void Button::handleEvent(const sf::Event&)
	{
	}

	void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(sprite, states);
		target.draw(text, states);
	}

}
