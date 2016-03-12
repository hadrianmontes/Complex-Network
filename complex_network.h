#pragma once
#include "stdafx.h"
#include "node.h"
class complex_network
{
public:
    complex_network( int);
    void set_bond( int,  int);
    void print_bonds( int);
	void print_all_bonds();
	double get_weight();
    int get_conections( int);
	int get_size();
	std::vector<std::shared_ptr<node>> get_nodes();
	std::vector<int> conectivity();
    void save(std::string);
private:
	std::vector<std::shared_ptr<node>> nodes;
     int number_of_nodes;
	double total_weight;
};

