#pragma once

#include "Component.h"
#include "ResourceIdientificators.h"
#include "ResourceHolder.h"

#include <SFML/Graphics.hpp>


namespace GUI
{

	struct Label : public Component
	{
		typedef std::shared_ptr<Label> Ptr;

		Label(const std::string& text, const FontHolder& fonts);

		virtual bool isSelectable() const override;
		void setText(const std::string& text);

		virtual void handleEvent(const sf::Event& event) override;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		sf::Text text;
	};

}

