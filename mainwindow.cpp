#include "mainwindow.h"

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  QWidget *centralWidget = new QWidget(this);
  QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
  mainLayout->setContentsMargins(0, 0, 0, 0);
  mainLayout->setSpacing(0);
  setCentralWidget(centralWidget);

  QWidget *navContainer = new QWidget(this);
  navContainer->setObjectName("navWidget"); // Utilisé par le QSS
  QVBoxLayout *navMenuLayout = new QVBoxLayout(navContainer);
  navMenuLayout->setContentsMargins(16, 24, 16, 24);
  navMenuLayout->setSpacing(8);

  QLabel *appTitle = new QLabel("<b>VITALIS</b>", this);
  appTitle->setStyleSheet(
      "font-size: 22px; color: #FFFFFF; margin-bottom: 20px;");
  navMenuLayout->addWidget(appTitle);

  // création des boutons avec la classe navBtn
  btnDashboard = new QPushButton(" Tableau de bord", this);
  btnPatient = new QPushButton(" Nouveau Patient", this);
  btnMedecin = new QPushButton(" Nouveau Médecin", this);
  btnMedicament = new QPushButton(" Nouveau Médicament", this);
  btnConsultation = new QPushButton(" Nouvelle Consultation", this);
  btnHistorique = new QPushButton(" Historique Patients", this);

  QList<QPushButton *> navBtns = {btnDashboard,    btnPatient,
                                  btnMedecin,      btnMedicament,
                                  btnConsultation, btnHistorique};
  for (auto *btn : navBtns) {
    btn->setProperty("class", "navBtn");
    navMenuLayout->addWidget(btn);
  }
  navMenuLayout->addStretch();

  // zone de contenu principal
  stackedWidget = new QStackedWidget(this);
  stackedWidget->setStyleSheet("padding: 20px;");

  dashboardPage = new QWidget(this);
  QVBoxLayout *dashLayout = new QVBoxLayout(dashboardPage);
  QLabel *welcomeLabel =
      new QLabel("<h1 style='color:#1E293B;'>Bienvenue chez Vitalis</h1><p "
                 "style='color:#64748B;'>Sélectionnez une option dans le menu "
                 "latéral pour commencer.</p>",
                 dashboardPage);
  welcomeLabel->setAlignment(Qt::AlignCenter);
  dashLayout->addWidget(welcomeLabel);

  consultationPage = new consultationForm(this);
  historiquePage = new HistoriquePatientsForm(this);

  stackedWidget->addWidget(dashboardPage);
  stackedWidget->addWidget(consultationPage);
  stackedWidget->addWidget(historiquePage);

  mainLayout->addWidget(navContainer, 1);
  mainLayout->addWidget(stackedWidget, 4);

  connect(btnDashboard, &QPushButton::clicked, this,
          &MainWindow::showDashboard);
  connect(btnConsultation, &QPushButton::clicked, this,
          &MainWindow::showConsultationPage);
  connect(btnHistorique, &QPushButton::clicked, this,
          &MainWindow::showHistoriquePage);

  setWindowTitle("Vitalis - Gestion Médicale");
  resize(1100, 700);
}

void MainWindow::showConsultationPage() {
  stackedWidget->setCurrentWidget(consultationPage);
  consultationPage->refreshData();
}

void MainWindow::showDashboard() {
  stackedWidget->setCurrentWidget(dashboardPage);
}

void MainWindow::showHistoriquePage() {
  stackedWidget->setCurrentWidget(historiquePage);
  historiquePage->refreshData();
}