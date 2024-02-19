// #include "MLP.h"

// double frand(){
// 	return (2.0*(double)rand() / RAND_MAX) - 1.0;
// }


// // Return a new Perceptron object with the specified number of inputs (+1 for the bias).
// Perceptron::Perceptron(int inputs, double bias){
// 	this->bias = bias;
// 	weights.resize(inputs+1);
// 	generate(weights.begin(),weights.end(),frand);
// }

// // Run the perceptron. x is a vector with the input values.
// double Perceptron::run(vector<double> x){
// 	x.push_back(bias);
// 	double sum = inner_product(x.begin(),x.end(),weights.begin(),(double)0.0);
// 	return sigmoid(sum);
// }

// // Challenge: Finish the following functions:

// void Perceptron::set_weights(vector<double> w_init){
// 	// w_init is a vector of doubles. Organize it as you'd like.
// }

// double Perceptron::sigmoid(double x){
// 	// Return the output of the sigmoid function applied to x
// }



//--------------------------------------------------------------------------------------------------

#include "MLP.h"

double frand() {
    return (2.0 * (double)rand() / RAND_MAX) - 1.0;
}

// Return a new Perceptron object with the specified number of inputs (+1 for the bias).
Perceptron::Perceptron(int inputs, double bias) {
    this->bias = bias;
    weights.resize(inputs + 1);
    generate(weights.begin(), weights.end(), frand);
}

// Run the perceptron. x is a vector with the input values.
double Perceptron::run(vector<double> x) {
    x.push_back(bias);
    double sum = inner_product(x.begin(), x.end(), weights.begin(), (double)0.0);
    return sigmoid(sum);
}

void Perceptron::set_weights(vector<double> w_init) {
    // Check if the provided weight vector has the expected size
    if (w_init.size() == weights.size()) {
        weights = w_init; // Directly assign new weights
    } else {
        // Handle incorrect w_init size - You might want to throw an error here
        cout << "Error: Weight vector size mismatch." << endl;
    }
}

double Perceptron::sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

// Constructor for MultiLayerPerceptron
MultiLayerPerceptron::MultiLayerPerceptron(vector<int> layers, double bias, double eta) {
    this->layers = layers;
    this->bias = bias;
    this->eta = eta;

    // Create network layers 
    for (int i = 0; i < layers.size(); ++i) {
        network.push_back(vector<Perceptron>());
        values.push_back(vector<double>());
        d.push_back(vector<double>());

        // Number of inputs for the current layer (add bias)
        int inputs = (i == 0) ? layers[0] : layers[i - 1] + 1;

        for (int j = 0; j < layers[i]; ++j) {
            network[i].push_back(Perceptron(inputs, bias));
            values[i].push_back(0.0);
            d[i].push_back(0.0);
        }
    }
}

void MultiLayerPerceptron::set_weights(vector<vector<vector<double>>> w_init) {
    // Nested loop to set weights for each Perceptron
    for (int i = 0; i < w_init.size(); ++i) {
        for (int j = 0; j < w_init[i].size(); ++j) {
            network[i][j].set_weights(w_init[i][j]);
        }
    }
}

void MultiLayerPerceptron::print_weights() {
    cout << "MLP Network Weights:" << endl;
    for (int i = 0; i < network.size(); ++i) {
        cout << "Layer " << i + 1 << endl;
        for (int j = 0; j < network[i].size(); ++j) {
            cout << " Neuron " << j + 1 << ": ";
            for (auto w : network[i][j].weights) {
                cout << w << " ";
            }
            cout << endl;
        }
    }
}

