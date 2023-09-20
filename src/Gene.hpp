#include <cstdint>
#include <string>

struct Gene {
        int sourceLayerIndex; // index of layer source neuron is from
        int sourceNeuronIndex;
        int destNeuronIndex;
        int weight;

        std::string to_string() {
                return "Connection layer: " + std::to_string(sourceLayerIndex) + " | "\
                        "Source N. index: "  + std::to_string(sourceNeuronIndex) + " | "\
                        "Dest N. index: "  + std::to_string(destNeuronIndex) + " | "\
                        "Weight: " + std::to_string(destNeuronIndex);
        }
};
