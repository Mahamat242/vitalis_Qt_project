#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QHBoxLayout>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QWidget>


#include "consultationform.h"
#include "historiquePatientForm.h"

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow() override = default;

private slots:
  void showConsultationPage();
  void showHistoriquePage();

private:
  QStackedWidget *stackedWidget;
  consultationForm *consultationPage;
  HistoriquePatientsForm *historiquePage;
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
