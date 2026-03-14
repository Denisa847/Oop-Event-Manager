# 🎟️ OOP Event Manager

A desktop application developed in **C++ using the Qt framework**, designed to demonstrate **Object-Oriented Programming (OOP)** principles.

The application allows **administrators to manage events** while **users can browse and save events to a personal list**. It features a clear separation between administrator and user functionality, data validation, and multiple export options.

---

# ✨ Features

## 👨‍💼 Administrator Mode

Administrators are responsible for managing the main repository of events.

### Event Management
Add, update, and delete events with the following attributes:

- Title  
- Description  
- Date  
- Time  
- Number of Participants  
- Event Link

### Data Validation
Input data is validated using custom **Validator classes** and **exception handling** to ensure data integrity.

### Repository Management
Administrators control the central repository where all events are stored.

### Live GUI Updates
Changes made by the administrator are immediately reflected in the graphical interface.

---

## 👤 User Mode

Users can browse available events and manage their own personal event list.

### Event Browsing
Users can filter and browse events **by month** using an interactive interface.

### Personal Event List
Users can:

- add events to their personal list
- remove events when no longer interested

### Participant Tracking
When a user joins an event, the **number of participants is automatically updated** in the repository.

### Export Options
Users can export their personal event list in:

- **CSV format**
- **HTML format**

---

# 🛠 Technologies Used

- **C++**
- **Qt Framework**
- **Object-Oriented Programming (OOP)**

---

# 📚 Concepts Demonstrated

This project demonstrates several important software development concepts:

- Object-Oriented Design
- Separation of concerns
- Data validation and exception handling
- Repository pattern
- GUI development using Qt

