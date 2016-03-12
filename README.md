# README #

This repository define classes that can be used to work with complex networks. It implements the class node and the complex_network. Now it only works with undirected networks, but it will be really easy to implement directed networks. It includes some functions in crea_net.h/cpp to create different kinds of networks and to calculate the distances between nodes.

There are also one module (histomgram.h/cpp) designed to make histograms of the final data and show it. Also in representations.h/cpp there are functions to represent the network. These make use of the files qcustomplot.h/cpp, mainwindow.h/cpp and the form mainwondow.ui. To compile these last modules the qt library is needed (I hace tested it with the 5.5 version but some older version should work).

It includes a .pro file. Using the latest version of Qt Creator with this .pro file should make a successful compilation. 