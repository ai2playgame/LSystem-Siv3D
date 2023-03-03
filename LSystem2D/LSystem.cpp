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
	replacementRules[token] = replaced;
}

void aiGraphics::LSystem::draw(uint32 state, double thickness, Color color) const
{
	Turtle turtle(startPosition);

	const auto replacedString = getStateString(state);

	std::stack<Vec2> positionStack;
	std::stack<Vec2> directionStack;

	for (const char32_t token : replacedString)
	{
		if (token == U'[')
		{
			positionStack.push(turtle.getTurtlePosition());
			directionStack.push(turtle.getTurtleDir());
		}
		else if (token == U']')
		{
			turtle.move(positionStack.top());
			turtle.rotate(directionStack.top());

			positionStack.pop();
			directionStack.pop();
		}
		else
		{
			// 今見ている文字に対応する操作を実行する
			commandMap.at(token)(turtle);
		}
	}

	turtle.draw(thickness, color);
}

String aiGraphics::LSystem::getStateString(uint32 state) const
{
	String str = initString;
	for (auto i = 0u; i < state; ++i)
	{
		String Buffer;
		for (const auto c : str)
		{
			if (replacementRules.contains(c))
			{
				// 置換ルールに合致するなら指定した文字列に置き換える
				Buffer += replacementRules.at(c);
			}
			else
			{
				Buffer += c;
			}
		}
		str = Buffer;
	}

	return str;
}

