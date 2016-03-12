#pragma once
#include "stdafx.h"
#include "mainwindow.h"
#include "qcustomplot.h"

class histogram
{
public:
	histogram(int,int);
    void add_data(std::vector<int>);
    void add_data(std::vector<std::vector<int>>);

    std::vector<int>get_hist();
    std::vector<double>get_normalized();
    void save(std::string,bool normalized=false);
    int plot(int argc, char **argv,std::string xlabel="",std::string savefile="");
    int plot_norm(int argc, char **argv,std::string xlabel="",std::string savefile="");

private:
	std::vector<int> hist;
	int min;
	int max;
    long int total;
};

