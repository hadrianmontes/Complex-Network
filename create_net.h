#include "stdafx.h"
#include "node.h"
#include "complex_network.h"

std::shared_ptr<complex_network> scale_free( int);
std::shared_ptr<complex_network>  small_world(int,int, double);
std::shared_ptr<complex_network> small_world1d(int,double);
std::vector<int> distance(std::shared_ptr<complex_network>,  int);
std::vector<std::vector<int>> full_distance(std::shared_ptr<complex_network>);
