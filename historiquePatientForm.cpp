#include "historiquepatientsform.h"

HistoriquePatientsForm::HistoriquePatientsForm(QWidget *parent)
    : QWidget(parent) {
  setupUi();
  loadHistory();
}

void HistoriquePatientsForm::setupUi() {
  QVBoxLayout *mainLayout = new QVBoxLayout(this);

  // Titre de la page
  QLabel *titleLabel =
      new QLabel("<h2>Historique des Consultations</h2>", this);
  mainLayout->addWidget(titleLabel);

  // Zone de recherche
  QHBoxLayout *searchLayout = new QHBoxLayout();
  QLabel *searchLabel = new QLabel("Rechercher (Nom ou N° SS) :", this);
  searchLineEdit = new QLineEdit(this);
  searchLineEdit->setPlaceholderText(
      "Tapez un nom ou un numéro de sécurité sociale...");

  searchLayout->addWidget(searchLabel);
  searchLayout->addWidget(searchLineEdit);
  mainLayout->addLayout(searchLayout);

  // Tableau des résultats
  historyTable = new QTableWidget(this);
  historyTable->setColumnCount(6);
  QStringList headers = {"Date",    "Patient",    "N° SS",
                         "Médecin", "Diagnostic", "Médicament Prescrit"};
  historyTable->setHorizontalHeaderLabels(headers);

  // Configuration de l'affichage de la table
  historyTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  historyTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
  historyTable->setSelectionBehavior(QAbstractItemView::SelectRows);
  historyTable->setAlternatingRowColors(true);

  mainLayout->addWidget(historyTable);

  // Signal de recherche en temps réel
  connect(searchLineEdit, &QLineEdit::textChanged, this,
          &HistoriquePatientsForm::filterHistory);
}

void HistoriquePatientsForm::loadHistory(const QString &filter) {
  historyTable->setRowCount(0);

  QSqlQuery query;
  QString sql = "SELECT c.date_consultation, "
                "p.nom || ' ' || p.prenom AS patient_nom, "
                "p.num_ss, "
                "m.nom || ' ' || m.prenom AS medecin_nom, "
                "c.diagnostic, "
                "med.libelle "
                "FROM Consultation c "
                "JOIN Patient p ON c.id_patient = p.id "
                "JOIN Medecin m ON c.id_medecin = m.id "
                "LEFT JOIN Prescription pr ON c.id = pr.id_consultation "
                "LEFT JOIN Medicament med ON pr.id_medicament = med.id ";

  if (!filter.isEmpty()) {
    sql += "WHERE p.nom LIKE :filter OR p.prenom LIKE :filter OR CAST(p.num_ss "
           "AS TEXT) LIKE :filter ";
  }

  sql += "ORDER BY c.date_consultation DESC";

  query.prepare(sql);
  if (!filter.isEmpty()) {
    query.bindValue(":filter", "%" + filter + "%");
  }

  if (query.exec()) {
    int row = 0;
    while (query.next()) {
      historyTable->insertRow(row);

      historyTable->setItem(row, 0,
                            new QTableWidgetItem(query.value(0).toString()));
      historyTable->setItem(row, 1,
                            new QTableWidgetItem(query.value(1).toString()));
      historyTable->setItem(row, 2,
                            new QTableWidgetItem(query.value(2).toString()));
      historyTable->setItem(row, 3,
                            new QTableWidgetItem(query.value(3).toString()));
      historyTable->setItem(row, 4,
                            new QTableWidgetItem(query.value(4).toString()));
      historyTable->setItem(
          row, 5,
          new QTableWidgetItem(query.value(5).toString().isEmpty()
                                   ? "-"
                                   : query.value(5).toString()));

      row++;
    }
  } else {
    qDebug() << "Erreur de chargement de l'historique :"
             << query.lastError().text();
  }
}

void HistoriquePatientsForm::filterHistory(const QString &text) {
  loadHistory(text);
}

void HistoriquePatientsForm::refreshData() {
  searchLineEdit->clear();
  loadHistory();
}