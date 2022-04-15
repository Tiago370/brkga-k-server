#include <iostream>
#include <fstream>
#include "../third-party-code/chromosome.h"
#include "../third-party-code/fitness_type.h"
#include "../third-party-code/brkga_mp_ipr.h"

#include "net_k_server_decoder.h"
#include "journey.h"
#include "environment.h"

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

fitness_t decode(Journey journey, Chromosome *cromosome, unsigned int nInputs, unsigned int nHiddenLayers, unsigned int nHiddenNeurons, unsigned int nOutputs){
    fitness_t fitness = 0;
    Net net(nInputs, nHiddenLayers, nHiddenNeurons, nOutputs); 
    net.parse_chromosome(cromosome);
    fitness = journey.runJourney(&net);
    return fitness;
}
int main(int argc, char* argv[]) {
    if(argc < 4) {
        cerr << "Usage: "<< argv[0]
             << " <seed> <config-file> <num-generations>"
                " <map-file> <instances-path>"  << endl;
        return 1;
    }
    try {
    // Read command-line arguments and the instance
    const unsigned seed = stoi(argv[1]);
    const string config_file = argv[2];
    const unsigned num_generations = stoi(argv[3]);

    // Read algorithm parameters

    cout << "Reading parameters..." << endl;

    auto [brkga_params, control_params] =
        BRKGA::readConfiguration(config_file);

        // Build the BRKGA data structures and initialize

        cout << "Building BRKGA data and initializing..." << endl;

        NetKServerDecoder decoder = NetKServerDecoder("mapa.txt", "req-trn/", (2+1)*2, 4, 4, 2);
        BRKGA::BRKGA_MP_IPR<NetKServerDecoder> algorithm(decoder, BRKGA::Sense::MINIMIZE, seed, size_chromosome((2+1)*2, 4, 4, 2), brkga_params);

        // NOTE: don't forget to initialize the algorithm.
        algorithm.initialize();

        // Find good solutions / evolve

        cout << "Evolving " << num_generations << " generations..." << endl;
        algorithm.evolve(num_generations);

        auto best_cost = algorithm.getBestFitness();
        cout << "Best cost: " << best_cost;
    }
    catch(exception& e) {
        cerr << "\n***********************************************************"
             << "\n****  Exception Occured: " << e.what()
             << "\n***********************************************************"
             << endl;
        return 70; // BSD software internal error code
    }
 

    /*
    Chromosome chromosome;
    Journey journey = Journey("mapa.txt");
    journey.readInstances("req-trn/");

    read_chromosome(&chromosome, "rede.txt");
    fitness_t fitness = decode(journey, &chromosome, (2+1)*2, 4, 4, 2);

    std::cout << "Fitness: " << fitness << std::endl;
    */

    /*
    Net net = Net((2+1)*2, 4, 4, 2);
    net.saveNet((char*)"rede.txt");
    */

    /*Chromosome chromosome;
    read_chromosome(&chromosome, "rede.txt");
    NetKServerDecoder decoder = NetKServerDecoder("mapa.txt", "req-trn/", (2+1)*2, 4, 4, 2);
    cout << "fitness: " << decoder.decode(chromosome, NULL) << endl;
    cout << "OK" << endl;
    */
    return 0;
}

