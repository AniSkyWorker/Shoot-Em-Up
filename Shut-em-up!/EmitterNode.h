#pragma once
#include "SceneNode.h"
#include "Particle.h"

struct ParticleNode;

struct EmitterNode : public SceneNode
{
	EmitterNode(Particle::Type type);
	virtual void updateCurrent(sf::Time dt, CommandQueue& commands) override;
	void emitParticles(sf::Time dt);

	sf::Time accumulated_time;
	Particle::Type type;
	ParticleNode* particle_system;
};