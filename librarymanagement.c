#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Book {
    int bookId;
    char title[100];
    char author[50];
    int totalCopies;
    int availableCopies;
};

/* Function Declarations */
void addBook();
void displayAll();
void searchBook();
void issueBook();
void returnBook();
void updateBook();
void deleteBook();

/* Main Function */
int main() {
    int choice;
    do {
        printf("\nLIBRARY MANAGEMENT SYSTEM\n");
        printf("1. Add Book\n");
        printf("2. Display All Books\n");
        printf("3. Search Book\n");
        printf("4. Issue Book\n");
        printf("5. Return Book\n");
        printf("6. Update Book\n");
        printf("7. Delete Book\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addBook(); break;
            case 2: displayAll(); break;
            case 3: searchBook(); break;
            case 4: issueBook(); break;
            case 5: returnBook(); break;
            case 6: updateBook(); break;
            case 7: deleteBook(); break;
            case 0: printf("Exiting program...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 0);

    return 0;
}

/* Add Book */
void addBook() {
    FILE *fp = fopen("books.txt", "a");
    struct Book b;

    printf("Enter Book ID: ");
    scanf("%d", &b.bookId);
    getchar();

    printf("Enter Title: ");
    gets(b.title);

    printf("Enter Author: ");
    gets(b.author);

    printf("Enter Total Copies: ");
    scanf("%d", &b.totalCopies);

    b.availableCopies = b.totalCopies;

    fprintf(fp, "%d|%s|%s|%d|%d\n",
            b.bookId, b.title, b.author,
            b.totalCopies, b.availableCopies);

    fclose(fp);
    printf("Book added successfully!\n");
}

/* Display All Books */
void displayAll() {
    FILE *fp = fopen("books.txt", "r");
    struct Book b;

    if (fp == NULL) {
        printf("No books available!\n");
        return;
    }

    printf("\nBookID  Title               Author            Available\n");
    while (fscanf(fp, "%d|%[^|]|%[^|]|%d|%d\n",
                  &b.bookId, b.title, b.author,
                  &b.totalCopies, &b.availableCopies) != EOF) {
        printf("%d   %s   %s   %d\n",
               b.bookId, b.title, b.author, b.availableCopies);
    }
    fclose(fp);
}

/* Search Book */
void searchBook() {
    FILE *fp = fopen("books.txt", "r");
    struct Book b;
    int id, found = 0;

    printf("Enter Book ID to search: ");
    scanf("%d", &id);

    while (fscanf(fp, "%d|%[^|]|%[^|]|%d|%d\n",
                  &b.bookId, b.title, b.author,
                  &b.totalCopies, &b.availableCopies) != EOF) {
        if (b.bookId == id) {
            printf("\nBook Found!\n");
            printf("Title: %s\nAuthor: %s\nAvailable Copies: %d\n",
                   b.title, b.author, b.availableCopies);
            found = 1;
            break;
        }
    }
    if (!found)
        printf("Book not found!\n");

    fclose(fp);
}

/* Issue Book */
void issueBook() {
    FILE *fp = fopen("books.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    struct Book b;
    int id, found = 0;

    printf("Enter Book ID to issue: ");
    scanf("%d", &id);

    while (fscanf(fp, "%d|%[^|]|%[^|]|%d|%d\n",
                  &b.bookId, b.title, b.author,
                  &b.totalCopies, &b.availableCopies) != EOF) {

        if (b.bookId == id && b.availableCopies > 0) {
            b.availableCopies--;
            found = 1;
            printf("Book issued successfully! Available copies: %d\n", b.availableCopies);
        }
        fprintf(temp, "%d|%s|%s|%d|%d\n",
                b.bookId, b.title, b.author,
                b.totalCopies, b.availableCopies);
    }

    if (!found)
        printf("Book not available or not found!\n");

    fclose(fp);
    fclose(temp);
    remove("books.txt");
    rename("temp.txt", "books.txt");
}

/* Return Book */
void returnBook() {
    FILE *fp = fopen("books.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    struct Book b;
    int id, found = 0;

    printf("Enter Book ID to return: ");
    scanf("%d", &id);

    while (fscanf(fp, "%d|%[^|]|%[^|]|%d|%d\n",
                  &b.bookId, b.title, b.author,
                  &b.totalCopies, &b.availableCopies) != EOF) {

        if (b.bookId == id && b.availableCopies < b.totalCopies) {
            b.availableCopies++;
            found = 1;
            printf("Book returned successfully! Available copies: %d\n", b.availableCopies);
        }
        fprintf(temp, "%d|%s|%s|%d|%d\n",
                b.bookId, b.title, b.author,
                b.totalCopies, b.availableCopies);
    }

    if (!found)
        printf("Invalid return operation!\n");

    fclose(fp);
    fclose(temp);
    remove("books.txt");
    rename("temp.txt", "books.txt");
}

/* Update Book */
void updateBook() {
    FILE *fp = fopen("books.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    struct Book b;
    int id, found = 0;

    printf("Enter Book ID to update: ");
    scanf("%d", &id);
    getchar();

    while (fscanf(fp, "%d|%[^|]|%[^|]|%d|%d\n",
                  &b.bookId, b.title, b.author,
                  &b.totalCopies, &b.availableCopies) != EOF) {

        if (b.bookId == id) {
            found = 1;
            printf("Enter new Title: ");
            gets(b.title);
            printf("Enter new Author: ");
            gets(b.author);
            printf("Enter new Total Copies: ");
            scanf("%d", &b.totalCopies);
            b.availableCopies = b.totalCopies;
        }

        fprintf(temp, "%d|%s|%s|%d|%d\n",
                b.bookId, b.title, b.author,
                b.totalCopies, b.availableCopies);
    }

    if (!found)
        printf("Book not found!\n");

    fclose(fp);
    fclose(temp);
    remove("books.txt");
    rename("temp.txt", "books.txt");
}

/* Delete Book */
void deleteBook() {
    FILE *fp = fopen("books.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    struct Book b;
    int id, found = 0;

    printf("Enter Book ID to delete: ");
    scanf("%d", &id);

    while (fscanf(fp, "%d|%[^|]|%[^|]|%d|%d\n",
                  &b.bookId, b.title, b.author,
                  &b.totalCopies, &b.availableCopies) != EOF) {

        if (b.bookId != id)
            fprintf(temp, "%d|%s|%s|%d|%d\n",
                    b.bookId, b.title, b.author,
                    b.totalCopies, b.availableCopies);
        else
            found = 1;
    }

    if (found)
        printf("Book deleted successfully!\n");
    else
        printf("Book not found!\n");

    fclose(fp);
    fclose(temp);
    remove("books.txt");
    rename("temp.txt", "books.txt");
}
