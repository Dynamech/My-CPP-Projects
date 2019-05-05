#pragma once

#include "Neuron.h"
#include "Libraries.h"

class NeuralNetwork : Neuron
{
private:
	int m_inputLayerSize;
	int m_hiddenLayerSize;
	int m_hiddenLayers;
	int m_outputLayerSize;
	const double m_eta = -0.3;
	std::vector<std::vector<Neuron>>m_neuralNet;

public:
	
	NeuralNetwork(int inputLayerSize, int hiddenLayers, int hiddenLayerSize, int outputLayersize);
	NeuralNetwork();
	~NeuralNetwork();

	void feedForward(std::vector<double>&);
	void backPropagation(std::vector<double> &);
	double dEdWk(double,double);
	double dEdWj(double);

	double NeuralNetwork::dotProduct(std::vector<Neuron>&,int index);
	double binaryCrossEntropy(std::vector<double>& t);
	double MSE(std::vector<double>& t);
	bool checkIfCorrectPrediction(std::vector<double>& t);
	double NeuralNetwork::dotProductTransposed(std::vector<Neuron>&, std::vector<Neuron>&, int index);

	void print(std::vector<double>&);
	void printResults(std::vector<double>& t);
	double sig(double);

};

