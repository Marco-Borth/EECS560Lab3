/* -----------------------------------------------------------------------------
*
* File Name:  User.cpp
* Author: Marco Borth
* Assignment:   EECS-560 Lab 3 - Implementation of Hash Table (Closed Hashing)
* Description:  User set and get methods defined here.
* Date: 2/11/20
*
---------------------------------------------------------------------------- */

#include "User.h"
#include <string>
using namespace std;

User::User(){}

User::~User(){}

User::User(string alias, string pword) {
  Username = alias;
  password = pword;
}

void User::setUsername(string alias) {
  if(alias.length() > 0) {
    Username = alias;
  }
}

string User::getUsername() const {
  return(Username);
}

void User::setPassword(string pword) {
  if(pword.length() > 0) {
    password = pword;
  }
}

string User::getPassword() const {
  return(password);
}

bool User::operator==(const User& other)
{
  return(Username == other.getUsername());
}

bool User::operator>(const User& other)
{
  return(Username > other.getUsername());
}

bool User::operator<(const User& other)
{
  return(Username < other.getUsername());
}
