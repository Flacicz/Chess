#include "headers/Pieces.h"

std::string convertFiguresToString(FiguresNames figure) {
	switch (figure) {
	case FiguresNames::Pawn: return "Pawn"; break;
	case FiguresNames::Rook: return "Rook"; break;
	case FiguresNames::Knight: return "Knight"; break;
	case FiguresNames::Bishop: return "Bishop"; break;
	case FiguresNames::Queen: return "Queen"; break;
	case FiguresNames::King: return "King"; break;
	default: return "Unknown"; break;
	}
}

FiguresNames convertCharToEnum(const char ch) {
	switch (ch) {
	case 'p': return FiguresNames::Pawn; break;
	case 'n': return FiguresNames::Knight; break;
	case 'b': return FiguresNames::Bishop; break;
	case 'r': return FiguresNames::Rook; break;
	case 'q': return FiguresNames::Queen; break;
	case 'k': return FiguresNames::King; break;
	default: std::cout << "No figure" << std::endl; break;
	}
}

std::string convertColorsToString(Colors color) {
	switch (color) {
	case Colors::Black: return "Black"; break;
	case Colors::White: return "White"; break;
	default: return "Unknown"; break;
	}
}

void Pieces::initBitboards(const std::string& state) {
	uint8_t x = 0;
	uint8_t y = 7;

	Colors color = Colors::Black;

	for (auto charecter : state) {
		if (charecter == '/') {
			x = 0;
			y--;
		}
		else if (std::isdigit(charecter)) {
			x += charecter - '0';
		}
		else {
			if (std::isupper(charecter)) {
				charecter = std::tolower(charecter);
				color = Colors::White;
			}
			else {
				color = Colors::Black;
			}

			switch (charecter) {
			case 'r':
				getBitboard(color, FiguresNames::Rook).set1(y * 8 + x);
				break;
			case 'n':
				getBitboard(color, FiguresNames::Knight).set1(y * 8 + x);
				break;
			case 'b':
				getBitboard(color, FiguresNames::Bishop).set1(y * 8 + x);
				break;
			case 'q':
				getBitboard(color, FiguresNames::Queen).set1(y * 8 + x);
				break;
			case 'k':
				getBitboard(color, FiguresNames::King).set1(y * 8 + x);
				break;
			case 'p':
				getBitboard(color, FiguresNames::Pawn).set1(y * 8 + x);
				break;
			}

			x++;
		}
	}

	updateBitboards();
}

void Pieces::updateBitboards() {
	colorBitboards[Colors::Black] = getBitboard(Colors::Black, FiguresNames::Pawn) |
									getBitboard(Colors::Black, FiguresNames::Rook) |
									getBitboard(Colors::Black, FiguresNames::Knight) |
									getBitboard(Colors::Black, FiguresNames::Bishop) |
									getBitboard(Colors::Black, FiguresNames::Queen) |
									getBitboard(Colors::Black, FiguresNames::King);

	colorBitboards[Colors::White] = getBitboard(Colors::White, FiguresNames::Pawn) |
									getBitboard(Colors::White, FiguresNames::Rook) |
									getBitboard(Colors::White, FiguresNames::Knight) |
									getBitboard(Colors::White, FiguresNames::Bishop) |
									getBitboard(Colors::White, FiguresNames::Queen) |
									getBitboard(Colors::White, FiguresNames::King);

	all = colorBitboards[Colors::Black] | colorBitboards[Colors::White];
	empty = ~all;
}

Bitboard& Pieces::getBitboard(Colors color) {
	return colorBitboards[color];
}

Bitboard& Pieces::getBitboard(Colors color, FiguresNames figure) {
	return figuresBitboards[color][figure];
}