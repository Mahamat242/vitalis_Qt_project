#ifndef AJOUTMEDECIN_H
#define AJOUTMEDECIN_H

#include<QWidget>
#include<QLineEdit>
#include<QPushButton>
#include<QFormLayout>
#include<QSqlQuery>
#include<QSqlError>
#include<QMessageBox>

class FormMedecin : public QWidget
{
    Q_OBJECT

public :
    explicit FormMedecin(QWidget *parent = nullptr);
private slots:
        void saveMedecin();
private :
    QLineEdit *matriculeEdit;
    QLineEdit *nomEdit;
    QPushButton *saveButton;

};
#endif//AJOUTMEDECIN_H
