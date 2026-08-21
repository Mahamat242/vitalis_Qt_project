#include "dbmanager.h"
#include "login.h"
#include "mainwindow.h"

#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString style = R"(
        /* arrière plan
        QMainWindow, QDialog
        {
            background-color: #F8FAFC;
        }*/
        /* barre de navigation */
        QWidget#navWidget
        {
            background-color: #0F172A;
        }
        QPushButton.navBtn
        {
            background-color: transparent;
            color: #94A3B8;
            text-align: left;
            padding: 12px 16px;
            border: none;
            border-radius: 6px;
            font-size: 14px;
            font-weight: 500;
        }
        QPushButton.navBtn:hover
        {
            background-color: #1E293B;
            color: #38BDF8;
        }
        QPushButton.navBtn:checked, QPushButton.navBtn:pressed
        {
            background-color: inherit;
            color: #0284C7;
            font-weight: bold;
            border-top-left-radius: 6px;
            border-bottom-left-radius: 6px;
            border-top-right-radius: 20px;
            border-bottom-right-radius: 20px;
        }
        /* champs de saisie
        QLineEdit, QComboBox, QSpinBox, QTextEdit, QDateEdit
        {
            background-color: #FFFFFF;
            border: 1px solid #CBD5E1;
            border-radius: 6px;
            padding: 8px 12px;
            font-size: 13px;
            color: #0F172A;
        }
        QLineEdit:focus, QComboBox:focus, QSpinBox:focus, QTextEdit:focus, QDateEdit:focus
        {
            border: 2px solid #0284C7;
        }*/
        /* --- boutons --- */
        QPushButton.btnPrimary
        {
            background-color: #0284C7;
            color: white;
            border: none;
            border-radius: 6px;
            padding: 10px 18px;
            font-weight: bold;
        }
        QPushButton.btnPrimary:hover { background-color: #0369A1; }
        QPushButton.btnSuccess
        {
            background-color: #16A34A;
            color: white;
            border: none;
            border-radius: 6px;
            padding: 10px 18px;
            font-weight: bold;
        }
        QPushButton.btnSuccess:hover { background-color: #15803D; }
        QPushButton.btnDanger
        {
            background-color: #DC2626;
            color: white;
            border: none;
            border-radius: 6px;
            padding: 8px 14px;
            font-weight: bold;
        }
        QPushButton.btnDanger:hover { background-color: #B91C1C; }
        QPushButton.btnSecondary
        {
            background-color: #64748B;
            color: white;
            border: none;
            border-radius: 6px;
            padding: 8px 14px;
        }
        QPushButton.btnSecondary:hover { background-color: #475569; }
        QTableWidget
        {
            background-color: #FFFFFF;
            border: 1px solid #E2E8F0;
            border-radius: 8px;
            gridline-color: #F1F5F9;
            selection-background-color: #E0F2FE;
            selection-color: #0369A1;
        }
        QHeaderView::section
        {
            background-color: #0284C7;
            color: #FFFFFF;
            padding: 8px;
            font-weight: bold;
            border: none;
        }
    )";

    a.setStyleSheet(style);

    if (!databaseManager::connexion())
    {
        QMessageBox::critical(nullptr, "erreur BD", "Impossible de se connecter à la base MySQL.\nVérifier que le conteneur tourne.");
        return -1;
    }

    login logForm;
    if (logForm.exec() == QDialog::Accepted)
    {
        // si l'authentification est acceptée, alors afficher la page principale
        MainWindow w;
        w.show();
        return a.exec();
    }

    return 0; // si l'utilisateur clique ferme la fenêtre
}
