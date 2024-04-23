#include <stdio.h>
#include <string.h>

struct Book {
  int id;
  char title[50];
  char author[50];
  int price;
};

struct BookShop {
  char name[32];
  struct Book books[100];
  int nbooks;
};

int main(int argc, char const* argv[]) {
  struct BookShop shops[10];
  int nshops;
  scanf("%d", &nshops);
  for (int i = 0; i < nshops; i++) {
    struct BookShop* shop = &shops[i];
    scanf("%s", shop->name);
    scanf("%d", &shop->nbooks);
    for (int j = 0; j < shop->nbooks; j++) {
      struct Book* book = &shop->books[j];
      scanf("%d", &book->id);
      scanf("%s", book->title);
      scanf("%s", book->author);
      scanf("%d", &book->price);
    }
  }

  // input an author name, find all the books written by the author, and print the
  // shop name, book title, and price of each book
  char author[50];
  scanf("%s", author);
  for (int i = 0; i < nshops; i++) {
    struct BookShop* shop = &shops[i];
    for (int j = 0; j < shop->nbooks; j++) {
      struct Book* book = &shop->books[j];
      if (strcmp(book->author, author) == 0) {
        printf("%s %s %d\n", shop->name, book->title, book->price);
      }
    }
  }

  return 0;
}

/*give an example input

3
shop1
3
1 book1 author1 105
2 book2 author1 520
3 book3 author2 200
shop2
2
4 book4 author1 350
5 book5 author2 240
shop3
4
6 book6 author3 230
7 book7 author4 380
8 book8 author1 105
9 book9 author5 260
author1

*/
