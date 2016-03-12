#include "stdafx.h"
#include "node.h"


node::node( int i)
{
	index = i;
	weight = 1.;
	coordination = 0;
}

node::node( int i,double peso)
{
	index = i;
	weight = peso;
	coordination = 0;
}

void node::set_bond(std::shared_ptr<node> other) {
	coordination++;
	bonds.push_back(other);
}

void node::print_index() {
	std::cout << index;
}

void node::print_bonds() {
    for (unsigned int i = 0; i < bonds.size(); i++) {
		bonds[i]->print_index();
		std::cout << "\t";
	}
	std::cout << std::endl;
}

double node::get_weight() {
	return weight;
}

int node::conectivity() {
	return coordination;
}

std::vector<int> node::index_conections() {
	std::vector<int> vec;
	for (int i = 0; i < coordination; i++) {
		vec.push_back(bonds[i]->index);
	}
	return vec;
}
