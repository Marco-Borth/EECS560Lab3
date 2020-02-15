/* -----------------------------------------------------------------------------
 *
 * File Name:  Operator.cpp
 * Author: Marco Borth
 * Assignment:   EECS-560 Lab 3 - Implementation of Hash Table (Closed Hashing)
 * Description:  Operator Class will either run the Interactive program for a Hash Table (Closed Hashing)
 * Date: 2/15/20
 *
 ---------------------------------------------------------------------------- */

#include "Operator.h"
#include <iostream>
#include <string>
#include <fstream>
#include <limits>
using namespace std;

Operator::Operator(string filename){
  file = filename;
  uParse = "\0";
  pParse = "\0";
  uname = "\0";
  pword = "\0";
  hashValue = 0;
  placedLinear = false;
  placedQuadratic = false;
}

void Operator::printCommands() {
  cout << "Please choose one of the following commands:\n\n";
  cout << "1- Add User\n";
  cout << "2- Remove User\n";
  cout << "3- Forgot Password\n";
  cout << "4- Forgot Username\n";
  cout << "5- Print Users\n";
  cout << "6- Exit\n\n> ";
}

void Operator::parseUsername(string parse) {
  uname = "\0";

  for (int i = 0; i < parse.length(); i++) {
    if(parse.at(i) != ':' && parse.at(i) != ' ' && parse.at(i) != ',')
    uname = uname + parse.at(i);
  }
}

void Operator::parsePassword(string parse) {
  pword = "\0";

  for (int i = 0; i < parse.length(); i++) {
    if(parse.at(i) != ':' && parse.at(i) != ' ' && parse.at(i) != ',')
    pword = pword + parse.at(i);
  }
}

int Operator::hashKey(string passkey) {
  int key = 0;

  for (int i = 0; i < passkey.length(); i++) {
    char ascii = passkey.at(i);

    if (int (ascii) >= 48 && int (ascii) <= 57) {
      key = key + ( (int (ascii) + 2) % 10 );
    } else {
      key = key + ascii;
    }
  }

  return key;
}

void Operator::insertRecord(string table) {
  hashValue = hashKey(pword);
  int index = hashValue % hashTableLength;
  int position = 0;

  if (table == "LinearTable") {
    placedLinear = false;

    while(!placedLinear && position < LinearTable.getLength()) {
      if(LinearTable.getEntry(index + 1).getUsername() == "\0" &&
         LinearTable.getEntry(index + 1).getPassword() == "\0" &&
         LinearTable.getEntry(index + 1).getUsername() != uname) {
        placedLinear = true;
        LinearTable.replace(index + 1, User(uname, pword));
      } else {
        index++;
        position++;
        index = index % hashTableLength;
      }
    }
  } else if (table == "QuadraticTable") {
    placedQuadratic = false;
    int exponent = position;

    while(!placedQuadratic && position < QuadraticTable.getLength()) {
      if(QuadraticTable.getEntry(index + 1).getUsername() == "\0" &&
         QuadraticTable.getEntry(index + 1).getPassword() == "\0" &&
         QuadraticTable.getEntry(index + 1).getUsername() != uname) {
        placedQuadratic = true;
        QuadraticTable.replace(index + 1, User(uname, pword));
      } else {
        position++;
        exponent = position^2;
        index = ( (index % hashTableLength) + exponent ) % hashTableLength;
      }
    }
  }

  // Insert is over.
}

void Operator::run() {
  cout << "\nWelcome to the Interactive Hash Table Program!\n\n";
  ifstream inFile;
  hashTableLength = 11;

  for (int i = 0; i < hashTableLength; i++) {
    LinearTable.insert(1, User());
    QuadraticTable.insert(1, User());
  }

  //Open File.
  inFile.open(file);

  if (!inFile.is_open()) {
    cout << "File name not valid!\n\n";
  } else {
    while (!inFile.eof( )) {
      inFile >> uParse >> pParse;

      parseUsername(uParse);
      parsePassword(pParse);

      if(inFile.fail()) {
        inFile.clear();
        inFile.ignore(numeric_limits<streamsize>::max(),'\n');
      } else {
        insertRecord("LinearTable");
        insertRecord("QuadraticTable");
      }
    }
  }

  // Close File.
  inFile.close();

  do {
    printCommands();
    cin >> option;

    while(1) {
      // Error Handling for an non-number entry.
      if(cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << "\nERROR! Invalid Option!\n\n"; //if not an int, must try again.
        printCommands();
        cin >> option;
      }
      // Operation Number has been selected.
      else {
        // 1- Add User - Complete!
        if (option == 1) {
          cout << "\nPreparing to Insert a New User...\n";

          cout << "\nEnter user details to be added:\n\n> ";
          cin >> uParse >> pParse;

          parseUsername(uParse);
          parsePassword(pParse);

          while(1) {
            if(cin.fail()) {
              cin.clear();
              cin.ignore(numeric_limits<streamsize>::max(),'\n');
              cout << "\n\nERROR! Invalid entry!\n\n";
              cout << "\nEnter user details to be added:\n\n> ";
              cin >> uParse >> pParse;

              parseUsername(uParse);
              parsePassword(pParse);
            } else {
              try {
                cout << "\nDeleting New User into the records...\n\n";

                insertRecord("LinearTable");
                cout << "Linear Probing:\n";
                if(placedLinear)
                  cout << "Record successfully inserted\n\n";
                else
                  cout << "ERROR! cannot place record\n\n";

                insertRecord("QuadraticTable");
                cout << "Quadratic Probing:\n";
                if(placedQuadratic)
                  cout << "Record successfully inserted\n\n";
                else
                  cout << "ERROR! cannot place record\n\n";
              } catch (runtime_error) {
                cout << "\nERROR! Invalid Position!\n\n";
              }

              break;
            }
          }

        }
        // 2- Remove User - Complete!
        else if (option == 2) {
          cout << "\nPreparing to Delete a New User...\n";

          cout << "\nEnter user and password to be removed:\n\n> ";
          cin >> uParse >> pParse;

          parseUsername(uParse);
          parsePassword(pParse);

          while(1) {
            if(cin.fail()) {
              cin.clear();
              cin.ignore(numeric_limits<streamsize>::max(),'\n');
              cout << "\n\nERROR! Invalid entry!\n\n";
              cout << "\nEnter user and password to be removed:\n\n> ";
              cin >> uParse >> pParse;

              parseUsername(uParse);
              parsePassword(pParse);
            } else {
              try {
                cout << "\nDeleting Defined User from the records...\n\n";

                hashValue = hashKey(pword);

                placedLinear = false;
                int index = hashValue % hashTableLength;
                int position = 0;

                while(!placedLinear && position < LinearTable.getLength()) {
                  if(LinearTable.getEntry(index + 1).getUsername() == uname &&
                     LinearTable.getEntry(index + 1).getPassword() == pword) {
                    placedLinear = true;
                    LinearTable.replace(index + 1, User());
                  } else {
                    index++;
                    position++;
                    index = index % hashTableLength;
                  }
                }

                cout << "Linear Probing:\n";
                if(placedLinear)
                  cout << "Record successfully removed\n\n";
                else
                  cout << "ERROR! cannot remove record\n\n";

                placedQuadratic = false;
                index = hashValue % hashTableLength;
                position = 0;
                int exponent = position;

                while(!placedQuadratic && position < QuadraticTable.getLength()) {
                  if(QuadraticTable.getEntry(index + 1).getUsername() == uname &&
                     QuadraticTable.getEntry(index + 1).getPassword() == pword) {
                    placedQuadratic = true;
                    QuadraticTable.replace(index + 1, User());
                  } else {
                    position++;
                    exponent = position^2;
                    index = ( (index % hashTableLength) + exponent ) % hashTableLength;
                  }
                }

                cout << "Quadratic Probing:\n";
                if(placedQuadratic)
                  cout << "Record successfully removed\n\n";
                else
                  cout << "ERROR! cannot remove record\n\n";
              } catch (runtime_error) {
                cout << "\nERROR! Invalid Position!\n\n";
              }

              break;
            }
          }
        }
        // 3- Forgot Password - Complete!
        else if (option == 3) {
          cout << "\nEnter Username:\n\n> ";
          cin >> uParse;

          parseUsername(uParse);
          while(1) {
            if(cin.fail()) {
              cin.clear();
              cin.ignore(numeric_limits<streamsize>::max(),'\n');
              cout << "\n\nERROR! Invalid entry!\n\n";
              cout << "\nEnter Username:\n\n> ";
              cin >> uParse;

              parseUsername(uParse);
            } else {
              cout << "\nLooking for the password of Username: " << uname << "\n\n";

              bool linearFound = false;
              int index = 1;

              while(!linearFound && index <= LinearTable.getLength()) {
                if(LinearTable.getEntry(index).getUsername() == uname) {
                  linearFound = true;
                  pword = LinearTable.getEntry(index).getPassword();
                }
                index++;
              }

              cout << "Linear Probing:\n";
              if(linearFound)
                cout << uname << " : " << pword << "\n\n";
              else
                cout << "ERROR! Record does not exist\n\n";

              bool quadraticFound = false;
              index = 1;

              while(!quadraticFound && index <= LinearTable.getLength()) {
                if(QuadraticTable.getEntry(index).getUsername() == uname) {
                  quadraticFound = true;
                  pword = QuadraticTable.getEntry(index).getPassword();
                }
                index++;
              }

              cout << "Quadratic Probing:\n";
              if(quadraticFound)
                cout << uname << " : " << pword << "\n\n";
              else
                cout << "ERROR! Record does not exist\n\n";

              break;
            }
          }
        }
        // 4- Forgot Username - Complete!
        else if (option == 4) {
          cout << "\nEnter Password:\n\n> ";
          cin >> pParse;

          parsePassword(pParse);
          while(1) {
            if(cin.fail()) {
              cin.clear();
              cin.ignore(numeric_limits<streamsize>::max(),'\n');
              cout << "\n\nERROR! Invalid entry!\n\n";
              cout << "\nEnter Password:\n\n> ";
              cin >> pParse;

              parsePassword(pParse);
            } else {
              cout << "\nLooking for a Username with the password: " << pword << "\n\n";

              bool linearFound = false;
              int index = 1;

              while(!linearFound && index <= LinearTable.getLength()) {
                if(LinearTable.getEntry(index).getPassword() == pword) {
                  linearFound = true;
                  uname = LinearTable.getEntry(index).getUsername();
                }
                index++;
              }

              cout << "Linear Probing:\n";
              if(linearFound)
                cout << uname << " : " << pword << "\n\n";
              else
                cout << "ERROR! Record does not exist\n\n";

              bool quadraticFound = false;
              index = 1;

              while(!quadraticFound && index <= LinearTable.getLength()) {
                if(QuadraticTable.getEntry(index).getPassword() == pword) {
                  quadraticFound = true;
                  uname = QuadraticTable.getEntry(index).getUsername();
                }
                index++;
              }

              cout << "Quadratic Probing:\n";
              if(quadraticFound)
                cout << uname << " : " << pword << "\n\n";
              else
                cout << "ERROR! Record does not exist\n\n";

              break;
            }
          }
        }
        // 5- Print Users - Complete!
        else if (option == 5) {
          cout << "\nPrinting List of Users...\n\n";

          cout << "Linear Probing:\n";
          for(int i = 0; i < LinearTable.getLength(); i++) {
            cout << i << ":";
            try {
              if (LinearTable.getEntry(i + 1).getUsername() != "\0")
                cout << " " << LinearTable.getEntry(i + 1).getUsername() << ": " << LinearTable.getEntry(i + 1).getPassword();
            } catch (runtime_error) {
              cout << "\nERROR! Invalid Position!\n\n";
            }
            cout << "\n";
          }
          cout << "\n";

          cout << "Quadratic Probing:\n";
          for(int i = 0; i < QuadraticTable.getLength(); i++) {
            cout << i << ":";
            try {
              if (QuadraticTable.getEntry(i + 1).getUsername() != "\0")
                cout << " " << QuadraticTable.getEntry(i + 1).getUsername() << ": " << QuadraticTable.getEntry(i + 1).getPassword();
            } catch (runtime_error) {
              cout << "\nERROR! Invalid Position!\n\n";
            }
            cout << "\n";
          }
          cout << "\n";
        }
        // 6- Exit - Complete!
        else if (option == 6) {
          cout << "\nClosing Program...\n";
        }
        // Otherwise - Complete!
        else {
          cout << "\nERROR! Invalid Option!\n\n";
        }

        break;
      }
    }
  } while(option != 6);
  LinearTable.~LinkedList();
  QuadraticTable.~LinkedList();

  uParse = "\0";
  pParse = "\0";
  uname = "\0";
  pword = "\0";
  hashValue = 0;

  cout << "\nBye Bye!\n";
  cout << "\nHave a nice day!...\n\n";
}
