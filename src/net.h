#ifndef NET_H
#define NET_H
#include "neuron.h"
#include <vector>
#include <string>
#include <stdlib.h>
#include "../third-party-code/chromosome.h"

using namespace std;
using namespace BRKGA;

class Net{
public:
	unsigned int nInputs;
	unsigned int nHiddenLayers;
	unsigned int nHiddenNeurons;
	unsigned int nOutput;
	double fitness;

	vector<vector<Neuron>> layers;

	Net(unsigned int nInputs, unsigned int nHiddenLayers, unsigned int nHiddenNeurons, unsigned int nOutput);
	Net();

	~Net();

	void setFitness(double pfitness);
	double getFitness();
	unsigned int getNInputs();
	unsigned int getNHiddenLayers();
	unsigned int getNHiddenNeurons();
	unsigned int getNOutput();

	void mutation();

	//activerLayers recebe um vetor de entrada, ativa todas as camadas e
	//devolve o resultado no vetor poutputs, que deve ser passado previamente alocado
	void activateLayers(vector<double>* inputs, vector<double>* poutputs);
	void copiar_rede(Net * origem);
	void imprimeRede();
	void rerandom();
	void openNet(char* arquiv);
	void saveNet(char* arquiv);

	void configureOutputs(vector<double> poutputs);

	void parse_chromosome(Chromosome *cromosome);
private:
	vector<vector<Neuron>>* getLayers();
	void imprimeCamada(unsigned int i);
};
#endif
