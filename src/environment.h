#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
#include <vector>
#include <utility>
#include <string>
using namespace std;

class Environment{
public:

	Environment(string arquivo);
	~Environment();

	void move(unsigned int node, unsigned int server);
	void print();
	unsigned int get_nNodes();
	void reset();
	vector<unsigned int> getKLocal();
	double getCustoAcumulado();
	double getCusto(unsigned int node1, unsigned int node2);
	unsigned int closest_server(unsigned int node);
	unsigned int getKServes();
	void printMapa();
	vector <double> getCoord(unsigned int requisition); // Retorna as coordenadas dos servidres e as cordenadas a requisição.
    
private:
	unsigned int nNodes;
	unsigned int kServes;
    double custo_acumulado;
	vector<pair<unsigned int, unsigned int>> nodes;
    vector<unsigned int> k_local_fixo;
	vector<unsigned int> k_local;
	vector<unsigned int> historico;
	void copy_k_local();
    double custo(unsigned int node1, unsigned int node2);
};
#endif