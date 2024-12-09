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
extern customer *custBase;
extern account *accBase;
extern int numCust;
extern int numAcc;
/*��������� ��� ���������� �� �������� ��� ����������� � ������
������� �� ����������*/
double accountBalance(char *uAccount)
{
    int i=0, j, found=0;
    while(!found && i<numAcc)
    {
        /*�������� ��� ������� ��� ���������� ��� ���� �������� ��� ���
        ��������� ��� ������� ������ found=1*/
        if (strcmp(uAccount, accBase[i].bban)==0)
        {
            j=i;
            found=1;
        }
        i++;
    }
    /*���������� �� �������� ��� ����������� ��� ��������*/
    return(accBase[j].amount);
}
/*�������� ��� �������� ��������*/

void accountDeposit(char *uaccount, double amount)
{
    transactionsRec currTransaction;
    int i=0;
    FILE *fp;
    char c;
    /*��������� ��� ����������� ��� ���������*/
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    currTransaction.day=tm.tm_mday;
    currTransaction.month=tm.tm_mon+1;
    currTransaction.year=tm.tm_year+1900;
    strcpy(currTransaction.bban, uaccount);
    currTransaction.amount=amount;
    /*�������� �������*/
    printf("����� ��������� ��������� �� ���� 50 ����������:");
    while ((c=getchar())!='\n' && i<50) currTransaction.comments[i++]=c;
    currTransaction.comments[i]='\0';
    rewind(stdin);
    fp=fopen("deposits.bin", "rb+");
    /*������� ��� ����*/
    if (fp==NULL)
    {
        printf("Error Opening File %s\n", "deposits.bin");
    }
    /*��������� ��� ���������*/
    fseek(fp, 0, SEEK_SET);
    fread(&i, sizeof(int), 1, fp);
    if (i<0) i=1;
    else i++;
    fseek(fp, 0, SEEK_SET);
    fwrite(&i, sizeof(int), 1, fp);
    /*�������� ��� ������� ��������� �� ��� ��������� ����������*/
    fseek(fp, 0L, SEEK_END);
    fwrite(&currTransaction, sizeof(transactionsRec), 1, fp);
    fclose(fp);
    fp=fopen("accounts.bin", "rb+");
    fseek(fp, sizeof(int), SEEK_SET);
    i=0;
    /*��������� ��� ����������� ��� �������� ��� ���� ����� ������� ���
    ������ accounts.bin, ����� � ���������� ������ �� ����� ������*/
    while(i<numAcc)
    {
        if (strcmp(uaccount, accBase[i].bban)==0)
        {
            accBase[i].amount+=currTransaction.amount;
            fseek(fp, sizeof(int)+i*sizeof(account), SEEK_SET);
            fwrite(&accBase[i], sizeof(account), 1, fp);
        }
        i++;
    }
    fclose(fp);
}
/*�������� ��� ������� ��������*/
double accountWithdrawals(char *uaccount)
{
    transactionsRec currTransaction;
    int i=0;
    FILE *fp;
    char c;
    /*��������� ��� ����������� ��� ���������*/
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    currTransaction.day=tm.tm_mday;
    currTransaction.month=tm.tm_mon+1;
    currTransaction.year=tm.tm_year+1900;
    strcpy(currTransaction.bban, uaccount);
    printf("����� �� ���� ��� ��������:");
    scanf("%lf", &currTransaction.amount);
    rewind(stdin);
    fp=fopen("accounts.bin", "rb+");
    fseek(fp, sizeof(int), SEEK_SET);
    i=0;
    /*��������� ��� ����������� ��� �������� ��� ���� ����� ������� ���
    ������ accounts.bin, ����� � ���������� ������ �� ����� ������*/
    while(i<numAcc)
    {
        if (strcmp(uaccount, accBase[i].bban)==0)
        {
            /*������� �� �� ���� ����� ��������� ��� �� �� �������� ��� �����������*/
            if(currTransaction.amount<=accBase[i].amount)
            {
                accBase[i].amount-=currTransaction.amount;
                fseek(fp, sizeof(int)+i*sizeof(account), SEEK_SET);
                fwrite(&accBase[i], sizeof(account), 1, fp);
            }
            else
            {
                /*�� ���� ��� ������ ��� ��� ������ ����� ���������� ��� ��
                �������� ��� ����������� ���� ���������� -1*/
                printf("��� ������� ������� ��������\n");
                fclose(fp);
                return (-1);
            }
        }
        i++;
    }
    fclose(fp);
    i=0;
    /*�������� �������*/
    printf("����� ��������� �������� �� ���� 50 ����������:");
    while ((c=getchar())!='\n' && i<50) currTransaction.comments[i++]=c;
    currTransaction.comments[i]='\0';
    rewind(stdin);
    fp=fopen("withdrawal.bin", "rb+");
    /*������� ��� ����*/
    if (fp==NULL)
    {
        printf("Error Opening File %s\n", "withdrawal.bin");
    }
    /*��������� ��� ��������*/
    fseek(fp, 0, SEEK_SET);
    fread(&i, sizeof(int), 1, fp);
    if (i<0) i=1;
    else i++;
    fseek(fp, 0, SEEK_SET);
    fwrite(&i, sizeof(int), 1, fp);
    /*�������� ��� ������� ��������� �� ��� ��������� �������*/
    fseek(fp, 0L, SEEK_END);
    fwrite(&currTransaction, sizeof(transactionsRec), 1, fp);
    fclose(fp);
    return(currTransaction.amount);
}
/*�������� ��� �������� �������� ������ ��� �����������*/
void accountTansfer(char *uaccount)
{
    transactionsRec currTransaction;
    int i=0, j, found=0;

    double temp;
    printf("����� ��� ���������� ��� ����� ��� ��������:");
    scanf("%23s", currTransaction.bban);
    rewind(stdin);
    /*��������� ��� ����������� ��� ������ ��� ����� ������� found=1
    �� ��������� ��� ��� ����*/
    while(!found && i<numAcc)
    {
        if (strcmp(currTransaction.bban, accBase[i].bban)==0)
        {
            j=i;
            found=1;
        }
        i++;
    }
    if(found==1)
    {
        /*������� ��� ����� ��� ����� � ������� �� ����� ���������� ��� �� �������� ���
        �����������*/
        if((temp=accountWithdrawals(uaccount))>0)accountDeposit(accBase[j].bban, temp);
        system("CLS");
        printf("� �������� ����� �� ��������!\n");
    }
    else
    {
        system("CLS");
        printf("����������� �����������!\n");
        return;
    }
}
