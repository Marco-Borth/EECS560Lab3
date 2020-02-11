/* -----------------------------------------------------------------------------
*
* File Name:  User.h
* Author: Marco Borth
* Assignment:   EECS-560 Lab 3 - Implementation of Hash Table (Closed Hashing)
* Description:  User Class is defined.
* Date: 2/11/20
*
---------------------------------------------------------------------------- */

#ifndef USER_H
#define USER_H

#include <string>
#include <stdexcept>
using namespace std;

class User
{
private:
  string Username;
  string password;

public:
/*
* @pre none.
* @param alias must be a string value.
* @post Username is set to alias.
*/
  void setUsername(string alias);

/*
* @pre none.
* @post return Username value.
*/
  string getUsername() const;

/*
* @pre none.
* @param password must be a string value.
* @post password is set to pword.
*/
  void setPassword(string pword);

/*
* @pre none.
* @post return password.
*/
  string getPassword() const;

  bool operator==(const User& other);

  bool operator>(const User& other);

  bool operator<(const User& other);

  User();

  ~User();

  User(string alias, string pword);
};
#endif
