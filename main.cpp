#include "mainwindow.h"
#include "login.h"
#include "dbmanager.h"

#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if(!databaseManager::connexion())
    {
        QMessageBox::critical(nullptr, "erreur BD", "Impossible de se connecter à la base MySQL.\nVérifier que le conteneur tourne.");
        return -1;
    }

    login logForm;
    if(logForm.exec() == QDialog::Accepted)
    {
        // si l'authentification est acceptée, alors afficher la page principale
        MainWindow w;
        w.show();
        return a.exec();
    }

    return 0; // si l'utilisateur clique ferme la fenêtre
}
