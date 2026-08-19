#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    QWidget *centralWidget = new QWidget(this);
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
    setCentralWidget(centralWidget);

    QVBoxLayout *navMenuLayout = new QVBoxLayout();

    QLabel *appTitle = new QLabel("<b>VITALIS</b>", this);
    appTitle->setStyleSheet("font-size: 20px; margin-bottom: 15px;");
    navMenuLayout->addWidget(appTitle);

    btnDashboard = new QPushButton("Tableau de bord", this);
    btnPatient = new QPushButton("Nouveau Patient", this);
    btnMedecin = new QPushButton("Nouveau Médecin", this);
    btnMedicament = new QPushButton("Nouveau Médicament", this);
    btnConsultation = new QPushButton("Nouvelle Consultation", this);
    btnHistorique = new QPushButton("Historique Patients", this);

    navMenuLayout->addWidget(btnDashboard);
    navMenuLayout->addWidget(btnPatient);
    navMenuLayout->addWidget(btnMedecin);
    navMenuLayout->addWidget(btnMedicament);
    navMenuLayout->addWidget(btnConsultation);
    navMenuLayout->addWidget(btnHistorique);
    navMenuLayout->addStretch();

    // zone d'affichage dynamique
    stackedWidget = new QStackedWidget(this);

    dashboardPage = new QWidget(this);
    QVBoxLayout *dashLayout = new QVBoxLayout(dashboardPage);
    QLabel *welcomeLabel = new QLabel("<h1>Bienvenue chez Vitalis</h1><p>Sélectionnez une option dans le menu latéral.</p>", dashboardPage);
    welcomeLabel->setAlignment(Qt::AlignCenter);
    dashLayout->addWidget(welcomeLabel);

    consultationPage = new consultationForm(this);
    historiquePage = new HistoriquePatientsForm(this);

    // ajout des pages dans la pile
    stackedWidget->addWidget(dashboardPage);
    stackedWidget->addWidget(consultationPage);
    stackedWidget->addWidget(historiquePage);

    mainLayout->addLayout(navMenuLayout, 1);
    mainLayout->addWidget(stackedWidget, 4);

    connect(btnConsultation, &QPushButton::clicked, this, &MainWindow::showConsultationPage);
    connect(btnDashboard, &QPushButton::clicked, this, &MainWindow::showDashboard);
    connect(btnHistorique, &QPushButton::clicked, this, &MainWindow::showHistoriquePage);

    setWindowTitle("Vitalis - Gestion médicale");
    resize(900, 600);
}

void MainWindow::showConsultationPage()
{
    stackedWidget->setCurrentWidget(consultationPage);
    consultationPage->refreshData();
}

void MainWindow::showDashboard()
{
    stackedWidget->setCurrentWidget(dashboardPage);
}

void MainWindow::showHistoriquePage()
{
    stackedWidget->setCurrentWidget(historiquePage);
    historiquePage->refreshData();
}