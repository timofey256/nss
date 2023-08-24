#include <vector>
#include <cmath>
#include "Neuron.hpp"

Neuron::Neuron(size_t index) {
        myIndex = index;
}

void Neuron::addConnection(Neuron neuron, double weight) {
        std::pair<Neuron, double> con = std::make_pair(neuron, weight);

        connections.push_back(con);
}

void Neuron::feedForward() {
        double sum = 0.0;

        for (size_t n = 0; n < connections.size(); n++) {
                sum += connections[n].first.getOutput() * connections[n].second;
        }

        output = tanh(sum);
}

double Neuron::getOutput() const {
	return output;
}

void Neuron::setOutput(double val) {
	output = val;
}
