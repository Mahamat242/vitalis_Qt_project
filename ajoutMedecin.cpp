#include"ajoutMedecin.h"
FormMedecin::FormMedecin(QWidget *parent):QWidget(parent)
{
    QFormLayout *formLayout = new QFormLayout();

    matriculeEdit =new QLineEdit(this);
    matriculeEdit->setPlaceholderText("Ex:1002");

    nomEdit =new QLineEdit(this);
    nomEdit->setPlaceholderText("Ex:Dr. DIALLO");

    saveButton =new QPushButton("Enregistrer le médecin",this);
    saveButton->setProperty("class", "btnPrimary");

    formLayout->addRow("Matricule :",matriculeEdit);
    formLayout->addRow("Nom du médecin :",nomEdit);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(saveButton);
    mainLayout->addStretch();

    setLayout(mainLayout);

    connect(saveButton, &QPushButton::clicked,this,&FormMedecin::saveMedecin);
}

void FormMedecin::saveMedecin()
{
    QString matriculeStr = matriculeEdit->text().trimmed();
    QString nom = nomEdit->text().trimmed();

    if(matriculeStr.isEmpty() || nom.isEmpty())
    {
        QMessageBox::warning(this,"Saisie incomplète","Veuillez remplir tous les champs.");
        return;
    }

    bool ok;
    int matricule=matriculeStr.toInt(&ok);
    if(!ok)
    {
        QMessageBox::warning(this,"Format incorrect","Le matricule doit être un nombre.");
        return;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO Medecin(Matricule,Nom) VALUES (:mat, :nom)");
    query.bindValue(":mat", matricule);
    query.bindValue(":nom", nom);

    if(query.exec())
    {
        QMessageBox::information(this, "Succès","Medecin enregistré avec succès!");
        matriculeEdit->clear();
        nomEdit->clear();
    }
    else
    {
        QMessageBox::critical(this,"Erreur BDD", "Echec de l'enregistrement:" + query.lastError().text());
    }
}