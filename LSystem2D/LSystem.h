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

		// 描画開始位置を指定する
		void move(Vec2 position);

		// 文字とそれに対応する操作を紐づける
		void set(const char32_t token, std::function<void(Turtle&)> command);

		// 初期状態の文字列を指定する
		void init(const String& start);

		// 文字の置き換えルールを指定する
		void rule(const char32_t token, String replaced);

		// 描画する
		void draw(uint32 state, double thickness, Color color = Palette::White) const;

	private:
		String initString;
		std::map<char32_t, std::function<void(Turtle&)>> commandMap;
		std::map<char32_t, String> replacementMap;
		Vec2 startPosition;
	};
}

