#pragma once
#include <random>

class Random {
private:
	// Random device to seed the generator
	static std::random_device rd;
	// Mersenne Twister pseudo-random generator
	static std::mt19937 gen;
	
public:
	// Generate a random integer within a given range
	static int getRandomInt(int min, int max);
};