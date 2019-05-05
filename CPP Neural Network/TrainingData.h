#pragma once
#include "Libraries.h"

class TrainingData
{
private:
	std::string m_data;
	std::ifstream(trainingData);
	std::vector<double>m_input;
	std::vector<std::string>m_flowerType = {"Iris-setosa","Iris-versicolor","Iris-virginica"};
	std::vector<double>m_target;

public:
	TrainingData();
	void getInputData(std::vector<double>&);
	void getTrainingData(std::vector<std::vector<double>>&,
		std::vector<std::vector<double>>&, std::vector<std::vector<double>>&,
		std::vector<std::vector<double>>&, std::vector<std::vector<double>>&, std::vector<std::vector<double>>&);
	void displayTrainingData(std::vector<double>& );
	void createValidationData(std::vector<double>& , std::vector<std::vector<double>>& , std::vector<std::vector<double>>& );
	void getTargetData(std::vector<double>&);
	bool checkEof();
	void resetPointer();
	~TrainingData();
};
