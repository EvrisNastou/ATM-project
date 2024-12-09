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
#include "ATM.h"
/*� ��������� ���� ����������, ������������� ��� �������
�� ������ �� ���� �������, �� ���� ������������ ����, ��
������ ��������� ��� ����������*/
void admin()
{
    int choice;
    while(1)
    {
        printf("1-������������ ������� �������\n");
        printf("2-������������ ������� �����������\n");
        printf("3-������������ ������� ����������\n");
        printf("4-������������ ������� ���������\n");
        printf("5-�������� �������\n");
        printf("6-�������� �����������\n");
        printf("7-�������� �������\n");
        printf("8-�������� �����������\n");
        printf("9-�������� ����������\n");
        printf("10-�������� ���������\n");
        printf("11-������\n");
        printf("��������:");
        scanf("%i", &choice);
        system("CLS");
        switch (choice)
        {
        case 1:
            initCust();
            break;
        case 2:
            initAccount();
            break;
        case 3:
            initDeposit();
            break;
        case 4:
            initWithdrawal();
            break;
        case 5:
            addCust();
            break;
        case 6:
            addAccount();
            break;
        case 7:
            printCust();
            break;
        case 8:
            printAccount();
            break;
        case 9:
            printDeposit();
            break;
        case 10:
            printWithdrawals();
            break;
        case 11:
            printf("����������.\n");
            exit(0);
            break;
        default:
            printf("��������� �������\n");
            break;
        }
    }
}
/*��� ��� ������������ ��� ������� �� ��� ����������*/
void initDeposit()
{
    int i=-1;
    FILE *fp;
    fp=fopen("deposits.bin", "w+b");
    /*������� �� ������� ��� �������*/
    if (fp==NULL) printf("Error Opening File\n");
    fwrite(&i, sizeof(int), 1, fp);
    fclose(fp);
}
/*��� ��� ������������ ��� ������� �� ��� ���������*/
void initWithdrawal()
{
    int i=-1;
    FILE *fp;
    fp=fopen("withdrawal.bin", "w+b");
    /*������� �� ������� ��� �������*/
    if (fp==NULL) printf("Error Opening File\n");
    fwrite(&i, sizeof(int), 1, fp);

    fclose(fp);
}
/*��� ��� ������������ ��� ������� �� �� �������� ��� �������*/
void initCust()
{
    FILE *cust;
    customer currCust;
    int choice, numCust=0;
    cust=fopen("users.bin", "wb");
    fseek(cust, sizeof(int), SEEK_SET);
    while(1)
    {
        printf("1-�������� ������\n");
        printf("2-������\n");
        printf("��������:");
        scanf("%i", &choice);
        switch (choice)
        {
        /*�������� ��� ��������� ��� ������� ���� ���� ���������*/
        case 1:
            printf("�����:");
            scanf("%19s", currCust.firstName);
            rewind(stdin);
            printf("�������:");
            scanf("%19s", currCust.lastName);
            rewind(stdin);
            printf("���:");
            scanf("%10s", currCust.vat);
            rewind(stdin);
            printf("Username:");
            scanf("%19s", currCust.username);
            rewind(stdin);
            printf("PIN:");
            scanf("%4s", currCust.PIN);
            rewind(stdin);
            fwrite(&currCust, sizeof(currCust), 1, cust);
            numCust++;
            break;
        /*������ ���� ��� ������� ��� ��������� ��� ������*/
        case 2:
            printf("�����!\n");
            rewind(cust);
            fwrite(&numCust, sizeof(int), 1, cust);
            fclose(cust);
            return;
            break;
        default:
            printf("��������� �������\n");
            break;
        }
    }
}
/*��� ��� ������������ ��� ������� �� ��� ���������*/
void initAccount()
{
    FILE *acc;
    account currAcc;
    int choice, numAcc=0;
    acc=fopen("accounts.bin", "wb");

    fseek(acc, sizeof(int), SEEK_SET);
    while(1)
    {
        printf("1-�������� �����������\n");
        printf("2-������\n");
        printf("��������:");
        scanf("%i", &choice);
        switch (choice)
        {
        case 1:
            printf("Username:");
            scanf("%19s", currAcc.username);
            rewind(stdin);
            printf("BBAN:");
            scanf("%23s", currAcc.bban);
            /*���������� ��� ���� �� ����� ��������� ��� �� ����*/
            strcpy(currAcc.iban, "GR23");
            strcat(currAcc.iban, currAcc.bban);
            printf("��������:");
            scanf("%lf", &currAcc.amount);
            rewind(stdin);
            fwrite(&currAcc, sizeof(currAcc), 1, acc);
            numAcc++;
            break;
        /*������ ���� ��� ������� ��� ��������� ��� ������*/
        case 2:
            printf("�����!\n");
            rewind(acc);
            fwrite(&numAcc, sizeof(int), 1, acc);
            fclose(acc);
            return;
            break;
        /*������ ���� ��� ������� ��� ������� ��� ��������� ��� ������*/
        default:
            printf("��������� �������\n");
            break;
        }
    }
}
/*�������� ������ ��� ������*/
void addCust()
{
    FILE *cust;
    customer currCust;
    int choice, numCust;
    /*������� ������� ��� �������*/
    cust=fopen("users.bin", "rb+");
    fread(&numCust, sizeof(int), 1, cust);
    fseek(cust, 0, SEEK_END);
    while(1)
    {
        printf("1-�������� ������\n");
        printf("2-������\n");
        printf("��������:");
        scanf("%i", &choice);
        switch (choice)
        {
        /*�������� ��� ��������� ��� ������ ��� ������*/
        case 1:

            printf("�����:");
            scanf("%19s", currCust.firstName);
            rewind(stdin);
            printf("�������:");
            scanf("%19s", currCust.lastName);
            rewind(stdin);
            printf("���:");
            scanf("%10s", currCust.vat);
            rewind(stdin);
            printf("Username:");
            scanf("%19s", currCust.username);
            rewind(stdin);
            printf("PIN:");
            scanf("%4s", currCust.PIN);
            rewind(stdin);
            fwrite(&currCust, sizeof(currCust), 1, cust);
            numCust++;
            break;
        /*������ ���� ��� ������� ��� ��������� ���
        ��� ��� ������� ��� �������� ��� ������*/
        case 2:
            printf("�����!\n");
            fseek(cust, 0, SEEK_SET);
            printf("������� ������� �������=%d\n", numCust);
            fwrite(&numCust, sizeof(int), 1, cust);
            fclose(cust);
            return;
            break;
        default:
            printf("��������� �������\n");
            break;
        }
    }
}
/*�������� ����������� ������ ��� ������*/
void addAccount()
{
    FILE *acc;
    account currAcc;
    int choice, numAcc;
    acc=fopen("accounts.bin", "rb+");
    fread(&numAcc, sizeof(int), 1, acc);
    fseek(acc, 0, SEEK_END);
    while(1)
    {
        printf("1-�������� �����������\n");
        printf("2-������\n");
        printf("��������:");
        scanf("%i", &choice);
        switch (choice)
        {
        /*�������� ��� ��������� ��� ����������� ��� ������*/
        case 1:
            printf("Username:");
            scanf("%19s", currAcc.username);
            rewind(stdin);
            printf("BBAN:");
            scanf("%23s", currAcc.bban);
            strcpy(currAcc.iban, "GR23");
            strcat(currAcc.iban, currAcc.bban);

            printf("��������:");
            scanf("%lf", &currAcc.amount);
            rewind(stdin);
            fwrite(&currAcc, sizeof(currAcc), 1, acc);
            numAcc++;
            break;
        /*������ ���� ��� ������� ��� ��������� ��� �����������
        ��� ��� ������� ��� �������� ��� ������*/
        case 2:
            printf("�����!\n");
            fseek(acc, 0, SEEK_SET);
            printf("��������� ������� �����������=%d\n", numAcc);
            fwrite(&numAcc, sizeof(int), 1, acc);
            fclose(acc);
            return;
            break;
        default:
            printf("��������� �������\n");
            break;
        }
    }
}
/*��� ��� �������� ��� �����������*/
void printAccount()
{
    FILE *fp;
    int numAcc, i;
    account *accBase;
    char c;
    /*������� ��� ������� ��� �������� ��� ��������� ������� ��� �����������*/
    fp=fopen("accounts.bin", "rb");
    fread(&numAcc, sizeof(int), 1, fp);
    printf("������ �����������=%d\n\n", numAcc);
    /*���������� ���� ��� ��� ���������� �� �������� ����� account
    ����� ������ ���� ����� � ������� ��� �������� ��� ���������
    ������������ ��� ������ accounts.bin*/
    accBase=(account *) malloc(numAcc*sizeof(account));
    if(accBase==NULL)
    {
        printf("��� ������� ���������� �����");
        exit(1);
    }
    fread(accBase, sizeof(account), numAcc, fp);
    for(i=0; i<numAcc; i++)
    {
        printf("�������=%s BBAN=%s\n", accBase[i].username, accBase[i].bban);
        printf("IBAN=%s ��������=%lf\n\n", accBase[i].iban, accBase[i].amount);
    }
    printf("��� �������� ������� ��� �������:");
    rewind(stdin);
    scanf("%c", &c);
    system("CLS");
    free(accBase);
    fclose(fp);
}
/*��� ��� �������� ��� ��������� ��� �������*/
void printCust()
{
    FILE *fp;
    int numCust, i;
    customer *custBase;
    char c;
    /*������� ��� ������� ��� �������� ��� ��������� ������� ��� �������*/
    fp=fopen("users.bin", "rb");
    fread(&numCust, sizeof(int), 1, fp);

    printf("������ �������=%d\n\n", numCust);
    /*���������� ���� ��� ��� ���������� �� �������� ����� customer
    ����� ������ ���� ����� � ������� ��� �������� ��� ���������
    ������������ ��� ������ users.bin*/
    custBase=(customer *) malloc(numCust*sizeof(customer));
    if(custBase==NULL)
    {
        printf("��� ������� ���������� �����");
        exit(1);
    }
    fread(custBase, sizeof(customer), numCust, fp);
    for(i=0; i<numCust; i++)
    {
        printf("%s %s %s\n", custBase[i].firstName, custBase[i].lastName, custBase[i].vat);
        printf("%s %s\n\n", custBase[i].username, custBase[i].PIN);
    }
    printf("��� �������� ������� ��� �������:");
    rewind(stdin);
    scanf("%c", &c);
    system("CLS");
    free(custBase);
    fclose(fp);
}
/*��� ��� �������� ��� ������� ��� ����������*/
void printDeposit()
{
    FILE *fp;
    int numDeposits, i;
    transactionsRec temp;
    char c;
    /*������� ��� ������� ��� �������� ��� ��������� ������� ��� ����������*/
    fp=fopen("deposits.bin", "rb");
    fread(&numDeposits, sizeof(int), 1, fp);
    printf("������ ����������=%d\n\n", numDeposits);
    for(i=0; i<numDeposits; i++)
    {
        fread(&temp, sizeof(transactionsRec), 1, fp);
        printf("BBAN=%s ����=%lf\n", temp.bban, temp.amount);
        printf("Date:%d/%d/%d\n", temp.day, temp.month, temp.year);
        printf("������:%s\n", temp.comments);
    }
    printf("��� �������� ������� ��� �������:");
    rewind(stdin);
    scanf("%c", &c);
    system("CLS");
    fclose(fp);
}
/*��� ��� �������� ��� ������� ��� ���������*/
void printWithdrawals()
{
    FILE *fp;
    int numWithdrawals, i;
    transactionsRec temp;
    char c;
    /*������� ��� ������� ��� �������� ��� ��������� ������� ��� ���������*/
    fp=fopen("withdrawal.bin", "rb");
    fread(&numWithdrawals, sizeof(int), 1, fp);
    printf("������ ���������=%d\n\n", numWithdrawals);
    for(i=0; i<numWithdrawals; i++)
    {
        fread(&temp, sizeof(transactionsRec), 1, fp);
        printf("BBAN=%s ����=%lf\n", temp.bban, temp.amount);
        printf("Date:%d/%d/%d\n", temp.day, temp.month, temp.year);
        printf("������:%s\n", temp.comments);
    }
    printf("��� �������� ������� ��� �������:");
    rewind(stdin);
    scanf("%c", &c);
    system("CLS");
    fclose(fp);
}
