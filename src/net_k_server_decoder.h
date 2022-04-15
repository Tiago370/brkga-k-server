#ifndef DECODER_HPP_
#define DECODER_HPP_

#include <string>
#include "../third-party-code/chromosome.h"
#include "../third-party-code/fitness_type.h"
#include "../src/journey.h"

/**
 * \brief Interface for TSP_Decoder class.
 *
 * Simple Traveling Salesman Problem decoder. It creates a permutation of nodes
 * induced by the chromosome and computes the cost of the tour.
 */
class NetKServerDecoder {
public:
    unsigned int nInputs;
    unsigned int nHiddenLayers;
    unsigned int nHiddenNeurons;
    unsigned int nOutputs;
    Journey journey;
    fitness_t fitness;
    /** \brief Default Constructor.
     */
    NetKServerDecoder(string map, string instances, unsigned int nInputs, unsigned int nHiddenLayers, unsigned int nHiddenNeurons, unsigned int nOutputs);

    /** \brief Given a chromossome, builds a tour.
     *
     * \param chromosome A vector of doubles represent a problem solution.
     * \param rewrite Indicates if the chromosome must be rewritten. Not used
     *                this decoder, but keep due to API requirements.
     * \return the cost of the tour.
     */
    BRKGA::fitness_t decode(BRKGA::Chromosome& chromosome, bool rewrite);

public:
    
};

#endif // DECODER_HPP_