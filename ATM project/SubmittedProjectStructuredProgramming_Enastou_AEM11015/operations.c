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
/*εντοπίζει και επιστρέφει το υπόλοιπο του λογαριασμού ο οποίος
περνάει ως παράμετρος*/
double accountBalance(char *uAccount)
{
    int i=0, j, found=0;
    while(!found && i<numAcc)
    {
        /*αναζητεί και βρίσκει τον λογαριασμό που έχει περαστει από την
        παράμετρο και σηκώνει σημαία found=1*/
        if (strcmp(uAccount, accBase[i].bban)==0)
        {
            j=i;
            found=1;
        }
        i++;
    }
    /*επιστρέφει το υπόλοιπο του λογαριασμού που εντόπισε*/
    return(accBase[j].amount);
}
/*Υλοποιεί την κατάθεση χρημάτων*/

void accountDeposit(char *uaccount, double amount)
{
    transactionsRec currTransaction;
    int i=0;
    FILE *fp;
    char c;
    /*καταγραφή της ημερομηνίας της κατάθεσης*/
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    currTransaction.day=tm.tm_mday;
    currTransaction.month=tm.tm_mon+1;
    currTransaction.year=tm.tm_year+1900;
    strcpy(currTransaction.bban, uaccount);
    currTransaction.amount=amount;
    /*εισαγωγή σχολίων*/
    printf("Δώστε περιγραφή Κατάθεσης το πολύ 50 χαρακτήρες:");
    while ((c=getchar())!='\n' && i<50) currTransaction.comments[i++]=c;
    currTransaction.comments[i]='\0';
    rewind(stdin);
    fp=fopen("deposits.bin", "rb+");
    /*Έλεγχος της ροής*/
    if (fp==NULL)
    {
        printf("Error Opening File %s\n", "deposits.bin");
    }
    /*καταγραφή της κατάθεσης*/
    fseek(fp, 0, SEEK_SET);
    fread(&i, sizeof(int), 1, fp);
    if (i<0) i=1;
    else i++;
    fseek(fp, 0, SEEK_SET);
    fwrite(&i, sizeof(int), 1, fp);
    /*ανανεωση του αρχείου αναλήψεων με την τελευταία καταθέσεων*/
    fseek(fp, 0L, SEEK_END);
    fwrite(&currTransaction, sizeof(transactionsRec), 1, fp);
    fclose(fp);
    fp=fopen("accounts.bin", "rb+");
    fseek(fp, sizeof(int), SEEK_SET);
    i=0;
    /*Αναζήτηση του λογαριασμού και ανανέωση του όσες φορές υπάρχει στο
    αρχείο accounts.bin, καθώς ο λογαρισμός μπορεί να είναι κοινός*/
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
/*Υλοποιεί την ανάληψη χρημάτων*/
double accountWithdrawals(char *uaccount)
{
    transactionsRec currTransaction;
    int i=0;
    FILE *fp;
    char c;
    /*καταγραφή της ημερομηνίας της κατάθεσης*/
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    currTransaction.day=tm.tm_mday;
    currTransaction.month=tm.tm_mon+1;
    currTransaction.year=tm.tm_year+1900;
    strcpy(currTransaction.bban, uaccount);
    printf("Δώστε το ποσό της Ανάλυψης:");
    scanf("%lf", &currTransaction.amount);
    rewind(stdin);
    fp=fopen("accounts.bin", "rb+");
    fseek(fp, sizeof(int), SEEK_SET);
    i=0;
    /*Αναζήτηση του λογαριασμού και ανανέωση του όσες φορές υπάρχει στο
    αρχείο accounts.bin, καθώς ο λογαρισμός μπορεί να είναι κοινός*/
    while(i<numAcc)
    {
        if (strcmp(uaccount, accBase[i].bban)==0)
        {
            /*Έλεγχος αν το ποσό είναι μικρότερο από το το υπόλοιπο του λογαριασμού*/
            if(currTransaction.amount<=accBase[i].amount)
            {
                accBase[i].amount-=currTransaction.amount;
                fseek(fp, sizeof(int)+i*sizeof(account), SEEK_SET);
                fwrite(&accBase[i], sizeof(account), 1, fp);
            }
            else
            {
                /*το ποσό που δόθηκε από τον χρήστη είναι μεγαλύτερο από το
                υπόλοιπο του λογαριασμού τότε επιστρεφει -1*/
                printf("Δεν υπάρχει επαρκές υπόλοιπο\n");
                fclose(fp);
                return (-1);
            }
        }
        i++;
    }
    fclose(fp);
    i=0;
    /*εισαγωγή σχολίων*/
    printf("Δώστε περιγραφή Ανάληψης το πολύ 50 χαρακτήρες:");
    while ((c=getchar())!='\n' && i<50) currTransaction.comments[i++]=c;
    currTransaction.comments[i]='\0';
    rewind(stdin);
    fp=fopen("withdrawal.bin", "rb+");
    /*Έλεγχος της ροής*/
    if (fp==NULL)
    {
        printf("Error Opening File %s\n", "withdrawal.bin");
    }
    /*καταγραφή της ανάληψης*/
    fseek(fp, 0, SEEK_SET);
    fread(&i, sizeof(int), 1, fp);
    if (i<0) i=1;
    else i++;
    fseek(fp, 0, SEEK_SET);
    fwrite(&i, sizeof(int), 1, fp);
    /*Ανανέωση του αρχείου αναλήψεων με την τελευταία ανάληψη*/
    fseek(fp, 0L, SEEK_END);
    fwrite(&currTransaction, sizeof(transactionsRec), 1, fp);
    fclose(fp);
    return(currTransaction.amount);
}
/*Υλοποιεί την μεταφορά χρημάτων μεταξύ δύο λογαριασμών*/
void accountTansfer(char *uaccount)
{
    transactionsRec currTransaction;
    int i=0, j, found=0;

    double temp;
    printf("Δώστε τον λογαριασμό που ειναι για μεταφορα:");
    scanf("%23s", currTransaction.bban);
    rewind(stdin);
    /*Αναζήτηση του λογαριασμού που δόθηκε και ύψωση σημαίας found=1
    σε περίπτωση που τον βρει*/
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
        /*Έλεγχος του ποσού που δίνει ο χρήστης αν ειναι μεγαλύτερο απο το υπολοιπο του
        λογαριασμού*/
        if((temp=accountWithdrawals(uaccount))>0)accountDeposit(accBase[j].bban, temp);
        system("CLS");
        printf("Η μεταφορά έγινε με επιτυχία!\n");
    }
    else
    {
        system("CLS");
        printf("Λανθασμένος λογαριασμός!\n");
        return;
    }
}
