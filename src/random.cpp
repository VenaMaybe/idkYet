#include "random.h"

// Define static members outside the class
std::random_device Random::rd;
std::mt19937 Random::gen(Random::rd()); 

// Generate a random integer in the range [min, max]
int Random::getRandomInt(int min, int max) {
	std::uniform_int_distribution<> dist(min, max);
	return dist(gen);
}