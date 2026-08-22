#include "dbmanager.h"
#include "login.h"
#include "mainwindow.h"

#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString style = R"(
        QMainWindow {
            background-color: #DDE2F0;
        }
        QWidget#centralWidget {
            background-color: #FAFAFD;
        }

        QWidget#navWidget {
            background-color: #122056;
            border-radius: 26px;
            border: 1px solid rgba(148, 163, 184, 0.12);
        }

        QLabel#navLogo {
            background-color: transparent;
            color: #5B65DC;
            border-radius: 12px;
            font-size: 30px;
            font-weight: 700;
            padding: 8px 0 18px 8px;
        }

        QPushButton[class="navBtn"] {
            color: #FAFAFD;
            border-radius: 14px;
            min-height: 46px;
            font-size: 13px;
            text-align: left;
            padding: 10px 14px;
        }
        QPushButton[class="navBtn"]:hover {
            background-color: #5B65DC;
            color: #122056;
        }
        QPushButton[class="navBtn"]:checked {
            background-color: #5B65DC;
            color: #122056;
        }

        QStackedWidget {
            background: transparent;
        }

        QLabel {
            background: transparent;
            color: #111827;
        }

        QLineEdit, QComboBox, QSpinBox, QDateEdit, QTextEdit {
            background-color: #F9FAFB;
            border: 1px solid #EEEFFD;
            border-radius: 10px;
            padding: 10px 14px;
            font-size: 13px;
            color: #111827;
            selection-background-color: #E5E7EB;
        }
        QLineEdit:focus, QComboBox:focus, QSpinBox:focus,
        QDateEdit:focus, QTextEdit:focus {
            border: 1px solid #111827;
        }
        QLineEdit:disabled, QComboBox:disabled {
            background-color: #F3F4F6;
            color: #9CA3AF;
        }

        /* comboBox dropdown arrow */
        QComboBox::drop-down {
            border: none;
            width: 28px;
        }
        QComboBox::down-arrow {
            width: 0;
            height: 0;
            border-left:   5px solid transparent;
            border-right:  5px solid transparent;
            border-top:    5px solid #6B7280;
            margin-right:  8px;
        }
        QComboBox QAbstractItemView {
            background-color: #FFFFFF;
            border-radius: 10px;
            selection-background-color: #F3F4F6;
            selection-color: #111827;
            padding: 4px;
            outline: 0;
        }
        QComboBox QAbstractItemView::item {
            padding: 8px 12px;
            border-radius: 6px;
        }

        QSpinBox::up-button, QSpinBox::down-button,
        QDateEdit::up-button, QDateEdit::down-button {
            background: transparent;
            border: none;
            width: 16px;
        }
        QDateEdit::drop-down {
            border: none;
            width: 28px;
        }

        QPushButton {
            background-color: #5B65DC;
            color: #FFFFFF;
            border: 1px solid #4E59D4;
            border-radius: 10px;
            min-height: 40px;
            padding: 9px 16px;
            font-size: 13px;
            font-weight: 600;
        }
        QPushButton:hover {
            background-color: #6A74E7;
            border-color: #5B65DC;
        }
        QPushButton:pressed {
            background-color: #4956CB;
        }

        QPushButton[class="btnPrimary"] {
            background-color: #5B65DC;
            color: #FFFFFF;
            border: 1px solid #4E59D4;
            border-radius: 10px;
            padding: 11px 22px;
            font-weight: 600;
            font-size: 13px;
        }
        QPushButton[class="btnPrimary"]:hover    { background-color: #6A74E7; border-color: #5B65DC; }
        QPushButton[class="btnPrimary"]:pressed  { background-color: #4956CB; }

        QPushButton[class="btnSuccess"] {
            background-color: #059669;
            color: #FFFFFF;
            border: none;
            border-radius: 10px;
            padding: 11px 22px;
            font-weight: 600;
            font-size: 13px;
        }
        QPushButton[class="btnSuccess"]:hover    { background-color: #047857; }
        QPushButton[class="btnSuccess"]:pressed  { background-color: #065F46; }

        QPushButton[class="btnDanger"] {
            background-color: #EF4444;
            color: #FFFFFF;
            border: none;
            border-radius: 10px;
            padding: 10px 20px;
            font-weight: 600;
            font-size: 13px;
        }
        QPushButton[class="btnDanger"]:hover    { background-color: #DC2626; }
        QPushButton[class="btnDanger"]:pressed  { background-color: #B91C1C; }

        QPushButton[class="btnSecondary"] {
            background-color: #F3F4F6;
            color: #374151;
            border: none;
            border-radius: 10px;
            padding: 10px 20px;
            font-size: 13px;
            font-weight: 500;
        }
        QPushButton[class="btnSecondary"]:hover  { background-color: #E5E7EB; }
        QPushButton[class="btnSecondary"]:pressed { background-color: #D1D5DB; }

        QPushButton[class="navBtn"] {
            background: transparent;
            border: 1px solid transparent;
            color: #FAFAFD;
            border-radius: 14px;
            min-height: 46px;
            font-size: 13px;
            text-align: left;
            padding: 10px 14px;
        }
        QPushButton[class="navBtn"]:hover {
            background-color: #5B65DC;
            color: #122056;
            border-color: #5B65DC;
        }
        QPushButton[class="navBtn"]:checked {
            background-color: #5B65DC;
            color: #122056;
            border-color: #5B65DC;
        }

        QTableWidget {
            background-color: #FFFFFF;
            border: none;
            gridline-color: #F3F4F6;
            selection-background-color: #F3F4F6;
            selection-color: #111827;
            alternate-background-color: #FAFAFA;
            outline: 0;
        }
        QTableWidget::item {
            padding: 11px 14px;
            color: #374151;
            font-size: 13px;
            border-bottom: 1px solid #F3F4F6;
        }
        QTableWidget::item:selected {
            background-color: #F3F4F6;
            color: #111827;
        }
        QHeaderView {
            background-color: transparent;
        }
        QHeaderView::section {
            background-color: #F9FAFB;
            color: #9CA3AF;
            padding: 10px 14px;
            font-weight: 700;
            font-size: 11px;
            border: none;
            border-bottom: 1px solid #E5E7EB;
            text-transform: uppercase;
            letter-spacing: 0.5px;
        }
        QHeaderView::section:first {
            border-top-left-radius: 10px;
        }
        QHeaderView::section:last {
            border-top-right-radius: 10px;
        }

        QScrollBar:vertical {
            background: transparent;
            width: 5px;
            margin: 0;
        }
        QScrollBar::handle:vertical {
            background: #D1D5DB;
            border-radius: 3px;
            min-height: 40px;
        }
        QScrollBar::handle:vertical:hover { background: #9CA3AF; }
        QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
            height: 0; background: transparent;
        }
        QScrollBar:horizontal {
            background: transparent;
            height: 5px;
            margin: 0;
        }
        QScrollBar::handle:horizontal {
            background: #D1D5DB;
            border-radius: 3px;
        }
        QScrollBar::add-line:horizontal, QScrollBar::sub-line:horizontal {
            width: 0; background: transparent;
        }

        QDialog {
            background-color: #FFFFFF;
        }

        QToolTip {
            background-color: #111827;
            color: #FFFFFF;
            border: none;
            border-radius: 6px;
            padding: 6px 10px;
            font-size: 12px;
        }

    )";

    a.setStyleSheet(style);

    if (!databaseManager::connexion())
    {
        QMessageBox::critical(nullptr, "Erreur BD", "Impossible de se connecter à la base MySQL.\nVérifier que le conteneur Docker tourne.");
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

    return 0; // si l'utilisateur ferme la fenêtre de login
}
