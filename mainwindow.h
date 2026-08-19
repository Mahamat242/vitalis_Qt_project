#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include "consultationform.h"


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
    ConsultationForm *consultationPage;

    QPushButton *btnConsultation;
};

#endif // MAINWINDOW_H
