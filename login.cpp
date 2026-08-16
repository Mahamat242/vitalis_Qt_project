#include "login.h"

login::login(QWidget *parent) : QDialog(parent) {
  setWindowTitle("Vitalis - login");
  setFixedSize(320, 220);

  // création des composants du formulmaire d'authentification
  QLabel *title = new QLabel("<h2>Vitalis</h2><p>Veuillez vous identifier</p>");
  title->setAlignment(Qt::AlignCenter);

  loginEdit = new QLineEdit(this);
  loginEdit->setPlaceholderText("identifiant");

  pwdEdit = new QLineEdit(this);
  pwdEdit->setPlaceholderText("mot de passe");
  pwdEdit->setEchoMode(QLineEdit::Password);

  loginButton = new QPushButton("Se connecter", this);
  cancelButton = new QPushButton("Annuler", this);

  // configuration de la disposition
  QVBoxLayout *mainLayout = new QVBoxLayout(this);
  QHBoxLayout *btnLayout = new QHBoxLayout();

  btnLayout->addWidget(loginButton);
  btnLayout->addWidget(cancelButton);

  mainLayout->addWidget(title);
  mainLayout->addWidget(loginEdit);
  mainLayout->addWidget(pwdEdit);
  mainLayout->addLayout(btnLayout);

  setLayout(mainLayout);

  // connexion des signaux aux slots
  connect(loginButton, &QPushButton::clicked, this, &login::login_func);
  connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

void login::login_func() {
  QString username = loginEdit->text().trimmed();
  QString password = pwdEdit->text();

  if (username.isEmpty() || password.isEmpty()) {
    QMessageBox::warning(this, "champs requis",
                         "Veuillez remplir tous les champs !");
    return;
  }

  QSqlQuery query;
  query.prepare("select * from Utilisateur where login = :login and password = "
                ":password");
  query.bindValue(":login", username);
  query.bindValue(":password", password);

  if (query.exec() && query.next()) {
    accept();
  } else {
    QMessageBox::critical(this, "échec de la connexion",
                          "Identifiant ou mot de passe incorrect !");
    pwdEdit->clear();
  }
}