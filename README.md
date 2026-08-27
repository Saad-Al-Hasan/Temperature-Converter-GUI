# Temperature Converter with GUI

A simple **Java Swing-based Temperature Converter** developed as a group project for **CSE 110**.

The application allows users to enter a temperature value and convert it between **Celsius, Fahrenheit, and Kelvin** through a graphical user interface.

## Features

* Convert temperatures between:

  * Celsius
  * Fahrenheit
  * Kelvin
* Simple graphical user interface using Java Swing
* Input validation for invalid temperature values
* Easy-to-use dropdown menus for selecting conversion units
* Object-oriented implementation using abstraction, inheritance, and polymorphism

## Technologies Used

* **Java**
* **Java Swing**
* **Java AWT**
* **Object-Oriented Programming (OOP)**

## Project Structure

```text
Temperature-Converter-GUI/
└── TemperatureConverterApp.java
```

## How to Run

### 1. Compile the program

Open a terminal in the project directory and run:

```bash
javac TemperatureConverterApp.java
```

### 2. Run the application

```bash
java TemperatureConverterApp
```

## Supported Conversions

| From       | To         |
| ---------- | ---------- |
| Celsius    | Fahrenheit |
| Celsius    | Kelvin     |
| Fahrenheit | Celsius    |
| Fahrenheit | Kelvin     |
| Kelvin     | Celsius    |
| Kelvin     | Fahrenheit |
| Celsius    | Celsius    |
| Fahrenheit | Fahrenheit |
| Kelvin     | Kelvin     |

## OOP Concepts Demonstrated

The project uses an abstract `TemperatureConverter` class as the base class for the different temperature conversion types.

The application demonstrates:

* **Abstraction** — `TemperatureConverter` defines the conversion method.
* **Inheritance** — Celsius, Fahrenheit, and Kelvin converters extend the base class.
* **Polymorphism** — The application uses a `TemperatureConverter` reference to work with different converter implementations.
* **Event Handling** — Java's `ActionListener` is used to handle the Convert button.

## Team Members

* **Md. Saad Al Hasan** — 2024-1-60-233


## Academic Information

**Course:** CSE 110
**Project:** Temperature Converter with GUI
**Group:** Group-02, Section-04

---

*Developed as an academic group project.*
