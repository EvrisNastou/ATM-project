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
/*� �������� ��� ����������� ����������� �� ������ �������,
�����������. ��������� ��� �������� ��� ��������� ��� �������
��� ��� ���������� �� ���� ��� ����� �� ���������� ���������
��� �������*/
void admin();
/*�� ��� ����������� ��� ��� ������������ ��� �������,
��� ��� ���� ������� ��� ��� ��� ���� ������������ ����*/
void initCust();
void initAccount();
/*�� ��� ����������� ��� ��� �������� ��������� ��� �������
��� �������� ����������� ��� ���� �������, ����������*/
void addCust();
void addAccount();
/*��� ��� �������� ��� ������� �� �� �������� ��� �������
��� ��� ����������� ��� �������, ����������*/
void printCust();
void printAccount();
/*��� ��� ������������� ��� ������� ��� ���������� ��� ���
���������, ����������*/
void initDeposit();
void initWithdrawal();
/*��� ��� �������� ��� ������� ��� ���������� ��� ���
��� ��� ���������, ����������*/

void printDeposit();
void printWithdrawals();
/*����������� ��� ��� ���������� ��� ATM*/
void setupDataBase();
void login();
void atmMenu(char *uAccount);
double accountBalance(char *uAccount);
void accountDeposit(char *uaccount, double amount);
double accountWithdrawals(char *uaccount);
void accountTansfer(char *uaccount);
/*���� ��� �� �������� ��� �������*/
typedef struct
{
    char username[N];
    char PIN[5];
    char firstName[N], lastName[N];
    char vat[11];
} customer;
/*���� ��� �� �������� ��� ����������� ��� �������*/
typedef struct
{
    char username[N];
    char bban[M];
    char iban[28];
    double amount;
} account;
/*���� ��� �� �������� ����������/���������/�����o��� ��� �������*/
typedef struct
{
    char bban[M];
    int day;
    int month;
    int year;
    double amount;
    char comments[51];
} transactionsRec;
