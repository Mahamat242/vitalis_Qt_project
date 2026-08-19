#include "mainwindow.h"
#include "consultationForm.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    consultationForm *consultationPage = new consultationForm(this);
}

MainWindow::~MainWindow() = default;
