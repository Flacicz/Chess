#pragma once

#include <array>

#include "Bitboard.h"
#include "../../Graphics/headers/Sprite.h"

enum FiguresNames {
	Pawn,
	Rook,
	Knight,
	Bishop,
	Queen,
	King,
};

enum Colors {
	Black,
	White
};

std::string convertFiguresToString(FiguresNames figure);
std::string convertColorsToString(Colors color);
FiguresNames convertCharToEnum(const char ch);

struct Piece {
	int id;
	Colors color;
	FiguresNames figureName;
	int row, col;

	std::shared_ptr<Sprite> sprite;

	void setPosition(int row, int col) {
		this->row = row;
		this->col = col;

		this->sprite->setPosition(glm::vec2(70 + 160 * col, 60 + 120 * row));
	}
};

class Pieces {
public:
	void initBitboards(const std::string& state);
	void updateBitboards();

	std::array<std::array<Bitboard, 6>, 2> getFiguresBitboards() const { return figuresBitboards; };
	std::array<Bitboard, 2> getColorsBitboards() const { return colorBitboards; };
	std::array<Bitboard, 2> getInverseBitboards() const { return inverseColorBitboards; };
	Bitboard getAllBitbiard() const { return all; };
	Bitboard getEmptyBitboard() const { return empty; };

	Bitboard& getBitboard(Colors color);
	Bitboard& getBitboard(Colors color, FiguresNames figure);
private:
	std::array<std::array<Bitboard, 6>, 2> figuresBitboards;
	std::array<Bitboard, 2> colorBitboards;
	std::array<Bitboard, 2> inverseColorBitboards;
	Bitboard all;
	Bitboard empty;
};