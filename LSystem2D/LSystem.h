#pragma once
#include <functional>
#include <map>
#include "Turtle.h"

namespace aiGraphics
{
	class LSystem
	{
	public:
		LSystem() = default;

		void Set(const String& token, std::function<void> command)
		{
			commandMap[token] = command;
		}

		void Init(const String& start)
		{
			initState = start;
		}

		void Rule(const String token, String replaced)
		{
			replacementMap[token] = replaced;
		}

		void Draw(uint32 state);

	private:
		String initState;
		std::map<String, std::function<void>> commandMap;
		std::map<String, String> replacementMap;
	};
}

