#ifndef NEURON_HPP
#define NEURON_HPP

#include <vector>
#include <cmath>

class Neuron {
public:
    Neuron(size_t index);
    void setOutput(double val);
    double getOutput() const;
    void feedForward();
    void addConnection(Neuron neuron, double weight);
private:
    size_t myIndex;
    double output;
    std::vector<std::pair<Neuron, double>> connections;
};

#endif
