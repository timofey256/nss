#include <vector>
#include <cstddef>
#include <cstdint>
#include <array>

constexpr int GENOME_LENGTH = 8;

struct Gene {
        uint8_t connectionLayerIndex;
        uint8_t sourceNeuronIndex;
        uint8_t destNeuronIndex;
        uint8_t weight;
};

class Nature {
public:
	static std::array<Gene, GENOME_LENGTH> generateRandomGenome(const int length);
private:
	Nature() {};
};
