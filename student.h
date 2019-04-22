#ifndef STUDENT_H_INCLUDED
#define STUDENT_H_INCLUDED

#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//the data structure of student
typedef struct student {
	char username[50]; //user name
	char password[50]; //password
	char mobile[50]; //phone number
	char email[50]; //email

	struct student* next; //pointer to next node
} Student;

//the data structure of book
typedef struct book {
	char no[50]; //number of book
	char type[50]; //type of book
	char name[50]; //name of book
	char publisher[50]; //publisher of book
	char location[50]; //location of storing

	int stock; //the remaining number of books available for borrowing

	struct book* next; //pointer to next node
} Book;

//the data structure of borrow record
typedef struct borrow {
	char username[50]; //the username of borrower
	char bookno[50]; //the number of book borrowed

	struct borrow* next; //pointer to next node
} Borrow;


//read one line data
int readLine(char *buffer, FILE *fp);

//save students to students.txt
void saveStudents();
//load students from students.txt
void loadStudents();
//register a new user
void studentRegister();
//student login
void studentLogin();
//find a student by username, return the pointer of node if found, NULL otherwise
Student* findStudent(char *username);
//print out a student to screen
void printStudent(Student* student);
//print all students
void printAllStudents();
//free the linked list of student
void freeStudentsList();

//save books to books.txt
void saveBooks();
//load books from books.txt
void loadBooks();
//add a new book
void addBook();
//remove a book
void removeBook();
//find a book by bookno, return the pointer of node if found, NULL otherwise
Book* findBook(char *bookno);
//search books by keyword, print the result to screen
void searchBooks(char *keyword);
//print out a book
void printBook(Book* book);
//print all books
void printAllBooks();
//free the linked list of books
void freeBooksList();

//save borrow records to books.txt
void saveBorrows();
//load borrow records from borrows.txt
void loadBorrows();
//borrow a book, create a new borrow record by username and book number
void borrowBook(char *username, char *bookno);
//return a book
void returnBook(Borrow* borrow);
//the the records of a user
void printAllBorrows(char *username);
//check whether a user borrow the book or not
Borrow* checkBorrow(char *username, char *bookno);
//free the linked list of borrow records
void freeBorrowsList();

//show main menu
void mainMenu();
//show student menu
void studentMenu();
//show admin menu
void adminMenu();

#endif // STUDENT_H_INCLUDED
