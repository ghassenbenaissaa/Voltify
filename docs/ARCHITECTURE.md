# Architecture Technique - Voltify

## Vue d'ensemble

Voltify suit une architecture **modulaire à hub central** où le module `profil` agit comme point d'entrée de navigation, orchestrant l'affichage des différents modules métier via un `QStackedWidget`.

---

## Flux d'initialisation

```
Application Start
     │
     ▼
main.cpp
     │── Crée QApplication
     │── Instancie Connection (Singleton ODBC)
     │── Vérifie la connexion DB
     │── Affiche profil (Main Window)
     ▼
profil::profil()
     │── Instancie tous les modules (station, client, employee...)
     │── Insère chaque module dans le QStackedWidget
     │── Connecte les boutons de navigation aux slots
     ▼
[Application prête - en attente d'interaction utilisateur]
```

---

## Modules et responsabilités

### 1. Couche Présentation (UI)

| Module | Fichiers | Rôle |
|---|---|---|
| **profil** | profil.cpp/h, profil.ui | Hub de navigation, QStackedWidget (7 pages) |
| **station** | station.cpp/h, station.ui | Interface CRUD, onglets (Afficher, Ajouter, Chercher, Modifier, Supprimer) |
| **client** | client.cpp/h, client.ui | Saisie de consommation, affichage éco-mode |

Chaque module hérite de `QDialog` et est intégré dans le `QStackedWidget` du `profil` via `insertWidget()`.

### 2. Couche Métier (Business Logic)

**Station Module** (~1100 lignes) — Module principal contenant :

```
station.cpp
├── CRUD Operations
│   ├── Ajouter()         → INSERT avec bindValue()
│   ├── Modifier()        → UPDATE avec validation
│   ├── Suprimer()        → DELETE simple
│   └── Suprimer_P()      → DELETE multiple
│
├── Data Visualization
│   ├── statistique()     → Pie chart (répartition par type)
│   └── statistique2()    → Bar chart (consommation par station)
│
├── PDF Generation
│   └── generatePDF()     → Export PDF multi-colonnes
│
├── Arduino Communication
│   ├── capteur()         → Lecture capteur (timer 2s)
│   └── lcd()             → Écriture LCD (timer 3s)
│
├── Smart Alerts
│   └── proposition()     → Détection anomalies mensuelles
│
└── Search & Filter
    └── on_lineEdit_textChanged() → Filtrage dynamique SQL LIKE
```

**Client Module** — Logique éco-mode :

```
client.cpp
├── Verif()        → Vérifie limite 300 kWh/jour en mode Économique
├── Modifier()     → Met à jour consommation + profit + compteur charges
└── comboBox_id()  → Peuple la liste des stations depuis la DB
```

### 3. Couche Communication IoT

```
arduino.cpp
├── connect_arduino()     → Détection auto par VID:PID (9025:66)
├── read_from_arduino()   → Lecture QByteArray depuis port série
├── write_to_arduino()    → Envoi QByteArray vers Arduino
└── getserial()           → Accesseur QSerialPort*

Configuration série:
  Baud Rate: 9600 | Data Bits: 8 | Stop Bits: 1
  Parity: None    | Flow Control: None
```

### 4. Couche Données

```
dbmaneger.cpp (Connection)
├── Connection()     → Constructeur: configure driver ODBC + DSN
├── createconnect()  → Ouvre la connexion, retourne bool
└── getDB()          → Accesseur QSqlDatabase (Singleton)

DSN: "Source_Projet2A"
Driver: QODBC
```

---

## Diagramme de communication

```
┌─────────────┐        Signals/Slots        ┌──────────────┐
│   Arduino    │◄──── Serial (9600 baud) ───►│  station.cpp │
│   Mega 2560  │                              │              │
│  ┌─────────┐ │      capteur() [2s timer]   │  ┌────────┐  │
│  │ Capteur │─┼─────── état station ────────►│  │ Update │  │
│  └─────────┘ │                              │  │   DB   │  │
│  ┌─────────┐ │       lcd() [3s timer]      │  └────┬───┘  │
│  │   LCD   │◄┼──── kWh restant ────────────┤       │      │
│  └─────────┘ │                              │       ▼      │
└─────────────┘                              │  ┌────────┐  │
                                              │  │ Oracle │  │
┌─────────────┐     QSqlTableModel           │  │   DB   │  │
│  TableView  │◄─── Model-View binding ──────┤  └────────┘  │
│  (Qt Widget)│                              │              │
└─────────────┘                              └──────────────┘
```

---

## Machine à états — Station

```
                    ┌──────────┐
         capteur=2  │          │  capteur=1
        ┌──────────►│  Libre   ├──────────────┐
        │           │          │              │
        │           └────┬─────┘              ▼
        │                │              ┌──────────┐
   ┌────┴─────┐          │              │          │
   │          │          │              │ Occupé   │
   │ En repos │◄─────────┘              │          │
   │          │   éco-mode >= 300 kWh   └──────────┘
   └──────────┘
        ▲
        │  anomalie détectée
   ┌────┴─────┐
   │          │
   │ En panne │
   │          │
   └──────────┘
```

---

## Eco-Mode — Flux de décision

```
Nouvelle consommation demandée
         │
         ▼
    Mode == "Économique" ?
    ┌────┴────┐
   Non       Oui
    │         │
    ▼         ▼
 Accepter   CONJ_ST + nouvelle > 300 kWh ?
             ┌────┴────┐
            Non       Oui
             │         │
             ▼         ▼
          Accepter   Refuser
          Mettre à   Afficher reste
          jour DB    disponible
```

---

## Génération PDF — Pipeline

```
generatePDF()
     │
     ├── 1. Créer QPrinter (format A4, orientation paysage)
     │
     ├── 2. Initialiser QPainter sur le QPrinter
     │
     ├── 3. Dessiner en-tête
     │      ├── Logo gauche (loo.png)
     │      ├── Titre centré
     │      └── Logo droit (llll.png)
     │
     ├── 4. Dessiner en-têtes de colonnes (10 colonnes)
     │
     ├── 5. Itérer sur les lignes du modèle
     │      ├── Dessiner cellules avec drawText()
     │      └── Nouvelle page si dépassement
     │
     ├── 6. Dessiner pied de page
     │
     └── 7. Sauvegarder → ~/Desktop/stations.pdf
```

---

## Statistiques — Visualisation

### Pie Chart (répartition par type)

```sql
SELECT COUNT(*) FROM STATIONS WHERE TYPE_ST = :type
-- Pour chaque type: Tesla, Porsche, Toyota, Autre voiture
```

```
Résultat → QPieSeries → QChart → QChartView → grab() → QPixmap → QLabel
```

### Bar Chart (consommation par station)

```sql
SELECT ID_ST, SUM(CONSC_ST) FROM STATIONS
GROUP BY ID_ST ORDER BY SUM(CONSC_ST) DESC
```

```
Résultat → QBarSet (par station) → QBarSeries → QChart → QChartView → QPixmap → QLabel
```

---

## Technologies et patterns récapitulatifs

| Catégorie | Détail |
|---|---|
| **Langage** | C++11 (auto, lambda, range-for) |
| **Framework UI** | Qt 5 Widgets + Designer |
| **Pattern architectural** | Hub central + modules |
| **Pattern Singleton** | Connexion DB unique |
| **Pattern Model-View** | QSqlTableModel ↔ QTableView |
| **Pattern Observer** | Signals & Slots Qt |
| **Communication série** | QSerialPort (protocole custom) |
| **Base de données** | Oracle via ODBC, requêtes paramétrées |
| **Visualisation** | QtCharts (Pie + Bar) |
| **Export documents** | QPrinter + QPainter → PDF |
| **Gestion ressources** | QRC (icônes, sons, images) |
| **Timer-based polling** | QTimer pour temps réel |
