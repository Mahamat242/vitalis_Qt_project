void consultationForm::loadPatient() {
  patient->clear();
  QSqlQuery query;
  query.prepare("SELECT num_ss, nom FROM Patient ORDER BY nom");

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
  query.prepare("SELECT code, libelle FROM Medicament ORDER BY libelle");

  if (query.exec()) {
    while (query.next()) {
      QString code = query.value(0).toString();
      QString libelle = query.value(1).toString();
      medicament->addItem(QString("%1 (%2)").arg(libelle, code), code);
    }
  }
}