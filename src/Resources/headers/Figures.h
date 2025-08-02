#pragma once

#include <string>

namespace Figures {
	enum class Figures {
		BlackQueen,
		WhiteQueen,
		BlackKing,
		WhiteKing,
		BlackElephant,
		WhiteElephant,
		BlackRook,
		WhiteRook,
		BlackHorse,
		WhiteHorse,
		BlackPawn,
		WhitePawn
	};

	std::string convertToString(Figures Figure);
}