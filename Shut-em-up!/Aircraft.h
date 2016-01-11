#pragma once
#include "Entity.h"
#include "ResourceIdientificators.h"
#include "Projectile.h"
#include "Pickup.h"
#include "TextNode.h"
#include "HealthNode.h"
#include "MissileIcon.h"
#include "PickupNode.h"
#include "Data.h"
#include "Command.h"
#include "Animation.h"

struct Aircraft : public Entity
{
	enum Type
	{
		Eagle,
		Raptor,
		Avenger,
		Boss,
		TypeCount
	};

	Aircraft(Type type, const TextureHolder& textures, const FontHolder& fonts);

	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void updateCurrent(sf::Time dt, CommandQueue& commands) override;
	virtual unsigned int getCategory() const override;
	virtual sf::FloatRect getBoundingRect() const override;
	
	bool isAllied() const;
	float getMaxSpeed() const;

	virtual void remove() override;
	virtual bool isMarkedForRemoval() const override;
	void increaseFireRate();
	void increaseSpread();
	void collectMissiles(unsigned int count);

	void fire();
	void launchMissile();
	void updateMovementPattern(sf::Time dt);
	void checkProjectileLaunch(sf::Time dt, CommandQueue& commands);

	void createBullets(SceneNode& node, const TextureHolder& textures) const;
	void createProjectile(SceneNode& node, Projectile::Type type, float xOffset, float yOffset, const TextureHolder& textures) const;

	void checkPickupDrop(CommandQueue& commands);
	void createPickup(SceneNode& node, const TextureHolder& textures) const;

	void updateTexts();
	void updateBar();
	void updateMissile();
	void updatePickupBar();

	void updatePlayerInterface();

	void playLocalSound(CommandQueue& commands, SoundEffect::ID effect);

	Type type;
	sf::Sprite sprite;

	Command fire_command;
	Command missile_command;

	sf::Time fire_countdown;
	sf::Time missile_countdown;

	bool is_firing;
	bool is_missile_launch;

	int	fire_rate;
	int	spread_level;
	int missile_ammo;

	Command pickup_command;
	bool spawned_pickup;

	float travalled_distance;
	std::size_t	direction_index;

	TextNode* missile_display;
	HealthNode* health_bar;
	MissileIcon* missile_icon;
	PickupNode* pickup_bar;

	Animation explosion;
	Animation flame;
	Animation smoke;

	bool show_explosion;

	void updateRollAnimation();
	void initAnimations();
	void checkHitpoints(sf::Time dt);

	bool played_exp_sound;

	bool show_smoke;
	bool show_flame;
};