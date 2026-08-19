#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include "consultationform.h"
#include <QLabel>

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow() override = default;

    private slots:
        void showConsultationPage();

    private:
        QStackedWidget *stackedWidget;
        consultationForm *consultationPage;
        QWidget *dashboardPage;
        QPushButton *btnDashboard;
        QPushButton *btnPatient;
        QPushButton *btnMedecin;
        QPushButton *btnMedicament;
        QPushButton *btnConsultation;
        QPushButton *btnHistorique;

        void showDashboard();
};

#endif // MAINWINDOW_H
