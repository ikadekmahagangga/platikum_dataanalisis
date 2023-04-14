#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

int main(int argc, char* argv[]) {
  sqlite3* db;
  char* errmsg;
  int rc;

  // membuka koneksi dengan database Titanic
  rc = sqlite3_open("titanic.db", &db);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "Tidak dapat membuka database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return 1;
  }

  // query untuk menampilkan jumlah penumpang yang selamat dan tidak selamat
  int survived, not_survived;
  rc = sqlite3_exec(db, "SELECT COUNT(*) FROM passenger WHERE survived = 1;", callback, &survived, &errmsg);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "Tidak dapat menjalankan query: %s\n", errmsg);
    sqlite3_free(errmsg);
    sqlite3_close(db);
    return 1;
  }

  rc = sqlite3_exec(db, "SELECT COUNT(*) FROM passenger WHERE survived = 0;", callback, &not_survived, &errmsg);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "Tidak dapat menjalankan query: %s\n", errmsg);
    sqlite3_free(errmsg);
    sqlite3_close(db);
    return 1;
  }

  printf("Jumlah penumpang Titanic yang selamat: %d\n", survived);
  printf("Jumlah penumpang Titanic yang tidak selamat: %d\n", not_survived);

  // query untuk menampilkan jumlah penumpang pria dan wanita
  int male, female;
  rc = sqlite3_exec(db, "SELECT COUNT(*) FROM passenger WHERE sex = 'male';", callback, &male, &errmsg);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "Tidak dapat menjalankan query: %s\n", errmsg);
    sqlite3_free(errmsg);
    sqlite3_close(db);
    return 1;
  }

  rc = sqlite3_exec(db, "SELECT COUNT(*) FROM passenger WHERE sex = 'female';", callback, &female, &errmsg);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "Tidak dapat menjalankan query: %s\n", errmsg);
    sqlite3_free(errmsg);
    sqlite3_close(db);
    return 1;
  }

  printf("Jumlah penumpang pria di Titanic: %d\n", male);
  printf("Jumlah penumpang wanita di Titanic: %d\n", female);

  // query untuk menampilkan distribusi usia penumpang Titanic
  rc = sqlite3_exec(db, "SELECT age FROM passenger WHERE age NOT NULL;", callback_histogram, NULL, &errmsg);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "Tidak dapat menjalankan query: %s\n", errmsg);
    sqlite3_free(errmsg);
    sqlite3_close(db);
    return 1;
  }

  // menutup koneksi dengan database
  sqlite3_close(db);
  return 0;
}

int callback(void* data, int argc, char** argv, char** colname) {
  *(int*)data = atoi(argv[0]);
  return 0;
}

int callback_histogram(void* data, int argc, char** argv, char** colname) {
  int age = atoi(argv[0]);
  printf("Usia: %d\n", age);
  return 
