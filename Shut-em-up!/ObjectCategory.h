#pragma once
namespace Category
{
	enum Type
	{
		none = 0,
		scene = 0 << 1,
		player_aircraft = 1 << 1,
		allied_aircraft = 1 << 2,
		enemy_aircraft = 1 << 3,
	};
}