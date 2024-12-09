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
customer *custBase;
account *accBase;
int numCust;
int numAcc;
/*���� ��������� ��� � ��������������� ������� �� �� username ���������������
�� ����������� ��� ��� ��� �������� �� �������� ��� ��� ������ ��� �� ������� ������
��������*/
void selectAccount(char *uName, char *uAccount)
{
    int i=0, j, count=0, found;
    char **candiAccounts;
    /*��������� ��� ���������� ��� ����������� ��� ������*/
    while(i<numAcc)
    {
        if (strcmp(uName, accBase[i].username)==0)
        {
            count++;
            /*j ����� � ������� ��� �� ������ ��� ���������� ���
            ������ �� ��������� ��� ����� ���� ���� ���������.*/
            j=i;
        }
        i++;
    }
    if (count==1) strcpy(uAccount, accBase[j].bban);
    else
    {
        candiAccounts=(char **) malloc(count*sizeof(char *));
        if(candiAccounts==NULL)
        {
            printf("��� ������� ���������� �����");
            exit(1);
        }
        i=0;
        j=0;
        /*��������� ���� ��� �����������*/
        while(i<numAcc)
        {
            /*��� � j ��������� ���� ������������ ��� ������*/
            if (strcmp(uName, accBase[i].username)==0)
            {
                candiAccounts[j]=accBase[i].bban;
                j++;
            }
            i++;
        }
        found=0;
        /*��� ���������� ���� �� ����������� �� ������ ������� ���� ������
        ��� �������� ���� �������*/
        while(!found)
        {

            for (i=0; i<count; i++)
            {
                printf("%d-BBAN=%s\n", i, candiAccounts[i]);
            }
            printf("������� ����������:");
            scanf("%d", &j);
            system("CLS");
            if (j<count && j>=0)
            {
                strcpy(uAccount, candiAccounts[j]);

                found=1;

            }
            else printf("��������� �������! ���������� ����!\n");
        }
        free(candiAccounts);
    }
}
/*��� ���������� �� �� username ��� �� PIN ��� ����� � �������
�������� ��� ���� ���������*/
int verifyUser(char *uName, char *PIN)
{
    int i=0;
    while(i<numCust)
    {
        if (strcmp(uName, custBase[i].username)==0)
        {
            if(strcmp(PIN, custBase[i].PIN)==0)return(1);
        }
        i++;
    }
    /*��� �� ������ � ��� ���� �� �������� ��� ����������
    �� ������� ��� ���� �������������� �������*/
    return(0);
}
/*��� ���������� �� � ����������� ��� �� PIN ��� ����� � �������
�������� ��� ���� ���������*/
int verifyAccount(char *uAccount, char *PIN)
{
    int i=0;
    while(i<numAcc)
    {
        /*��������� � ��������� ��� ������ ������� ����� ������������� ���� �����������*/
        if (strcmp(uAccount, accBase[i].bban)==0)
        {
            if (verifyUser(accBase[i].username, PIN)) return(1);
        }
        i++;
    }
    /*��� �� ������ � ��� ���� �� �������� ��� ����������
    �� ��� ������ ��� ����� �� PIN*/
    return(0);
}
/*��� ��� ������ ��� ������� ��� ATM �� ���� �������� ����*/
void login()
{
    char PIN[5], c;
    char uName[N], uAccount[M];
    int choice, i;
    while(1)
    {
        printf("   ATM\n");
        printf("������� ��:\n");
        printf("1-����� ������\n");
        printf("2-������ �����������\n");
        //printf("3-������\n");
        printf("��������:");

        scanf("%i", &choice);
        system("CLS");
        switch (choice)
        {
        case 1:
            while(1)
            {
                printf("User name:");
                scanf("%19s", uName);
                rewind(stdin);
                printf("PIN:");
                i=0;
                /*��� ��������� �� PIN ����� �� �������� ��� ��������� ����
                ����� �� �������������� * */
                while((c=_getch())!=13 && i<4)
                {
                    PIN[i++]=c;
                    printf("*");
                }
                PIN[i]='\0';
                system("CLS");
                /*������� ��� ������� ���� ��� ���������� verifyUser(char *uName, char
                *PIN);*/
                if(verifyUser(uName, PIN))
                {
                    selectAccount(uName, uAccount);
                    system("CLS");
                    printf("%s\n", uAccount);
                    atmMenu(uAccount);
                    break;
                }
                else printf("���������� ������� � ����� ������\n");
            }
            break;
        case 2:
            while(1)
            {
                printf("������� �����������:");
                scanf("%23s", uAccount);
                rewind(stdin);
                printf("PIN:");
                i=0;
                /*��� ��������� �� PIN ����� �� �������� ��� ��������� ����
                ����� �� �������������� * */
                while((c=_getch())!=13 && i<4)
                {
                    PIN[i++]=c;
                    printf("*");
                }
                /*������� ��� ������� ���� ��� ���������� verifyAccount(char *uAccount,
                char *PIN);*/
                if(verifyAccount(uAccount, PIN))
                {
                    atmMenu(uAccount);
                    break;
                }
                else printf("���������� ������� � ����� ������\n");
            }
            break;
        case 3:
            printf("Shutting Down ATM!!!\n");
            exit(0);
            break;
        default:
            printf("��������� �������\n");
            break;
        }
    }
}
/*���������� ��� ������ �� ���� ������� ��� ��� ������ ��� ���� ������������
����������� �������� ��� �� ������ users.bin ��� accounts.bin*/
void setupDataBase()
{
    FILE *fp;
    fp=fopen("users.bin", "rb");
    fread(&numCust, sizeof(int), 1, fp);
    custBase=(customer *) malloc(numCust*sizeof(customer));
    if(custBase==NULL)
    {
        printf("��� ������� ���������� �����");
        exit(1);
    }
    fread(custBase, sizeof(customer), numCust, fp);
    fclose(fp);
    fp=fopen("accounts.bin", "rb");
    fread(&numAcc, sizeof(int), 1, fp);
    accBase=(account *) malloc(numAcc*sizeof(account));
    if(accBase==NULL)
    {
        printf("��� ������� ���������� �����");
        exit(1);
    }
    fread(accBase, sizeof(account), numAcc, fp);
    fclose(fp);
}
/*��� ��� ������ ��� Menu ��� ATM ���� ��� ������ ��� ���������*/
void atmMenu(char *uaccount)
{
    int choice;
    double amount;
    while(1)
    {
        printf("1-�������� �����������\n");
        printf("2-��������\n");
        printf("3-�������\n");
        printf("4-��������\n");
        printf("5-����������\n");
        printf("��������:");
        scanf("%i", &choice);
        system("CLS");
        switch (choice)
        {
        case 1:
            printf("�������� �����������=%lf\n", accountBalance(uaccount));
            break;
        case 2:
            printf("����� �� ���� ��� ���������:");
            scanf("%lf", &amount);
            rewind(stdin);
            accountDeposit(uaccount, amount);
            system("CLS");
            printf("� �������� ����� �� ��������!\n");
            break;
        case 3:

            accountWithdrawals(uaccount);
            system("CLS");
            printf("� ������� ����� �� ��������!\n");
            break;
        case 4:
            accountTansfer(uaccount);
            break;
        case 5:
            return;
            break;
        default:
            printf("��������� �������\n");
            break;
        }
    }
}
