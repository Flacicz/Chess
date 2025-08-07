#include "headers/Figures.h"

std::string Figures::convertToString(Figures Figure) {
	switch (Figure) {
		case Figures::BlackPawn: return "BlackPawn";
		case Figures::BlackHorse: return "BlackHorse";
		case Figures::BlackElephant: return "BlackElephant";
		case Figures::BlackRook: return "BlackRook";
		case Figures::BlackKing: return "BlackKing";
		case Figures::BlackQueen: return "BlackQueen";

		case Figures::WhitePawn: return "WhitePawn";
		case Figures::WhiteHorse: return "WhiteHorse";
		case Figures::WhiteElephant: return "WhiteElephant";
		case Figures::WhiteRook: return "WhiteRook";
		case Figures::WhiteKing: return "WhiteKing";
		case Figures::WhiteQueen: return "WhiteQueen";

		case Figures::Click: return "Click";
		case Figures::Hand: return "Hand";
		case Figures::Fist: return "Fist";

		default: return "Unknown";
	}
}

Figures::Figures Figures::convertToString(const std::string& figure) {
	if (figure == "BlackPawn") return Figures::BlackPawn;
	if (figure == "BlackHorse") return Figures::BlackHorse;
	if (figure == "BlackElephant") return Figures::BlackElephant;
	if (figure == "BlackRook") return Figures::BlackRook;
	if (figure == "BlackKing") return Figures::BlackKing;
	if (figure == "BlackQueen") return Figures::BlackQueen;

	if (figure == "WhitePawn") return Figures::WhitePawn;
	if (figure == "WhiteHorse") return Figures::WhiteHorse;
	if (figure == "WhiteElephant") return Figures::WhiteElephant;
	if (figure == "WhiteRook") return Figures::WhiteRook;
	if (figure == "WhiteKing") return Figures::WhiteKing;
	if (figure == "WhiteQueen") return Figures::WhiteQueen;

	if (figure == "None") return Figures::None;
}
