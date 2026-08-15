# 🏥 Vitalis – Gestion des consultations médicales

## 📖 Description
Ce projet est un mini-projet en **C++ avec Qt** visant à développer une application de gestion des consultations dans un centre médical.  
Il permet de gérer les médecins, les patients, les médicaments et l’historique des consultations, avec une base de données **MySQL** déployée dans un conteneur **Docker**.

---

## ✨ Fonctionnalités
- 🔐 **Authentification** : connexion avec login et mot de passe
- 👨‍⚕️ **Gestion des médecins** : ajout et visualisation
- 🧑‍⚕️ **Gestion des patients** : ajout et visualisation
- 💊 **Gestion des médicaments** : ajout et visualisation
- 📅 **Consultations** :
  - Enregistrement des informations (date, motif, médecin, patient, médicaments prescrits)
  - Historique des consultations par patient
  - Détails complets d’une consultation

---

## 🛠️ Technologies utilisées
- **Langage** : C++  
- **Framework** : Qt6 (Widgets, Core)  
- **IDE** : Qt Creator  
- **Base de données** : MySQL (conteneurisé avec Docker)  
- **Conteneurisation** : Docker / Docker Compose  

---

## 🚀 Installation & Initialisation

### 1. Cloner le dépôt
```bash
git clone https://github.com/Mahamat242/vitalis_Qt_project.git
cd vitalis_Qt_project
```
### 2. lancer docker desktop si sur windows
### 3. lancer les services docker

```bash
docker compose up -d
