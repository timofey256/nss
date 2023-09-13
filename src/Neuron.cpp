#include <cmath>
#include <iostream>
#include <vector>
#include "Neuron.hpp"

Neuron::Neuron(size_t index) {
        myIndex = index;
}

void Neuron::addConnection(int sourceIndex, double weight) {
        std::pair<int, double> con = std::make_pair(sourceIndex, weight);
        connections.push_back(con);
}

void Neuron::feedForward(std::vector<std::vector<Neuron>> &layers, int prevLayerIndex) {
        double sum = 0.0;
        for (size_t i = 0; i < connections.size(); i++) {
                int sourceNeuronIndex = connections[i].first;
                int sourceNeuronOutput = layers[prevLayerIndex][sourceNeuronIndex].getOutput();
                double weight = connections[i].second;
                sum += sourceNeuronOutput * weight;
                //std::cout << "adding to sum : " << sourceNeuronOutput << " * " << weight << " = " << sourceNeuronOutput*weight << std::endl;
        }
        //std::cout << "total sum : " << sum << ". tanh(sum) : " << tanh(sum/10) << std::endl << std::endl;
        output = tanh(sum/10);
}

double Neuron::getOutput() const {
	return output;
}

void Neuron::setOutput(double val) {
	output = val;
}
