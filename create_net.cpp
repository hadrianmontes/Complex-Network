#include "stdafx.h"
#include "node.h"
#include "complex_network.h"


std::shared_ptr<complex_network> scale_free( int n) {
	std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
	std::uniform_real_distribution<double> distribution(0.0, 1.0);
	auto red(std::make_shared<complex_network>(n));
    std::vector< int> nodos(n, 0);
    for ( int i = 0; i<n; i++) {
		nodos[i] = i;
	}
	red->set_bond(0, 1);
     int t = 0;
	double prob = 0;
	while (t != n - 2) {
		bool conected = false;
        for ( int i = 0; i<t + 2; i++) {
			prob = (red->get_conections(i)) / (red->get_weight());
			if (distribution(generator) <= prob) {
				red->set_bond(i, t + 2);
				conected = true;
			}
		}
		if (conected) {
			t++;
		}

	}
	return red;
}


std::shared_ptr<complex_network> small_world1d(int n, double prob){
    std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    auto red(std::make_shared<complex_network>(n));
    for (int i = 2; i < n - 2; i++) {
        red->set_bond(i,i+1);
        red->set_bond(i,i+2);
        for (int j = i+3 ; j < n ; j++){
            if (distribution(generator)<prob) {
                red->set_bond(i,j);
            }
        }
    }
    //Hacemos los enlaces para el 0
    red->set_bond(0,1);
    red->set_bond(0,2);
    red->set_bond(0,n-1);
    red->set_bond(0,n-2);

    for (int i = 3 ; i< n-2 ; i++) {
        if (distribution(generator)<prob) {
            red->set_bond(0,i);
        }
    }
    //Hacemos los enlaces para el 1
    red->set_bond(1,2);
    red->set_bond(1,3);
    red->set_bond(1,n-1);
    for (int i = 4 ; i< n-1 ; i++) {
        if (distribution(generator)<prob) {
            red->set_bond(1,i);
        }
    }
    red->set_bond(n-2,n-1);
    return red;
}


std::shared_ptr<complex_network>  small_world(int n, int m, double prob) {
	std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
	std::uniform_real_distribution<double> distribution(0.0, 1.0);
	auto red(std::make_shared<complex_network>(n*m));
	// complex_network red(n*m);
	//Creamos los enlaces de la ultiam fila
	for (int j = 0; j < m - 1; j++) {
		red->set_bond((n - 1)*m + j, (n - 1)*m + j + 1);

	}
	//Creamos los enlaces de la ultima columna
	for (int i = 0; i < n - 1; i++) {
		red->set_bond((m - 1) + i*m, (m - 1) + (i + 1)*m);
	}
	//Creamos los enlaces base de la red, sin los bordes
	if (n > 2 && m > 2) {
		for (int i = 0; i < n - 1; i++) {
			for (int j = 0; j < m - 1; j++) {
				red->set_bond(i*m + j, i*m + j + 1);
				red->set_bond(i*m + j, (i + 1)*m + j);
			}
		}
	}

	// Introducimos las conexiones de largo alcance aleatorias
	for (int i1 = 0; i1 < n; i1++) {
		for (int j1 = 0; j1 < m; j1++) {
			for (int j2 = j1 + 2; j2 < m; j2++) {
				if (distribution(generator) <= prob) {
					red->set_bond(i1*m + j1, i1*m + j2);
				}
			}
			for (int i2 = i1+2; i2 < n; i2++) {
				if (distribution(generator) <= prob) {
					red->set_bond(i1*m + j1, i2*m + j1);
				}
			}
			for (int i2 = i1 + 1; i2 < n; i2++) {
				for (int j2 = 0; j2 < j1; j2++) {
						if (distribution(generator) <= prob) {
							red->set_bond(i1*m + j1, i2*m + j2);
						}
				}
				for (int j2 = j1+1; j2 < m; j2++) {
					if (distribution(generator) <= prob) {
						red->set_bond(i1*m + j1, i2*m + j2);
					}
				}
			}
		}

	}
	return red;
}




std::vector<int> distance(std::shared_ptr<complex_network> net,  int index) {
	//Iniciamos un vector para guardar las distancias
	//Para emular una distancia infinita ponemos el integer mas grande
	constexpr int max_int = std::numeric_limits<int>::max();
	//Guardamos un vector con las distancias
	std::vector<int> dist(net->get_size(), max_int);
	//cogemos un array con los nodos
	auto nodos = net->get_nodes();
	//Cogemos un array con los nodos visitados
	std::vector<bool> visited(net->get_size(),false);
	int number_visitados = 0;
	std::vector<int> tovisit(1,index);
	dist[index]=0;
	const int number_nodes = net->get_size();
	

	while (number_visitados != number_nodes) {
		int min_dist = max_int;
		int min_index = 0;
		int min_node = 0;
		// Eliminamos indices repetidos
		std::sort(tovisit.begin(), tovisit.end());
		tovisit.erase(unique(tovisit.begin(), tovisit.end()), tovisit.end());

		//Buscamos el mas cercano de los que tenemos que visitar
        for (unsigned int i = 0; i < tovisit.size(); i++) {
			if (dist[tovisit[i]] < min_dist) {
				min_dist = dist[tovisit[i]];
				min_node = tovisit[i];
				min_index = i;
			}
		}
		visited[min_node] = true;
		//Borramos el valor de tovisit
		tovisit.erase(tovisit.begin() + min_index);
		//Ya tenemos el valor de la distancia minima
		auto bonds = nodos[min_node]->index_conections();

		//anhadimos los pendientes de revisar
		// a la vez que calculamos la distancia
        for (unsigned int j = 0; j < bonds.size(); j++) {
			if (dist[min_node] + 1 < dist[bonds[j]]) {
				dist[bonds[j]] = dist[min_node] + 1;
			}
			if (!visited[bonds[j]]) {
				tovisit.push_back(bonds[j]);
			}
		}
		//Anhadimos el modo actual a los visitados
		number_visitados++;

	}

	return dist;
}


std::vector<std::vector <int>> full_distance(std::shared_ptr<complex_network> net) {
	int size = net->get_size();
	constexpr int max_int = std::numeric_limits<int>::max();
	std::vector<std::vector <int>> dist(size, std::vector <int>(size, max_int));
	auto nodes = net->get_nodes();
	//Ponemos las distancias de la diagonal a 0 y las de las conexiones a 1
	for (int i = 0; i < size; i++) {
		dist[i][i] = 0;
		auto bonds = nodes[i]->index_conections();
        for (unsigned int j = 0; j < bonds.size(); j++) {
			dist[i][bonds[j]] = 1;
		}
	}
	//Comenzamos ahora el algoritmo
    #pragma omp parallel for
	for (int k = 0; k < size; ++k) {
		for (int i = 0; i < size; ++i) {
			for (int j = 0; j < size; ++j) {
				if ((dist[i][k] != max_int) && (dist[k][j] != max_int)) {
                    dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
				}
			}
		}
	}

	return dist;
}
