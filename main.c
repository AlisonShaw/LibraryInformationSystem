#define _CRT_SECURE_DEPRECATE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "student.h"

int main()
{
	//load students, books and borrow records from file
    loadStudents();
    loadBooks();
    loadBorrows();

    //show menu
    mainMenu();

    //save students, books and borrow records to file
    saveStudents();
    saveBooks();
    saveBorrows();

    //free the 3 linked list
    freeStudentsList();
    freeBooksList();
    freeBorrowsList();
}
