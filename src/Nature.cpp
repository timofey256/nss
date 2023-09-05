#include <array>
#include "Nature.hpp"

std::array<Gene, GENOME_LENGTH> Nature::generateRandomGenome(const int length) {
	std::array<Gene, GENOME_LENGTH> genome;
	for (int i=0; i<length; i++) {
		Gene new_gene = {1,1,1,1};
		genome[i] = new_gene;
	}

	return genome;
}
