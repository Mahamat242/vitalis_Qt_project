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

    // 3. Conteneur multi-pages (QStackedWidget) à droite
    stackedWidget = new QStackedWidget(this);

    // Instanciation du formulaire de consultation
    consultationPage = new ConsultationForm(this);

    // Ajout de la page au QStackedWidget
    stackedWidget->addWidget(consultationPage);

    // 4. Assemblage dans le layout principal
    mainLayout->addLayout(navMenuLayout, 1);     // Menu prend 1/5 de la largeur
    mainLayout->addWidget(stackedWidget, 4);    // Contenu prend 4/5 de la largeur

    // 5. Connexion du bouton au changement de page
    connect(btnConsultation, &QPushButton::clicked, this, &MainWindow::showConsultationPage);

    // Titre et dimensions de la fenêtre
    setWindowTitle("Vitalis - Gestion Médicale");
    resize(900, 600);
}

void MainWindow::showConsultationPage()
{
    // Affiche la page dans le stackedWidget
    stackedWidget->setCurrentWidget(consultationPage);

    // Rafraîchit les listes déroulantes depuis la BDD (Médecins, Patients, Médicaments)
    consultationPage->refreshData();
}