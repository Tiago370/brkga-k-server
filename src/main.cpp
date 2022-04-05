#include <iostream>
#include <fstream>
#include "../third-party-code/chromosome.h"
#include "../third-party-code/fitness_type.h"
#include "net.h"

using namespace std;
using namespace BRKGA;
unsigned int size_chromosome(unsigned int nInputs, unsigned int nHiddenLayers, unsigned int nHiddenNeurons, unsigned int nOutputs){
    unsigned int sum = 0;
    // número de pesos entre a entrada e a primeira camada escondida
    sum += nInputs * nHiddenNeurons;
    // número de bias da primeira camada escondida
    sum += nHiddenNeurons;
    // número de pesos entre as camadas escondidas
    sum += (nHiddenLayers - 1) * nHiddenNeurons * nHiddenNeurons;
    // número de bias das camadas escondidas exceto a primeira
    sum += (nHiddenLayers - 1) * nHiddenNeurons;
    // número de pesos entre a última camada escondida e a saída
    sum += nHiddenNeurons * nOutputs;
    // número de bias da última camada escondida
    sum += nOutputs;
    return sum;
}

void read_chromosome(Chromosome *chromosome, string net_file){
    ifstream file(net_file);
    if(!file.is_open()){
        cout << "Erro ao abrir arquivo de rede" << endl;
        return;
    }
    unsigned int nInputs, nHiddenLayers, nHiddenNeurons, nOutputs;
    file >> nInputs >> nHiddenLayers >> nHiddenNeurons >> nOutputs;
    unsigned int size = size_chromosome(nInputs, nHiddenLayers, nHiddenNeurons, nOutputs);
    chromosome->resize(size);
    for(unsigned int i = 0; i < size; i++){
        double weight;
        file >> weight;
        chromosome->at(i) = weight;
    }
    file.close();
}

void print_chromosome(Chromosome chromosome){
    for(unsigned int i = 0; i < chromosome.size(); i++){
        std::cout << chromosome[i] << endl;
    }
    std::cout << std::endl;
}

fitness_t decode(Chromosome *cromosome, unsigned int nInputs, unsigned int nHiddenLayers, unsigned int nHiddenNeurons, unsigned int nOutputs){
    fitness_t fitness = 0;
    Net net(nInputs, nHiddenLayers, nHiddenNeurons, nOutputs);    
    net.parse_chromosome(cromosome);
    
    return fitness;
}
int main() {
    Chromosome chromosome;
    read_chromosome(&chromosome, "rede.txt");
    //print_chromosome(chromosome);
    fitness_t fitness = decode(&chromosome, 2, 4, 4, 2);
    std::cout << "Fitness: " << fitness << std::endl;
    return 0;
}

