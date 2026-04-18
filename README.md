# Voltify - Smart EV Charging Station Manager

<p align="center">
  <strong>Desktop application for managing electric vehicle charging stations with real-time IoT integration</strong>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/C++-11-blue?logo=cplusplus" alt="C++11">
  <img src="https://img.shields.io/badge/Qt-5-green?logo=qt" alt="Qt 5">
  <img src="https://img.shields.io/badge/Arduino-Mega-teal?logo=arduino" alt="Arduino">
  <img src="https://img.shields.io/badge/Database-Oracle%20ODBC-red" alt="ODBC">
  <img src="https://img.shields.io/badge/Platform-Desktop-orange" alt="Desktop">
</p>

---

## Overview

Voltify is a full-featured desktop application built with **Qt 5 / C++11** that provides end-to-end management of electric vehicle (EV) charging stations. The system integrates with **Arduino Mega** hardware for real-time sensor monitoring and LCD display control, connects to an **Oracle database via ODBC** for persistent data management, and offers advanced features including **PDF report generation**, **interactive chart-based analytics**, and an intelligent **Eco-Mode energy management system**.

This project demonstrates proficiency in embedded systems communication, database-driven applications, data visualization, and modular UI architecture.

---

## Key Features

### Station Management (CRUD)
- Full Create, Read, Update, Delete operations on charging stations
- Parameterized SQL queries with input validation
- Dynamic search and filtering across multiple fields (ID, type, date, status, speed, mode)
- Bulk deletion with confirmation dialogs

### Real-Time IoT Integration (Arduino)
- Two-way serial communication with Arduino Mega (9600 baud)
- Automatic hardware detection via Vendor/Product ID (VID: 9025, PID: 66)
- Sensor polling every 2 seconds for station occupancy status
- LCD display updates every 3 seconds showing remaining kWh capacity
- Automatic station state transitions: `Free` → `Occupied` → `Rest` → `Broken`

### Eco-Mode Energy Management
- Global energy-saving mode toggling all stations simultaneously
- Daily consumption cap of **300 kWh** per station in Eco mode
- Automatic station lockout when limit is reached
- Real-time remaining capacity calculation sent to Arduino LCD

### Data Visualization & Analytics
- **Pie charts**: Station distribution by vehicle type (Tesla, Porsche, Toyota, etc.)
- **Bar charts**: Aggregated consumption per station, sorted by usage
- Charts rendered using Qt Charts module with dynamic data refresh

### PDF Report Generation
- Automated multi-column PDF reports exported to Desktop
- Includes company logo, timestamps, and formatted station data tables
- Built with QPrinter/QPainter for pixel-precise document layout

### Smart Alert System
- Monthly consumption anomaly detection (triggers after the 5th of each month)
- Low-usage alerts (< 300 kWh): recommendation to pause station
- High-usage alerts (> 5000 kWh): urgent pause recommendation
- Escalating warning counter for repeated anomalies

---

## Tech Stack

| Layer | Technology |
|---|---|
| **Language** | C++11 |
| **UI Framework** | Qt 5 (Widgets, Designer) |
| **Database** | Oracle via ODBC (QSqlDatabase) |
| **IoT Hardware** | Arduino Mega 2560 |
| **Serial Communication** | Qt SerialPort (QSerialPort) |
| **Data Visualization** | Qt Charts (QPieSeries, QBarSeries) |
| **PDF Generation** | Qt PrintSupport (QPrinter, QPainter) |
| **Build System** | qmake |
| **UI Design** | Qt Designer (.ui files) |
| **Resources** | Qt Resource System (.qrc) |

### Qt Modules Used

```
Core · GUI · Widgets · SQL · Charts · SerialPort · PrintSupport · Multimedia
```

---

## Architecture

The application follows a **central navigation hub** pattern with a modular architecture:

```
┌──────────────────────────────────────────────┐
│                  main.cpp                     │
│           (Entry Point + DB Init)             │
└──────────────────┬───────────────────────────┘
                   │
┌──────────────────▼───────────────────────────┐
│              profil (Main Window)             │
│           ┌─── QStackedWidget ───┐           │
│           │                      │           │
│  ┌────────▼──┐  ┌────────┐  ┌───▼───────┐   │
│  │  Station  │  │ Client │  │ Employee  │   │
│  │  Module   │  │ Module │  │  Module   │   │
│  └─────┬─────┘  └────┬───┘  └──────────┘   │
│        │              │                      │
│  ┌─────▼─────┐  ┌────▼────┐  ┌──────────┐  │
│  │  Arduino  │  │Eco-Mode │  │ Service  │  │
│  │  Driver   │  │  Logic  │  │  Module  │  │
│  └───────────┘  └─────────┘  └──────────┘  │
│                                              │
│  ┌───────────┐  ┌─────────┐  ┌──────────┐  │
│  │ Charts &  │  │   PDF   │  │  Stock   │  │
│  │Statistics │  │ Export  │  │  Module  │  │
│  └───────────┘  └─────────┘  └──────────┘  │
└──────────────────────────────────────────────┘
         │
┌────────▼─────────────────────────────────────┐
│         Connection (Singleton)                │
│         ODBC → Oracle Database                │
└──────────────────────────────────────────────┘
```

### Design Patterns

| Pattern | Usage |
|---|---|
| **Singleton** | Database connection manager (`Connection` class) |
| **Model-View** | `QSqlTableModel` / `QSqlQueryModel` for data binding to table views |
| **Observer** | Qt Signals & Slots for event-driven UI updates |
| **Timer-based Polling** | `QTimer` for periodic Arduino sensor reads and LCD updates |
| **Navigation Hub** | `QStackedWidget` for page-based module switching |

---

## Database Schema

**Table: STATIONS**

| Field | Type | Description |
|---|---|---|
| `ID_ST` | NUMBER | Primary key |
| `TYPE_ST` | VARCHAR2 | Vehicle type (Tesla, Porsche, Toyota, etc.) |
| `PROFIT_ST` | FLOAT | Total revenue generated |
| `NBR_CHARGE_ST` | NUMBER | Number of completed charges |
| `DDM_ST` | DATE | Commissioning date |
| `CONJ_ST` | FLOAT | Daily consumption (kWh) |
| `CONSC_ST` | FLOAT | Cumulative consumption (kWh) |
| `ETAT_ST` | VARCHAR2 | Status: Libre / Occupe / En panne / En repos |
| `VITESSE_ST` | VARCHAR2 | Charging speed category |
| `MODE_ST` | VARCHAR2 | Mode: Normal / Economique |
| `PRIX_KW_ST` | FLOAT | Price per kWh |
| `CONSM_ST` | FLOAT | Monthly consumption (kWh) |
| `WARNING` | NUMBER | Alert escalation counter |

---

## Build & Run

### Prerequisites

- **Qt 5** (with modules: Core, GUI, Widgets, SQL, Charts, SerialPort, PrintSupport, Multimedia)
- **C++11** compatible compiler (GCC, MSVC, Clang)
- **Oracle ODBC Driver** configured with DSN `Source_Projet2A`
- **Arduino Mega 2560** (optional, for IoT features)

### Build

```bash
# Generate Makefile
qmake charging_station.pro

# Compile
make

# Run
./charging_station
```

### Clean Build

```bash
make clean
qmake charging_station.pro
make
```

---

## Project Structure

```
Voltify/
├── charging_station.pro      # Qt project configuration
├── src/
│   ├── main.cpp              # Application entry point
│   ├── profil.cpp/h          # Main window & navigation hub
│   ├── station.cpp/h         # Station CRUD, charts, PDF, Arduino
│   ├── client.cpp/h          # Consumption tracking & eco-mode
│   ├── arduino.cpp/h         # Serial communication driver
│   ├── dbmaneger.cpp/h       # Singleton database connection
│   ├── fonction_st.cpp/h     # Station data model helpers
│   ├── employee.cpp/h        # Employee management module
│   ├── service.cpp/h         # Service management module
│   ├── stock.cpp/h           # Stock management module
│   ├── reglage.cpp/h         # Settings module
│   └── insertdata.cpp/h      # Data insertion utilities
├── ui/
│   ├── profil.ui             # Main window layout
│   ├── station.ui            # Station management UI (1280x720)
│   ├── client.ui             # Client interface
│   └── ...                   # Other module UIs
└── resources/
    └── iconn.qrc             # Icons, logos, and sound assets
```

---

## Skills Demonstrated

- **C++11**: Modern C++ with OOP, encapsulation, and memory management
- **Qt Framework**: Widgets, Signals/Slots, Model-View, Resource System, Designer
- **Database Programming**: SQL queries, parameterized statements, ODBC connectivity
- **IoT / Embedded Systems**: Arduino serial communication, sensor data processing, LCD control
- **Data Visualization**: Interactive pie and bar charts with Qt Charts
- **Document Generation**: Programmatic PDF creation with QPrinter/QPainter
- **UI/UX Design**: Multi-page navigation, tab-based interfaces, dynamic styling
- **Software Architecture**: Modular design, singleton pattern, MVC separation
- **Real-Time Systems**: Timer-based polling, state machine transitions, live data updates

---

## Screenshots

> *Screenshots can be added in a `/screenshots` directory*

---

## License

This project was developed as an academic project at ESPRIT School of Engineering.

---

<p align="center">
  Built with C++, Qt, and Arduino
</p>
