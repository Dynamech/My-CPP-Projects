#include "Neuron.h"
#include <random>

Neuron::Neuron(double bias) : m_bias(bias) {}
Neuron::Neuron()
{
};

Neuron::~Neuron()
{
}

void Neuron::print()
{
	std::cout << "weight: " << m_weight[0]<<" bias: "<<m_bias<<std::endl;
}
