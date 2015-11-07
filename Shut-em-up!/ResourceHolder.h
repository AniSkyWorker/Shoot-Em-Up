
#include <map>
#include <string>
#include <memory>
#include <stdexcept>
#include <cassert>


template <typename Resource,typename Identifier>
struct ResourceHolder
{

	void load(Identifier id, const std::string filename)
	{
		std::unique_ptr<Resource> resource(new Resource());
		if (!resource->loadFromFile(filename))
			throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);
		auto inserted = resource_map.insert(std::make_pair(id, std::move(resource)));
		assert(inserted.second);
	}

	Resource& get(Identifier id)
	{
		auto found = mResourceMap.find(id);
		assert(found != mResourceMap.end());

		return found->second;
	}
	const Resource&	get(Identifier id) const
	{
		auto found = mResourceMap.find(id);
		assert(found != mResourceMap.end());

		return found->second;
	}

	std::map<Identifier, std::unique_ptr<Resource>> resource_map;
};