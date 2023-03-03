#include "stdafx.h"
#include "LSystem.h"

void aiGraphics::LSystem::move(Vec2 position)
{
	startPosition = position;
}

void aiGraphics::LSystem::set(const char32_t token, std::function<void(Turtle&)> command)
{
	commandMap[token] = command;
}

void aiGraphics::LSystem::init(const String& start)
{
	initString = start;
}

void aiGraphics::LSystem::rule(const char32_t token, String replaced)
{
	replacementMap[token] = replaced;
}

void aiGraphics::LSystem::draw(uint32 state, double thickness, Color color) const
{
	Turtle turtle(startPosition);
	String str = initString;
	for (auto i = 0u; i < state; ++i)
	{
		String Buffer;
		for (const auto c : str)
		{
			if (replacementMap.contains(c))
			{
				// 置換ルールに合致するなら指定した文字列に置き換える
				Buffer += replacementMap.at(c);
			}
			else
			{
				Buffer += c;
			}
		}
		str = Buffer;
	}

	for (const auto token : str)
	{
		commandMap.at(token)(turtle);
	}

	turtle.draw(thickness, color);
}
