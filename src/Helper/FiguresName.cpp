#include "headers/FiguresName.h"

std::string Figures::convertToString(Figures figure) {
	switch (figure) {
	case Figures::BlackPawn:
		return "Black_Pawn";
		break;
	case Figures::WhitePawn:
		return "White_Pawn";
		break;
	case Figures::BlackRook:
		return "Black_Rook";
		break;
	case Figures::WhiteRook:
		return "White_Rook";
		break;
	case Figures::BlackHorse:
		return "Black_Horse";
		break;
	case Figures::WhiteHorse:
		return "White_Horse";
		break;
	case Figures::BlackElephant:
		return "Black_Elephant";
		break;
	case Figures::WhiteElephant:
		return "White_Elephant";
		break;
	case Figures::BlackQueen:
		return "Black_Queen";
		break;
	case Figures::WhiteQueen:
		return "White_Queen";
		break;
	case Figures::BlackKing:
		return "Black_King";
		break;
	case Figures::WhiteKing:
		return "White_King";
		break;
	}
}