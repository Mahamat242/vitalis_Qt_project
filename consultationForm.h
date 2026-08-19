#ifndef CONSULTATIONFORM_H
#define CONSULTATIONFORM_H

#include <QWidget>
#include <QComboBox>
#include <QDateEdit>
#include <QTextEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QLabel>
#include <QHeaderView>

class consultationForm : public QWidget
{
    Q_OBJECT

    public :
        explicit consultationForm(QWidget *parent = nullptr);

        void refreshData(); // pour pouvoir raffraîchir les listes

    private slots:
        void addMedicamentToPrescription();
        void removeMedoc();
        void saveConsultation();

    private :
        void loadMedecin();
        void loadPatient();
        void loadMedicament();

        // les champs principaux
        QComboBox *medecin;
        QComboBox *patient;
        QDateEdit *dateEdit;
        QTextEdit *motifEdit;

        // pour les medocs et l'ordonnance
        QComboBox *medicament;
        QSpinBox *nbJours;
        QPushButton *addMedocButton;
        QTableWidget *prescriptionTable;

        QPushButton *save;
};

#endif // CONSULTATIONFORM_H
