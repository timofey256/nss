#include <vector>
#include <cmath>
#include "Neuron.hpp"

typedef unsigned int uint;
typedef std::vector<Neuron> Layer;

struct Gene {
	size_t connectionLayerIndex;
	size_t sourceNeuronIndex;
	size_t destNeuronIndex;
	short weight;
};

class NeuralNetwork {
public:
	NeuralNetwork(const std::vector<uint> &topology, std::vector<Gene> &genome);
	void feedForward(const std::vector<double> *inputValues);
	void getResults(std::vector<double> *resultValues) const;
private:
	std::vector<Layer> layers;
	void buildNetworkFromGenome(std::vector<Gene> &genome);
};

NeuralNetwork::NeuralNetwork(const std::vector<uint> &topology, std::vector<Gene> &genome) {
	uint numLayers = topology.size();
	for (size_t i = 0; i < numLayers; i++) {
		layers.push_back(Layer());
	
		for (size_t j = 0; j < topology[i]; j++) {
			layers.back().push_back(Neuron(j));
		}
	}

	buildNetworkFromGenome(genome);
}

void NeuralNetwork::buildNetworkFromGenome(std::vector<Gene> &genome) {
	for (Gene g : genome) {
		layers[g.connectionLayerIndex + 1][g.destNeuronIndex].addConnection(g.sourceNeuronIndex, g.weight);
	}	
}

void NeuralNetwork::getResults(std::vector<double> *resultValues) const {
	resultValues->clear();
	
	Layer lastLayer = layers[layers.size()-1];
	
	for (size_t i = 0; i < lastLayer.size() - 1; i++) {
		resultValues->push_back(lastLayer[i].getOutput());
	}
}

void NeuralNetwork::feedForward(const std::vector<double> *inputValues) {
	for (size_t i = 0; i < layers[0].size(); i++) {
		layers[0][i].setOutput(inputValues->at(i));
	}

	for (size_t i = 1; i < layers.size(); i++) {
		for (size_t j = 0; j < layers[i].size(); j++) {
			layers[i][j].feedForward();
		}
	}
}
