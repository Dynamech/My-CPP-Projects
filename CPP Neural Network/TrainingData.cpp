#include "TrainingData.h"



TrainingData::TrainingData()
{
	trainingData.open("Iris species.txt");

}

void TrainingData::getInputData(std::vector<double>&input)
{
	m_input.clear();
	m_input.resize(4);
	for (unsigned i = 0; i < m_input.size(); i++)
	{
		char delim;
		trainingData >> m_input[i];
		trainingData >> delim;
		//std::cout << m_input[i]<<",";
	}
	//std::cout<<std::endl;
	input = m_input;
	
}

void TrainingData::getTrainingData(std::vector<std::vector<double>>&trainingDataContainer,
	std::vector<std::vector<double>>&validationDataContainer, std::vector<std::vector<double>>&testDataContainer,
	std::vector<std::vector<double>>&validationTargetContainer, std::vector<std::vector<double>>&testTargetContainer, std::vector<std::vector<double>>&targetDataContainer)
{
	double a, b, c,d;
	std::string plantType;
	std::vector<double>row;
	unsigned valOneCount=0, valTwoCount=0, valThreeCount = 0, testOneCount=0, testTwoCount=0, testThreeCount = 0;

	while (trainingData >> a >> b >> c >> d >> plantType)
	{
		if (plantType == m_flowerType[0] && valOneCount < 10)
		{
			validationDataContainer.push_back(row);
			validationDataContainer.back().push_back(a);
			validationDataContainer.back().push_back(b);
			validationDataContainer.back().push_back(c);
			validationDataContainer.back().push_back(d);
			validationTargetContainer.push_back(row);
			validationTargetContainer.back().resize(3);
			validationTargetContainer.back()[0] = 1;
			valOneCount++;
		}
		else if (plantType == m_flowerType[1] && valTwoCount < 10)
		{
			validationDataContainer.push_back(row);
			validationDataContainer.back().push_back(a);
			validationDataContainer.back().push_back(b);
			validationDataContainer.back().push_back(c);
			validationDataContainer.back().push_back(d);
			validationTargetContainer.push_back(row);
			validationTargetContainer.back().resize(3);
			validationTargetContainer.back()[1] = 1;
			valTwoCount++;
		}
		else if (plantType == m_flowerType[2] && valThreeCount < 10)
		{
			validationDataContainer.push_back(row);
			validationDataContainer.back().push_back(a);
			validationDataContainer.back().push_back(b);
			validationDataContainer.back().push_back(c);
			validationDataContainer.back().push_back(d);
			validationTargetContainer.push_back(row);
			validationTargetContainer.back().resize(3);
			validationTargetContainer.back()[2] = 1;
			valThreeCount++;
		}
		else if (plantType == m_flowerType[0] && testOneCount < 10)
		{
			testDataContainer.push_back(row);
			testDataContainer.back().push_back(a);
			testDataContainer.back().push_back(b);
			testDataContainer.back().push_back(c);
			testDataContainer.back().push_back(d);
			testTargetContainer.push_back(row);
			testTargetContainer.back().resize(3);
			testTargetContainer.back()[0] = 1;
			testOneCount++;
		}
		else if (plantType == m_flowerType[1] && testTwoCount < 10)
		{
			testDataContainer.push_back(row);
			testDataContainer.back().push_back(a);
			testDataContainer.back().push_back(b);
			testDataContainer.back().push_back(c);
			testDataContainer.back().push_back(d);
			testTargetContainer.push_back(row);
			testTargetContainer.back().resize(3);
			testTargetContainer.back()[1] = 1;
			testTwoCount++;
		}
		else if (plantType == m_flowerType[2] && testThreeCount < 10)
		{
			testDataContainer.push_back(row);
			testDataContainer.back().push_back(a);
			testDataContainer.back().push_back(b);
			testDataContainer.back().push_back(c);
			testDataContainer.back().push_back(d);
			testTargetContainer.push_back(row);
			testTargetContainer.back().resize(3);
			testTargetContainer.back()[2] = 1;
			testThreeCount++;
		}
		else
		{
			trainingDataContainer.push_back(row);
			targetDataContainer.push_back(row);
			trainingDataContainer.back().push_back(a);
			trainingDataContainer.back().push_back(b);
			trainingDataContainer.back().push_back(c);
			trainingDataContainer.back().push_back(d);
			targetDataContainer.back().resize(3);
			if (plantType == m_flowerType[0])
				targetDataContainer.back()[0] = 1;
			else if (plantType == m_flowerType[1])
				targetDataContainer.back()[1] = 1;
			else if (plantType == m_flowerType[2])
			{
				targetDataContainer.back()[2] = 1;
			}
		}
	}
}

void TrainingData::displayTrainingData(std::vector<double>&trainingDataContainer)
{
	for (unsigned i=0; i < trainingDataContainer.size(); i++)
	{
		std::cout << trainingDataContainer[i] << std::endl;
	}

}/*
void TrainingData::createValidationData(std::vector<double>&trainingDataContainer, std::vector<std::vector<double>>&targetDataContainer, std::vector<std::vector<double>>&validationDataContainer)
{
	
	std::vector<double>row;

	for (unsigned i = 0; i < trainingDataContainer.size(); i++)
	{
		for (unsigned j = 0; j < trainingDataContainer.size(); j++)
		{
			if (targetDataContainer[i][0] == 1 && typeOneCount < 10);
			{
				validationDataContainer.push_back(row);
				validationDataContainer[i].push_back(trainingDataContainer[i]);
				
				typeOneCount++;
			}
			if (targetDataContainer[i][1] == 1 && typeTwoCount < 10);
			{
				validationDataContainer.push_back(row);
				validationDataContainer[i].push_back(trainingDataContainer[i]);
				typeTwoCount++;
			}
			if (targetDataContainer[i][2] == 1 && typeThreeCount < 10);
			{
				validationDataContainer.push_back(row);
				validationDataContainer[i].push_back(trainingDataContainer[i]);
				typeThreeCount++;
			}
		}
	}
}*/

void TrainingData::getTargetData(std::vector<double>&target)
{
	m_target.clear();
	m_target.resize(3);
	std::string tempTarget;
	trainingData >> tempTarget;
	//std::cout << tempTarget<<std::endl;
	if (tempTarget == m_flowerType[0])
		m_target[0] = 1;
	else if (tempTarget == m_flowerType[1])
		m_target[1] = 1;
	else if (tempTarget == m_flowerType[2])
	{
		m_target[2] = 1;
	}
	target = m_target;
}

bool TrainingData::checkEof()
{
	return trainingData.eof();
}

void TrainingData::resetPointer()
{
	trainingData.clear();
	trainingData.seekg(0,std::ios::beg);
}


TrainingData::~TrainingData()
{
	trainingData.close();
}
