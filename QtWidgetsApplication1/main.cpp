/*#include "QtWidgetsApplication1.h"
#include <QtWidgets/QApplication>
#include <crtdbg.h>

int main(int argc, char* argv[])
{

    
        QApplication a(argc, argv);
        QtWidgetsApplication1 w;
        w.setWindowTitle("Administrator View");
        w.resize(600, 400);
        w.show();
    
        _CrtDumpMemoryLeaks();
    

        return a.exec();
    
    
}
*/
#include <QApplication>
#include "QtWidgetsApplication1.h"
#include "UserWindow.h"
#include "CSVList.h"
#include "HTMLList.h"
#include "Administrator.h"
#include "User.h"
#include <QComboBox>
#include <QLabel>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    Repository repo;
    repo.loadFromFile("events.txt");

    Administrator admin(repo);

    //QWidget* startMenu = new QWidget;
    QWidget* startMenu = new QWidget;

    startMenu->setStyleSheet(R"(
    QWidget {
        background: qlineargradient(
            x1: 0, y1: 0, x2: 0, y2: 1,
            stop: 0   #89f7fe,   /* Light sky blue */
            stop: 0.5 #6ec6ff,   /* Medium blue */
            stop: 0.75 #5ca9ff,  /* Slightly deeper blue */
            stop: 1   #4e8cff    /* Deeper, calmer blue */
        );
    }
)");
    QVBoxLayout* layout = new QVBoxLayout(startMenu);


    //QVBoxLayout* layout = new QVBoxLayout(startMenu);
 
   

    // Add file format choice
    QLabel* formatLabel = new QLabel("Choose format for personal list:");
    QComboBox* fileFormatCombo = new QComboBox();
    fileFormatCombo->addItem("CSV");
    fileFormatCombo->addItem("HTML");

    layout->addWidget(formatLabel);
    layout->addWidget(fileFormatCombo);

    // Buttons for mode
    QPushButton* adminButton = new QPushButton("Admin Mode");
    QPushButton* userButton = new QPushButton("User Mode");

    layout->addWidget(adminButton);
    layout->addWidget(userButton);

    // Admin window setup
    QtWidgetsApplication1* adminWindow = new QtWidgetsApplication1;
    QObject::connect(adminButton, &QPushButton::clicked, [=]() {
        adminWindow->show();
        startMenu->hide();

        QObject::connect(adminWindow, &QtWidgetsApplication1::backToMenu, [=]() {
            adminWindow->hide();
            startMenu->show();
            });

        });

    //  User mode - dynamic setup based on format selection
    QObject::connect(userButton, &QPushButton::clicked, [&repo, &admin, fileFormatCombo, startMenu]()  {
        FilePersonalList* fileList = nullptr;
        QString selected = fileFormatCombo->currentText();

        if (selected == "CSV")
            fileList = new CSVList("my_events.csv");
        else
            fileList = new HTMLList("my_events.html");

        User* user = new User(repo, fileList);
        UserWindow* userWindow = new UserWindow(*user, admin);
        userWindow->show();
        startMenu->hide();

        QObject::connect(userWindow, &UserWindow::backToMenu, [=]() {
            userWindow->close();
            startMenu->show();
            delete userWindow;
            delete user;
            });
        });

    startMenu->setWindowTitle("Select Mode");
    startMenu->show();

    return a.exec();
}

