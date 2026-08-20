#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    formMedecin= new FormMedecin(this);
    formPatient= new FormPatient(this);
    formMedicament = new FormMedicament(this);

    setCentralWidget(formMedicament);
}

MainWindow::~MainWindow() = default;
