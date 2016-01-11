#pragma once
#include "SceneNode.h"
#include "ResourceIdientificators.h"


struct SoundPlayer;

struct SoundNode : public SceneNode
{
	SoundNode(SoundPlayer& player);
	void playSound(SoundEffect::ID sound, sf::Vector2f position);

	virtual unsigned int getCategory() const override;

	SoundPlayer& sounds;
};

