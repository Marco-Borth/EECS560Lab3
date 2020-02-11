/* -----------------------------------------------------------------------------
 *
 * File Name:  Operator.cpp
 * Author: Marco Borth
 * Assignment:   EECS-560 Lab 2 - Implementation of Hash Table
 * Description:  Operator Class will either run the Interactive program for a Hash Table
 * Date: 2/4/20
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
  hashKey = 0;
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

void Operator::run() {
  cout << "\nWelcome to the Interactive Hash Table Program!\n\n";
  ifstream inFile;
  hashTableLength = 11;

  LinkedList<User> LinearTable;
  LinkedList<User> QuadraticTable;

  for (int i = 0; i < hashTableLength; i++) {
    LinearTable.insert(1, User("\0","\0"));
    QuadraticTable.insert(1, User("\0","\0"));
  }

  //Open File.
  inFile.open(file);

  if (!inFile.is_open()) {
    cout << "File name not valid!\n\n";
  } else {
    while (!inFile.eof( )) {
      inFile >> uParse >> pParse;

      uname = "\0";

      for (int i = 0; i < uParse.length(); i++) {
        if(uParse.at(i) != ':' && uParse.at(i) != ' ' && uParse.at(i) != ',')
        uname = uname + uParse.at(i);
      }

      pword = "\0";

      for (int i = 0; i < pParse.length(); i++) {
        if(pParse.at(i) != ':' && pParse.at(i) != ' ' && pParse.at(i) != ',')
        pword = pword + pParse.at(i);
      }

      if(inFile.fail()) {
        inFile.clear();
        inFile.ignore(numeric_limits<streamsize>::max(),'\n');
      } else {
        hashKey = 0;

        for (int i = 0; i < pword.length(); i++) {
          char ascii = pword.at(i);

          if (int (ascii) >= 48 && int (ascii) <= 57) {
            hashKey = hashKey + ( (int (ascii) + 2) % 10 );
          } else {
            hashKey = hashKey + ascii;
          }
        }

        bool placedLinear = false;
        int index = hashKey % hashTableLength;

        while(!placedLinear) {
          if(LinearTable.getEntry(index + 1).getUsername() == "\0") {
            placedLinear = true;
            LinearTable.replace(index + 1, User(uname, pword));
          } else {
            index++;
            index = index % hashTableLength;
          }
        }

        bool placedQuadratic = false;
        index = hashKey % hashTableLength;
        int position = 0;
        int exponent = position;

        while(!placedQuadratic) {
          if (position < QuadraticTable.getLength()) {
            if(QuadraticTable.getEntry(index + 1).getUsername() == "\0") {
              placedQuadratic = true;
              QuadraticTable.replace(index + 1, User(uname, pword));
            } else {
              position++;
              exponent = position * position;
              index = ( index + exponent ) % hashTableLength;
            }
          } else {
            break;
          }
        }

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
        // 1. AddPlayer - Complete, but prone to input errors!
        if (option == 1) {
          cout << "\nPreparing to Insert a New Record...\n";

          /*
          cout << "\nEnter the record to be inserted:\n\n> ";
          cin >> srtInput;

          string strParser = "\0";

          for (int i = 0; i < srtInput.length(); i++) {
            if(srtInput.at(i) != ':')
            strParser = strParser + srtInput.at(i);
          }

          playerName = strParser;
          strParser = "\0";

          cin >> playerGoalRecord;

          while(1) {
            if(cin.fail()) {
              cin.clear();
              cin.ignore(numeric_limits<streamsize>::max(),'\n');
              cout << "\n\nERROR! Invalid entry!\n\n";
              cout << "\nEnter the record to be inserted:\n\n> ";
              cin >> srtInput;

              string strParser = "\0";

              for (int i = 0; i < srtInput.length(); i++) {
                if(srtInput.at(i) != ':')
                strParser = strParser + srtInput.at(i);
              }

              playerName = strParser;
              strParser = "\0";

              cin >> playerGoalRecord;
            } else {
              try {
                cout << "\nInserting " << playerName << " into the records...\n";

                bool isFound = false;

                for(int i = 0; i < hashTableLength; i++) {
                  if (hashTable[i].getLength() > 0) {
                    for (int j = 1; j <= hashTable[i].getLength(); j++) {
                      if (hashTable[i].getEntry(j).getName() == playerName && hashTable[i].getEntry(j).getGoalRecord() == playerGoalRecord) {
                        isFound = true;
                      }
                    }
                  }
                }

                if(isFound)
                  cout << "ERROR! Duplicate Entry Found. Player Record was not successfully inserted.\n\n";
                else {
                  int index = 0;
                  index = playerGoalRecord % hashTableLength;

                  hashTable[index].insert(hashTable[index].getLength() + 1, Player(playerName, playerGoalRecord));

                  cout << "Player Record was successfully inserted.\n\n";
                }
              } catch (runtime_error) {
                cout << "\nERROR! Invalid Position!\n\n";
              }

              break;
            }
          }
          */
        }
        // 2. RemovePlayer - Complete!
        else if (option == 2) {
          cout << "\nPreparing to Delete a Record...\n";

          /*
          int value;
          cout << "\nEnter a record with required goals to be removed:\n\n> ";
          cin >> value;

          while(1) {
            if(cin.fail()) {
              cin.clear();
              cin.ignore(numeric_limits<streamsize>::max(),'\n');
              cout << "\n\nERROR! Invalid entry!\n\n";
              cout << "\nEnter a record with required goals to be removed:\n\n> ";
              cin >> value;
            } else {
              try {
                cout << "\nDeleting any player found with " << value << " goals recorded from this list...\n\n";

                bool isFound = false;
                int index = 0;
                int position = 0;

                for(int i = 0; i < hashTableLength; i++) {
                  if (hashTable[i].getLength() > 0) {
                    for (int j = 1; j <= hashTable[i].getLength(); j++) {
                      if (hashTable[i].getEntry(j).getGoalRecord() == value) {
                        index = i;
                        position = j;
                        isFound = true;
                      }
                    }
                  }
                }

                if(!isFound)
                  cout << "ERROR! No Record Found.\n\n";
                else {
                  hashTable[index].remove(position);

                  cout << "Player Record was successfully inserted.\n\n";
                }
              } catch (runtime_error) {
                cout << "\nERROR! Invalid Position!\n\n";
              }

              break;
            }
          }
          */
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

  uParse = "\0";
  pParse = "\0";
  uname = "\0";
  pword = "\0";
  hashKey = 0;

  cout << "\nBye Bye!\n";
  cout << "\nHave a nice day!...\n\n";
}
