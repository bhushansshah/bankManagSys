#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include "supportFunc.h"
int isValidUserid(MYSQL **, int);
int isValidPassword(MYSQL* *, int, char *);
int getBalance(MYSQL **, int);
int isWithdrawalPossible(MYSQL **, int , int);
void withdraw(MYSQL **, int, int);
void deposit(MYSQL **, int, int);
void printProfile(MYSQL **, int);
void updateProfile(MYSQL **, int);
void transferMoney(MYSQL **, int, int, int);
void deleteUser(MYSQL **, int);
void insertUser(MYSQL **, int, char *, char *, char *, char *, long long int, char *, char *, char *, char *, char *, char *);
void updateFirstName(MYSQL **, int, char *);
void updateMiddleName(MYSQL **, int, char *);
void updateLastName(MYSQL **, int, char *);
void updateBranch(MYSQL **, int, char *);
void updateEmail(MYSQL **, int, char *);
void updateAddress(MYSQL **, int, char *);
void updateCity(MYSQL **, int, char *);
void updateState(MYSQL **, int, char *);
void updateCountry(MYSQL **, int, char *);

