#pragma once
#include <iostream>
#include <vector>
#ifndef JNLPU_H
#define JNLPU_H
namespace jeff
{
#define MINIMUM 0.0
#define MAXIMUM 1.0
#define REVERSE -1
	//operation of lan = ^factors;
	using LanLink = std::pair<double, std::string>;
	using LanList = std::vector<LanLink>;
	class JNLPU
	{
		std::vector<LanList> lanFactors;
	public:
	
	};
}

#endif