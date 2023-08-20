#include <cmath>
#include <vector>

class Neuron {
public:
        Neuron(size_t index);
        void setOutput(double val) { output = val; }
        double getOutput() { return output; }
        void feedForward();
        void addConnection(Neuron neuron, double weight);
private:
        size_t myIndex;
        double output;
        std::vector<std::pair<Neuron, double>> connections; // connection with neurons from *previous* layers!
};

typedef std::vector<Neuron> Layer;

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

