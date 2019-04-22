#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "student.h"

Student *head_student = NULL;
Book *head_book = NULL;
Borrow *head_borrow = NULL;
char currentStudent[50];

void mainMenu(){
	int option;
	setbuf(stdout, NULL);
	while(1){
		printf("\n");
		printf("1. administrator login\n");
		printf("2. student login\n");
		printf("3. student registration\n");
		printf("0. exit\n");

		printf("your select: ");
		scanf("%d",&option);
		if(option == 1){
			char password[50];
			printf("enter password(1234): ");
			scanf("%s",password);
			if(strcmp(password,"1234")==0){
				adminMenu();
			}else{
				printf("wrong password\n");
			}
		}else if(option == 2){
			studentLogin();
		}else if(option == 3){
			studentRegister();
		}else if(option == 0){
			break;
		}
	}
}

void studentMenu(){
	int option;
	while(1){
		printf("\n");
		printf("1. search books\n");
		printf("2. borrow book\n");
		printf("3. return book\n");
		printf("4. my borrows\n");
		printf("0. exit\n");

		printf("your select: ");
		scanf("%d",&option);
		if(option == 1){
			char keyword[50];
			printf("enter keyword: ");
			scanf("%s",keyword);
			searchBooks(keyword);
		}else if(option == 2){
			char bookno[50];
			Book* book;
			printf("enter the number of book: ");
			scanf("%s",bookno);

			book = findBook(bookno);
			if(book != NULL){
				if(book->stock > 0){
					book->stock--;
					borrowBook(currentStudent, bookno);
				}else{
					printf("this book has no more copies.\n");
				}
			}else{
				printf("this book no doesn't exist.\n");
			}
		}else if(option == 3){
			char bookno[50];
			Book* book;
			printf("enter the number of book: ");
			scanf("%s",bookno);

			book = findBook(bookno);
			if(book != NULL){
				Borrow *borrow = checkBorrow(currentStudent, bookno);
				if(borrow != NULL){
					book->stock++;
					returnBook(borrow);
				}else{
					printf("you didn't borrow this book.\n");
				}
			}else{
				printf("this book no doesn't exist.\n");
			}
		}else if(option == 4){
			printAllBorrows(currentStudent);
		}else if(option == 0){
			break;
		}
	}
}

void printAllBorrows(char *username){
	Borrow* borrow = head_borrow;
	while(borrow != NULL){
		Book* book = findBook(borrow->bookno);
		printBook(book);
		printf("\n");
		borrow = borrow->next;
	}
}

void borrowBook(char *username, char *bookno){
	Borrow* borrow = (Borrow*)malloc(sizeof(Borrow));
	borrow->next = NULL;
	strcpy(borrow->username, username);
	strcpy(borrow->bookno, bookno);

	if(head_borrow == NULL){
		head_borrow = borrow;
	}else{
		Borrow *tail = head_borrow;
		while(tail->next != NULL){
			tail = tail->next;
		}
		tail->next = borrow;
	}
}

Borrow* checkBorrow(char *username, char *bookno){
	Borrow *borrow = head_borrow;
	while(borrow != NULL){
		if(strcmp(borrow->username, username)==0 && strcmp(borrow->bookno, bookno)==0){
			return borrow;
		}
		borrow = borrow->next;
	}
	return NULL;
}

void returnBook(Borrow* borrow){
	if(head_borrow == borrow){
		Borrow* temp = head_borrow;
		head_borrow = head_borrow->next;
		free(temp);
	}else{
		Borrow* pre = head_borrow;
		Borrow* current = head_borrow->next;
		while(current != NULL){
			if(current == borrow){
				pre->next = current->next;
				free(current);
				break;
			}
			pre = current;
			current = current->next;
		}
	}
}

void adminMenu(){
	int option;
	while(1){
		printf("\n");
		printf("1. search books\n");
		printf("2. add book\n");
		printf("3. remove book\n");
		printf("4. show all books\n");
		printf("5. show all students\n");
		printf("0. exit\n");

		printf("your select: ");
		scanf("%d",&option);
		if(option == 1){
			char buffer[100];
			printf("enter keyword: ");
			scanf("%s",buffer);
			searchBooks(buffer);
		}else if(option == 2){
			addBook();
		}else if(option == 3){
			removeBook();
		}else if(option == 4){
			printAllBooks();
		}else if(option == 5){
			printAllStudents();
		}else if(option == 0){
			break;
		}
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

void freeBorrowsList(){
	Borrow* borrow = head_borrow;
	while(borrow != NULL){
		Borrow* temp = borrow;
		borrow = borrow->next;
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

Student* findStudent(char *username){
	Student* stu = head_student;
	while(stu != NULL){
		if(strcmp(stu->username, username)==0){
			return stu;
		}

		stu = stu->next;
	}
	return NULL;
}

void printStudent(Student* student){
	printf("%s\t%s\t%s\n",student->username, student->mobile, student->email);
}

void printAllStudents(){
	int count = 0;
	Student* student = head_student;
	while(student != NULL){
		printStudent(student);
		student = student->next;
		count++;
	}
	printf("%d result(s)\n",count);
}

void freeStudentsList(){
	Student* student = head_student;
	while(student != NULL){
		Student* temp = student;
		student = student->next;
		free(temp);
	}
}


void studentLogin(){
	char username[50];
	char password[50];
	Student *stu;

	printf("enter username: ");
	scanf("%s",username);
	stu = findStudent(username);
	if(stu != NULL){
		printf("enter password: ");
		scanf("%s",password);

		if(strcmp(stu->password, password)==0){
			strcpy(currentStudent, stu->username);
			studentMenu();
		}else{
			printf("wrong password\n");
		}
	}else{
		printf("no this student\n");
	}
}

void studentRegister(){
	char username[50];
	Student *stu;

	printf("enter username: ");
	scanf("%s",username);
	stu = findStudent(username);

	if(stu == NULL){
		//user name not found

		stu = (Student*)malloc(sizeof(Student));
		stu->next = NULL;

		strcpy(stu->username, username);

		//prompt user to enter user info
		printf("enter password: ");
		scanf("%s",stu->password);
		printf("enter your mobile number: ");
		scanf("%s",stu->mobile);
		printf("enter your email: ");
		scanf("%s",stu->email);

		//append new user to linked list
		if(head_student == NULL){
			head_student = stu;
		}else{
			//add new student after the tail of list, and the new node became tail
			Student *tail = head_student;
			while(tail->next != NULL){
				tail = tail->next;
			}
			tail->next = stu;
		}
	}else{
		printf("this username has been used\n");
	}
}

int readLine(char *buffer, FILE *fp){
	int length;
	char* status = fgets(buffer, 100, fp);
	if(status == NULL){
		return 0;
	}

	//remove \n and \r in the rear of buffer
	length = strlen(buffer);
	while(length > 0 && (buffer[length-1] == '\n' || buffer[length-1] == '\r')){
		buffer[length-1] = '\0';
		length = strlen(buffer);
	}
	return 1;
}

void saveStudents(){
	FILE *fp = fopen("students.txt", "w");
	Student* stu = head_student;
	while(stu != NULL){
		fprintf(fp, "%s,%s,%s,%s\n", stu->username, stu->password, stu->mobile, stu->email);
		stu = stu->next;
	}
	fclose(fp);
}

void saveBooks(){
	FILE *fp = fopen("books.txt", "w");
	Book* stu = head_book;
	while(stu != NULL){
		fprintf(fp, "%s,%s,%s,%s,%s,%d\n", stu->no, stu->type, stu->name, stu->publisher, stu->location, stu->stock);
		stu = stu->next;
	}
	fclose(fp);
}

void saveBorrows(){
	FILE *fp = fopen("borrows.txt", "w");
	Borrow* stu = head_borrow;
	while(stu != NULL){
		fprintf(fp, "%s,%s\n", stu->username, stu->bookno);
		stu = stu->next;
	}
	fclose(fp);
}

void loadStudents(){
	FILE *fp = fopen("students.txt", "r");
	if (fp) {
		char buffer[100];
		while (readLine(buffer,fp)) {
			//create a new node
			Student* stu = (Student*)malloc(sizeof(Student));
			stu->next = NULL;

			//parse tokens by ","
			int itemIndex = 0;
			char*temp = strtok(buffer,",");
			while(temp) {
				if(itemIndex == 0){
					strcpy(stu->username, temp);
				}else if(itemIndex == 1){
					strcpy(stu->password, temp);
				}else if(itemIndex == 2){
					strcpy(stu->mobile, temp);
				}else if(itemIndex == 3){
					strcpy(stu->email, temp);
				}

				itemIndex++;
				temp = strtok(NULL,",");
			}

			//append new node to linked list
			if(head_student == NULL){
				head_student = stu;
			}else{
				Student *tail = head_student;
				while(tail->next != NULL){
					tail = tail->next;
				}
				tail->next = stu;
			}
		}
		fclose(fp);
	} else {
		printf("not found students.txt\n");
	}
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

void loadBorrows(){
	FILE *fp = fopen("borrows.txt", "r");
	if (fp) {
		char buffer[100];
		while (readLine(buffer,fp)) {
			//create a new node
			Borrow* bor = (Borrow*)malloc(sizeof(Borrow));
			bor->next = NULL;

			//parse tokens by ","
			int itemIndex = 0;
			char*temp = strtok(buffer,",");
			while(temp) {
				if(itemIndex == 0){
					strcpy(bor->username, temp);
				}else if(itemIndex == 1){
					strcpy(bor->bookno, temp);
				}

				itemIndex++;
				temp = strtok(NULL,",");
			}

			//append new node to linked list
			if(head_borrow == NULL){
				head_borrow = bor;
			}else{
				Borrow *tail = head_borrow;
				while(tail->next != NULL){
					tail = tail->next;
				}
				tail->next = bor;
			}
		}
		fclose(fp);
	} else {
		//failed to open file
		printf("not found books.txt\n");
	}
}

