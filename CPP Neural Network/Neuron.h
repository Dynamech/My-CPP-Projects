#pragma once
#include "Libraries.h"

class Neuron 
{
protected:
	
public:
	std::vector<double>m_weight;
	double m_bias;
	double m_output;
	double m_delta;
	Neuron(double);
	Neuron();
	void print();
	~Neuron();
};

