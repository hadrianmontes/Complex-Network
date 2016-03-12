#include "representations.h"

int represent_small(std::string filename, int argc, char **argv, std::string savefile){
    QApplication app(argc, argv);
    MainWindow mainWindow;
    auto customPlot=mainWindow.axe();
    constexpr double pi=3.1415926;
    std::ifstream archivo;
    archivo.open(filename);
    int size=0;
    {
        std::string input;
        std::getline(archivo, input);
        std::stringstream stream(input);
        stream >> size;
    }
    std::vector<std::vector<int>> enlaces;
    enlaces.resize(size);
    int index=0;
    for (int i = 0; i< size ; ++i){
        std::string input;
        std::getline(archivo, input);
        std::stringstream stream(input);
        while(stream>>index){
            if (index<i){
                enlaces[i].push_back(index);
            }
        }
    }

    QVector<double> x(size), y(size);
    double pired=(float)2*pi/((float) size);
    for (int i=0; i<size; ++i)
    {
      x[i] = cos((double)i*pired);
      y[i] = sin((double)i*pired);
    }
    customPlot->setGeometry(mainWindow.geometry());
    customPlot->addGraph();
    customPlot->graph(0)->setData(x, y);
    int graph=0;
    for (int i = 0; i< size ; ++i){
        int size2=enlaces[i].size();
        for (int j = 0 ; j<size2;j++){
            graph++;
            customPlot->addGraph();
            QVector<double> x2(2), y2(2);
            x2[0] = cos((double)i*pired);
            x2[1] = cos((double)enlaces[i][j]*pired);
            y2[0] = sin((double)i*pired);
            y2[1] = sin((double)enlaces[i][j]*pired);
            customPlot->graph(graph)->setData(x2,y2);
        }
    }

    // set axes ranges, so we see all data:
    customPlot->graph(0)->setLineStyle(QCPGraph::lsNone);
    customPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 4));
    customPlot->xAxis->setRange(-1, 1);
    customPlot->yAxis->setRange(-1, 1);
    customPlot->replot();
    customPlot->setInteraction(QCP::iRangeDrag, true);
    customPlot->setInteraction(QCP::iRangeZoom,true);
    mainWindow.show();
    if (savefile!=""){
        customPlot->savePdf(QString::fromStdString(savefile));
    }

    return app.exec();
}
