import json

def transform_json(input_file_path, output_file_path):
    # Open and read the input JSON file
    with open(input_file_path, 'r') as file:
        data = json.load(file)

    layer_sizes = data['layerSizes']

    # Initialize variables for processing weights and biases
    new_connections = []

    # Iterate through each layer and create connections
    for layer_index in range(len(layer_sizes) - 1):
        all_weights = data['connections'][layer_index]['weights']
        all_bias = data['connections'][layer_index]['biases']

        for next_neuron_index in range(layer_sizes[layer_index + 1]):
            neuron_connection = {
                "bias": all_bias[next_neuron_index],
                "weights": []
            }

            for neuron_index in range(layer_sizes[layer_index]):
                # Extract weights for the current neuron
                weight_index = next_neuron_index * layer_sizes[layer_index] + neuron_index
                weights = all_weights[weight_index]
                neuron_connection["weights"].append(weights)

            new_connections.append(neuron_connection)

    # Update the data with the new connections
    data["connections"] = new_connections

    # Write the transformed data to the output JSON file
    with open(output_file_path, 'w') as file:
        json.dump(data, file, indent=4)

# Example usage
input_file_path = 'PetalModel.json'
output_file_path = 'rightPetaDataBase.json'
transform_json(input_file_path, output_file_path)
