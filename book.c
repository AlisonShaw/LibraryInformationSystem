#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "book.h"
Book *head_book = NULL;

void saveBooks(){
	FILE *fp = fopen("books.txt", "w");
	Book* stu = head_book;
	while(stu != NULL){
		fprintf(fp, "%s,%s,%s,%s,%s,%d\n", stu->no, stu->type, stu->name, stu->publisher, stu->location, stu->stock);
		stu = stu->next;
	}
	fclose(fp);
}


void loadBooks(){
	FILE *fp = fopen("books.txt", "r");
	if (fp) {
		char buffer[100];
		while (readLine(buffer,fp)) {
			//create a new node
			Book* book = (Book*)malloc(sizeof(Book));
			book->next = NULL;

			//parse tokens by ","
			int itemIndex = 0;
			char*temp = strtok(buffer,",");
			while(temp) {
				if(itemIndex == 0){
					strcpy(book->no, temp);
				}else if(itemIndex == 1){
					strcpy(book->type, temp);
				}else if(itemIndex == 2){
					strcpy(book->name, temp);
				}else if(itemIndex == 3){
					strcpy(book->publisher, temp);
				}else if(itemIndex == 4){
					strcpy(book->location, temp);
				}else if(itemIndex == 5){
					book->stock = atoi(temp);
				}

				itemIndex++;
				temp = strtok(NULL,",");
			}

			//append new node to linked list
			if(head_book == NULL){
				head_book = book;
			}else{
				Book *tail = head_book;
				while(tail->next != NULL){
					tail = tail->next;
				}
				tail->next = book;
			}
		}
		fclose(fp);
	} else {
		printf("not found books.txt\n");
	}
}

void printBook(Book *book){
	printf("ID: %s\n",book->no);
	printf("Type: %s\n",book->type);
	printf("Name: %s\n",book->name);
	printf("Publisher: %s\n",book->publisher);
	printf("Location: %s\n",book->location);
	printf("Stock: %d\n",book->stock);
}

void printAllBooks(){
	int count = 0;
	Book* book = head_book;
	while(book != NULL){
		printBook(book);
		book = book->next;
		count++;
	}
	printf("%d result(s)\n",count);
}

void freeBooksList(){
	Book* book = head_book;
	while(book != NULL){
		Book* temp = book;
		book = book->next;
		free(temp);
	}
}


void searchBooks(char *keyword){
	Book* book = head_book;
	int count = 0;
	while(book != NULL){
		if(strstr(book->name, keyword)!=NULL){
			count++;
			printBook(book);
		}
		book = book->next;
	}
	printf("%d result(s)\n",count);
}

void addBook(){
	char no[50];
	Book *book;

	printf("enter book no: ");
	scanf("%s",no);
	book = findBook(no);
	if(book == NULL){
		book = (Book*)malloc(sizeof(Book));
		book->next = NULL;

		strcpy(book->no, no);

		printf("enter book type: ");
		readLine(book->type, stdin);//remove the last '\n'
		readLine(book->type, stdin);
		printf("enter book name: ");
		readLine(book->name, stdin);
		printf("enter publisher: ");
		readLine(book->publisher, stdin);
		printf("enter location: ");
		readLine(book->location, stdin);
		printf("enter the number of stock(integer): ");
		scanf("%d",&book->stock);

		if(head_book == NULL){
			head_book = book;
		}else{
			Book *tail = head_book;
			while(tail->next != NULL){
				tail = tail->next;
			}
			tail->next = book;
		}
	}else{
		printf("this book id has been used\n");
	}
}

void removeBook(){
	char no[50];
	Book *book;

	printf("enter book no: ");
	scanf("%s",no);
	book = findBook(no);
	if(book != NULL){
		if(head_book == book){
			Book* temp = head_book;
			head_book = head_book->next;
			free(temp);
		}else{
			Book* pre = head_book;
			Book* current = head_book->next;
			while(current != NULL){
				if(current == book){
					pre->next = current->next;
					free(current);
					break;
				}
				pre = current;
				current = current->next;
			}
		}
	}else{
		printf("this book id doesn't exists.\n");
	}
}

Book* findBook(char *bookno){
	Book* book = head_book;
	while(book != NULL){
		if(strcmp(book->no, bookno)==0){
			return book;
		}

		book = book->next;
	}
	return NULL;
}
