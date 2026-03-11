#include "QtWidgetsApplication1.h"
#include "Exception.h"
#include "Administrator.h"
#include <QMessageBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QComboBox>
#include <QDate>  // For date comparison

QtWidgetsApplication1::QtWidgetsApplication1(QWidget* parent)
    : QWidget(parent), admin(repo)
{
    //ui.setupUi(this);

    try {
      
        //Repository repo;
        repo.loadFromFile("events.txt");
        //admin = Administrator(repo);
    }
    catch (const Exception& e) {
    }

    table = new QTableWidget(this);
    table->setColumnCount(6);
    QStringList headers{ "Title", "Description", "Date", "Time", "People", "Link"};
    table->setHorizontalHeaderLabels(headers);

    refreshButton = new QPushButton("Refresh", this);
    connect(refreshButton, &QPushButton::clicked, this, &QtWidgetsApplication1::loadEventsIntoTable);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(table);
    layout->addWidget(refreshButton);
    titleInput = new QLineEdit(this);
    descInput = new QLineEdit(this);
    linkInput = new QLineEdit(this);
    peopleInput = new QSpinBox(this);
    dayInput = new QSpinBox(this);
    monthInput = new QSpinBox(this);
    hourInput = new QSpinBox(this);
    minuteInput = new QSpinBox(this);

    dayInput->setRange(1, 28);
    monthInput->setRange(1, 12);
    hourInput->setRange(0, 23);
    minuteInput->setRange(0, 59);

    // Add to layout
    /*layout->addWidget(new QLabel("Title:"));
    layout->addWidget(titleInput);*/
    inputWidget = new QWidget(this);  
    QVBoxLayout* inputLayout = new QVBoxLayout(inputWidget);

    inputLayout->addWidget(new QLabel("Title:"));
    inputLayout->addWidget(titleInput);

    inputLayout->addWidget(new QLabel("Description:"));
    inputLayout->addWidget(descInput);

    inputLayout->addWidget(new QLabel("Link:"));
    inputLayout->addWidget(linkInput);

    inputLayout->addWidget(new QLabel("People:"));
    inputLayout->addWidget(peopleInput);

    inputLayout->addWidget(new QLabel("Day:"));
    inputLayout->addWidget(dayInput);

    inputLayout->addWidget(new QLabel("Month:"));
    inputLayout->addWidget(monthInput);

    inputLayout->addWidget(new QLabel("Hour:"));
    inputLayout->addWidget(hourInput);

    inputLayout->addWidget(new QLabel("Minute:"));
    inputLayout->addWidget(minuteInput);

    confirmAddButton = new QPushButton("Add", inputWidget);
    inputLayout->addWidget(confirmAddButton);
    connect(confirmAddButton, &QPushButton::clicked, this, &QtWidgetsApplication1::addEvent);

    confirmUpdateButton = new QPushButton("Save Update", inputWidget);
    inputLayout->addWidget(confirmUpdateButton);
    confirmUpdateButton->hide();  // hide by default
    connect(confirmUpdateButton, &QPushButton::clicked, this, &QtWidgetsApplication1::saveUpdatedEvent);

    confirmDeleteButton = new QPushButton("Confirm Delete", inputWidget);
    inputLayout->addWidget(confirmDeleteButton);
    confirmDeleteButton->hide();
    connect(confirmDeleteButton, &QPushButton::clicked, this, &QtWidgetsApplication1::confirmDeleteEvent);

    setLayout(layout);

    inputWidget->hide();


    //addButton = new QPushButton("Add", this);
    toggleFormButton = new QPushButton("Add Event", this);
    layout->addWidget(toggleFormButton);
    connect(toggleFormButton, &QPushButton::clicked, this, &QtWidgetsApplication1::toggleFormVisibility);

    updateButton = new QPushButton("Update", this);
    deleteButton = new QPushButton("Delete", this);

    // Add buttons to layout
    //layout->addWidget(addButton);
    layout->addWidget(inputWidget);
    layout->addWidget(updateButton);
    layout->addWidget(deleteButton);

    //connect(addButton, &QPushButton::clicked, this, &QtWidgetsApplication1::addEvent);
    connect(updateButton, &QPushButton::clicked, this, &QtWidgetsApplication1::updateEvent);
    connect(deleteButton, &QPushButton::clicked, this, &QtWidgetsApplication1::deleteEvent);
   

    QPushButton* displayButton = new QPushButton("Display Events", this);
    layout->addWidget(displayButton);
    connect(displayButton, &QPushButton::clicked, this, &QtWidgetsApplication1::loadEvents);


    QPushButton* exitButton = new QPushButton("Exit", this);
    layout->addWidget(exitButton);
    connect(exitButton, &QPushButton::clicked, this, &QWidget::close);
    //loadEventsIntoTable();

    comboDisplayMode = new QComboBox(this);
    comboDisplayMode->addItem("Short");
    comboDisplayMode->addItem("Detalied");
    layout->addWidget(comboDisplayMode);

    connect(comboDisplayMode, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &QtWidgetsApplication1::loadEvents);

    backButton = new QPushButton("Back to Menu", this);
    layout->addWidget(backButton);
    connect(backButton, &QPushButton::clicked, this, &QtWidgetsApplication1::backToMenu);

}

QtWidgetsApplication1::~QtWidgetsApplication1()
{
}

void QtWidgetsApplication1::loadEventsIntoTable() {
    std::vector<Event> events = admin.getEvents();
    table->setRowCount(static_cast<int>(events.size()));

    for (int i = 0; i < events.size(); ++i) {
        const Event& e = events[i];
        table->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(e.getTitle())));
        table->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(e.getDescription())));

        const DateTime& dt = e.getDateTime();
        QString date = QString("%1.%2.2025").arg(dt.date).arg(dt.month);
        QString time = QString("%1:%2").arg(dt.hour).arg(dt.minutes);

        table->setItem(i, 2, new QTableWidgetItem(date));
        table->setItem(i, 3, new QTableWidgetItem(time));
        table->setItem(i, 4, new QTableWidgetItem(QString::number(e.getNrPeople())));
        table->setItem(i, 5, new QTableWidgetItem(QString::fromStdString(e.getLink())));
    }
}

void QtWidgetsApplication1::addEvent() {
   // Event e("New Event", "Default Desc", { 1, 1, 12, 0 }, 50, "https://example.com");
    QString title = titleInput->text();
    QString desc = descInput->text();
    QString link = linkInput->text();
    int people = peopleInput->value();
    int day = dayInput->value();
    int month = monthInput->value();
    int hour = hourInput->value();
    int minutes = minuteInput->value();

    DateTime dt{ day, month, hour, minutes };

    try {
        admin.addEvent(title.toStdString(), desc.toStdString(), dt, people, link.toStdString());
        loadEventsIntoTable();
    }
    catch (const Exception& ex) {
        QMessageBox::warning(this, "Add Error", QString::fromStdString(ex.what()));
    }
    titleInput->clear();
    descInput->clear();
    linkInput->clear();
    peopleInput->setValue(0);
    dayInput->setValue(1);
    monthInput->setValue(1);
    hourInput->setValue(0);
    minuteInput->setValue(0);
}

void QtWidgetsApplication1::deleteEvent() {
    rowToUpdate = table->currentRow();
    if (rowToUpdate < 0) return;

    std::vector<Event> events = admin.getEvents();
    if (rowToUpdate >= events.size()) return;

    const Event& e = events[rowToUpdate];

    titleInput->setText(QString::fromStdString(e.getTitle()));
    descInput->setText(QString::fromStdString(e.getDescription()));
    linkInput->setText(QString::fromStdString(e.getLink()));

    const DateTime& dt = e.getDateTime();
    dayInput->setValue(dt.date);
    monthInput->setValue(dt.month);
    hourInput->setValue(dt.hour);
    minuteInput->setValue(dt.minutes);
    peopleInput->setValue(e.getNrPeople());

    inputWidget->show();
    toggleFormButton->setText("Hide Form");

    confirmAddButton->hide();
    confirmUpdateButton->hide();
    confirmDeleteButton->show();
}

void QtWidgetsApplication1::updateEvent() {
    rowToUpdate = table->currentRow(); 
    if (rowToUpdate < 0) return;

    std::vector<Event> events = admin.getEvents();
    if (rowToUpdate >= events.size()) return;

    const Event& e = events[rowToUpdate];

    // Pre-fill the input fields
    titleInput->setText(QString::fromStdString(e.getTitle()));
    descInput->setText(QString::fromStdString(e.getDescription()));
    linkInput->setText(QString::fromStdString(e.getLink()));

    const DateTime& dt = e.getDateTime();
    dayInput->setValue(dt.date);
    monthInput->setValue(dt.month);
    hourInput->setValue(dt.hour);
    minuteInput->setValue(dt.minutes);
    peopleInput->setValue(e.getNrPeople());

    inputWidget->show();
    toggleFormButton->setText("Hide Form");

    confirmAddButton->hide();
    confirmUpdateButton->show();
    /*try {
        admin.updateEvent(oldEvent.getTitle(), oldEvent.getDescription(),
            updated.getTitle(), updated.getDescription(),
            updated.getDateTime(), updated.getNrPeople(), updated.getLink());
        loadEventsIntoTable();
    }
    catch (const Exception& ex) {
        QMessageBox::warning(this, "Edit Error", QString::fromStdString(ex.what()));
    }*/
}

void QtWidgetsApplication1::toggleFormVisibility() {
    if (inputWidget->isVisible()) {
        inputWidget->hide();
        toggleFormButton->setText("Add Event");
    }
    else {
        inputWidget->show();
        toggleFormButton->setText("Hide Form");
    }
}


void QtWidgetsApplication1::saveUpdatedEvent() {
    if (rowToUpdate < 0) return;

    std::vector<Event> events = admin.getEvents();
    if (rowToUpdate >= events.size()) return;

    const Event& oldEvent = events[rowToUpdate];

    QString title = titleInput->text();
    QString desc = descInput->text();
    QString link = linkInput->text();
    int people = peopleInput->value();
    int day = dayInput->value();
    int month = monthInput->value();
    int hour = hourInput->value();
    int minutes = minuteInput->value();

    DateTime dt{ day, month, hour, minutes };

    try {
        admin.updateEvent(oldEvent.getTitle(), oldEvent.getDescription(),
            title.toStdString(), desc.toStdString(), dt, people, link.toStdString());

        loadEventsIntoTable();

        // Reset form
        inputWidget->hide();
        toggleFormButton->setText("Add Event");
        confirmUpdateButton->hide();
        confirmAddButton->show();
        rowToUpdate = -1;
    }
    catch (const Exception& ex) {
        QMessageBox::warning(this, "Update Error", QString::fromStdString(ex.what()));
    }

    titleInput->clear();
    descInput->clear();
    linkInput->clear();
    peopleInput->setValue(0);
    dayInput->setValue(1);
    monthInput->setValue(1);
    hourInput->setValue(0);
    minuteInput->setValue(0);
}

void QtWidgetsApplication1::confirmDeleteEvent() {
    //if (rowToUpdate < 0) return;
    if (rowToUpdate < 0) {
        QMessageBox::warning(this, "Delete Error", "No row selected.");
        return;
    }

    std::vector<Event> events = admin.getEvents();
    if (rowToUpdate >= events.size()) {
        QMessageBox::warning(this, "Delete Error", "Selected event does not exist anymore.");
        return;
    }

  

    const Event& e = events[rowToUpdate];

    try {
        admin.removeEvent(e.getTitle(), e.getDescription());
        loadEventsIntoTable();

        // Reset
        inputWidget->hide();
        toggleFormButton->setText("Add Event");
        confirmDeleteButton->hide();
        confirmAddButton->show();
        rowToUpdate = -1;

        // Clear form
        titleInput->clear();
        descInput->clear();
        linkInput->clear();
        peopleInput->setValue(0);
        dayInput->setValue(1);
        monthInput->setValue(1);
        hourInput->setValue(0);
        minuteInput->setValue(0);
    }
    catch (const Exception& ex) {
        QMessageBox::warning(this, "Delete Error", QString::fromStdString(ex.what()));
    }
}


/*
void QtWidgetsApplication1::loadEvents() {
    std::vector<Event> events = admin.getEvents();

    table->setRowCount(0); // Clear existing rows

    QDate currentDate = QDate::currentDate();

    for (const Event& e : events) {
        const DateTime& dt = e.getDateTime();

        // Show only current or future events
        QDate eventDate(2025, dt.month, dt.date); // Assuming 2025 as hardcoded
        if (eventDate < currentDate)
            continue;

        int row = table->rowCount();
        table->insertRow(row);

        if (comboDisplayMode->currentText() == "Short") {
            table->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(e.getTitle())));
            for (int col = 1; col < 6; ++col) {
                table->setItem(row, col, new QTableWidgetItem(""));
            }
           
        }
        else {
            table->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(e.getTitle())));
            table->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(e.getDescription())));
            table->setItem(row, 2, new QTableWidgetItem(eventDate.toString("dd.MM.yyyy")));
            table->setItem(row, 3, new QTableWidgetItem(QString("%1:%2").arg(dt.hour).arg(dt.minutes, 2, 10, QChar('0'))));
            table->setItem(row, 4, new QTableWidgetItem(QString::number(e.getNrPeople())));
            table->setItem(row, 5, new QTableWidgetItem(QString::fromStdString(e.getLink())));
          
        }
    }
}*/

void QtWidgetsApplication1::loadEvents() {
    std::vector<Event> events = admin.getEvents();
    table->setRowCount(0); // Clear existing rows

    QDate currentDate = QDate::currentDate();

    for (const Event& e : events) {
        const DateTime& dt = e.getDateTime();
        QDate eventDate(2025, dt.month, dt.date); // Use correct year logic if needed


        int row = table->rowCount();
        table->insertRow(row);

        if (comboDisplayMode->currentText() == "Short") {
            table->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(e.getTitle())));
            table->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(e.getDescription())));
            for (int col = 2; col < 6; ++col){
                table->setItem(row, col, new QTableWidgetItem(""));
         
            }
        }
        else {
            table->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(e.getTitle())));
            table->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(e.getDescription())));
            table->setItem(row, 2, new QTableWidgetItem(eventDate.toString("dd.MM.yyyy")));
            table->setItem(row, 3, new QTableWidgetItem(QString("%1:%2").arg(dt.hour).arg(dt.minutes, 2, 10, QChar('0'))));
            table->setItem(row, 4, new QTableWidgetItem(QString::number(e.getNrPeople())));
            table->setItem(row, 5, new QTableWidgetItem(QString::fromStdString(e.getLink())));
        }
    }
}





