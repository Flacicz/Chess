#pragma once

#include <string>

namespace Figures {
	enum class Figures {
		BlackPawn,
		BlackHorse,
		BlackElephant,
		BlackRook,
		BlackKing,
		BlackQueen,
		WhitePawn,
		WhiteHorse,
		WhiteElephant,
		WhiteRook,
		WhiteKing,
		WhiteQueen,
		Click,
		Hand,
		Fist,
		None,
	};

	std::string convertToString(Figures Figure);
	Figures convertToString(const std::string& figure);
}