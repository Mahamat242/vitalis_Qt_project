#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    formMedecin= new FormMedecin(this);
    setCentralWidget(formMedecin);
}

MainWindow::~MainWindow() = default;
