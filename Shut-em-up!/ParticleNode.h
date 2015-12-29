#pragma once
#include "SceneNode.h"

#include "ResourceIdientificators.h"
#include "Particle.h"
#include <SFML/Graphics/VertexArray.hpp>

#include <deque>

struct ParticleNode : public SceneNode
{
	ParticleNode(Particle::Type type, const TextureHolder& textures);

	void addParticle(sf::Vector2f position);
	Particle::Type getParticleType() const;
	virtual unsigned int getCategory() const;


	virtual void updateCurrent(sf::Time dt, CommandQueue& commands);
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

	void addVertex(float worldX, float worldY, float texCoordX, float texCoordY, const sf::Color& color) const;
	void computeVertices() const;


	std::deque<Particle> particles;
	const sf::Texture& texture;
	Particle::Type type;

	mutable sf::VertexArray	vertex_array;
	mutable bool needs_vertex_update;
};

