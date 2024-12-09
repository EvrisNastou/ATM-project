/*
Copyright (C) 2022, 2023 Euripides Nastou
This file is part of ATM Application.
ATM Application is free software: you can redistribute it and/or modify it under the
terms of the GNU General Public License as published by the Free Software Foundation,
either version 3 of the License, or (at your option) any later version.
ATM Application is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU General Public License for more details.
You should have received a copy of the GNU General Public License along with ATM
Application. If not, see <https://www.gnu.org/licenses/>.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#define N 20
#define M 24
/*η συνάτηση του διαχειριστή αρχικοποιεί τα αρχεία πελατών,
Λογαριασμών. Επιτρέπει την εισάγωγή των στοιχείων των πελατών
και των λογαρισμών σε αυτά και δίνει τη δυνατότητα εκτύπωσης
των αρχείων*/
void admin();
/*οι δυο συναρτήσεις για την αρχικοποίηση των αρχείων,
ενα για τους πελάτες και ενα για τους λογαριασμούς τους*/
void initCust();
void initAccount();
/*οι δυο συναρτήσεις για την προσθήκη στοιχείων των πελατών
και προσθήκη λογαριασμών για τους πελάτες, αντίστοιχα*/
void addCust();
void addAccount();
/*για την εκτύπωση των αρχείων με τα στοιχεία των πελατών
και των λογαριασμών των πελατών, αντίστοιχα*/
void printCust();
void printAccount();
/*για την αρχεικοποίηση των αρχείων των καταθέσεων και των
αναληψεων, αντίστοιχα*/
void initDeposit();
void initWithdrawal();
/*για την εκτύπωση των αρχείων των καταθέσεων και των
και των αναληψεων, αντίστοιχα*/

void printDeposit();
void printWithdrawals();
/*Συναρτήσεις για την λειτουργία του ATM*/
void setupDataBase();
void login();
void atmMenu(char *uAccount);
double accountBalance(char *uAccount);
void accountDeposit(char *uaccount, double amount);
double accountWithdrawals(char *uaccount);
void accountTansfer(char *uaccount);
/*δομή για τα στοιχεία των πελατών*/
typedef struct
{
    char username[N];
    char PIN[5];
    char firstName[N], lastName[N];
    char vat[11];
} customer;
/*δομή για τα στοιχεία των λογαριασμών των πελατών*/
typedef struct
{
    char username[N];
    char bban[M];
    char iban[28];
    double amount;
} account;
/*δομή για τα στοιχεία καταθέσεων/αναλήψεων/μεταφoρών των πελατών*/
typedef struct
{
    char bban[M];
    int day;
    int month;
    int year;
    double amount;
    char comments[51];
} transactionsRec;
