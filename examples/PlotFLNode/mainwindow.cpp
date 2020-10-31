#include "mainwindow.h"
#include "QwtPlotActions.h"
#include "QwtPlotWidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    QwtPlotWidget *widget = new QwtPlotWidget(this);
    setCentralWidget(widget);
}
