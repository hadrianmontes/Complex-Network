#include "stdafx.h"
#include "histogram.h"


histogram::histogram(int min_val,int max_val)
{
	min = min_val;
	max = max_val;
    total=0;
    for (int i = 0; i < (1 + max - min); i++) {
		hist.push_back(0);
	}
}

void histogram::add_data(std::vector<int> data) {
	for (int i = 0; i < data.size(); i++) {
        total++;
        hist[data[i] - min]++;
	}
}

void histogram::add_data(std::vector<std::vector<int>> data){
    for (int i = 0; i < data.size() ; i++){
        int size=data[i].size();
        for (int j = 0 ; j < size ; j++){
            total++;
            hist[data[i][j] - min]++;
        }
    }

}


std::vector<int> histogram::get_hist() {
	return hist;
}

std::vector<double> histogram::get_normalized(){
    std::vector<double> normed(1 + max - min,0.);
    for (int i = 0 ; i < max - min +1 ; ++i){
        normed[i]=(double)hist[i]/total;
    }
    return normed;
}

void histogram::save(std::string filename, bool normalized){
    std::ofstream savefile;
    savefile.open(filename);
    if (normalized){
        for (int i = 0 ; i < max - min +1 ; ++i){
            savefile << i << "\t" << (double)hist[i]/total << "\n";
        }
    }
    else {
        for (int i = 0 ; i < max - min +1 ; ++i){
            savefile << i << "\t" << hist[i] << "\n";
        }
    }
    savefile.close();
}


int histogram::plot_norm(int argc, char **argv, std::__cxx11::string xlabel,std::string savefile){
    QApplication app(argc, argv);
    MainWindow mainWindow;
    auto customPlot=mainWindow.axe();
    QCPBars *histograma = new QCPBars(customPlot->xAxis, customPlot->yAxis);
    customPlot->addPlottable(histograma);
    int max_t=0;
    double max_val=0;
    QVector <double> ticks,data;
    for (unsigned int i = 0 ; i< max-min+1;++i){
        ticks<<i;
        data<<(double)hist[i]/total;
        if (hist[i]!=0){
            max_t=i;
            max_val=std::max((double)hist[i]/total,max_val);
        }
    }
    customPlot->xAxis->setAutoTicks(false);
    customPlot->xAxis->setTickVector(ticks);

    histograma->setData(ticks,data);

    customPlot->replot();
    customPlot->setInteraction(QCP::iRangeDrag, true);
    customPlot->setInteraction(QCP::iRangeZoom,true);
    customPlot->xAxis->setRange(-0.5, max_t + 0.5 );
    customPlot->xAxis->setLabel(QString::fromStdString(xlabel));
    customPlot->yAxis->setRange(0, max_val);
    mainWindow.show();
    if (savefile!=""){
        customPlot->savePdf(QString::fromStdString(savefile));
    }
    return app.exec();
}

int histogram::plot(int argc, char **argv,std::string xlabel,std::string savefile){
    QApplication app(argc, argv);
    MainWindow mainWindow;
    auto customPlot=mainWindow.axe();
    QCPBars *histograma = new QCPBars(customPlot->xAxis, customPlot->yAxis);
    customPlot->addPlottable(histograma);
    int max_t=0;
    double max_val=0;
    QVector <double> ticks,data;
    for (unsigned int i = 0 ; i< max-min+1;++i){
        ticks<<i;
        data<<(double)hist[i];

        if (hist[i]!=0){
            max_t=i;
            max_val=std::max((double)hist[i],max_val);
        }
    }
    customPlot->xAxis->setAutoTicks(false);
    customPlot->xAxis->setTickVector(ticks);

    histograma->setData(ticks,data);

    customPlot->replot();
    customPlot->setInteraction(QCP::iRangeDrag, true);
    customPlot->setInteraction(QCP::iRangeZoom,true);
    customPlot->xAxis->setRange(-0.5, max_t + 0.5 );
    customPlot->xAxis->setLabel(QString::fromStdString(xlabel));
    customPlot->yAxis->setRange(0, max_val);
    mainWindow.show();
    if (savefile!=""){
        customPlot->savePdf(QString::fromStdString(savefile));
    }
    return app.exec();
}
