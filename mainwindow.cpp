#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    formMedecin= new FormMedecin(this);
    formPatient= new FormPatient(this);

    setCentralWidget(formPatient);
}

MainWindow::~MainWindow() = default;
