#include "historiquePatientForm.h"

HistoriquePatientsForm::HistoriquePatientsForm(QWidget *parent)
    : QWidget(parent)
{
    setupUi();
    loadHistory();
}

void HistoriquePatientsForm::setupUi()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Titre de la page
    QLabel *titleLabel = new QLabel("<h2>Historique des Consultations</h2>", this);
    mainLayout->addWidget(titleLabel);

    // Zone de recherche
    QHBoxLayout *searchLayout = new QHBoxLayout();
    QLabel *searchLabel = new QLabel("Rechercher (Nom patient ou N° SS) :", this);
    searchLineEdit = new QLineEdit(this);
    searchLineEdit->setPlaceholderText("Tapez un nom ou un numéro de sécurité sociale...");

    searchLayout->addWidget(searchLabel);
    searchLayout->addWidget(searchLineEdit);
    mainLayout->addLayout(searchLayout);

    // Tableau des résultats — colonnes adaptées au vrai schéma
    historyTable = new QTableWidget(this);
    historyTable->setColumnCount(5);
    QStringList headers = {"Date", "Patient (N° SS)", "Médecin", "N° Consultation", "Médicaments prescrits"};
    historyTable->setHorizontalHeaderLabels(headers);

    // Configuration de l'affichage de la table
    historyTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    historyTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    historyTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    historyTable->setAlternatingRowColors(true);

    mainLayout->addWidget(historyTable);

    // Signal de recherche en temps réel
    connect(searchLineEdit, &QLineEdit::textChanged, this, &HistoriquePatientsForm::filterHistory);
}

void HistoriquePatientsForm::loadHistory(const QString &filter)
{
    historyTable->setRowCount(0);
    QString sql = "SELECT c.date, "
      "  CONCAT(p.nom, ' (N°SS: ', p.num_ss, ')') AS patient, "
      "  CONCAT('Dr. ', m.nom, ' (Mat: ', m.matricule, ')') AS medecin, "
      "  c.numero, "
      "  IFNULL(GROUP_CONCAT(CONCAT(med.libelle, ' — ', pr.nombre_jours, ' j') "
      "         ORDER BY med.libelle SEPARATOR ' | '), '-') AS medicaments "
      "FROM Consultation c "
      "JOIN Patient p ON c.patient_num_ss = p.num_ss "
      "JOIN Medecin m ON c.medecin_matricule = m.matricule "
      "LEFT JOIN Prescrit pr ON c.numero = pr.consultation_num "
      "LEFT JOIN Medicament med ON pr.medicament_code = med.code ";

    if (!filter.isEmpty())
    {
        sql += "WHERE p.nom LIKE :filter OR CAST(p.num_ss AS CHAR) LIKE :filter ";
    }

    sql += "GROUP BY c.numero, c.date, p.nom, p.num_ss, m.nom, m.matricule "
         "ORDER BY c.date DESC, c.numero DESC";

    QSqlQuery query;
    query.prepare(sql);
    if (!filter.isEmpty())
    {
        query.bindValue(":filter", "%" + filter + "%");
    }

    if (query.exec())
    {
        int row = 0;
        while (query.next()) {
        historyTable->insertRow(row);
        historyTable->setItem(row, 0, new QTableWidgetItem(query.value(0).toString())); // date
        historyTable->setItem(row, 1, new QTableWidgetItem(query.value(1).toString())); // patient
        historyTable->setItem(row, 2, new QTableWidgetItem(query.value(2).toString())); // médecin
        historyTable->setItem(row, 3, new QTableWidgetItem(query.value(3).toString())); // n° consultation
        historyTable->setItem(row, 4, new QTableWidgetItem(query.value(4).toString())); // médicaments
        row++;
    }
    } else {
        qDebug() << "Erreur de chargement de l'historique :" << query.lastError().text();
    }
}

void HistoriquePatientsForm::filterHistory(const QString &text)
{
    loadHistory(text);
}

void HistoriquePatientsForm::refreshData()
{
    searchLineEdit->clear();
    loadHistory();
}