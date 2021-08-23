#pragma once

#include "Game.h"
#include "ListT.h"

class Store
{
	public:
		Store();
		~Store();
		List<Game*> games;
	private:
};