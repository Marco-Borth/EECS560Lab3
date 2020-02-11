/* -----------------------------------------------------------------------------
 *
 * File Name:  main.cpp
 * Author: Marco Borth
 * Assignment:   EECS-560 Lab 2 - Implementation of Hash Table
 * Description:  This lab will contain an implementation of an interactive singly Hash Table.
 * Date: 2/4/20
 *
 ---------------------------------------------------------------------------- */
//Start your program.

#include <iostream>
#include"Executive.h"

int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		std::cout << "Incorrect number of parameters!\n";
	}
	else
	{
		Executive exec(argv[1]);
		exec.run();
	}

	return(0);
}
