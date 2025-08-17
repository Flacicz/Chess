#pragma once

#include <vector>
#include <cstdint>
#include <string>
#include <bitset>
#include <iostream>

class Bitboard {
private:
	uint64_t data;
public:
	Bitboard();
	Bitboard(const uint64_t data);
	Bitboard(const std::vector<uint8_t> indecies);

	uint64_t getData() const { return data; };
	void setData(uint64_t data) { this->data = data; };

	void set1(uint8_t square);
	void set0(uint8_t square);
	bool getBit(uint8_t square) const;
	void printData() const;

	Bitboard operator |(const Bitboard& bb);
	Bitboard operator ~();
};