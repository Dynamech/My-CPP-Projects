#pragma once

#include "Libraries.h"
#include "Neuron.h"
#include "NeuralNetwork.h"
#include "TrainingData.h"
class NetworkLauncher
{
public:
	NetworkLauncher();
	void start();
	~NetworkLauncher();
private:
	TrainingData trainingdata;
	std::vector<double>target;
	std::vector<double>input;
	int epoch = 5000;
	double netLoss = 0.0;
	double bestPreviousAccuracy = 0;
	unsigned validationTestFrequency = 0;
	bool earlyStopping = 1;
	int currentAccuracy = 0;
	int currentTestAccuracy = 0;
	int patience = 0;
	double trainingAccuracy = 0.0;
	double a, b, c;
	std::vector<std::vector<double>>trainingDataContainer;
	std::vector<std::vector<double>>validationDataContainer;
	std::vector<std::vector<double>>testDataContainer;
	std::vector<std::vector<double>>validationTargetContainer;
	std::vector<std::vector<double>>testTargetContainer;
	std::vector<std::vector<double>>targetDataContainer;
};

