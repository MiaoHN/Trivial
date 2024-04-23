/**
 * 在一座城市里有几家不同的书店，每家书店有若干本书，每本书有自己的编号、书名、作者和价格。
 * 请编写一个程序，输入一个作者名，找到所有他出版的书，输出书名，价格，及其对应的书店名，
 * 注意按照价格从低到高的方式进行输出。
 *
 * - 输入：
3
store1
3
1 book1 author1 105
2 book2 author1 520
3 book3 author2 200
store2
2
4 book4 author1 350
5 book5 author2 240
store3
4
6 book6 author3 230
7 book7 author4 380
8 book8 author1 100
9 book9 author5 260
author1
 *
 * - 输出：
 * store1 book1 105
 * store3 book2 520
 * store2 book4 350
 * store1 book8 105
 */

#include <stdio.h>
#include <string.h>

struct Book {
  int id;
  char title[50];
  char author[50];
  int price;
};

struct BookStore {
  char name[32];
  struct Book books[100];
  int nbooks;
};

struct QueryResult {
  char store[32];
  char title[50];
  int price;
};

void search_books(struct BookStore* stores, int nstores, char* author);

void sort_results(struct QueryResult* results, int nresults);

int main(int argc, char const* argv[]) {
  struct BookStore stores[10];
  int nstores;
  scanf("%d", &nstores);
  for (int i = 0; i < nstores; i++) {
    struct BookStore* store = &stores[i];
    scanf("%s", store->name);
    scanf("%d", &store->nbooks);
    for (int j = 0; j < store->nbooks; j++) {
      struct Book* book = &store->books[j];
      scanf("%d", &book->id);
      scanf("%s", book->title);
      scanf("%s", book->author);
      scanf("%d", &book->price);
    }
  }

  char author[50];
  scanf("%s", author);

  search_books(stores, nstores, author);

  return 0;
}

void search_books(struct BookStore* stores, int nstores, char* author) {
  struct QueryResult results[100];
  int nresults = 0;
  for (int i = 0; i < nstores; i++) {
    struct BookStore* store = &stores[i];
    for (int j = 0; j < store->nbooks; j++) {
      struct Book* book = &store->books[j];
      if (strcmp(book->author, author) == 0) {
        struct QueryResult* result = &results[nresults];
        strcpy(result->store, store->name);
        strcpy(result->title, book->title);
        result->price = book->price;
        nresults++;
      }
    }
  }

  sort_results(results, nresults);

  for (int i = 0; i < nresults; i++) {
    struct QueryResult* result = &results[i];
    printf("%s %s %d\n", result->store, result->title, result->price);
  }
}

void sort_results(struct QueryResult* results, int nresults) {
  for (int i = 0; i < nresults; i++) {
    for (int j = i + 1; j < nresults; j++) {
      if (results[i].price > results[j].price) {
        struct QueryResult temp = results[i];
        results[i] = results[j];
        results[j] = temp;
      }
    }
  }
}