#ifndef AJOUTPATIENT_H
#define AJOUTPATIENT_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

class FormPatient : public QWidget
{
    Q_OBJECT

public :
    explicit FormPatient(QWidget *parent = nullptr);

private slots:
    void savePatient();
private:
    QLineEdit *numPatientEdit;
    QLineEdit *nomEdit;
    QPushButton *saveButton;
};
#endif