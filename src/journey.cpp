#include <string>
#include <fstream>
#include <iostream>
#include "journey.h"
using namespace std;
Journey::Journey(string arquivo){
	this->environment = new Environment(arquivo);
}
Journey::~Journey(){
    
}
void Journey::readInstances(string path){
    this->instancias = new vector<vector<unsigned int>>();
    string arquivo;
    for(unsigned int i = 1; ; i++){
        arquivo = path + "req" + to_string(i) + ".txt";
        if(!this->readInstance(arquivo)) break;
    }
}
bool Journey::readInstance(string arquivo){
    ifstream file(arquivo);
    if(!file.is_open()){
        cout << "Todas as intâncias já foram lidas" << endl;
        return false;
    }
    cout << "Abrindo arquivo: " << arquivo << endl;
    vector<unsigned int> instancia;
    unsigned int nRequests;
    file >> nRequests;
    instancia.resize(nRequests);
    for(unsigned int i = 0; i < nRequests; i++){
        file >> instancia[i];
    }
    this->instancias->push_back(instancia);
    file.close();
    return true;
}
void Journey::print(){
    environment->print();
    cout << "Instancias: " << endl;
    printInstances();
}
void Journey::printInstances(){
    for(unsigned int i = 0; i < this->instancias->size(); i++){
        cout << "Instância " << i << ": ";
        for(unsigned int j = 0; j < this->instancias->at(i).size(); j++){
            cout << this->instancias->at(i).at(j) << " ";
        }
        cout << endl;
    }
}
double Journey::runJourney(Net *net){
    double custo_acumulado = 0;
    for(unsigned int i = 0; i < this->instancias->size(); i++){
        custo_acumulado += play(net, &this->instancias->at(i));
    }
    //cout << "Custo acumulado: " << custo_acumulado << endl;
    return custo_acumulado;
}
double Journey::play(Net *net, vector<unsigned int> *instancia){
    environment->reset();
    for(unsigned int j = 0; j < instancia->size(); j++){
        //Obtendo os servidores
        vector<unsigned int> local_do_server = environment->getKLocal();
        //Para cada servidor, obtendo o custo
        vector<double> inputs;
        vector<double> outputs(environment->getKServes());
        
        //Obter entradas
        inputs = environment->getCoord(instancia->at(j));
        // Checar se o tamanho do vetor de entrada é igual ao tamanho da entrada da rede
        if(inputs.size() != net->getNInputs()){
            cout << "Tamanho do vetor de entrada não é igual ao tamanho da entrada da rede" << endl;
            exit(1);
        }
        //Ativando a rede
        net->activateLayers(&inputs, &outputs);
        //Escolhendo o servidor
        bool found = false;
        for(unsigned int i = 0; i < outputs.size(); i++){
            if(outputs[i] > 0){
                environment->move(instancia->at(j), i);
                found = true;
                break;
            }
        }
            
        if(!found){
            environment->move(instancia->at(j), 0);
        }
    }
    //returnando o custo total da instância
    return environment->getCustoAcumulado();
}