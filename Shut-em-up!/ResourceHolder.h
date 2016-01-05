#pragma once

#include <map>
#include <string>
#include <memory>
#include <stdexcept>
#include <cassert>


template <typename Resource, typename Identifier>
struct ResourceHolder
{
	void load(Identifier id, const std::string filename)
	{
		std::unique_ptr<Resource> resource(new Resource());
		if (!resource->loadFromFile(filename))
			throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);
		insertResource(id, std::move(resource));
	}

	template< typename Parameter> void load(Identifier id, const std::string filename, const Parameter& parameter)
	{
		std::unique_ptr<Resource> resource(new Resource());
		if (!resource->loadFromFile(filename, parameter))
			throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);
		insertResource(id, std::move(resource));
	}

	Resource& get(Identifier id)
	{
		auto found = resource_map.find(id);
		assert(found != resource_map.end());

		return *found->second;
	}

	const Resource&	get(Identifier id) const
	{
		auto found = resource_map.find(id);
		assert(found != resource_map.end());

		return *found->second;
	}

	void insertResource(Identifier id, std::unique_ptr<Resource> resource)
	{
		auto inserted = resource_map.insert(std::make_pair(id, std::move(resource)));
		assert(inserted.second);
	}

	std::map<Identifier, std::unique_ptr<Resource>> resource_map;
};
