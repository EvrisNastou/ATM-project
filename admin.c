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
/*Η συνάρτηση αυτή αρχικοποεί, διαχειρίζεται και τυπώνει
τα αρχεία με τους πελάτες, με τους λογαριασμούς τους, τα
αρχεία αναλήψεων και καταθέσεων*/
void admin()
{
    int choice;
    while(1)
    {
        printf("1-Αρχικοποίηση Αρχείου Πελατών\n");
        printf("2-Αρχικοποίηση Αρχείου Λογαριασμών\n");
        printf("3-Αρχικοποίηση Αρχείου Καταθέσεων\n");
        printf("4-Αρχικοποίηση Αρχείου Αναλήψεων\n");
        printf("5-Προσθήκη Πελάτων\n");
        printf("6-Προσθήκη Λογαριασμών\n");
        printf("7-Εκτύπωση Πελατών\n");
        printf("8-Εκτύπωση Λογαριασμών\n");
        printf("9-Εκτύπωση Καταθέσεων\n");
        printf("10-Εκτύπωση Αναλήψεων\n");
        printf("11-Έξοδος\n");
        printf("Επιλέξτε:");
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
            printf("Αποσύνδεση.\n");
            exit(0);
            break;
        default:
            printf("Εσφαλμένη επιλογή\n");
            break;
        }
    }
}
/*Για την αρχικοποίηση του αρχειου με τις καταθέσεις*/
void initDeposit()
{
    int i=-1;
    FILE *fp;
    fp=fopen("deposits.bin", "w+b");
    /*Ελένχει το άνοιγμα του αχρείου*/
    if (fp==NULL) printf("Error Opening File\n");
    fwrite(&i, sizeof(int), 1, fp);
    fclose(fp);
}
/*Για την αρχικοποίηση του αρχείου με τις αναλήψεις*/
void initWithdrawal()
{
    int i=-1;
    FILE *fp;
    fp=fopen("withdrawal.bin", "w+b");
    /*Ελέγχει το άνοιγμα του αρχείου*/
    if (fp==NULL) printf("Error Opening File\n");
    fwrite(&i, sizeof(int), 1, fp);

    fclose(fp);
}
/*Για την αρχικοποίηση του αρχείου με τα στοιχεία των πελατών*/
void initCust()
{
    FILE *cust;
    customer currCust;
    int choice, numCust=0;
    cust=fopen("users.bin", "wb");
    fseek(cust, sizeof(int), SEEK_SET);
    while(1)
    {
        printf("1-Προσθήκη Πελάτη\n");
        printf("2-Έξοδος\n");
        printf("Επιλέξτε:");
        scanf("%i", &choice);
        switch (choice)
        {
        /*Προσθήκη των στοιχείων των πελατών στην δομή δεδομένων*/
        case 1:
            printf("Όνομα:");
            scanf("%19s", currCust.firstName);
            rewind(stdin);
            printf("Επίθετο:");
            scanf("%19s", currCust.lastName);
            rewind(stdin);
            printf("ΑΦΜ:");
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
        /*Εξοδος μετά την εγγραφή των στοιχείων στο αρχείο*/
        case 2:
            printf("Τέλος!\n");
            rewind(cust);
            fwrite(&numCust, sizeof(int), 1, cust);
            fclose(cust);
            return;
            break;
        default:
            printf("Εσφαλμενη επιλογη\n");
            break;
        }
    }
}
/*Για την αρχικοποίηση του αρχείου με τις μεταφορές*/
void initAccount()
{
    FILE *acc;
    account currAcc;
    int choice, numAcc=0;
    acc=fopen("accounts.bin", "wb");

    fseek(acc, sizeof(int), SEEK_SET);
    while(1)
    {
        printf("1-Προσθήκη Λογαριασμού\n");
        printf("2-Έξοδος\n");
        printf("Επιλέξτε:");
        scanf("%i", &choice);
        switch (choice)
        {
        case 1:
            printf("Username:");
            scanf("%19s", currAcc.username);
            rewind(stdin);
            printf("BBAN:");
            scanf("%23s", currAcc.bban);
            /*Δημιουργία του ΙΒΑΝ το οποίο προκύπτει από το ΒΒΑΝ*/
            strcpy(currAcc.iban, "GR23");
            strcat(currAcc.iban, currAcc.bban);
            printf("Υπόλοιπο:");
            scanf("%lf", &currAcc.amount);
            rewind(stdin);
            fwrite(&currAcc, sizeof(currAcc), 1, acc);
            numAcc++;
            break;
        /*Έξοδος μετά την εγγραφή των στοιχείων στο αρχείο*/
        case 2:
            printf("Τέλος!\n");
            rewind(acc);
            fwrite(&numAcc, sizeof(int), 1, acc);
            fclose(acc);
            return;
            break;
        /*Έξοδος μετά την εγγραφή του πλήθους των στοιχείων στο αρχείο*/
        default:
            printf("Εσφαλμενη επιλογη\n");
            break;
        }
    }
}
/*Προσθηκη πελάτη στο αρχείο*/
void addCust()
{
    FILE *cust;
    customer currCust;
    int choice, numCust;
    /*Ανοιγμα αρχείου για εγγραφή*/
    cust=fopen("users.bin", "rb+");
    fread(&numCust, sizeof(int), 1, cust);
    fseek(cust, 0, SEEK_END);
    while(1)
    {
        printf("1-Προσθήκη Πελάτη\n");
        printf("2-Έξοδος\n");
        printf("Επιλέξτε:");
        scanf("%i", &choice);
        switch (choice)
        {
        /*Προσθήκη των στοιχείων του πελάτη στο αρχείο*/
        case 1:

            printf("Όνομα:");
            scanf("%19s", currCust.firstName);
            rewind(stdin);
            printf("Επίθετο:");
            scanf("%19s", currCust.lastName);
            rewind(stdin);
            printf("ΑΦΜ:");
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
        /*Εξοδος μετά την εγγραφή των στοιχείων του
        και του πλήθους των εγγραφών στο αρχείο*/
        case 2:
            printf("Τέλος!\n");
            fseek(cust, 0, SEEK_SET);
            printf("Σύνολος Αριθμός Πελατών=%d\n", numCust);
            fwrite(&numCust, sizeof(int), 1, cust);
            fclose(cust);
            return;
            break;
        default:
            printf("Εσφαλμένη επιλογή\n");
            break;
        }
    }
}
/*Προσθηκη λογαριασμού πελάτη στο αρχείο*/
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
        printf("1-Προσθήκη Λογαριασμού\n");
        printf("2-Έξοδος\n");
        printf("Επιλέξτε:");
        scanf("%i", &choice);
        switch (choice)
        {
        /*Προσθήκη των στοιχείων του λογαριασμού στο αρχείο*/
        case 1:
            printf("Username:");
            scanf("%19s", currAcc.username);
            rewind(stdin);
            printf("BBAN:");
            scanf("%23s", currAcc.bban);
            strcpy(currAcc.iban, "GR23");
            strcat(currAcc.iban, currAcc.bban);

            printf("Υπόλοιπο:");
            scanf("%lf", &currAcc.amount);
            rewind(stdin);
            fwrite(&currAcc, sizeof(currAcc), 1, acc);
            numAcc++;
            break;
        /*Έξοδος μετά την εγγραφή των στοιχείων του λογαριασμού
        και του πλήθους των εγγραφών στο αρχείο*/
        case 2:
            printf("Τέλος!\n");
            fseek(acc, 0, SEEK_SET);
            printf("Συνολικός αριθμός λογαριασμών=%d\n", numAcc);
            fwrite(&numAcc, sizeof(int), 1, acc);
            fclose(acc);
            return;
            break;
        default:
            printf("Εσφαλμενη επιλογη\n");
            break;
        }
    }
}
/*Για την εκτύπωση των λογαριασμών*/
void printAccount()
{
    FILE *fp;
    int numAcc, i;
    account *accBase;
    char c;
    /*Ανοιγμα του αρχείου και ανάγνωση του συνολικού αριθμού των λογαριασμών*/
    fp=fopen("accounts.bin", "rb");
    fread(&numAcc, sizeof(int), 1, fp);
    printf("Πλήθος Λογαριασμών=%d\n\n", numAcc);
    /*Δεσμεύουμε χώρο για μια συστοιχεία με εγγραφές τύπου account
    τόσων θέσεων όσος είναι ο αριθμός των εγγραφών που βρίσκεται
    αποθηκευμένο στο αρχείο accounts.bin*/
    accBase=(account *) malloc(numAcc*sizeof(account));
    if(accBase==NULL)
    {
        printf("Δεν υπάρχει διαθέσιμος χώρος");
        exit(1);
    }
    fread(accBase, sizeof(account), numAcc, fp);
    for(i=0; i<numAcc; i++)
    {
        printf("Χρήστης=%s BBAN=%s\n", accBase[i].username, accBase[i].bban);
        printf("IBAN=%s Υπόλοιπο=%lf\n\n", accBase[i].iban, accBase[i].amount);
    }
    printf("Για συνέχεια πατήστε ένα πλήκτρο:");
    rewind(stdin);
    scanf("%c", &c);
    system("CLS");
    free(accBase);
    fclose(fp);
}
/*Για την εκτύπωση των στοιχείων των πελατών*/
void printCust()
{
    FILE *fp;
    int numCust, i;
    customer *custBase;
    char c;
    /*Ανοιγμα του αχρείου και ανάγνωση του συνολικού αριθμού των πελατών*/
    fp=fopen("users.bin", "rb");
    fread(&numCust, sizeof(int), 1, fp);

    printf("Πλήθος Πελατών=%d\n\n", numCust);
    /*Δεσμεύουμε χώρο για μια συστοιχεία με εγγραφές τύπου customer
    τόσων θέσεων όσος είναι ο αριθμός των εγγραφών που βρίσκεται
    αποθηκευμένο στο αρχείο users.bin*/
    custBase=(customer *) malloc(numCust*sizeof(customer));
    if(custBase==NULL)
    {
        printf("Δεν υπάρχει διαθέσιμος χώρος");
        exit(1);
    }
    fread(custBase, sizeof(customer), numCust, fp);
    for(i=0; i<numCust; i++)
    {
        printf("%s %s %s\n", custBase[i].firstName, custBase[i].lastName, custBase[i].vat);
        printf("%s %s\n\n", custBase[i].username, custBase[i].PIN);
    }
    printf("Για συνέχεια πατήστε ένα πλήκτρο:");
    rewind(stdin);
    scanf("%c", &c);
    system("CLS");
    free(custBase);
    fclose(fp);
}
/*Για την εκτύπωση του αρχείου των καταθέσεων*/
void printDeposit()
{
    FILE *fp;
    int numDeposits, i;
    transactionsRec temp;
    char c;
    /*Ανοιγμα του αρχείου και ανάγνωση του συνολικού αριθμού των καταθέσεων*/
    fp=fopen("deposits.bin", "rb");
    fread(&numDeposits, sizeof(int), 1, fp);
    printf("Πλήθος Καταθέσεων=%d\n\n", numDeposits);
    for(i=0; i<numDeposits; i++)
    {
        fread(&temp, sizeof(transactionsRec), 1, fp);
        printf("BBAN=%s Ποσό=%lf\n", temp.bban, temp.amount);
        printf("Date:%d/%d/%d\n", temp.day, temp.month, temp.year);
        printf("Σχόλια:%s\n", temp.comments);
    }
    printf("Για συνέχεια πατήστε ένα πλήκτρο:");
    rewind(stdin);
    scanf("%c", &c);
    system("CLS");
    fclose(fp);
}
/*Για την εκτύπωση του αρχείου των αναλήψεων*/
void printWithdrawals()
{
    FILE *fp;
    int numWithdrawals, i;
    transactionsRec temp;
    char c;
    /*Ανοιγμα του αρχείου και ανάγνωση του συνολικού αριθμού των αναλήψεων*/
    fp=fopen("withdrawal.bin", "rb");
    fread(&numWithdrawals, sizeof(int), 1, fp);
    printf("Πλήθος Αναλήψεων=%d\n\n", numWithdrawals);
    for(i=0; i<numWithdrawals; i++)
    {
        fread(&temp, sizeof(transactionsRec), 1, fp);
        printf("BBAN=%s Ποσό=%lf\n", temp.bban, temp.amount);
        printf("Date:%d/%d/%d\n", temp.day, temp.month, temp.year);
        printf("Σχόλια:%s\n", temp.comments);
    }
    printf("Για συνέχεια πατήστε ένα πλήκτρο:");
    rewind(stdin);
    scanf("%c", &c);
    system("CLS");
    fclose(fp);
}
