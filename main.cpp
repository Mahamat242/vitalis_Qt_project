#include "dbmanager.h"
#include "login.h"
#include "mainwindow.h"

#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString style = R"(
        /*QMainWindow {
            background-color: #DDE2F0;
        }*/
        QWidget#centralWidget {
            background-color: #EEF1F8;
            border-radius: 28px;
            border: 1px solid rgba(148, 163, 184, 0.18);
        }

        QWidget#navWidget {
            background-color: rgba(255, 255, 255, 0.6);
            border-radius: 26px;
            border: 1px solid rgba(148, 163, 184, 0.12);
        }

        QLabel#navLogo {
            background-color: transparent;
            color: #1A1A1A;
            border-radius: 12px;
            font-size: 30px;
            font-weight: 700;
            padding: 8px 0 18px 8px;
        }

        QPushButton[class="navBtn"] {
            background-color: rgba(255, 255, 255, 0.12);
            color: #1F2937;
            border: 1px solid rgba(148, 163, 184, 0.10);
            border-radius: 14px;
            min-height: 46px;
            font-size: 13px;
            text-align: left;
            padding: 10px 14px;
        }
        QPushButton[class="navBtn"]:hover {
            background-color: rgba(17, 24, 39, 0.06);
            border-color: rgba(148, 163, 184, 0.18);
        }
        QPushButton[class="navBtn"]:checked {
            background-color: #111827;
            color: #FFFFFF;
            border-color: rgba(17, 24, 39, 0.8);
            box-shadow: inset 0 0 0 1px rgba(255, 255, 255, 0.08);
        }

        QStackedWidget {
            background: transparent;
        }

        QWidget#dashboardPage {
            background: transparent;
        }

        QLabel#pageTitle {
            color: #1A1A1A;
            font-size: 16px;
            font-weight: 700;
        }

        QWidget#searchWrap {
            background: rgba(255, 255, 255, 0.60);
            border: 1px solid rgba(148, 163, 184, 0.18);
            border-radius: 18px;
            min-height: 42px;
        }
        QLabel#searchIcon {
            color: #6B7280;
            font-size: 20px;
        }
        QLineEdit#searchBox {
            background: transparent;
            border: none;
            color: #374151;
            font-size: 14px;
        }

        QWidget#headerActions {
            background: transparent;
        }
        QPushButton#miniActionButton {
            background: rgba(255, 255, 255, 0.7);
            border: 1px solid rgba(148, 163, 184, 0.12);
            border-radius: 12px;
            min-width: 30px;
            min-height: 30px;
            color: #111827;
            font-size: 12px;
        }
        QPushButton#avatarButton {
            background: linear-gradient(135deg, #F5C8B6, #D7C6FF);
            border: none;
            border-radius: 50%;
            min-width: 36px;
            min-height: 36px;
            color: #1F2937;
            font-weight: 700;
        }

        QLabel#sectionTitle {
            color: #1A1A1A;
            font-size: 16px;
            font-weight: 700;
        }

        QFrame#bankCard {
            background: #121418;
            border-radius: 22px;
            min-height: 180px;
            border: 1px solid rgba(255, 255, 255, 0.08);
        }
        QLabel#chipIcon {
            color: #F3F4F6;
            font-size: 28px;
        }
        QWidget#signalWidget {
            background: transparent;
            min-width: 52px;
        }
        QLabel#cardNumber {
            color: #F8FAFC;
            font-size: 18px;
            letter-spacing: 1.4px;
            font-weight: 500;
        }
        QLabel#ownerName {
            color: #E5E7EB;
            font-size: 12px;
        }
        QLabel#cardLogo {
            color: #F3F4F6;
            font-size: 12px;
            font-weight: 700;
        }

        QFrame#miniStatCard {
            background: rgba(255, 255, 255, 0.72);
            border: 1px solid rgba(148, 163, 184, 0.12);
            border-radius: 18px;
            min-height: 120px;
        }
        QFrame#miniIconBox {
            background: #F3F5F9;
            border-radius: 10px;
            min-width: 40px;
            min-height: 40px;
        }
        QLabel#miniIconLabel {
            color: #111827;
            font-size: 20px;
        }
        QLabel#miniStatTitle {
            color: #111827;
            font-size: 13px;
        }
        QLabel#miniStatValue {
            color: #111827;
            font-size: 15px;
            font-weight: 700;
        }

        QFrame#transactionCard {
            background: rgba(255, 255, 255, 0.2);
            border: 1px solid rgba(148, 163, 184, 0.12);
            border-radius: 18px;
        }
        QLabel#transactionTitle {
            color: #1A1A1A;
            font-size: 14px;
            font-weight: 700;
        }
        QPushButton#sortButton {
            background: rgba(255, 255, 255, 0.75);
            border: 1px solid rgba(148, 163, 184, 0.18);
            border-radius: 12px;
            color: #374151;
            padding: 4px 12px;
        }
        QWidget#transactionRow {
            border-top: 1px solid rgba(148, 163, 184, 0.18);
        }
        QLabel#rowLabel {
            color: #1F2937;
            font-size: 13px;
        }
        QLabel#rowMeta {
            color: #6B7280;
            font-size: 12px;
        }
        QLabel#rowAmount {
            color: #111827;
            font-size: 13px;
            font-weight: 600;
        }
        QLabel#rowMenu {
            color: #6B7280;
            font-size: 18px;
        }

        QFrame#statsPanel {
            background: rgba(255, 255, 255, 0.65);
            border: 1px solid rgba(148, 163, 184, 0.12);
            border-radius: 24px;
        }
        QLabel#amountLabel {
            color: #1F2937;
            font-size: 14px;
        }
        QLabel#amountValue {
            color: #1A1A1A;
            font-size: 28px;
            font-weight: 700;
        }
        QLabel#rangeLabel,
        QLabel#monthLabel {
            color: #6B7280;
            font-size: 11px;
        }
        QLabel#rangeSelected,
        QLabel#monthSelected {
            background: #1F2937;
            color: #FFFFFF;
            border-radius: 12px;
            padding: 5px 8px;
            font-size: 11px;
        }
        QWidget#chartWidget {
            background: transparent;
            min-height: 150px;
        }
        QWidget#chartBar {
            background: rgba(148, 163, 184, 0.55);
            border-radius: 8px 8px 0 0;
            min-width: 18px;
        }

        QFrame#progressCard {
            background: #111827;
            border-radius: 18px;
            min-height: 130px;
        }
        QLabel#progressText {
            color: #F9FAFB;
            font-size: 15px;
            line-height: 1.2;
        }
        QLabel#progressValue {
            color: #F9FAFB;
            font-size: 24px;
            font-weight: 700;
        }

        QLabel {
            background: transparent;
            color: #111827;
        }

        QLineEdit, QComboBox, QSpinBox, QDateEdit, QTextEdit {
            background-color: #F9FAFB;
            border: 1.5px solid #E5E7EB;
            border-radius: 10px;
            padding: 10px 14px;
            font-size: 13px;
            color: #111827;
            selection-background-color: #E5E7EB;
        }
        QLineEdit:focus, QComboBox:focus, QSpinBox:focus,
        QDateEdit:focus, QTextEdit:focus {
            background-color: #FFFFFF;
            border: 1.5px solid #111827;
        }
        QLineEdit:disabled, QComboBox:disabled {
            background-color: #F3F4F6;
            color: #9CA3AF;
        }

        /* ComboBox dropdown arrow */
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
            border: 1.5px solid #E5E7EB;
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

        /* SpinBox / DateEdit boutons */
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

        /* Primaire — noir charcoal */
        QPushButton[class="btnPrimary"] {
            background-color: #111827;
            color: #FFFFFF;
            border: none;
            border-radius: 10px;
            padding: 11px 22px;
            font-weight: 600;
            font-size: 13px;
        }
        QPushButton[class="btnPrimary"]:hover    { background-color: #1F2937; }
        QPushButton[class="btnPrimary"]:pressed  { background-color: #374151; }

        /* Succès — vert */
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

        /* Danger — rouge */
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

        /* Secondaire — gris clair */
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
