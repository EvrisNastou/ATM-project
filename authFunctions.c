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
/*Στην περίπτωση που η αυθεντικοποίηση γίνεται με το username συγκεντρώνονται
οι λογαριασμοί του και του ζητείται να επιλέξει ένα από αυτούς που θα ζητήσει κάποια
ενέργεια*/
void selectAccount(char *uName, char *uAccount)
{
    int i=0, j, count=0, found;
    char **candiAccounts;
    /*Αναζητηση και απαρίθμηση των λογαριασμων του πελάτη*/
    while(i<numAcc)
    {
        if (strcmp(uName, accBase[i].username)==0)
        {
            count++;
            /*j είναι ο δείκτης για να βρούμε τον λογαριασμό του
            χρήστη σε περίπτωση που αυτός έχει έναν λογαρισμό.*/
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
            printf("Δεν υπάρχει διαθέσιμος χώρος");
            exit(1);
        }
        i=0;
        j=0;
        /*αναζήτηση όλων των λογαριασμών*/
        while(i<numAcc)
        {
            /*Εδώ η j απαριθμεί τους λογαριασμούς του πελάτη*/
            if (strcmp(uName, accBase[i].username)==0)
            {
                candiAccounts[j]=accBase[i].bban;
                j++;
            }
            i++;
        }
        found=0;
        /*Εδώ τυπώνονται όλοι οι λογαριασμοί οι οποίοι ανήκουν στον πελάτη
        και δίνονται προς επιλογή*/
        while(!found)
        {

            for (i=0; i<count; i++)
            {
                printf("%d-BBAN=%s\n", i, candiAccounts[i]);
            }
            printf("Επέλεξε Λογαριασμό:");
            scanf("%d", &j);
            system("CLS");
            if (j<count && j>=0)
            {
                strcpy(uAccount, candiAccounts[j]);

                found=1;

            }
            else printf("Εσφαλμένη επιλογή! Προσπάθησε ξανά!\n");
        }
        free(candiAccounts);
    }
}
/*Εδω ελέγχονται αν το username και το PIN που δίνει ο χρήστης
υπάρχουν στη βάση δεδομένων*/
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
    /*Εδώ θα βρεθεί η ροή όταν τα στοιχεία δεν ταιριάζουν
    με κανενός από τους καταχωρημένους χρήστες*/
    return(0);
}
/*Εδω ελέγχονται αν ο λογαριασμός και το PIN που δίνει ο χρήστης
υπάρχουν στη βάση δεδομένων*/
int verifyAccount(char *uAccount, char *PIN)
{
    int i=0;
    while(i<numAcc)
    {
        /*Ελέγχεται η περίπτωση που πολλοί χρήστες είναι συνδικαιούχοι ενός λογαριασμού*/
        if (strcmp(uAccount, accBase[i].bban)==0)
        {
            if (verifyUser(accBase[i].username, PIN)) return(1);
        }
        i++;
    }
    /*Εδώ θα βρεθεί η ροή όταν τα στοιχεία δεν ταιριάζουν
    με του χρήστη που έδωσε το PIN*/
    return(0);
}
/*Για την είσοδο των πελατών στο ATM με τους κωδικούς τους*/
void login()
{
    char PIN[5], c;
    char uName[N], uAccount[M];
    int choice, i;
    while(1)
    {
        printf("   ATM\n");
        printf("Σύνδεση με:\n");
        printf("1-Όνομα χρήστη\n");
        printf("2-Αριθμό λογαριασμού\n");
        //printf("3-Έξοδος\n");
        printf("Επιλέξτε:");

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
                /*Εδω εισάγεται το PIN χωρις να φαίνεται και τυπώνεται στην
                οθόνη το χαρακτηριστικο * */
                while((c=_getch())!=13 && i<4)
                {
                    PIN[i++]=c;
                    printf("*");
                }
                PIN[i]='\0';
                system("CLS");
                /*Έλεγχος του κωδικού μέσω της συνάρτησης verifyUser(char *uName, char
                *PIN);*/
                if(verifyUser(uName, PIN))
                {
                    selectAccount(uName, uAccount);
                    system("CLS");
                    printf("%s\n", uAccount);
                    atmMenu(uAccount);
                    break;
                }
                else printf("Εσφαλμένος κωδικός ή όνομα χρήστη\n");
            }
            break;
        case 2:
            while(1)
            {
                printf("Αριθμός λογαριασμού:");
                scanf("%23s", uAccount);
                rewind(stdin);
                printf("PIN:");
                i=0;
                /*Εδω εισάγεται το PIN χωρις να φαίνεται και τυπώνεται στην
                οθόνη το χαρακτηριστικο * */
                while((c=_getch())!=13 && i<4)
                {
                    PIN[i++]=c;
                    printf("*");
                }
                /*Έλεγχος του κωδικού μέσω της συνάρτησης verifyAccount(char *uAccount,
                char *PIN);*/
                if(verifyAccount(uAccount, PIN))
                {
                    atmMenu(uAccount);
                    break;
                }
                else printf("Εσφαλμένος κωδικός ή όνομα χρήστη\n");
            }
            break;
        case 3:
            printf("Shutting Down ATM!!!\n");
            exit(0);
            break;
        default:
            printf("Εσφαλμένη επιλογή\n");
            break;
        }
    }
}
/*Δημιουργεί ένα πίνακα με τους πελάτες και ένα πίνακα για τους λογαριασμούς
διαβάζοντας δεδομένα από τα αρχεία users.bin και accounts.bin*/
void setupDataBase()
{
    FILE *fp;
    fp=fopen("users.bin", "rb");
    fread(&numCust, sizeof(int), 1, fp);
    custBase=(customer *) malloc(numCust*sizeof(customer));
    if(custBase==NULL)
    {
        printf("Δεν υπάρχει διαθέσιμος χώρος");
        exit(1);
    }
    fread(custBase, sizeof(customer), numCust, fp);
    fclose(fp);
    fp=fopen("accounts.bin", "rb");
    fread(&numAcc, sizeof(int), 1, fp);
    accBase=(account *) malloc(numAcc*sizeof(account));
    if(accBase==NULL)
    {
        printf("Δεν υπάρχει διαθέσιμος χώρος");
        exit(1);
    }
    fread(accBase, sizeof(account), numAcc, fp);
    fclose(fp);
}
/*Για την είσοδο στο Menu του ATM μετά τον έλεγχο των στοιχείων*/
void atmMenu(char *uaccount)
{
    int choice;
    double amount;
    while(1)
    {
        printf("1-Υπόλοιπο Λογαριασμού\n");
        printf("2-Κατάθεση\n");
        printf("3-Ανάληψη\n");
        printf("4-Μεταφορά\n");
        printf("5-Αποσύνδεση\n");
        printf("Επιλέξτε:");
        scanf("%i", &choice);
        system("CLS");
        switch (choice)
        {
        case 1:
            printf("Υπόλοιπο Λογαριασμού=%lf\n", accountBalance(uaccount));
            break;
        case 2:
            printf("Δώστε το ποσό της κατάθεσης:");
            scanf("%lf", &amount);
            rewind(stdin);
            accountDeposit(uaccount, amount);
            system("CLS");
            printf("Η κατάθεση έγινε με επιτυχία!\n");
            break;
        case 3:

            accountWithdrawals(uaccount);
            system("CLS");
            printf("Η ανάληψη έγινε με επιτυχία!\n");
            break;
        case 4:
            accountTansfer(uaccount);
            break;
        case 5:
            return;
            break;
        default:
            printf("Εσφαλμενη επιλογη\n");
            break;
        }
    }
}
