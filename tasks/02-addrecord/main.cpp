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

int findArg(int argc, char* argv[], string pattern);
bool isLastArg(int argc, int argi);
void addRecord(string fileName, int sid, string name, int phoneNumber, vector<float> grades, vector<string> enrollments, int gradesLen);
bool isSidInDb(string fileName, int sid);
int countOf(string arg, char* argv[], int argc);

/*
 * Adds a NEW user to the end of an existing database file or the start of a new file
 *
 * The user can pass the following parameters to this application:
 *
 * addrecord -db <database file> [-sid <id> -name <name> [-phone <phone-number>] [-modulecodes <code1> <code2> ... <codeN> [-grades <grade1> <grade2> ... <gradeM> ]]]
 *
 * addrecord
 *  Without any parameters, this creates an example database file computing.txt (already done for you)
 *
 * The -db <database file> parameters are ALWAYS required if you wish to add a record.
 *  If the file does not exist, it should be created (as an empty database)
 * 
 * Where -sid is provided.
 *    • A numerical student ID <id> MUST also be provided.
 *       o <id> must be an unsigned integer. 
 *       o <id> must be unique. If another record in the database has the same value, an error should be reported.
 * 
 * Where -sid is provided, the following MUST also be included:
 *    • The tag -name and a student name <name>.
 *       o <name> is a full name, so will comprise only alphabetical characters and spaces.
 *       o <name> must contain at least two words separated by spaces.
 * 
 * Where -sid is provided, the following MAY also be included:
 *    • The tag -phone followed by a phone number.
 *      o <phone-number> is a string with no spaces.
 *    • The tag -modulecodes, followed by a list of module codes.
 *       o Each module code is a single alpha-numeric word. It cannot contain any symbols.
 *       o Each module code is separated by a space.
 *       o There must be at least one module code provided.
 *    • IF a -modulecodes tag is provided, the following MAY also be provided:
 *       o The tag -grades, followed by a list of grades.
 *       o Each grade must be a fractional number.
 *       o Each grade must be separated by a space.
 *       o The number of grades MUST match the number of module codes.
 *       o You cannot use -grades tag without an accompanying -modulecodes tag
 * 
 *
 * **********************
 * *** VALID EXAMPLES ***
 * **********************
 *
 * Create an empty database file computing.txt
 *  addrecord -db computing.txt
 * 
 * Add a record with a student ID <id> and name <name>, where <id> is an integer and name <name> is a string (space separated)
 *  addrecord -db computing.txt -sid 12345 -name Sam Eold
 *
 * This version also includes the phone number <phone>, where <phone> is a string with no spaces
 *  addrecord -db computing.txt -sid 12345 -name Sam Eold -phone 44-1234-456123
 *
 * This version includes the modules the student is enrolled on
 *  addrecord -db computing.txt -sid 13579 -name Les Sismore -modulecodes COMP101 COMP110 COMP123 COMP145 COMP165
 *
 * This includes the grades as well as the module codes. The number of grades must equal the number of codes or an error is displayed
 *  addrecord -db computing.txt -sid 24680 -name Jo King -modulecodes COMP101 COMP110 COMP123 COMP145 COMP165 -grades 40.5 55.6 35.7 67.5 80.1
 *
 *
 * *************************************
 * *** EXAMPLES OF INVALID ARGUMENTS ***
 * *************************************
 *
 *  Missing the database filename
 *   addrecord -db -sid 12345 -name Sam Eold
 *
 *  Name is missing
 *   addrecord -db computing.txt -sid 12345
 *
 *  -sid is missing
 *   addrecord -db computing.txt -name Sam Eold
 *
 *  <id> is not an integer
 *   addrecord -db computing.txt -sid a2345 -name Sam Eold
 *
 *  phone number cannot contain spaces
 *   addrecord -db computing.txt -sid 12345 -name Sam Eold -phone 44 01234 456123
 *
 *  grades cannot be provided without module codes
 *   addrecord -db computing.txt -sid 24680 -name Jo King -grades 40.5 55.6 35.7 67.5 80.1
 *
 *  Number of module codes and grades do not match
 *  addrecord -db computing.txt -sid 24680 -name Jo King -modulecodes COMP101 COMP110 -grades 40.5 55.6 35.7
 *
 * *************
 * *** NOTES ***
 * *************
 * 
 * o The verb ADD implies you are created a new object. The object in this context is a student record.
 *  o You cannot add a student record that already exists
 *  o To add data to a student record that already exist, see task C
 * 
 * o Errors should be communicated with the user
 * o No tag should be repeated (e.g. you cannot specify -sid twice)
 * o New records should be added to the end of the database file (known as appending). See the labs on FileIO and ios::app
 * o Open files should always be closed before the program exits
 * o You may copy or (better) reuse code from Task A where possible
 * o Code should be consistently indented and commented
*/

// Main program here - you may shared / reuse as much code as you like with other projects included in this starter code

int main(int argc, char *argv[])
{
    // argv is an array of strings, where argv[0] is the path to the program, argv[1] is the first parameter, ...
    // argc is the number of strings in the array argv
    // These are passed to the application as command line arguments
    // Return value should be EXIT_FAILURE if the application exited with an error, or EXIT_SUCCESS otherwise

    if (argc == 1) {
        //Welcome message
        cout << "addrecord (c)2023" << endl;

        //Create some test data
        createTestDB("computing.txt");

        //Done
        return EXIT_SUCCESS;
    }

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

    vector<string> flags = {"-sid", "-name", "-phone", "-modulecodes", "-grades"};
    for (string flag : flags)
    {
        if (countOf(flag, argv, argc) > 1) {
            cerr << "Please provide only one " << flag << " flag" << endl;
            return EXIT_FAILURE;
        }
    }

    int sidArgInt = findArg(argc, argv, "-sid");
    if (!sidArgInt || isLastArg(argc, sidArgInt)) {
        cout << "Please proviude a student ID with -sid <id>\n";
		return EXIT_FAILURE;
    }
    // we know there is a sid
  
    int sid;

    try {
		sid = stoi(argv[sidArgInt + 1]);
	}
    catch (exception e) {
		cout << "Please proviude a student ID as an int\n";
		return EXIT_FAILURE;
	}
    // we know its a number
    // if sid is > 0
    if (sid < 1) {
		cout << "Please proviude a student ID as an int greater then 0\n";
        return EXIT_FAILURE;
    }
    // if sid is unique
    if (isSidInDb(dataBaseName, sid)) 
    {
        cout << "Please proviude a unique student ID\n";
    	return EXIT_FAILURE;
    }

    int nameArgInt = findArg(argc, argv, "-name");
    if (!nameArgInt || isLastArg(argc, nameArgInt)) {
		cout << "Please proviude a student name with -name <name>\n";
        return EXIT_FAILURE;
    }

    string name = "";
    int nameCount = 0;
    for (int i = nameArgInt + 1; i < argc; i++) {
        if (isLastArg(argc, i) && argv[i][0] != '-') {
            nameCount += 1;
            name += argv[i];
            name += " ";

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
        name += argv[i];
        name += " ";
    }
    // name needs to be 2+ words


    // 1 && bigger then truethy
    // 0 and below is falsey
    
    // Below this we know there is a name and a sid thats a number

    int phoneArgInt = findArg(argc, argv, "-phone");
    int phone = 0;
    if (phoneArgInt && !isLastArg(argc, phoneArgInt)) {
        if (!isLastArg(argc, phoneArgInt + 1) && argv[phoneArgInt + 2][0] != '-') {
            cout << "No spaces in phone number\n";
            return EXIT_FAILURE;
        }

        try {
			phone = stoi(argv[phoneArgInt + 1]);
		}
        catch (exception e) {
			cout << "Please proviude a phone number as an int\n";
			return EXIT_FAILURE;
		}
	}

    int enrollmentsArgInt = findArg(argc, argv, "-modulecodes");
    int gradesArgInt = findArg(argc, argv, "-grades");

    vector<string> enrollments;
    vector<float> grades;
    int gradesLen = 0;
    int enrollmentsLen = 0;

    if (enrollmentsArgInt && !isLastArg(argc, enrollmentsArgInt)) {
        if (gradesArgInt && !isLastArg(argc, gradesArgInt)) {
            int i = enrollmentsArgInt + 1;

            for (int i = enrollmentsArgInt + 1; i < argc; i++) {
                if (argv[i][0] == '-') break;

                enrollments.push_back(argv[i]);
                enrollmentsLen += 1;
            }


            i = gradesArgInt + 1;
            for (int i = gradesArgInt + 1; i < argc; i++) {
                if (argv[i][0] == '-') break;

                try {
                    grades.push_back(stof(argv[i]));
                }
                catch (exception e) {
                    cout << "Make sure grades are of type float\n";
                    return EXIT_FAILURE;
                }
                gradesLen += 1;
            }

            if (gradesLen != enrollmentsLen) {
				cout << "Please proviude the same number of grades as enrollments\n";
				return EXIT_FAILURE;
			}
		} else {
			cout << "Please proviude grades with -grades <grade1> <grade2> ... <gradeN>\n";
			return EXIT_FAILURE;
		}
    }
    else if (gradesArgInt && !isLastArg(argc, gradesArgInt)) {
        cout << "Please proviude enrollments with -modulecodes <enrollment1> <enrollment2> ... <enrollmentN>\n";
        return EXIT_FAILURE;
    }

    addRecord(dataBaseName, sid, name, phone, grades, enrollments, gradesLen);

    return EXIT_SUCCESS;
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

void addRecord(string fileName, int sid, string name, int phone, vector<float> grades, vector<string> enrollments, int gradesLen) {
    string newRecord  = "\n#RECORD\n";
    newRecord += " #SID\n";
    newRecord += "     " + to_string(sid);
    newRecord += "\n #NAME\n";
    newRecord += "     " + name;

    if (gradesLen) {
        newRecord += "\n #ENROLLMENTS\n";
        newRecord += "     ";
        for (int i = 0; i < gradesLen; i++) {
            newRecord += enrollments[i] + " ";
        }
        newRecord += "\n #GRADES\n";
        newRecord += "     ";
        for (int i = 0; i < gradesLen; i++) {
            newRecord += to_string(grades[i]) + " ";
        }
        newRecord += "\n";
    }

    if (phone) {
		newRecord += " #PHONE\n";
		newRecord += "     " + to_string(phone) + "\n";
	}

    ifstream inFile(fileName);

    string line;

    string currentRecords = "";

    while (getline(inFile, line)) {
        currentRecords += line + "\n";
    }

    inFile.close();

    ofstream outFile(fileName);

    currentRecords += newRecord;

    outFile << currentRecords;

    outFile.close();

    printf("Added record to %s\n", fileName.c_str());
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
bool isLastArg(int argc, int argi)
{
	return argi + 1 == argc;
}

bool isSidInDb(string fileName, int sid) {
	ifstream inFile(fileName);

	string line;

    while (getline(inFile, line)) {
        if (line == " #SID") {
			getline(inFile, line);
            if (stoi(line) == sid) {
				cout << "Student ID already in database\n";
                inFile.close();
				return true;
			}
		}
	}

    inFile.close();

	return false;
}