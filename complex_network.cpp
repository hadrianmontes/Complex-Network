#include "stdafx.h"
#include "complex_network.h"


complex_network::complex_network( int n)
{
	for (int i = 0; i < n; i++) {
		nodes.push_back(std::make_shared<node>(i));
		number_of_nodes = n;
		total_weight = 0.;
	}
}

void complex_network::set_bond( int i,  int j) {
	nodes[i]->set_bond(nodes[j]);
	nodes[j]->set_bond(nodes[i]);
	total_weight += nodes[i]->get_weight();
	total_weight += nodes[j]->get_weight();
}

void complex_network::print_bonds( int i) {
	nodes[i]->print_bonds();
}

void complex_network::print_all_bonds() {
    for (unsigned int i = 0; i < nodes.size(); i++) {
		nodes[i]->print_bonds();
	}
}

double complex_network::get_weight() {
	return total_weight;
}

std::vector<int> complex_network::conectivity() {
	std::vector<int> vec(number_of_nodes, 0);
	for (int i = 0; i < number_of_nodes; i++) {
		vec[i] = nodes[i]->conectivity();
	}
	return vec;
}

int complex_network::get_conections( int i){
  return nodes[i]->conectivity();
} 

int complex_network::get_size() {
	return number_of_nodes;
}

std::vector<std::shared_ptr<node>> complex_network::get_nodes() {
	return nodes;
}

void complex_network::save(std::string filename){
    std::ofstream archivo_guardado;
    archivo_guardado.open(filename);
    archivo_guardado<<number_of_nodes<<std::endl;
    for (int i = 0; i < number_of_nodes ; i++) {
        auto bonds = nodes[i]->index_conections();
        for (unsigned int j = 0; j < bonds.size() ; j++){
            archivo_guardado << bonds[j] << " ";
        }
        archivo_guardado << std::endl;
    }
    archivo_guardado.close();
}
