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

		void move(Vec2 position)
		{
			startPosition = position;
		}

		void set(const char32_t token, std::function<void(Turtle&)> command)
		{
			commandMap[token] = command;
		}

		void init(const String& start)
		{
			initString = start;
		}

		void rule(const char32_t token, String replaced)
		{
			replacementMap[token] = replaced;
		}

		void draw(uint32 state, double thickness, Color color = Palette::White) const
		{
			Turtle turtle(startPosition);
			String str = initString;
			for (int i = 0; i < state; ++i)
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

	private:
		String initString;
		std::map<char32_t, std::function<void(Turtle&)>> commandMap;
		std::map<char32_t, String> replacementMap;
		Vec2 startPosition;
	};
}

