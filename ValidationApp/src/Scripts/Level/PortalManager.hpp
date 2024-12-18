#pragma once

#include <Engine/Delta.hpp>

#include "PortalBehaviour.hpp"

class PortalManager
{
public:
	PortalBehaviour* GetOther(PortalBehaviour* you)
	{ 
		for (PortalBehaviour* portal : _portals)
		{
			if (portal == you)
			{
				continue;
			}

			if (portal->_data.identifier == you->_data.identifier)
			{
				return portal;
			}

			return nullptr;
		}
	}

private:
	std::vector<PortalBehaviour*> _portals;
};