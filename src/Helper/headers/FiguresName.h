#pragma once

#include <string>

namespace Figures {
	enum class Figures {
		BlackRook,
		WhiteRook,
		BlackHorse,
		WhiteHorse,
		BlackPawn,
		WhitePawn,
		BlackQueen,
		WhiteQueen,
		BlackKing,
		WhiteKing,
		BlackElephant,
		WhiteElephant,
	};

	std::string convertToString(Figures figure);
}


