#include "Store.h"

Store::Store()
{
}

Store::~Store()
{
	for (int i = 0; i < games.size(); ++i)
	{
		delete games[i]->item;
	}
}