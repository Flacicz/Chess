#pragma once

#include <map>
#include <string>

#include "Pieces.h"
#include "../../Resources/headers/ResourceManager.h"

class ChessEngine {
public:
	static ChessEngine& getInstance() {
		static ChessEngine instance;
		return instance;
	}
	
	void initPieces();
	void render();

	std::string getState() const { return state; };
private:
	ChessEngine() {};
	ChessEngine(const ChessEngine&) = delete;
	ChessEngine& operator=(const ChessEngine&) = delete;

	std::string state = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
	std::vector<Piece> pieces;
};