#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include <array>
#include <cmath>
#include "Neuron.hpp"
#include "Gene.hpp"

typedef unsigned int uint;
typedef std::vector<Neuron> Layer;

constexpr short GENOME_LENGTH = 8;
constexpr short LAYERS_NUM = 3;
constexpr short NEURONS_NUM = 3;
constexpr short MAX_WEIGHT = 3;

class NeuralNetwork {
public:
	NeuralNetwork();
	NeuralNetwork(std::array<Gene, GENOME_LENGTH> &genome);
	void feedForward(const std::vector<double> *inputValues);
	void getResults(std::vector<double> *resultValues) const;
private:
	std::vector<Layer> layers;
	void buildNetworkFromGenome(std::array<Gene, GENOME_LENGTH> &genome);
};

#endif // NEURALNETWORK_H