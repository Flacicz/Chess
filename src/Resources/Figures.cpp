#include "headers/Figures.h"

std::string Figures::convertToString(Figures Figure) {
	switch (Figure) {
		case Figures::BlackQueen: return "BlackQueen";
		case Figures::WhiteQueen: return "WhiteQueen";
		case Figures::BlackKing: return "BlackKing";
		case Figures::WhiteKing: return "WhiteKing";
		case Figures::BlackElephant: return "BlackElephant";
		case Figures::WhiteElephant: return "WhiteElephant";
		case Figures::BlackRook: return "BlackRook";
		case Figures::WhiteRook: return "WhiteRook";
		case Figures::BlackHorse: return "BlackHorse";
		case Figures::WhiteHorse: return "WhiteHorse";
		case Figures::BlackPawn: return "BlackPawn";
		case Figures::WhitePawn: return "WhitePawn";
		default: return "Unknown";
	}
}
