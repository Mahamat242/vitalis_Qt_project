create DATABASE IF NOT EXISTS vitalis_db;
use vitalis_db;

-- table utilisateur pour la page d'authentification
create table if not exists Utilisateur(
    id int auto_increment primary key,
    login varchar(45) unique not null,
    password varchar(255) not null
);

insert into Utilisateur (login, password) values ('mahamat', 'mahamat@admin')
on duplicate key update login=login;

insert into Utilisateur (login, password) values ('diariou', 'diariou@admin')
on duplicate key update login=login;

-- table médecin
create table if not exists Medecin(
    matricule int auto_increment primary key,
    nom varchar(45) not null
);

-- table patient
create table if not exists Patient(
    num_ss int auto_increment primary key,
    nom varchar(45) not null
);

-- table consulte
create table if not exists Consulte(
    medecin_matricule int,
    patient_num_ss int,
    primary key (medecin_matricule, patient_num_ss),
    foreign key (medecin_matricule) references Medecin(matricule) on delete cascade,
    foreign key (patient_num_ss) references Patient(num_ss) on delete cascade
);

-- table consultation
create table if not exists Consultation(
    numero int auto_increment primary key,
    date Date not null,
    medecin_matricule int not null,
    patient_num_ss int not null,
    foreign key (medecin_matricule) references Medecin(matricule),
    foreign key (patient_num_ss) references Patient(num_ss)
);

-- table médicament
create table if not exists Medicament(
    code varchar(6) primary key,
    libelle varchar(45) not null,
    indications varchar(45),
    posologie varchar(45)
);

-- table prescrit
create table if not exists Prescrit(
    medicament_code varchar(6),
    consultation_num int,
    nombre_jours int,
    primary key (medicament_code, consultation_num),
    foreign key (medicament_code) references Medicament(code) on delete cascade,
    foreign key (consultation_num) references Consultation(numero) on delete cascade
);