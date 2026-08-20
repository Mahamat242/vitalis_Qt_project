#include "ajoutMedicament.h"

FormMedicament::FormMedicament(QWidget *parent)
    : QWidget(parent)
{
    QFormLayout *formLayout = new QFormLayout();

    codeMedocEdit = new QLineEdit(this);
    codeMedocEdit->setPlaceholderText("Ex: MED001");

    libelleEdit = new QLineEdit(this);
    libelleEdit->setPlaceholderText("Ex: Paracétamol 500mg");

    saveButton = new QPushButton("Enregistrer le Médicament", this);

    formLayout->addRow("Code Médicament :", codeMedocEdit);
    formLayout->addRow("Libellé :", libelleEdit);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(saveButton);
    mainLayout->addStretch();

    setLayout(mainLayout);

    connect(saveButton, &QPushButton::clicked, this, &FormMedicament::saveMedicament);
}

void FormMedicament::saveMedicament()
{
    QString code = codeMedocEdit->text().trimmed();
    QString libelle = libelleEdit->text().trimmed();

    if (code.isEmpty() || libelle.isEmpty()) {
        QMessageBox::warning(this, "Saisie incomplète", "Veuillez remplir tous les champs.");
        return;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO Medicament (Code_medoc, Libelle) VALUES (:code, :libelle)");
    query.bindValue(":code", code);
    query.bindValue(":libelle", libelle);

    if (query.exec()) {
        QMessageBox::information(this, "Succès", "Médicament enregistré avec succès !");
        codeMedocEdit->clear();
        libelleEdit->clear();
    } else {
        QMessageBox::critical(this, "Erreur BDD", "Échec de l'enregistrement : " + query.lastError().text());
    }
}