/* -----------------------------------------------------------------------------
 *
 * File Name:  Operator.h
 * Author: Marco Borth
 * Assignment:   EECS-560 Lab 3 - Implementation of Hash Table (Closed Hashing)
 * Description:  Operator Class is defined.
 * Date: 2/11/20
 *
 ---------------------------------------------------------------------------- */

#ifndef OPERATOR_H
#define OPERATOR_H

#include "LinkedList.h"
#include "User.h"
#include <string>
#include <stdexcept>
using namespace std;

class Operator
{
private:
  int option;
  int hashTableLength;
  int hashTableLoadFactor;
  int hashValue;

  string file;

  string uname;
  string pword;
  string uParse;
  string pParse;

  bool placedLinear;
  bool placedQuadratic;

  LinkedList<User> LinearTable;
  LinkedList<User> QuadraticTable;

public:
/**
* @pre none.
* @post stops running after code exits loop.
*/
	void run();

/**
* @pre none.
* @post prints list of commands to display for the user.
*/
  void printCommands();

  void inputUsername(string parse);

  void parseUsername(string parse);

  void parsePassword(string parse);

  int hashKey(string passkey);

  void rehashTables();

  void insertRecord(string table);

  void removeRecord(string table);

/*
* @pre filename is a string.
* @post Operator object is constructed, file == filename.
*/
  Operator(string filename);
};
#endif
