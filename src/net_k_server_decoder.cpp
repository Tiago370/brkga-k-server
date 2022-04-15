#include "net_k_server_decoder.h"
#include <string>
#include <algorithm>
#include <iostream>
#include <limits.h>
#include <cfloat>

using namespace std;
using namespace BRKGA;

//-----------------------------[ Constructor ]--------------------------------//

NetKServerDecoder::NetKServerDecoder(string map, string instances,unsigned int nInputs, unsigned int nHiddenLayers, unsigned int nHiddenNeurons, unsigned int nOutputs):
journey(map)
{
    this->nInputs = nInputs;
    this->nHiddenLayers = nHiddenLayers;
    this->nHiddenNeurons = nHiddenNeurons;
    this->nOutputs = nOutputs;
    //this->journey = Journey(map);
    this->journey.readInstances(instances);
    this->fitness = DBL_MAX;
}

//-------------------------------[ Decode ]-----------------------------------//

BRKGA::fitness_t NetKServerDecoder::decode(Chromosome& chromosome, bool /* not-used */) {
    fitness_t fit = 0;
    Net net(nInputs, nHiddenLayers, nHiddenNeurons, nOutputs); 
    net.parse_chromosome(&chromosome);
    fit = journey.runJourney(&net);
    if(fit < this->fitness){
        this->fitness = fit;
        //cout << "fitness: " << this->fitness << endl;
    }
    //cout << "fit: " << fit << endl;
    return fit;
}