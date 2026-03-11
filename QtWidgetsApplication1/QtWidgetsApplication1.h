#pragma once
/*
#include <QtWidgets/QMainWindow>
#include "ui_QtWidgetsApplication1.h"
*/

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QTableWidgetItem>
#include "Repository.h"
#include "Administrator.h"
#include <QLineEdit>
#include <QSpinBox>

class QtWidgetsApplication1 : public QWidget
{
    Q_OBJECT

public:
    QtWidgetsApplication1(QWidget* parent = nullptr);
    ~QtWidgetsApplication1();

private:
    //Ui::QtWidgetsApplication1Class ui;
    QTableWidget* table;
    QPushButton* refreshButton;
    Repository repo;
    Administrator admin;
    QPushButton* addButton;
    QPushButton* updateButton;
    QPushButton* deleteButton;

    QLineEdit* titleInput;
    QLineEdit* descInput;
    QLineEdit* linkInput;
    QSpinBox* peopleInput;
    QSpinBox* dayInput;
    QSpinBox* monthInput;
    QSpinBox* hourInput;
    QSpinBox* minuteInput;
    QWidget* inputWidget;
    QPushButton* toggleFormButton;
    QPushButton* confirmAddButton;
    QPushButton* confirmUpdateButton;
    QPushButton* confirmDeleteButton;
    int rowToUpdate = -1;  // store which row is being updated
    QComboBox* comboDisplayMode;
    QPushButton* backButton;


    void loadEventsIntoTable();
    void addEvent();
    void updateEvent();
    void deleteEvent();
    void toggleFormVisibility();
    void saveUpdatedEvent();
    void confirmDeleteEvent();
    void loadEvents();

signals:
    void backToMenu();
};