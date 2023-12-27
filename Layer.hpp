#include <vector>
#include "Node.hpp"

class Layer
{
    private:
        std::vector<Node> nodes;

    public:
        Layer(int numberOfNodes);
		void ComputeOutputs(Node *node);
		
        // Méthodes pour initialiser les nœuds, définir les entrées/sorties, etc.
};
