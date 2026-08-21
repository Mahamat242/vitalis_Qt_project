#ifndef AJOUTMEDICAMENT_H
#define AJOUTMEDICAMENT_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

class FormMedicament : public QWidget
{
    Q_OBJECT

public:
    explicit FormMedicament(QWidget *parent = nullptr);

private slots:
    void saveMedicament();

private:
    QLineEdit *codeMedocEdit;
    QLineEdit *libelleEdit;
    QLineEdit *indicationsEdit;
    QLineEdit *posologieEdit;
    QPushButton *saveButton;
};

#endif // AJOUTMEDICAMENT_H