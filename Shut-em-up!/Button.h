#pragma once

#include "Component.h"
#include "ResourceIdientificators.h"
#include "ResourceHolder.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <vector>
#include <string>
#include <memory>
#include <functional>


namespace GUI
{

	struct Button : public Component
	{
			typedef std::shared_ptr<Button>		Ptr;
			typedef std::function<void()>		Callback;
		
			Button(const FontHolder& fonts, const TextureHolder& textures);

			void setCallback(Callback callback);
			void setText(const std::string& text);
			void setToggle(bool flag);

			virtual bool isSelectable() const override;
			virtual void select() override;
			virtual void deselect() override;

			virtual void activate() override;
			virtual void deactivate() override;

			virtual void handleEvent(const sf::Event& event) override;
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

			Callback callback;
			const sf::Texture& norm_texture;
			const sf::Texture& select_texture;
			const sf::Texture& press_texture;
			sf::Sprite sprite;
			sf::Text text;
			bool is_toggle;
	};

}

