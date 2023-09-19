#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include <array>
#include <cmath>
#include "Neuron.hpp"
#include "Gene.hpp"

typedef unsigned int uint;
typedef std::vector<Neuron> Layer;

constexpr short GENOME_LENGTH = 16;
constexpr short LAYERS_NUM = 3;
constexpr short NEURONS_NUM = 3;
constexpr short MAX_WEIGHT = 7;

class NeuralNetwork {
public:
/*
	Input neurons:
	1. Current position X
	2. Current position Y
	3. Current energy
	4. Nearest enemy X (in a radius of sense). If not in sight, then 0
	5. Nearest enemy Y (in a radius of sense). If not in sight, then 0
	6. Current size

	Output neurons: 
	1. move left/right (+/-)
	2. move up/down (+/-)

*/
	static constexpr std::array<int, LAYERS_NUM> topology = {6, 3, 2}; // including input and output layer
	
	NeuralNetwork();
	NeuralNetwork(std::array<Gene, GENOME_LENGTH> &genome);
	void feedForward(const std::vector<double> *inputValues);
	void getResults(std::vector<double> *resultValues) const;
private:
	std::vector<Layer> layers;
	void buildNetworkFromGenome(std::array<Gene, GENOME_LENGTH> &genome);
};

#endif // NEURALNETWORK_H
