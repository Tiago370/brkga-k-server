#ifndef JOURNEY_H
#define JOURNEY_H
#include <vector>
#include <string>
#include "environment.h"
#include "net.h"
using namespace std;

class Journey{
public:
    
	Environment *environment;
	vector<vector<unsigned int>> *instancias;

	Journey(string arquivo);
	~Journey();
	void print();
	void readInstances(string path);
	double runJourney(Net *net);
private:
	bool readInstance(string arquivo);
	void printInstances();
	double play(Net *net, vector<unsigned int> *instancia);

};
#endif
