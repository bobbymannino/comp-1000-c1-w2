#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <regex>
#include <map>
#include <string>
#include "testdb.h"
#include "studentrecord.h"
using namespace std;

/*
 * Updates an EXISTING user in an existing database file
 *
 * The user can pass the following parameters to this application:
 * 
 *  updaterecord -db <database file> -sid <id> [-name <name>] [-phone <phone-number>] [-modulecode <code> -grade <grade>]
 *
 *  updaterecord
 *   Without any parameters, this creates an example database file computing.txt (already done for you)
 *
 *  The -db <database file> parameters are ALWAYS required if you wish to update any records.
 *   If the file does not exist, it should be created (as an empty database)
 * 
 *  When -sid parameter is provided, you must also provide an integer <id>.
 *   The <id> must match a record in the database file.
 * 
 *  The following properties are optional, and may be provided to update data for a given student with id <sid>:
 *
 *   o The student name can be updated with the -name tag. The value <name> is a string, composed of at least two words, separated by spaces. This should replace the existing name
 * 
 *   o The phone number can be added OR updated by specifying the -phone parameter followed by a new phone number. 
 * 
 *   o An individual student grade can be added OR updated using the -modulecode and -grade parameters together.
 *
 * Note that the format of all data items should be consistent with those specified in the previous tasks.
 * The same error checking should also apply.
 *
 * **********************
 * *** VALID EXAMPLES ***
 * **********************
 *
 *
 * Create an empty database file computing.txt
 *  updaterecord -db computing.txt
 * 
 * update the phone number of a record with a student ID 12345
 *  updaterecord -db computing.txt -sid 12345 -phone 00-12-34567
 *
 * update the name and phone number of a record with a student ID 12345
 *  updaterecord -db computing.txt -sid 12345 -phone 00-12-34567 -name Jo Kingly Blunte
 *
 * update (or add) the COMP1001 grade for student with id 12345
 *  updaterecord -db computing.txt -sid 12345 -modulecode COMP1001 -grade 78.4
 *
 * Enrol the student in COMP1001 for student with id 12345
 *  updaterecord -db computing.txt -sid 12345 -modulecode COMP1001
 *
 * **********************
 * *** INVALID EXAMPLES *
 * **********************
 * 
 *  Examples of invalid parameters include:
 *
 *  Missing the database tag
 *   updaterecord -sid 12345
 *
 *  ID does not exist (assuming there is no record with ID 99999)
 *   updaterecord -db computing.txt -sid 99999 -modulecode COMP1001 -grade 78.4
 *
 *  Missing module code
 *   updaterecord -db computing.txt -sid 12345 -grade 78.4
 * 
 *  Spaces in the phone number
 *   updaterecord -db computing.txt -sid 12345 -phone 00 12 34567 -name Jo Kingly Blunte
 *
 *  Name is missing
 *   updaterecord -db computing.txt -sid 12345 -phone 00-12-34567 -name
 *
 *  Name must have at least 2 words
 *   updaterecord -db computing.txt -sid 12345 -phone 00-12-34567 -name Sam
 * 
 * *************
 * *** NOTES ***
 * *************
 * 
 * o The verb update implies you are changing an existing object. The object in this context is a student record.
 *  o You cannot update a student record that does not exist
 *  o You cannot add a student record with update command
 *  o You can update OR add data within an existing record
 *   o For example, if you update a student phone number and no number is currently held on record, 
 *     then in effect you are adding a phone number.
 * o Errors should be communicated with the user
 * o No tag should be repeated (e.g. you cannot specify -sid twice)
 * o Open files should always be closed before the program exits
 * o Code should be consistently indented and commented
 * o Marks are awarded for reuse of code from Tasks A and/or B (where possible)
 * o Marks are awarded for using Object Orientated Programming to make your code more modular and reusable
*/

// Main program here

int findArg(int argc, char* argv[], string pattern);
bool isLastArg(int argc, int argi);
void updateRecord(string fileName, int sid, string name, int phoneNumber, vector<float> grades, vector<string> enrollments, int gradesLen);
void checkFlags(char* argv[], vector<string> flags, int argc);
int countOf(string arg, char* argv[], int argc);

int main(int argc, char* argv[])
{
    if (argc == 1) {
        //Welcome message
        cout << "updaterecord (c)2023" << endl;

        //Create some test data
        createTestDB("computing.txt");

        //Done
        return EXIT_SUCCESS;
    }

    checkFlags(argv, { "-db", "-sid", "-name", "-phone", "-modulecodes", "-grades" }, argc);

    string dataBaseName;
    int p = findArg(argc, argv, "-db");
    if (p) {
        dataBaseName = argv[p + 1];
        cout << "Data base: " << dataBaseName << "\n";
    }
    else {
        cout << "Please proviude a database with -db <filename>\n";
        return EXIT_FAILURE;
    }

    //Open database file
    ifstream ip(dataBaseName);
    if (!ip.is_open()) {
        cout << "Cannot open file " << dataBaseName << "\n";
        return EXIT_FAILURE;
    }
    ip.close();

    // Check for student id
    int sidArgIndex = findArg(argc, argv, "-sid"); // 0 if flag does not exist. if the flag exists whatever number index it will be
    if (!sidArgIndex)
    {
        cout << "Please provide a student id with -sid <id>\n";
        return EXIT_FAILURE;
    }
    // sidArgIndex = index of -sid
    // check if there is another argument afterwards
    // set sid to that argument
    // check if its a number

    bool sidIsLastArg = isLastArg(argc, sidArgIndex);
    // true || false
    if (sidIsLastArg == true) {
        cout << "Please provide a sid with a number\n";
        return EXIT_FAILURE;
    }

    int sid;
    try {
        sid = stoi(argv[sidArgIndex + 1]);
	}
    catch (exception e) {
        cout << "Please provide a sid with a number\n";
        return EXIT_FAILURE;
    }
    // sid = a number

    // check if at least one flag exists
    int phoneArgIndex = findArg(argc, argv, "-p");
    int nameArgIndex = findArg(argc, argv, "-n");
    int enrollmentsArgIndex = findArg(argc, argv, "-e");
    int gradesArgIndex = findArg(argc, argv, "-g");

    if (!(phoneArgIndex || nameArgIndex || enrollmentsArgIndex || gradesArgIndex)) {
        cout << "Please provide at least one flag\n";
		return EXIT_FAILURE;
    }

    string newName = "";
    // check if name flag exists
    if (nameArgIndex) {
        // check if there is another argument afterwards
		bool nameIsLastArg = isLastArg(argc, nameArgIndex);
        if (nameIsLastArg == true) {
			cout << "Please provide a name\n";
			return EXIT_FAILURE;
		}

        // Set new name to argument after name flag
        int nameCount = 0;
        for (int i = nameArgIndex + 1; i < argc; i++) {
            if (isLastArg(argc, i) && argv[i][0] != '-') {
                nameCount += 1;
                newName += argv[i];
                newName += " ";

                if (nameCount < 2)
                {
                    cout << "Please provide a 2 or more words name\n";
                    return EXIT_FAILURE;
                }

                break;
            }

            if (argv[i][0] == '-') {
                if (nameCount < 2)
                {
                    cout << "Please provide a 2 or more words name\n";
                    return EXIT_FAILURE;
                }

                break;
            }

            nameCount += 1;
            newName += argv[i];
            newName += " ";
        }
        // name needs to be 2+ words
    }
    // name = "" || "bob bob"

    // check if phone flag exists
    // check if its a number

    int newPhone = 0;
    if (phoneArgIndex) {
        // check if there is another argument afterwards
		bool phoneIsLastArg = isLastArg(argc, phoneArgIndex);
		if (phoneIsLastArg == true){
			cout << "Please provide a number\n";
			return EXIT_FAILURE;
        }

        // if phone number exists in 2+ parts
        // e.g. 3456 45678
        if (!isLastArg(argc, phoneArgIndex + 1) && argv[phoneArgIndex + 2][0] != '-') {
			cout << "Please provide a phone number as a single int\n";
			return EXIT_FAILURE;
		}

        // check if its a number
        try {
            newPhone = stoi(argv[phoneArgIndex + 1]);
        }
        catch (exception e) {
            cout << "Please proviude a phone number as an int\n";
            return EXIT_FAILURE;
        }
    }
    // phone = 0 || 123456789

    vector<string> newEnrollments;
    vector<float> newGrades;
    int newGradesLen = 0;
    int newEnrollmentsLen = 0;

    if (enrollmentsArgIndex && !isLastArg(argc, enrollmentsArgIndex)) {
        if (gradesArgIndex && !isLastArg(argc, gradesArgIndex)) {
            int i = enrollmentsArgIndex + 1;

            for (int i = enrollmentsArgIndex + 1; i < argc; i++) {
                if (argv[i][0] == '-') break;

                newEnrollments.push_back(argv[i]);
                newEnrollmentsLen += 1;
            }

            i = gradesArgIndex + 1;
            for (int i = gradesArgIndex + 1; i < argc; i++) {
                if (argv[i][0] == '-') break;

                try {
                    newGrades.push_back(stof(argv[i]));
                }
                catch (exception e) {
                    cout << "Make sure grades are of type float\n";
                    return EXIT_FAILURE;
                }
                newGradesLen += 1;
            }

            if (newGradesLen != newEnrollmentsLen) {
                cout << "Please proviude the same number of grades as enrollments\n";
                return EXIT_FAILURE;
            }
        }
        else {
            cout << "Please proviude grades with -g <grade1> <grade2> ... <gradeN>\n";
            return EXIT_FAILURE;
        }
    }
    else if (gradesArgIndex && !isLastArg(argc, gradesArgIndex)) {
        cout << "Please proviude enrollments with -e <enrollment1> <enrollment2> ... <enrollmentN>\n";
        return EXIT_FAILURE;
    }
    // grades = [] || [1.00, 2.00, 2.50]
    // enrollments = [] || ["COMP1001", "COMP1002", "COMP1003"]

    updateRecord(dataBaseName, sid, newName, newPhone, newGrades, newEnrollments, newGradesLen);

    return EXIT_SUCCESS;
}

// Checks no more then one of each flag exists
void checkFlags(char* argv[], vector<string> flags, int argc)
{
    for (string flag : flags)
    {
        if (countOf(flag, argv, argc) > 1) {
            cerr << "Please provide only one " << flag << " flag" << endl;
            return exit(EXIT_FAILURE);
        }
    }
}

// A function to count the amount of times a string apears
int countOf(string arg, char* argv[], int argc)
{
    int count = 0;
    for (int i = 0; i < argc; i++) {
        string s1(argv[i]);

        if (arg == s1) count++;
    }
    return count;
}

// Find an argument on the command line and return the location
int findArg(int argc, char* argv[], string pattern)
{
    for (int n = 1; n < argc; n++) {
        string s1(argv[n]);

        if (s1 == pattern) return n;
    }

    return 0;
}

// Returns is the arg index is the last arg
bool isLastArg(int argCount, int argIndex)
{
    return argIndex + 1 == argCount;
}

void updateRecord(string fileName, int sid, string newName, int newPhoneNumber, vector<float> newGrades, vector<string> newEnrollments, int newGradesLen) {
    // open file
    
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

    //This is just an integer type, where START=0, NEXTTAG=1, RECORD=2 etc.....
    enum state_t { START, NEXTTAG, RECORD, SID, NAME, ENROLLMENTS, GRADES, PHONE };
    state_t state = START;

    //"Look up table" - maps a string to an integer. e.g. nextState["#SID"] returns 1
    map<string, state_t> nextState = {
        {"#RECORD", RECORD},
        {"#SID", SID},
        {"#NAME", NAME},
        {"#ENROLLMENTS", ENROLLMENTS},
        {"#GRADES", GRADES},
        {"#PHONE", PHONE}
    };
    // 
    //*********
    //Main loop
    //*********

    ifstream ip(fileName);

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
                    nextRecord = { 0 };
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
        ip.close();

    }
    catch (exception e) {
        //Many things could go wrong, so we catch them here, tell the user and close the file (tidy up)
        ip.close();
        cout << "Error reading data" << endl;
        cerr << e.what() << endl;
    } 
    //end try
    
    // edit said record with sid (if exists)
    // for loop to go through every record in vector
    int indexOfRecord = -1;
    for (int i = 0; db.size(); i++) {
        // if the student id is in the database
        if (db[i].SID == sid) {
            indexOfRecord = i;
            break;
        }
    }

    // if record does not exist (-1)
    if (indexOfRecord == -1) {
		cout << "Record with sid " << sid << " does not exist\n";
		return;
	}
   
    // update said record
    if (newName != "") db[indexOfRecord].name = newName;
    if (newPhoneNumber != 0) db[indexOfRecord].phone = to_string(newPhoneNumber);
    if (newGradesLen) {
        db[indexOfRecord].grades = {};
        for (int i = 0; i < newGradesLen; i++) {
			db[indexOfRecord].grades.push_back(newGrades[i]);
		}


        db[indexOfRecord].enrollments = {};
        for (int i = 0; i < newGradesLen; i++) {
            db[indexOfRecord].enrollments.push_back(newEnrollments[i]);
        }
    }

    string newFileStr = "";

    for (int i = 0; i < db.size(); i++) {
		newFileStr += "#RECORD\n";
		newFileStr += " #SID\n";
		newFileStr += "     " + to_string(db[i].SID) + "\n";
		newFileStr += " #NAME\n";
		newFileStr += "     " + db[i].name + "\n";
        if (db[i].enrollments.size()) {
            newFileStr += " #ENROLLMENTS\n";
            newFileStr += "     ";
            for (int j = 0; j < db[i].enrollments.size(); j++) {
                newFileStr += db[i].enrollments[j] + " ";
            }
            newFileStr += "\n";
            newFileStr += " #GRADES\n";
            newFileStr += "     ";
            for (int j = 0; j < db[i].grades.size(); j++) {
                newFileStr += to_string(db[i].grades[j]) + " ";
            }
		    newFileStr += "\n";
        }
        if (db[i].phone != "") {
            newFileStr += " #PHONE\n";
            newFileStr += "     " + db[i].phone + "\n";
        }
        newFileStr += '\n';
	}


    ofstream outFile(fileName);

    outFile << newFileStr;

    outFile.close();
    
    // close file
    ip.close();
}