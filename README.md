# Disaster Relief Logistics Management System Using Core Data Structures

## 📌 Objective

This C++ project simulates a disaster relief logistics operation by modeling core components such as supply distribution, volunteer coordination, emergency response prioritization, and transport scheduling.

The system is entirely written in **C++** using **core language features**, with **no third-party libraries for data structures**. It employs:

- Stack
- Queue
- Priority Queue
- Circular Queue

The program is designed to be **menu-driven** and **user-friendly**, and it uses custom data structures **without relying on STL containers** such as `list`, `vector`, or `queue`.

## 🌍 Scenario Background

In the aftermath of a natural disaster, timely and organized relief operations are critical. This system supports:

- Managing emergency supply movement
- Coordinating volunteer dispatch
- Prioritizing urgent aid requests
- Scheduling transport vehicles for continuous operation

---

## 👥 Team Structure

The system is developed collaboratively by us, a group of 4 students. We work on developing the system for several roles with the implementation of **three functionalities** for each role, utilizing a specific core data structure. Code modules are integrated using standard integration techniques to form a unified system.

---

## 🧩 Roles and Responsibilities

### 🔹 Role 1: Supply Base Manager (Uses Stack)

**Manages the dispatch of supply packages from the base to the field.**

- **Pack Supply Box**: Add a new supply box with details (ID, type, quantity).
- **Send Supply Package**: Remove and dispatch one supply package for delivery.
- **View Packed Supplies**: Display all supply boxes waiting for dispatch.

---

### 🔹 Role 2: Volunteer Operations Officer (Uses Queue)

**Handles the registration and orderly deployment of volunteer workers.**

- **Register Volunteer**: Accept new volunteer registration (name, contact, skill area).
- **Deploy Volunteer to Field**: Assign a volunteer to a relief site.
- **View Registered Volunteers**: Display all available volunteers yet to be deployed.

---

### 🔹 Role 3: Emergency Request Coordinator (Uses Priority Queue)

**Processes incoming emergency aid requests and handles them based on urgency.**

- **Log Emergency Request**: Add a new request (location, type, urgency level).
- **Process Most Critical Request**: Identify and respond to the most urgent request.
- **View Pending Requests**: Display all pending requests with full details.

---

### 🔹 Role 4: Transport Unit Scheduler (Uses Circular Queue)

**Manages the active duty scheduling of transport vehicles.**

- **Add Vehicle to Schedule**: Register a vehicle into the active duty rotation.
- **Rotate Vehicle Shift**: Rotate the vehicle list to balance usage.
- **Display Vehicle Schedule**: Show the current order and availability of transport units.

---

## 📄 Note

This project is developed for academic purposes as part of the coursework for the Data Structures and Algorithm module and is intended to demonstrate data structure application in a real-world scenario.
