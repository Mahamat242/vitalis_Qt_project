#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QLabel>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override = default;

private slots:
    void showDashboard();

private:
    // contener principale qui permet de faire le toogle entre les pages
    QStackedWidget *stackedWidget;

    QWidget *dashboardPage;

    QPushButton *btnDashboard;
    QPushButton *btnPatient;
    QPushButton *btnMedecin;
    QPushButton *btnMedicament;
    QPushButton *btnConsultation;
    QPushButton *btnHistorique;
};

#endif // MAINWINDOW_H