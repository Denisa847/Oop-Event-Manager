
#include "UserWindow.h"
#include "Administrator.h"
#include "User.h"
#include <QMessageBox>
#include <QDate>
#include <QLabel>
#include <QVBoxLayout>
#include <QInputDialog>

UserWindow::UserWindow(User& userRef, Administrator& adminRef, QWidget* parent)
    : QWidget(parent), user(userRef), admin(adminRef)
{
    QVBoxLayout* layout = new QVBoxLayout(this);

    monthInput = new QLineEdit(this);
    layout->addWidget(new QLabel("Filter by month (optional):"));
    layout->addWidget(monthInput);

    filterButton = new QPushButton("Show Events", this);
    layout->addWidget(filterButton);
    connect(filterButton, &QPushButton::clicked, this, &UserWindow::loadFilteredEvents);

    table = new QTableWidget(this);
    table->setColumnCount(6);
    QStringList headers{ "Title", "Description", "Date", "Time", "People", "Link" };
    table->setHorizontalHeaderLabels(headers);
    layout->addWidget(table);

    QPushButton* showMyListButton = new QPushButton("Show My Personal List", this);
    layout->addWidget(showMyListButton);
    connect(showMyListButton, &QPushButton::clicked, this, &UserWindow::showPersonalList);

    addButton = new QPushButton("Add to My List", this);
    layout->addWidget(addButton);
    connect(addButton, &QPushButton::clicked, this, &UserWindow::addSelectedEvent);

    removeButton = new QPushButton("Remove from My List", this);
    layout->addWidget(removeButton);
    connect(removeButton, &QPushButton::clicked, this, &UserWindow::removeSelectedEvent);

	filterButton = new QPushButton("Browse Events by Month", this);
	layout->addWidget(filterButton);
    connect(filterButton, &QPushButton::clicked, this, &UserWindow::browseEventsByMonthInteractive);

    openListButton = new QPushButton("Open Personal List", this);
    layout->addWidget(openListButton);
    connect(openListButton, &QPushButton::clicked, this, &UserWindow::openPersonalList);

    backButton = new QPushButton("Back to Menu", this);
    layout->addWidget(backButton);
    connect(backButton, &QPushButton::clicked, this, &UserWindow::backToMenu);
}


void UserWindow::loadFilteredEvents() {
    QString monthText = monthInput->text();
    int month = 0;
    if (!monthText.isEmpty()) {
        bool ok;
        month = monthText.toInt(&ok);
        if (!ok || month < 1 || month > 12) {
            QMessageBox::warning(this, "Input Error", "Invalid month. Enter a number between 1 and 12.");
            return;
        }
    }

    std::vector<Event> events = user.getEventsbyMonth(admin.getEvents(), month);
    table->setRowCount(static_cast<int>(events.size()));

    for (int i = 0; i < events.size(); ++i) {
        const Event& ev = events[i];
        const DateTime& dt = ev.getDateTime();
        QString date = QString("%1.%2.2025").arg(dt.date).arg(dt.month);
        QString time = QString("%1:%2").arg(dt.hour).arg(dt.minutes, 2, 10, QLatin1Char('0'));

        table->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(ev.getTitle())));
        table->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(ev.getDescription())));
        table->setItem(i, 2, new QTableWidgetItem(date));
        table->setItem(i, 3, new QTableWidgetItem(time));
        table->setItem(i, 4, new QTableWidgetItem(QString::number(ev.getNrPeople())));
        table->setItem(i, 5, new QTableWidgetItem(QString::fromStdString(ev.getLink())));
    }
}

void UserWindow::addSelectedEvent() {
    int row = table->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Selection Error", "No event selected.");
        return;
    }

    std::string title = table->item(row, 0)->text().toStdString();
    std::string desc = table->item(row, 1)->text().toStdString();

    const auto& events = admin.getEvents();
    auto it = std::find_if(events.begin(), events.end(), [&](const Event& e) {
        return e.getTitle() == title && e.getDescription() == desc;
        });

    if (it == events.end()) {
        QMessageBox::warning(this, "Error", "Selected event not found in repository.");
        return;
    }

    if (user.addEvent(*it)) {
        // Also update the admin repository (increment people)
        Event updated = *it;
        updated.setNrPeople(updated.getNrPeople() + 1);
        admin.updateEvent(it->getTitle(), it->getDescription(),
            updated.getTitle(), updated.getDescription(),
            updated.getDateTime(), updated.getNrPeople(), updated.getLink());
        QMessageBox::information(this, "Success", "Event added to your list.");
    }
    else {
        QMessageBox::information(this, "Duplicate", "You already added this event.");
    }
}

void UserWindow::removeSelectedEvent() {
    int row = table->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Selection Error", "No event selected.");
        return;
    }

    std::string title = table->item(row, 0)->text().toStdString();
    std::string desc = table->item(row, 1)->text().toStdString();

    if (user.deleteEvent(title, desc)) {
        // Decrease the people count in admin's list
        const auto& events = admin.getEvents();
        auto it = std::find_if(events.begin(), events.end(), [&](const Event& e) {
            return e.getTitle() == title && e.getDescription() == desc;
            });

        if (it != events.end()) {
            Event updated = *it;
            updated.setNrPeople(std::max(0, updated.getNrPeople() - 1));
            admin.updateEvent(it->getTitle(), it->getDescription(),
                updated.getTitle(), updated.getDescription(),
                updated.getDateTime(), updated.getNrPeople(), updated.getLink());
        }

        QMessageBox::information(this, "Success", "Event removed from your list.");
    }
    else {
        QMessageBox::warning(this, "Not Found", "This event is not in your personal list.");
    }
}

void UserWindow::openPersonalList() {
    FilePersonalList* file = user.getFileList();
    if (!file) {
        QMessageBox::warning(this, "Error", "No personal list available.");
        return;
    }

    QString filePath = QString::fromStdString(file->getFilename());

    QString command = "start " + filePath;


    system(command.toStdString().c_str());
}


void UserWindow::browseEventsByMonthInteractive() {
    // Ask user to enter a month (or leave blank)
    QString input = QInputDialog::getText(this, "Browse Events",
        "Enter month (1-12) or leave empty to view all:");

    int month = 0; // Default: all
    if (!input.trimmed().isEmpty()) {
        bool ok;
        month = input.toInt(&ok);
        if (!ok || month < 1 || month > 12) {
            QMessageBox::warning(this, "Input Error",
                "Invalid month. Please enter a number between 1 and 12, or leave it blank.");
            return;
        }
    }

    std::vector<Event> events = user.getEventsbyMonth(admin.getEvents(), month);
    if (events.empty()) {
        QMessageBox::information(this, "No Events", "No events found for the given month.");
        return;
    }

    size_t index = 0;
    while (true) {
        if (index >= events.size())
            index = 0;

        const Event& ev = events[index];
        const DateTime& dt = ev.getDateTime();

        QString message = QString("Title: %1\nDescription: %2\nDate: %3.%4.2025\nTime: %5:%6\nPeople: %7\nLink: %8")
            .arg(QString::fromStdString(ev.getTitle()))
            .arg(QString::fromStdString(ev.getDescription()))
            .arg(dt.date).arg(dt.month)
            .arg(dt.hour).arg(dt.minutes, 2, 10, QLatin1Char('0'))
            .arg(ev.getNrPeople())
            .arg(QString::fromStdString(ev.getLink()));

        QMessageBox msgBox;
        msgBox.setWindowTitle(QString("Event %1 of %2").arg(index + 1).arg(events.size()));
        msgBox.setText(message);
        QPushButton* addBtn = msgBox.addButton("Add", QMessageBox::AcceptRole);
        QPushButton* nextBtn = msgBox.addButton("Next", QMessageBox::RejectRole);
        QPushButton* exitBtn = msgBox.addButton("Exit", QMessageBox::DestructiveRole);

        msgBox.exec();

        if (msgBox.clickedButton() == addBtn) {
            if (user.addEvent(ev)) {
                Event updated(ev.getTitle(), ev.getDescription(), ev.getDateTime(), ev.getNrPeople() + 1, ev.getLink());
                admin.updateEvent(ev.getTitle(), ev.getDescription(), updated.getTitle(), updated.getDescription(),
                    updated.getDateTime(), updated.getNrPeople(), updated.getLink());
                QMessageBox::information(this, "Added", "Event added to your list.");
            }
            else {
                QMessageBox::information(this, "Duplicate", "You already added this event.");
            }
            index++;
        }
        else if (msgBox.clickedButton() == nextBtn) {
            index++;
        }
        else if (msgBox.clickedButton() == exitBtn) {
            break;
        }
    }
}





/*
void UserWindow::browseEventsByMonthInteractive() {
    QString monthText = monthInput->text();
    int month = 0;

    if (!monthText.isEmpty()) {
        bool ok;
        month = monthText.toInt(&ok);
        if (!ok || month < 1 || month > 12) {
            QMessageBox::warning(this, "Input Error", "Invalid month. Enter a number between 1 and 12.");
            return;
        }
    }

    std::vector<Event> events = user.getEventsbyMonth(admin.getEvents(), month);
    if (events.empty()) {
        QMessageBox::information(this, "No Events", "No events found for the selected month.");
        return;
    }

    size_t index = 0;

    while (true) {
        if (index >= events.size())
            index = 0;  // loop back or break depending on desired behavior

        const Event& ev = events[index];
        const DateTime& dt = ev.getDateTime();

        QString message = QString("Title: %1\nDescription: %2\nDate: %3.%4.2025\nTime: %5:%6\nPeople: %7\nLink: %8")
            .arg(QString::fromStdString(ev.getTitle()))
            .arg(QString::fromStdString(ev.getDescription()))
            .arg(dt.date).arg(dt.month)
            .arg(dt.hour).arg(dt.minutes, 2, 10, QLatin1Char('0'))
            .arg(ev.getNrPeople())
            .arg(QString::fromStdString(ev.getLink()));

        QMessageBox msgBox;
        msgBox.setWindowTitle(QString("Event %1 of %2").arg(index + 1).arg(events.size()));
        msgBox.setText(message);
        QPushButton* addBtn = msgBox.addButton("Add", QMessageBox::AcceptRole);
        QPushButton* nextBtn = msgBox.addButton("Next", QMessageBox::RejectRole);
        QPushButton* exitBtn = msgBox.addButton("Exit", QMessageBox::DestructiveRole);

        msgBox.exec();

        if (msgBox.clickedButton() == addBtn) {
            if (user.addEvent(ev)) {
                Event updated(ev.getTitle(), ev.getDescription(), ev.getDateTime(), ev.getNrPeople() + 1, ev.getLink());
                admin.updateEvent(ev.getTitle(), ev.getDescription(), updated.getTitle(), updated.getDescription(),
                    updated.getDateTime(), updated.getNrPeople(), updated.getLink());
                QMessageBox::information(this, "Added", "Event added to your list.");
            }
            else {
                QMessageBox::information(this, "Duplicate", "You already added this event.");
            }
            index++;
        }
        else if (msgBox.clickedButton() == nextBtn) {
            index++;
        }
        else if (msgBox.clickedButton() == exitBtn) {
            break;
        }
    }
}

*/
void UserWindow::showPersonalList() {
    std::vector<Event> personalEvents = user.getlist();
    table->setRowCount(static_cast<int>(personalEvents.size()));

    for (int i = 0; i < personalEvents.size(); ++i) {
        const Event& ev = personalEvents[i];
        const DateTime& dt = ev.getDateTime();

        QString date = QString("%1.%2.2025").arg(dt.date).arg(dt.month);
        QString time = QString("%1:%2").arg(dt.hour).arg(dt.minutes, 2, 10, QLatin1Char('0'));

        table->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(ev.getTitle())));
        table->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(ev.getDescription())));
        table->setItem(i, 2, new QTableWidgetItem(date));
        table->setItem(i, 3, new QTableWidgetItem(time));
        table->setItem(i, 4, new QTableWidgetItem(QString::number(ev.getNrPeople())));
        table->setItem(i, 5, new QTableWidgetItem(QString::fromStdString(ev.getLink())));
    }
}

void backToMenu() {

}