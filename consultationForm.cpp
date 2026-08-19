#include "consultationForm.h"

consultationForm::consultationForm(QWidget *parent) : QWidget(parent) {
  QVBoxLayout *mainLayout = new QVBoxLayout(this);

  QLabel *title = new QLabel("<h2>Enregistrer une consultation</h2>", this);
  mainLayout->addWidget(title);

  // formulaire sur les infos d'une consultation
  QFormLayout *formLayout = new QFormLayout();

  medecin = new QComboBox(this);
  patient = new QComboBox(this);
  dateEdit = new QDateEdit(QDate::currentDate(), this);
  dateEdit->setCalendarPopup(true);
  dateEdit->setDisplayFormat("dd-MM-yyyy");

  formLayout->addRow("Médicin :", medecin);
  formLayout->addRow("Patient :", patient);
  formLayout->addRow("Date :", dateEdit);

  mainLayout->addLayout(formLayout);

  // section pour la prescription des medocs
  QLabel *prescTitle =
      new QLabel("<h3>Ordonnance ou médicaments prescrits</h3>", this);
  mainLayout->addWidget(prescTitle);

  QHBoxLayout *medocLayout = new QHBoxLayout();
  medicament = new QComboBox(this);
  nbJours = new QSpinBox(this);
  nbJours->setRange(1, 365);
  nbJours->setSuffix(" Jour(s)");
  nbJours->setValue(7);

  addMedocButton = new QPushButton("Ajouter à l'ordonnance", this);

  medocLayout->addWidget(new QLabel("Médicament :", this));
  medocLayout->addWidget(medicament, 1);
  medocLayout->addWidget(new QLabel("Durée :", this));
  medocLayout->addWidget(nbJours);
  medocLayout->addWidget(addMedocButton);

  mainLayout->addLayout(medocLayout);

  // tableau de prévisualisation des médocs ajoutés
  prescriptionTable = new QTableWidget(0, 3, this);
  prescriptionTable->setHorizontalHeaderLabels(
      {"code", "Médicament", "Nombre de jours"});
  prescriptionTable->horizontalHeader()->setSectionResizeMode(
      QHeaderView::Stretch);
  prescriptionTable->setMaximumHeight(150);

  mainLayout->addWidget(prescriptionTable);

  // boutton pour retirer un medoc du tableau
  QPushButton *removeMedocButton =
      new QPushButton("Retirer le médicament sélectionné");
  mainLayout->addWidget(removeMedocButton);

  // button enregistrer
  save = new QPushButton("valider et enregistrer la consultation", this);
  save->setStyleSheet("font-weight : bold; padding: 8px");
  mainLayout->addWidget(save);

  // connexions
  connect(addMedocButton, &QPushButton::clicked, this,
          &consultationForm::addMedicamentToPrescription);
  connect(removeMedocButton, &QPushButton::clicked, this,
          &consultationForm::removeMedoc);
  connect(save, &QPushButton::clicked, this,
          &consultationForm::saveConsultation);

  // charger les données de la base de donnée
  refreshData();
}

void consultationForm::refreshData() {
  loadMedecin();
  loadPatient();
  loadMedicament();
}

void consultationForm::loadMedecin() {
  medecin->clear();
  QSqlQuery query;
  query.prepare("select matricule, nom from Medecin order by nom");

  while (query.next()) {
    int matricule = query.value(0).toInt();
    QString nom = query.value(1).toString();
    // on stocke le matricule comme QVariant
    medecin->addItem(QString("Dr. %1 (Matricule : %2)").arg(nom).arg(matricule),
                     matricule);
  }
}

void consultationForm::loadPatient() {
  patient->clear();
  QSqlQuery query;
  query.prepare("select num_ss, nom from Patient order by nom");

  if (query.exec()) {
    while (query.next()) {
      int num_ss = query.value(0).toInt();
      QString nom = query.value(1).toString();
      patient->addItem(QString("%1 (N° SS : %2)").arg(nom).arg(num_ss), num_ss);
    }
  }
}

void consultationForm::loadMedicament() {
  medicament->clear();
  QSqlQuery query;
  query.prepare("select code, libelle from Medicament order by libelle");

  if (query.exec()) {
    while (query.next()) {
      QString code = query.value(0).toString();
      QString libelle = query.value(1).toString();
      medicament->addItem(QString("%1 (%2)").arg(libelle, code), code);
    }
  }
}

void consultationForm::addMedicamentToPrescription() {
  if (medicament->currentIndex() == -1)
    return;

  QString libelle = medicament->currentText();
  QString code = medicament->currentData().toString();
  int nb_jours = nbJours->value();

  // vérifier si le medoc est déjà dans la table
  for (int i = 0; i < prescriptionTable->rowCount(); ++i) {
    if (prescriptionTable->item(i, 0)->text() == code) {
      QMessageBox::warning(this, "Doublon",
                           "Ce médicament est déjà présent dans l'ordonnance");
      return;
    }
  }

  int row = prescriptionTable->rowCount();
  prescriptionTable->insertRow(row);
  prescriptionTable->setItem(row, 0, new QTableWidgetItem(code));
  prescriptionTable->setItem(row, 1, new QTableWidgetItem(libelle));
  prescriptionTable->setItem(row, 2,
                             new QTableWidgetItem(QString::number(nb_jours)));
}

void consultationForm::removeMedoc() {
  int currentRow = prescriptionTable->currentRow();
  if (currentRow >= 0) {
    prescriptionTable->removeRow(currentRow);
  } else {
    QMessageBox::warning(this, "Sélection requise",
                         "Veuillez sélectionner une ligne à retirer.");
  }
}

void consultationForm::saveConsultation() {
  if (medecin->currentIndex() == -1 || patient->currentIndex() == -1) {
    QMessageBox::warning(this, "Incomplet",
                         "un médecin et un patient doivent être sélectionner.");
    return;
  }

  int matMedecin = medecin->currentData().toInt();
  int num_ssPatient = patient->currentData().toInt();
  QString date = dateEdit->date().toString("dd-MM-yyyy");

  QSqlDatabase db = QSqlDatabase::database();
  db.transaction();

  // insertion dans la table des consultations
  QSqlQuery query;
  query.prepare("insert into Consultation (date, medecin_matricule, "
                "patient_num_ss) values (:date, :medecin, :patient)");
  query.bindValue(":date", date);
  query.bindValue(":medecin", matMedecin);
  query.bindValue(":patient", num_ssPatient);

  if (!query.exec()) {
    db.rollback();
    QMessageBox::critical(this, "Erreur BD",
                          "Imposssible d'enregistrer la consultation : " +
                              query.lastError().text());
    return;
  }

  int numeroConsultation = query.lastInsertId().toInt();

  // insertion des medocs associées dans prescrit
  QSqlQuery prescQuery;
  prescQuery.prepare(
      "insert into Prescrit (medicament_code, consultation_num, nombre_jours) "
      "values (:code_medoc, :consult_num, :nb_jours)");

  for (int i = 0; i < prescriptionTable->rowCount(); ++i) {
    QString codeMedoc = prescriptionTable->item(i, 0)->text();
    int nbJours = prescriptionTable->item(i, 2)->text().toInt();

    prescQuery.bindValue(":code_medoc", codeMedoc);
    prescQuery.bindValue(":consult_num", numeroConsultation);
    prescQuery.bindValue(":nb_jours", nbJours);

    if (!prescQuery.exec()) {
      db.rollback();
      QMessageBox::critical(this, "Erreur BD",
                            "Erreur lors de la sauvegarde de l'ordonnance : " +
                                prescQuery.lastError().text());
      return;
    }
  }

  // valider la sauvegard si tout est ok
  db.commit();
  QMessageBox::information(
      this, "Succèes",
      QString("Consultaiton N°%1 enregistrée avec succès !")
          .arg(numeroConsultation));

  // réinitialisation du formulaire
  prescriptionTable->setRowCount(0);
}
