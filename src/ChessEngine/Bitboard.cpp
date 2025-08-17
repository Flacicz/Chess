#include "headers/Bitboard.h"

Bitboard::Bitboard(): data(0) {};

Bitboard::Bitboard(const uint64_t data) : data(data) {};

Bitboard::Bitboard(const std::vector<uint8_t> indexes): data(0) {
	for (int i = 0; i < indexes.size(); i++) {
		this->set1(indexes[i]);
	}
}

void Bitboard::set1(uint8_t square) {
	data |= (1ull << square);
}

void Bitboard::set0(uint8_t square) {
	data &= ~(1ull << square);
}

bool Bitboard::getBit(uint8_t square) const {
	return data & (1ull << square);
}

void Bitboard::printData() const {
	std::bitset<64> binary(data);
	std::cout << binary << std::endl;
}

Bitboard Bitboard::operator |(const Bitboard& bb) {
	return Bitboard{ this->getData() | bb.getData() };
}

Bitboard Bitboard::operator ~() {
	return Bitboard{ ~this->getData() };
}