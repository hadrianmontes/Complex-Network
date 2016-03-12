// red_compleja.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "create_net.h"
#include "histogram.h"
#include "representations.h"

int main(int argc, char **argv)
{

//    int size=0;
//    std::cout<< "Introduce tamanho de la red"<<std::endl;
//    std::cin>>size;
//    std::shared_ptr<complex_network> red;
//    std::string tipo="";
//    while (tipo==""){
//        std::cout<< "Introduce tipo de red"<<std::endl;
//        std::cin>>tipo;
//        if (tipo=="scalefree"){
//            red = scale_free(size);
//        }
//        else if (tipo=="smallworld"){
//            float prob=0;
//            std::cout<<"Introduce la probabilidad"<<std::endl;
//            std::cin>>prob;
//            red=small_world1d(size,prob);
//        }
//        else{
//            tipo="";
//        }
//    }

    auto red=small_world1d(500,0.003);
    red->save("small1d");

    //red->print_all_bonds();

    auto hist_con = histogram(0, red->get_size());
    hist_con.add_data(red->conectivity());
    hist_con.save("histograma");
    hist_con.plot_norm(argc,argv,"Conectividad","histogram_con.pdf");


    histogram hist2(0, red->get_size());
    hist2.add_data(full_distance(red));
    hist2.save("histograma_dist",true);
    hist2.plot_norm(argc,argv,"Distancia","histogram_dist.pdf");
    represent_small("small1d",argc,argv,"network.pdf");
    return 0;
}
