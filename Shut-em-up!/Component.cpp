#include "Component.h"

namespace GUI
{

	Component::Component()
	: is_selected(false)
	, is_active(false)
	{
	}

	Component::~Component()
	{
	}

	bool Component::isSelected() const
	{
		return is_selected;
	}

	void Component::select()
	{
		is_selected = true;
	}

	void Component::deselect()
	{
		is_selected = false;
	}

	bool Component::isActive() const
	{
		return is_active;
	}

	void Component::activate()
	{
		is_active = true;
	}

	void Component::deactivate()
	{
		is_active = false;
	}

}