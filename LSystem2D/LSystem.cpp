#include "stdafx.h"
#include "LSystem.h"
#include <algorithm>

void aiGraphics::LSystem::clear()
{
	startPosition = Vec2{ 0, 0 };
	initString = U"";
	commandMap.clear();
	replacementRules.clear();
}

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

bool aiGraphics::LSystem::validate() const
{
	// 初期文字列の長さは1文字以上
	if (initString.length() == 0)
	{
		return false;
	}

	// 文字列に含まれてもよい文字リストを作る
	Array<char32_t> validatedTokens;

	// 操作が定義されている文字は有効
	for (const auto& [c, command] : commandMap)
	{
		validatedTokens.push_back(c);
	}
	// 状態スタック・ポップは有効
	validatedTokens.push_back(U'[');
	validatedTokens.push_back(U']');

	auto isValidChar = [&validatedTokens](char32_t c) {
		return std::find(validatedTokens.begin(), validatedTokens.end(), c) != validatedTokens.end();
	};

	// 初期文字列に誤ったデータが含まれていないか？
	for (const auto initChar : initString)
	{
		bool found = isValidChar(initChar);
		if (!found)
		{
			return false;
		}
	}

	for (const auto& [beReplacedChar, replacedString] : replacementRules)
	{
		// 置き換えたあとの文字列に、操作が定義されていない文字が含まれていないか？
		for (const auto c : replacedString)
		{
			if (!isValidChar(c))
			{
				return false;
			}
		}
	}

	return true;
}

void aiGraphics::LSystem::draw(uint32 state, double thickness, Color color) const
{
	Turtle turtle(startPosition);

	// 指定状態の文字列を取得する
	const auto replacedString = getStateString(state);

	std::stack<Vec2> positionStack;
	std::stack<Vec2> directionStack;

	for (const char32_t token : replacedString)
	{
		if (token == U'[')
		{
			// '['で位置と回転の値をスタックする
			positionStack.push(turtle.getTurtlePosition());
			directionStack.push(turtle.getTurtleDir());
		}
		else if (token == U']')
		{
			// ']'で位置と回転の値をポップする
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

