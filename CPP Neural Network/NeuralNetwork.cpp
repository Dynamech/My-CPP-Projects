#include "NeuralNetwork.h"



NeuralNetwork::NeuralNetwork(int inputLayerSize, int hiddenLayers, int hiddenLayerSize, int outputLayerSize)
	:m_inputLayerSize(inputLayerSize), m_hiddenLayers(hiddenLayers),
m_hiddenLayerSize(hiddenLayerSize), m_outputLayerSize(outputLayerSize)
{
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	std::uniform_real_distribution<> dis(0.0, 0.1);

	std::vector<std::vector<Neuron>>neuralNet(2+hiddenLayers);
	// Input layer
	for (unsigned j = 0; j < m_inputLayerSize; j++)
	{
		Neuron inputLayerNeuron(1);
		neuralNet[0].push_back(inputLayerNeuron);
		//neuralNet[0][j].m_output = j+1;
		
	}

	// Hidden Layer
	
	for (unsigned i = 1; i < m_hiddenLayers + 1; i++)
	{
		for (unsigned j = 0; j < m_hiddenLayerSize; j++)
		{
			Neuron hiddenLayerNeuron(1);
			neuralNet[i].push_back(hiddenLayerNeuron);
		}
	}

	// Output Layer
	
	for (unsigned k = 0; k < m_outputLayerSize; k++)
	{
		Neuron outputLayerNeuron;
		neuralNet[m_hiddenLayers + 1].push_back(outputLayerNeuron);
	}

	//Create Weights
	
	for (unsigned i = 0; i <neuralNet.size()-1 ; i++)
	{
		for (unsigned j = 0; j <neuralNet[i].size() ; j++)
		{
			for (unsigned k = 0; k < neuralNet[i+1].size(); k++)
			{
				neuralNet[i][j].m_weight.push_back(dis(gen));
				std::cout << neuralNet[i][j].m_weight[k] << std::endl;
			}
		}
	}
	//m_bias = 1;
	m_neuralNet = neuralNet;
}

NeuralNetwork::NeuralNetwork()
{
}


NeuralNetwork::~NeuralNetwork()
{
}

void NeuralNetwork::feedForward(std::vector<double>&inputs)
{

	for (unsigned i = 0; i < m_neuralNet.front().size(); i++)
	{
		m_neuralNet[0][i].m_output = inputs[i];
	}
	//hiddenLayer

	for (unsigned i = 1; i < m_hiddenLayers+1; i++)
	{
		for (unsigned j = 0; j < m_hiddenLayerSize; j++)
		{

			m_neuralNet[i][j].m_output=sig(m_bias+dotProduct(m_neuralNet[i-1],j));
		}
	}

	//OutputLayer

		for (unsigned j = 0; j < m_neuralNet.back().size(); j++)
		{
			m_neuralNet.back()[j].m_output = sig(m_bias + dotProduct(m_neuralNet[m_hiddenLayers], j));
		}
}

void NeuralNetwork::backPropagation(std::vector<double> &t)
{
	
//	std::vector<double>weights_transposed;
	
	//output layer

	for (int k = 0; k < m_outputLayerSize; k++)
	{
		m_neuralNet.back()[k].m_delta = dEdWk(t[k], m_neuralNet.back()[k].m_output);
	}
	
	
	//hidden layer

	for (unsigned i = m_neuralNet.size()-2; i >0; i--)
	{
		for (unsigned j = 0; j < m_neuralNet[i].size(); j++)
		{
			m_neuralNet[i][j].m_delta = dEdWj(m_neuralNet[i][j].m_output)*dotProductTransposed(m_neuralNet[i + 1], m_neuralNet[i], j);
		}
	}

	//update weights

	for (unsigned i = 0; i < m_neuralNet.size() - 1; i++)
	{
		for (unsigned j = 0; j < m_neuralNet[i+1].size(); j++)
		{
			for (unsigned k = 0; k < m_neuralNet[i].size(); k++)
				m_neuralNet[i][k].m_weight[j] += m_eta*m_neuralNet[i][k].m_output*m_neuralNet[i + 1][j].m_delta;
		}
	}
}

double NeuralNetwork::dEdWk(double t,double y)
{
	return y*(1.0 - y)*(y - t);
}

double NeuralNetwork::dEdWj(double y)
{
	return y*(1.0 - y);

}

void NeuralNetwork::print(std::vector<double>&t)
{
	for (int i = 0; i < m_neuralNet.back().size(); i++)
	{
		std::cout << "output" << i << ": " << m_neuralNet.back()[i].m_output << "	target" << i << ": " << t[i] <<" Loss: "<< abs(m_neuralNet.back()[i].m_output-t[i]) << std::endl;
		std::cout << "_________________________________________" << std::endl;
	}
	//std::max_element(m_neuralNet.back());
	
}

void NeuralNetwork::printResults(std::vector<double>&t)
{
	unsigned firedNeuronIndex=0;
	double tempMax=m_neuralNet.back().front().m_output;
	
	for (unsigned i = 1; i < m_neuralNet.back().size(); i++)
	{
		if (m_neuralNet.back()[i].m_output > tempMax)
		{
			tempMax = m_neuralNet.back()[i].m_output;
			firedNeuronIndex = i;
		}
			
	}

	std::cout << "output = " << firedNeuronIndex << ",target = " << std::distance(t.begin(), std::max_element(t.begin(), t.end()))<<std::endl;
}

double NeuralNetwork::sig(double z)
{
	return (double) 1.0 / (1.0 + exp(-z));
}

 double NeuralNetwork::dotProduct(std::vector<Neuron>& currentLayer,int index)
{
	double sum = 0;
		for (unsigned j = 0; j <currentLayer.size(); j++)
		{
			sum += currentLayer[j].m_output *currentLayer[j].m_weight[index];
		}
	
		return  sum;
}

 double NeuralNetwork::binaryCrossEntropy(std::vector<double>&t)
 {
	 double sumScore = 0.0;
	 double meanSumScore = 0.0;
	 for (unsigned i = 0; i < t.size(); i++)
	 {
		 sumScore += t[i] * log(1e-15 + m_neuralNet.back()[i].m_output);
	 }
	 meanSumScore = (double) 1.0 / t.size()*sumScore;
	 return -meanSumScore;
 }

 double NeuralNetwork::MSE(std::vector<double>&t)
 {
	 double sumScore = 0.0;
	 for (unsigned i = 0; i < t.size(); i++)
	 {
		 sumScore += pow(m_neuralNet.back()[i].m_output - t[i], 2);
	 }
	 return sumScore;
 }

 bool NeuralNetwork::checkIfCorrectPrediction(std::vector<double>&t)
 {
	 unsigned firedNeuronIndex = 0;
	 unsigned targetIndex = std::distance(t.begin(), std::max_element(t.begin(), t.end()));
	 double tempMax = m_neuralNet.back().front().m_output;

	 for (unsigned i = 1; i < m_neuralNet.back().size(); i++)
	 {
		 if (m_neuralNet.back()[i].m_output > tempMax)
		 {
			 tempMax = m_neuralNet.back()[i].m_output;
			 firedNeuronIndex = i;
		 }

	 }
	 if (firedNeuronIndex == targetIndex)
		 return 1;
	 else
		 return 0;
 }

 double NeuralNetwork::dotProductTransposed(std::vector<Neuron>& currentLayer, std::vector<Neuron>& previousLayer, int index)
 {
	 double sumT = 0;

	 for (unsigned j = 0; j <currentLayer.size(); j++)
	 {
		 sumT += currentLayer[j].m_delta *previousLayer[index].m_weight[j];
	 }

	 return sumT;
 }
