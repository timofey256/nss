#include <iostream>
#include "NeuralNetwork.hpp"

NeuralNetwork::NeuralNetwork() {}

NeuralNetwork::NeuralNetwork(std::array<Gene, GENOME_LENGTH> &genome) {
	for (size_t i = 0; i < LAYERS_NUM; i++) {
		layers.push_back(Layer());
	
		for (size_t j = 0; j < topology[i]; j++) {
			if (layers.size() == 1 && layers[0].size() == 6) {std::cout << "HEY!!!" << std::endl;}
			layers.back().push_back(Neuron(j));
		}
	}

	buildNetworkFromGenome(genome);
}

void NeuralNetwork::buildNetworkFromGenome(std::array<Gene, GENOME_LENGTH> &genome) {
	for (Gene g : genome) {
		layers[g.sourceLayerIndex + 1][g.destNeuronIndex].addConnection(g.sourceNeuronIndex, g.weight);
	}	
}

void NeuralNetwork::getResults(std::vector<double> *resultValues) const {
	resultValues->clear();
	
	Layer lastLayer = layers[layers.size()-1];
	
	for (size_t i = 0; i < lastLayer.size(); i++) {
		resultValues->push_back(lastLayer[i].getOutput());
	}
}

void NeuralNetwork::feedForward(const std::vector<double> *inputValues) {
	for (size_t i = 0; i < topology[0]; i++) {
		layers[0][i].setOutput(inputValues->at(i));
	}

	for (size_t i = 1; i < layers.size(); i++) {
		for (size_t j = 0; j < topology[i]; j++) {
			layers[i][j].feedForward(layers, i-1);
		}
	}
}
