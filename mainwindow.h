#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ajoutMedecin.h"
#include "ajoutPatient.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private :
    FormMedecin *formMedecin;
    FormPatient *formPatient;
};
#endif // MAINWINDOW_H
