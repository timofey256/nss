#include <vector>

class Neuron {
public:
    Neuron(size_t index);
    void setOutput(double val);
    double getOutput() const;
    void feedForward(std::vector<std::vector<Neuron>> &layers, int prevLayerIndex);    
    void addConnection(int index, double weight);
private:
    size_t myIndex;
    double output;
    std::vector<std::pair<int, double>> connections;
};

typedef std::vector<Neuron> Layer;
