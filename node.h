#pragma once
#include "stdafx.h"
class node
{
public:
    node( int);
    node( int,double);
	void set_bond(std::shared_ptr<node>);
	void print_index();
	void print_bonds();
	double get_weight();
	int conectivity();
	std::vector<int> index_conections();
private:
     int index;
     int coordination;
	double weight;
	std::vector<std::shared_ptr<node>> bonds;
};

