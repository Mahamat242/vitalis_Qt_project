#include "historiquePatientForm.h"

HistoriquePatientsForm::HistoriquePatientsForm(QWidget *parent)
    : QWidget(parent) {
  setupUi();
  loadHistory();
}

void HistoriquePatientsForm::setupUi()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QLabel *titleLabel =  new QLabel("<h2>Historique des Consultations</h2>", this);
    mainLayout->addWidget(titleLabel);

    QHBoxLayout *searchLayout = new QHBoxLayout();
    QLabel *searchLabel = new QLabel("Rechercher (Nom ou N° SS) :", this);
    searchLineEdit = new QLineEdit(this);
    searchLineEdit->setPlaceholderText("Tapez un nom ou un numéro de sécurité sociale...");

    searchLayout->addWidget(searchLabel);
    searchLayout->addWidget(searchLineEdit);
    mainLayout->addLayout(searchLayout);

    historyTable = new QTableWidget(this);
    historyTable->setColumnCount(6);
    QStringList headers = {"Date", "Patient", "N° SS", "Médecin", "Diagnostic", "Médicament Prescrit"};
    historyTable->setHorizontalHeaderLabels(headers);

    // configuration de l'affichage de la table
    historyTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    historyTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    historyTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    historyTable->setAlternatingRowColors(true);

    mainLayout->addWidget(historyTable);

    connect(searchLineEdit, &QLineEdit::textChanged, this, &HistoriquePatientsForm::filterHistory);
}

void HistoriquePatientsForm::loadHistory(const QString &filter)
{
    historyTable->setRowCount(0);

    QSqlQuery query;
    QString sql = "select c.date, "
                "p.nom as patient_nom, "
                "p.num_ss, "
                "m.nom as medecin_nom, "
                "med.libelle "
                "from Consultation c "
                "join Patient p ON c.patient_num_ss = p.num_ss "
                "join Medecin m ON c.medecin_matricule = m.matricule "
                "left join Prescrit pr on c.numero = pr.consultation_num "
                "left join Medicament med on pr.medicament_code = med.code ";

    if (!filter.isEmpty())
    {
        sql += "where p.nom like :filter or p.prenom like :filter or CAST(p.num_ss AS CHAR) like :filter ";
    }

    sql += "order by c.date desc";

    query.prepare(sql);
    if (!filter.isEmpty())
    {
        query.bindValue(":filter", "%" + filter + "%");
    }

    if (query.exec())
    {
        int row = 0;
        while (query.next())
        {
            historyTable->insertRow(row);
            historyTable->setItem(row, 0, new QTableWidgetItem(query.value(0).toString()));
            historyTable->setItem(row, 1, new QTableWidgetItem(query.value(1).toString()));
            historyTable->setItem(row, 2, new QTableWidgetItem(query.value(2).toString()));
            historyTable->setItem(row, 3, new QTableWidgetItem(query.value(3).toString()));
            historyTable->setItem(row, 4, new QTableWidgetItem(query.value(4).toString()));
            historyTable->setItem(row, 5, new QTableWidgetItem(query.value(5).toString().isEmpty() ? "-": query.value(5).toString()));

            row++;
        }
    }else
    {
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