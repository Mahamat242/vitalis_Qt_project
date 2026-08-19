#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *centralWidget = new QWidget(this);
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
    setCentralWidget(centralWidget);

    QVBoxLayout *navMenuLayout = new QVBoxLayout();

    btnConsultation = new QPushButton("Enregistrer consultation", this);
    navMenuLayout->addWidget(btnConsultation);
    navMenuLayout->addStretch();

    stackedWidget = new QStackedWidget(this);
    consultationPage = new ConsultationForm(this);

    stackedWidget->addWidget(consultationPage);

    mainLayout->addLayout(navMenuLayout, 1);
    mainLayout->addWidget(stackedWidget, 4);

    connect(btnConsultation, &QPushButton::clicked, this, &MainWindow::showConsultationPage);

    setWindowTitle("Vitalis - Gestion médicale");
    resize(900, 600);
}

void MainWindow::showConsultationPage()
{
    stackedWidget->setCurrentWidget(consultationPage);
    consultationPage->refreshData();
}