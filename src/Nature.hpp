#include <vector>
#include "Gene.cpp"

class Nature {
public:
	static std::vector<Gene> generateRandomGenome(int length);
private:
	Nature() {};
};
