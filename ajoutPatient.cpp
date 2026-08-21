#include "ajoutPatient.h"

FormPatient::FormPatient(QWidget *parent): QWidget(parent)
{
    QFormLayout *formLayout = new QFormLayout();

    numPatientEdit = new QLineEdit(this);
    numPatientEdit->setPlaceholderText("Ex:1984104");

    nomEdit = new QLineEdit(this);
    nomEdit->setPlaceholderText("Ex: Mahamat Haroun ");

    saveButton = new QPushButton("Enregistrer le Patient", this);

    formLayout->addRow("N° Sécurité Sociale :",numPatientEdit);
    formLayout->addRow("Prénom et Nom du Patient",nomEdit);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(saveButton);
    mainLayout->addStretch();

    setLayout(mainLayout);

    connect(saveButton, &QPushButton::clicked,this,&FormPatient::savePatient);
}

void FormPatient::savePatient()
{
    QString numPatientStr = numPatientEdit->text().trimmed();
    QString nom = nomEdit->text().trimmed();

    if(numPatientStr.isEmpty() || nom.isEmpty())
    {
        QMessageBox::warning(this,"Saisie incomplète","Veuillez remplir tous les champs.");
        return;
    }

    bool ok;
    int numPatient=numPatientStr.toInt(&ok);
    if(!ok)
    {
        QMessageBox::warning(this,"Format incorrect","Le numéro de Sécurité Sociale doit être un nombre.");
        return;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO Patient (num_ss, nom) VALUES (:num, :nom)");
    query.bindValue(":num", numPatient);
    query.bindValue(":nom", nom);

    if(query.exec())
    {
        QMessageBox::information(this, "Succès","Patient enregistré avec succès!");
        numPatientEdit->clear();
        nomEdit->clear();
    }
    else
    {
        QMessageBox::critical(this,"Erreur BDD", "Echec de l'enregistrement:" + query.lastError().text());
    }
}

