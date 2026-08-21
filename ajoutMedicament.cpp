#include "ajoutMedicament.h"

FormMedicament::FormMedicament(QWidget *parent)
    : QWidget(parent)
{
    QFormLayout *formLayout = new QFormLayout();

    codeMedocEdit = new QLineEdit(this);
    codeMedocEdit->setPlaceholderText("Ex: MED001");

    libelleEdit = new QLineEdit(this);
    libelleEdit->setPlaceholderText("Ex: Paracétamol 500mg");

    indicationsEdit = new QLineEdit(this);
    indicationsEdit->setPlaceholderText("Ex: Fièvre, douleurs");

    posologieEdit = new QLineEdit(this);
    posologieEdit->setPlaceholderText("Ex: 1 comprimé toutes les 6h");

    saveButton = new QPushButton("Enregistrer le Médicament", this);

    formLayout->addRow("Code Médicament :", codeMedocEdit);
    formLayout->addRow("Libellé :", libelleEdit);
    formLayout->addRow("Indications :", indicationsEdit);
    formLayout->addRow("Posologie :", posologieEdit);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(saveButton);
    mainLayout->addStretch();

    setLayout(mainLayout);

    connect(saveButton, &QPushButton::clicked, this, &FormMedicament::saveMedicament);
}

void FormMedicament::saveMedicament()
{
    QString code    = codeMedocEdit->text().trimmed();
    QString libelle = libelleEdit->text().trimmed();

    if (code.isEmpty() || libelle.isEmpty()) {
        QMessageBox::warning(this, "Saisie incomplète", "Le code et le libellé sont obligatoires.");
        return;
    }

    QString indications = indicationsEdit->text().trimmed();
    QString posologie   = posologieEdit->text().trimmed();

    QSqlQuery query;
    query.prepare("INSERT INTO Medicament (code, libelle, indications, posologie) "
                  "VALUES (:code, :libelle, :indications, :posologie)");
    query.bindValue(":code",        code);
    query.bindValue(":libelle",     libelle);
    query.bindValue(":indications", indications.isEmpty() ? QVariant() : indications);
    query.bindValue(":posologie",   posologie.isEmpty()   ? QVariant() : posologie);

    if (query.exec()) {
        QMessageBox::information(this, "Succès", "Médicament enregistré avec succès !");
        codeMedocEdit->clear();
        libelleEdit->clear();
        indicationsEdit->clear();
        posologieEdit->clear();
    } else {
        QMessageBox::critical(this, "Erreur BDD", "Échec de l'enregistrement : " + query.lastError().text());
    }
}