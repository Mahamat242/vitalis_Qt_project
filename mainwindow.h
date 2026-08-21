#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QButtonGroup>
#include <QHBoxLayout>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QWidget>
#include "consultationForm.h"
#include "historiquePatientForm.h"
#include "ajoutMedecin.h"
#include "ajoutPatient.h"
#include "ajoutMedicament.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    public:
        explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow() override = default;

    private slots:
        void showConsultationPage();
        void showHistoriquePage();
        void showMedecinPage();
        void showPatientPage();
        void showMedicamentPage();

    private:
        QStackedWidget *stackedWidget;
        consultationForm *consultationPage;
        HistoriquePatientsForm *historiquePage;
        FormMedecin   *medecinPage;
        FormPatient   *patientPage;
        FormMedicament *medicamentPage;
        QWidget *dashboardPage;
        QPushButton *btnDashboard;
        QPushButton *btnPatient;
        QPushButton *btnMedecin;
        QPushButton *btnMedicament;
        QPushButton *btnConsultation;
        QPushButton *btnHistorique;
        QButtonGroup *navGroup;

        void showDashboard();
};
#endif // MAINWINDOW_H