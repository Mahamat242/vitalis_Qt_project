#ifndef HISTORIQUEPATIENTSFORM_H
#define HISTORIQUEPATIENTSFORM_H

#include <QDebug>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QSqlError>
#include <QSqlQuery>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QWidget>


class HistoriquePatientsForm : public QWidget {
  Q_OBJECT

    public:
      explicit HistoriquePatientsForm(QWidget *parent = nullptr);
      void refreshData();

    private slots:
      void filterHistory(const QString &text);

    private:
      QLineEdit *searchLineEdit;
      QTableWidget *historyTable;

      void setupUi();
      void loadHistory(const QString &filter = "");
};

#endif // HISTORIQUEPATIENTSFORM_H