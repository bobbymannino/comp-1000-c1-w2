#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <regex>
#include <map>
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "studentrecord.h"
#include <QFileDialog>
#include <QMessageBox>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

vector<Record> stringToRecords(string str);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_Open_Database_triggered()
{
    QString selectedFilePath = QFileDialog::getOpenFileName(this, tr("Open Database"), QDir::homePath(), tr("Database Files (*.txt)"));

    QFile file(selectedFilePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString fileContents = in.readAll();
        file.close();

        ui->nameLabel->setText(fileContents);
        vector<Record> db = stringToRecords(fileContents.toStdString());
        ui->nameLabel->setText(QString::fromStdString(db[0].name));

    } else {
        QMessageBox::information(nullptr, "Alert", "Failed to open file");
    }
}

vector<Record> stringToRecords(string str) {
vector<Record> db;

//Locals used for navigating the database file
string nextLine;
string nextStr;
int recordNumber = -1;
Record nextRecord;
stringstream moduleCodes;
stringstream moduleGrades;
string moduleCode = "";
string moduleGrade = "";

//Locals used for the "state machine"

//This is just an integer type, where START=0, NEXTTAG=1, RECORD=2 etc.....
enum state_t {START, NEXTTAG, RECORD, SID, NAME, ENROLLMENTS, GRADES, PHONE};
state_t state = START;

//"Look up table" - maps a string to an integer. e.g. nextState["#SID"] returns 1
map<string,state_t> nextState = {
    {"#RECORD", RECORD},
    {"#SID", SID},
    {"#NAME", NAME},
    {"#ENROLLMENTS", ENROLLMENTS},
    {"#GRADES", GRADES},
    {"#PHONE", PHONE}
};


stringstream ip(str);
try
{
    //Read the next line (loop exits on end of file)
    while (getline(ip, nextLine))
    {
        // Remove leading spaces
        // Replace "start of line (^) followed by any number of trailing spaces (' +')" with with nothing ""
        string nextStr = regex_replace(nextLine, regex("^ +"), "");

        //Skip blank lines
        if (nextStr.empty()) continue;

        //Enter "state machine" - study this carefully - it's a really useful "pattern"
        switch (state)
        {
        case START:
            //We begin here - the first non-blank line MUST start with "#RECORD"
            if (nextStr != "#RECORD") {
                //The first list MUST simply read #RECORD
                throw("Expected #RECORD as first tag");
            }
            //Next time around the loop, use the RECORD state
            state = RECORD;
            recordNumber = 0;
            break;
        case RECORD: //Everytime a #RECORD is found, we enter this state on the next line
            //Except for the first occasion, save the record we have just finished reading
            if (recordNumber > 0) {
                //For each new #RECORD tag, store the previous
                db.push_back(nextRecord);
                //Reset the nextRecord to defaults
                nextRecord = {0};
            }
            //Increment the record number
            recordNumber++;
            //Fall through into SEEK (note the break is missing) - #RECORD is always followed by a tag
        case NEXTTAG:
            //nextString should contain a tag at this point - will throw an exception if not
            state = nextState[nextStr];
            break;
        case SID:
            //nextStr should contain a string representation of an integer. If not, an exception will be thrown
            nextRecord.SID = stoi(nextStr);
            //Now look for the next tag
            state = NEXTTAG;
            break;
        case NAME:
            //nextStr should contain a name
            nextRecord.name = nextStr;
            state = NEXTTAG;
            break;
        case ENROLLMENTS:
            //nextString should be a list of module codes separated by spaces
            moduleCodes = stringstream(nextStr);
            //Extract each separate module code
            while (moduleCodes.eof() == false) {
                moduleCodes >> moduleCode;
                //If the prevous line did not succeed, we've probably read a space on the end
                if (moduleCodes.fail()) {
                    break;
                }
                //Add the module string to the `enrollments` vector
                nextRecord.enrollments.push_back(moduleCode);
            }
            state = NEXTTAG;
            break;
        case GRADES:
            //nextString should contain a list of grades, separated by spaces
            moduleGrades = stringstream(nextStr);
            //Extract each separate module grade as a float
            while (moduleGrades.eof() == false) {
                moduleGrades >> moduleGrade;
                if (moduleGrades.fail()) {
                    break;
                }
                //Convert to float, and save in the grades vector
                nextRecord.grades.push_back(stof(moduleGrade)); //This can throw an exception
            }
            state = NEXTTAG;
            break;

        case PHONE:
            //Next String should be a phone number (no spaces)
            nextRecord.phone = nextStr;
            state = NEXTTAG;
            break;
        } //End Switch

    } //End while

    //The loop above may exit before pushing the last record into db
    if (nextRecord.SID > 0) {
        db.push_back(nextRecord);
    }

    //Close the file - we are done reading it. Everything is now in the db vector

}  catch (exception e) {
    QMessageBox::information(nullptr, "Alert", "Failed to read file");
    return {};

} //end try

return db;


}
