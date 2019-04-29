#ifndef BOOK_H_INCLUDED
#define BOOK_H_INCLUDED

#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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



//read one line data
int readLine(char *buffer, FILE *fp);

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

#endif // BOOK_H_INCLUDED
