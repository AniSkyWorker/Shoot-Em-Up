#include "EmitterNode.h"
#include "ParticleNode.h"
#include "CommandQueue.h"
#include "Command.h"


EmitterNode::EmitterNode(Particle::Type type)
	:SceneNode()
	,accumulated_time(sf::Time::Zero)
	,type(type)
	,particle_system(nullptr)
{
}

void EmitterNode::updateCurrent(sf::Time dt, CommandQueue& commands)
{
	if (particle_system)
	{
		emitParticles(dt);
	}
	else
	{
		auto finder = [this](ParticleNode& container, sf::Time)
		{
			if (container.getParticleType() == type)
				particle_system = &container;
		};

		Command command;
		command.category = Category::Particle;
		command.action = derivedAction<ParticleNode>(finder);

		commands.push(command);
	}
}

void EmitterNode::emitParticles(sf::Time dt)
{
	const float emissionRate = 30.f;
	const sf::Time interval = sf::seconds(1.f) / emissionRate;


	accumulated_time += dt;

	while (accumulated_time > interval)
	{
		accumulated_time -= interval;
		particle_system->addParticle(getWorldPosition());
	}
}

