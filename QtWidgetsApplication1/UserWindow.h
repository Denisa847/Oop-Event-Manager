
#pragma once
#include <QWidget>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QSpinBox>
#include "User.h"
#include "Administrator.h"
#include "Repository.h"

class UserWindow : public QWidget
{
    Q_OBJECT

public:
    UserWindow(User& userRef, Administrator& adminRef, QWidget* parent = nullptr);

private:
    User& user;
    Administrator& admin;

    QTableWidget* table;
    QPushButton* filterButton;
    QPushButton* addButton;
    QPushButton* removeButton;
    QPushButton* openListButton;
    QLineEdit* monthInput;
    QPushButton* backButton;
   

    void loadFilteredEvents();
    void addSelectedEvent();
    void removeSelectedEvent();
    void browseEventsByMonthInteractive();
    void openPersonalList();
    void showPersonalList();
signals:
    void backToMenu();
};
