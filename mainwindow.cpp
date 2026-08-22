#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setObjectName("centralWidget");
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
    mainLayout->setContentsMargins(18, 18, 18, 18);
    mainLayout->setSpacing(18);
    setCentralWidget(centralWidget);

    QWidget *navContainer = new QWidget(this);
    navContainer->setObjectName("navWidget");
    QVBoxLayout *navMenuLayout = new QVBoxLayout(navContainer);
    navMenuLayout->setContentsMargins(20, 22, 20, 22);
    navMenuLayout->setSpacing(10);

    QLabel *appTitle = new QLabel("<b>VITALIS</b>", this);
    appTitle->setObjectName("navLogo");
    navMenuLayout->addWidget(appTitle);

    btnPatient     = new QPushButton("Nouveau Patient", this);
    btnMedecin     = new QPushButton("Nouveau Médecin", this);
    btnMedicament  = new QPushButton("Nouveau Médicament", this);
    btnConsultation= new QPushButton("Nouvelle Consultation", this);
    btnHistorique  = new QPushButton("Historique Patients", this);

    QList<QPushButton *> navBtns = {btnPatient, btnMedecin, btnMedicament, btnConsultation, btnHistorique};

    navGroup = new QButtonGroup(this);
    navGroup->setExclusive(true);

    for (auto *btn : navBtns)
    {
        btn->setProperty("class", "navBtn");
        btn->setCheckable(true);
        btn->setCursor(Qt::PointingHandCursor);
        navGroup->addButton(btn);
        navMenuLayout->addWidget(btn);
    }

    btnPatient->setChecked(true);
    navMenuLayout->addStretch();

    stackedWidget = new QStackedWidget(this);
    stackedWidget->setObjectName("stackedWidget");

    medecinPage    = new FormMedecin(this);
    patientPage    = new FormPatient(this);
    medicamentPage = new FormMedicament(this);
    consultationPage = new consultationForm(this);
    historiquePage   = new HistoriquePatientsForm(this);

    stackedWidget->addWidget(patientPage);
    stackedWidget->addWidget(medecinPage);
    stackedWidget->addWidget(medicamentPage);
    stackedWidget->addWidget(consultationPage);
    stackedWidget->addWidget(historiquePage);

    mainLayout->addWidget(navContainer, 1);
    mainLayout->addWidget(stackedWidget, 4);

    connect(btnMedecin,      &QPushButton::clicked, this, &MainWindow::showMedecinPage);
    connect(btnPatient,      &QPushButton::clicked, this, &MainWindow::showPatientPage);
    connect(btnMedicament,   &QPushButton::clicked, this, &MainWindow::showMedicamentPage);
    connect(btnConsultation, &QPushButton::clicked, this, &MainWindow::showConsultationPage);
    connect(btnHistorique,   &QPushButton::clicked, this, &MainWindow::showHistoriquePage);

    setWindowTitle("Vitalis - Gestion Médicale");
    resize(1100, 700);
}

void MainWindow::showMedecinPage()
{
    stackedWidget->setCurrentWidget(medecinPage);
}

void MainWindow::showPatientPage()
{
    stackedWidget->setCurrentWidget(patientPage);
}

void MainWindow::showMedicamentPage()
{
    stackedWidget->setCurrentWidget(medicamentPage);
}

void MainWindow::showConsultationPage()
{
    stackedWidget->setCurrentWidget(consultationPage);
    consultationPage->refreshData();
}

void MainWindow::showHistoriquePage()
{
    stackedWidget->setCurrentWidget(historiquePage);
    historiquePage->refreshData();
}