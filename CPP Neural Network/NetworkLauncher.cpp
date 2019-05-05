#include "NetworkLauncher.h"

NetworkLauncher::NetworkLauncher()
{	

}
NetworkLauncher::~NetworkLauncher()
{

}

void NetworkLauncher::start()
{
	NeuralNetwork network(numberOfInputNeurons, hiddenLayerSize, numberOfhiddenLayerNeurons, numberOfOutputNeurons);
	trainingdata.getTrainingData(trainingDataContainer,
		validationDataContainer, testDataContainer,
		validationTargetContainer, testTargetContainer, targetDataContainer);
	
	std::vector<int> trainingIndexes;
	trainingIndexes.reserve(trainingDataContainer.size());
	for (unsigned i = 0; i < trainingDataContainer.size(); ++i)
		trainingIndexes.push_back(i);
	std::random_shuffle(trainingIndexes.begin(), trainingIndexes.end());

	while (epoch && earlyStopping)
	{
		std::cout << "||||||||||||||||||||||||EPOCH:" << 5000 - epoch << std::endl;
		for (unsigned i = 0; i < targetDataContainer.size(); i++)
		{
			network.feedForward(trainingDataContainer[trainingIndexes[i]]);
			network.backPropagation(targetDataContainer[trainingIndexes[i]]);
			trainingAccuracy += network.checkIfCorrectPrediction(targetDataContainer[trainingIndexes[i]]);
		}
		for (unsigned i = 0; i < validationDataContainer.size(); i++)
		{
			network.feedForward(validationDataContainer[i]);
			currentAccuracy += network.checkIfCorrectPrediction(validationTargetContainer[i]);
		}

		if (currentAccuracy > bestPreviousAccuracy)
		{
			bestPreviousAccuracy = currentAccuracy;
			patience = 0;
		}
		else if (currentAccuracy <= bestPreviousAccuracy)
		{
			if (patience == 7)
			{
				earlyStopping = 0;
				std::cout << "TRAINING COMPLETE" << patience << std::endl;
				for (unsigned i = 0; i < testDataContainer.size(); i++)
				{
					network.feedForward(testDataContainer[i]);
					currentTestAccuracy += network.checkIfCorrectPrediction(testTargetContainer[i]);
				}
				std::cout << "The network's test accuracy is " << ((double)currentTestAccuracy / testTargetContainer.size()) * 100 << "%" << std::endl;
			}
			else
				patience++;

		}

		std::cout << "Validation test correct guesses: " << currentAccuracy << " previous best correct guesses : " << bestPreviousAccuracy << std::endl;
		bestPreviousAccuracy = currentAccuracy;
		std::cout << "The network's training accuracy is " << (trainingAccuracy / trainingDataContainer.size()) * 100 << "%" << std::endl;
		std::cout << "The network's validation accuracy is " << (currentAccuracy / validationDataContainer.size()) * 100 << "%" << std::endl;

		trainingAccuracy = 0;
		currentAccuracy = 0;
		currentTestAccuracy = 0;
		std::random_shuffle(trainingIndexes.begin(), trainingIndexes.end());
		epoch--;
	}
}

