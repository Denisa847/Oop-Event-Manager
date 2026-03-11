# Oop-Event-Manager

A C++ application developed using Object-Oriented Programming principles and the Qt framework.
The application allows administrators to manage events and users to browse and save events to a personal list.

## Core Features

### Administrator Mode

**Event Management:** Add, update, and delete events (Title, Description, Date, Time, Number of Participants, Link).

**Validation:** Strict data validation using custom `Validator` classes and exception handling.

**Repository Control:** The administrator manages the main repository of events.

**Live Updates:** Changes made by the administrator are immediately reflected in the GUI.



### User Mode

**Event Browsing:** Users can filter events by month and browse them interactively.

**Personal Event List:** Users can add events to a personal list and remove them when needed.

**Participant Updates:** When a user joins an event, the number of participants is updated in the repository.

**Export Options:** Personal event lists can be saved in **CSV** or **HTML** format.


## Technologies Used

* C++
* Qt Framework
* Object-Oriented Programming (OOP)

