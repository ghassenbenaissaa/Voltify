# Rapport Technique - Voltify

## 1. Introduction

### 1.1 Contexte du projet

Voltify est une application desktop de gestion de bornes de recharge pour véhicules électriques, développée dans le cadre d'un projet académique à ESPRIT. Le projet combine programmation orientée objet en C++, développement d'interfaces graphiques avec Qt, communication IoT avec Arduino, et gestion de bases de données Oracle.

### 1.2 Objectifs

- Concevoir une application de gestion complète (CRUD) pour les bornes de recharge
- Intégrer une communication temps réel avec du matériel Arduino
- Implémenter un système intelligent de gestion d'énergie (Eco-Mode)
- Fournir des outils d'analyse et de reporting (graphiques, PDF)
- Mettre en place un système d'alertes prédictives basé sur la consommation

---

## 2. Compétences techniques mises en oeuvre

### 2.1 Programmation C++11

| Compétence | Mise en application |
|---|---|
| **Programmation Orientée Objet** | Classes avec encapsulation (station, client, arduino), héritage (QDialog, QMainWindow) |
| **Gestion mémoire** | Allocation dynamique (new/delete) pour les charts et pixmaps |
| **STL & Types modernes** | QString, QByteArray, QDate pour la manipulation de données |
| **Signals & Slots** | Mécanisme de callback type-safe propre à Qt (connect/slot) |

### 2.2 Framework Qt 5

**8 modules Qt** intégrés dans un seul projet :

| Module | Utilisation concrète |
|---|---|
| `QtCore` | QObject, QTimer, QDate, QByteArray |
| `QtGui` | QPainter, QPixmap, QFont, QColor |
| `QtWidgets` | QMainWindow, QDialog, QStackedWidget, QTabWidget, QTableView, QComboBox |
| `QtSql` | QSqlDatabase, QSqlQuery, QSqlTableModel, QSqlQueryModel |
| `QtCharts` | QChart, QPieSeries, QBarSeries, QChartView, QValueAxis |
| `QtSerialPort` | QSerialPort, QSerialPortInfo |
| `QtPrintSupport` | QPrinter, QPdfWriter |
| `QtMultimedia` | Support audio pour les notifications |

### 2.3 Base de données Oracle (ODBC)

```cpp
// Connexion Singleton via ODBC
db.setDatabaseName("Source_Projet2A");  // DSN Oracle
db.setUserName("system");
db.setPassword("esprit");
```

**Opérations SQL implémentées** :

- `INSERT INTO` avec paramètres liés (`bindValue`) — protection injection SQL
- `UPDATE` avec validation des champs avant exécution
- `DELETE` simple et en lot avec confirmation utilisateur
- `SELECT` avec `GROUP BY`, `SUM()`, `ORDER BY` pour les statistiques
- `LIKE` avec wildcards pour le filtrage dynamique

### 2.4 Communication série Arduino

**Protocole implémenté** :

```
Direction PC → Arduino:
  - Envoi de la valeur kWh restante (texte ASCII)
  - Affiché sur écran LCD connecté à l'Arduino

Direction Arduino → PC:
  - Lecture capteur: "1" = Occupé, "2" = Libre
  - Polling toutes les 2 secondes via QTimer
```

**Détection automatique du matériel** :

```cpp
// Scan de tous les ports série disponibles
foreach(const QSerialPortInfo &port, QSerialPortInfo::availablePorts()) {
    if (port.hasVendorIdentifier() && port.hasProductIdentifier()) {
        if (port.vendorIdentifier() == 9025 && port.productIdentifier() == 66) {
            // Arduino Mega détecté
        }
    }
}
```

### 2.5 Visualisation de données

**Pie Chart** — Répartition des stations par type de véhicule :

- Requêtes `COUNT(*)` groupées par `TYPE_ST`
- Rendu via `QPieSeries` avec labels et pourcentages
- Conversion `QChartView` → `QPixmap` pour affichage dans `QLabel`

**Bar Chart** — Consommation cumulée par station :

- Requête `SUM(CONSC_ST) GROUP BY ID_ST ORDER BY DESC`
- Rendu via `QBarSeries` avec axes personnalisés (`QValueAxis`)
- Mise à jour dynamique après chaque opération CRUD

### 2.6 Génération de documents PDF

```cpp
QPrinter printer;
printer.setOutputFormat(QPrinter::PdfFormat);
printer.setOutputFileName(path + "/stations.pdf");

QPainter painter(&printer);
// Dessin de l'en-tête, du tableau de données, et du pied de page
// Gestion automatique des sauts de page
```

- Export au format A4 avec mise en page tabulaire
- En-tête avec logos et horodatage
- Itération sur le modèle de données pour remplir les lignes
- Sauvegarde automatique sur le Bureau de l'utilisateur

### 2.7 Algorithme Eco-Mode

L'Eco-Mode est un système de gestion d'énergie intelligent :

```
Algorithme Verif():
  1. Lire MODE_ST de la station sélectionnée
  2. Si MODE_ST == "Economique":
     a. Calculer total = CONJ_ST (consommation du jour)
     b. reste = 300 - total
     c. Si nouvelle_consommation > reste:
        → Refuser la charge
        → Afficher "Reste disponible: {reste} kWh"
     d. Sinon:
        → Accepter et mettre à jour:
           CONJ_ST += nouvelle_consommation
           CONSC_ST += nouvelle_consommation
           PROFIT_ST = CONSC_ST * PRIX_KW_ST
           NBR_CHARGE_ST += 1
        → Si CONJ_ST >= 300: ETAT_ST = "En repos"
  3. Si MODE_ST != "Economique":
     → Accepter sans limite
```

### 2.8 Système d'alertes prédictives

```
Algorithme proposition():
  Pour chaque station dans la DB:
    Si jour_du_mois > 5:
      Si CONSM_ST < 300 kWh:
        → Alerte: "Mettre en pause cette station"
        → WARNING += 1
      Si CONSM_ST > 5000 kWh:
        → Alerte urgente: "Pause d'1 jour recommandée"
        → WARNING += 1
      Afficher suggestion formatée en HTML
```

---

## 3. Patterns de conception

### 3.1 Singleton (Connection)

La classe `Connection` garantit une instance unique de la connexion base de données, partagée par tous les modules.

### 3.2 Model-View (Qt MVC)

`QSqlTableModel` sert de modèle de données lié directement à `QTableView`. Les modifications en base se reflètent automatiquement dans l'interface via `model->select()`.

### 3.3 Observer (Signals & Slots)

Le mécanisme Signal/Slot de Qt est utilisé pour :
- Réagir aux clics boutons (navigation, CRUD)
- Traiter les données série entrantes (`QSerialPort::readyRead`)
- Déclencher les lectures capteur (`QTimer::timeout`)
- Filtrer dynamiquement lors de la saisie (`QLineEdit::textChanged`)

### 3.4 State Machine (États station)

Les stations suivent une machine à états gérée par la combinaison capteur Arduino + logique éco-mode, avec 4 états : Libre, Occupé, En repos, En panne.

---

## 4. Interface utilisateur

### 4.1 Navigation

L'application utilise un `QStackedWidget` à 7 pages, avec des boutons de navigation stylisés dynamiquement (gradient vert `RGB(66, 117, 102)`). Le module actif est visuellement identifié.

### 4.2 Module Station (6 onglets)

| Onglet | Fonctionnalité |
|---|---|
| Afficher | Tableau des stations + graphiques statistiques |
| Ajouter | Formulaire d'ajout avec validation |
| Chercher | Recherche dynamique multi-critères |
| Modifier | Édition des propriétés d'une station |
| Supprimer | Suppression simple et en lot |
| Eco-Mode | Activation/désactivation + propositions |

### 4.3 Design

- Résolution cible : **1280 x 720 pixels**
- Interface construite avec **Qt Designer** (.ui compilés par uic)
- Icônes et assets gérés via **Qt Resource System** (.qrc)
- Stylesheets CSS-like pour le thème visuel

---

## 5. Outils et environnement

| Outil | Usage |
|---|---|
| **Qt Creator** | IDE principal, édition et débogage |
| **Qt Designer** | Conception visuelle des interfaces |
| **qmake** | Système de build (génération Makefile) |
| **moc** | Meta-Object Compiler (signals/slots) |
| **uic** | UI Compiler (.ui → .h) |
| **Arduino IDE** | Programmation du microcontrôleur |
| **Oracle Database** | Stockage persistant via ODBC |

---

## 6. Conclusion

Ce projet démontre la maîtrise de multiples compétences en développement logiciel :

- **Développement C++ moderne** avec le framework Qt 5
- **Intégration IoT** via communication série avec Arduino
- **Programmation base de données** avec Oracle et SQL avancé
- **Visualisation de données** avec des graphiques interactifs
- **Génération de documents** au format PDF
- **Architecture logicielle** modulaire avec patterns de conception
- **Conception d'interfaces** riches et ergonomiques
- **Algorithmes métier** (éco-mode, alertes prédictives, machine à états)

L'application couvre l'ensemble du cycle de vie d'un logiciel de gestion, de la couche données à la présentation, en passant par l'intégration matérielle et l'intelligence métier.
