/*Project 1 - ATM SIMULATION in C using linked list
by Andrew R. Oloroso and Armand Angelo C. Barrios*/
#include <stdio.h>
#include <conio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

typedef struct details{
    char accountName[31];
    int accountNumber;
    char birthday[31];
    int contactNumber;
    int initialDeposit;
    char pinCode[7];
}REC;
typedef struct node{
    REC atm;
    struct node* next;
}LIST; LIST *L;

void piin(){
    int i;
    for (i = 0;i<6;i++){
        L->atm.pinCode[i]=getch();
        putchar('*');
    } L->atm.pinCode[i]='\0';
}

void insertcard(){
    FILE *fp;
    do{ system("cls");
        printf("Please insert card...");
        fp=fopen("F:\pakanangpakshet.txt","r");
    } while(fp==NULL);
    fclose(fp);
    printf("Thank you. Please enter PIN: ");
    piin();
}

void makenull(){
    L=NULL;
}

void addNewATMaccount(REC x){
    LIST *p,*q,*temp;
    q=p=L;
    temp = (LIST*) ((malloc(sizeof(LIST))));
    temp->atm = x;
    while (p!=NULL && strcmp (x.accountName, p->atm.accountName)>=0){
        q=p;
        p=p->next;
    }
    if (p==L){//first element
        L=temp;
    }else{
        q->next = temp;
    }temp->next = p;
}

void updateAccount(char n[31]){
    int x;
    LIST *p, *q;
    p=q=L;
    while(p!=NULL && strcmp (n, p->atm.accountName)!=0){
        q=p;
        p=p->next;
    }
    if (p==NULL){
        printf("Not found.\n");system("pause");
    }else{
        while(x!=6){
            system("cls");
            printf("Updating Account: \n");
            printf("\nAccount Number: %d",p->atm.accountNumber);
            printf("\nAccount Name: %s",p->atm.accountName);
            printf("\nBirthday: %s",p->atm.birthday);
            printf("\nContact Number: %d",p->atm.contactNumber);
            printf("\nPIN Code: %d",p->atm.pinCode);
            printf("\nUPDATE: \n");
            printf("\n[1] Account Number");
            printf("\n[2] Account Name");
            printf("\n[3] Birthday");
            printf("\n[4] Contact Number");
            printf("\n[5] PIN Code");
            printf("\n[6] Back");
            printf("\n\nEnter a Number: ");scanf("%d", &x);
            switch(x){
                case 1: printf("\nInput new Account Number: ");scanf("%d", &p->atm.accountNumber);break;
                case 2: printf("\nInput new Account Name: ");scanf("%d",p->atm.accountName);break;
                case 3: printf("\nInput new Birthday: ");scanf("%d",p->atm.birthday);break;
                case 4: printf("\nInput new Contact Number: ");scanf("%d", &p->atm.contactNumber);break;
                case 5: printf("\nInput new PIN Code: ");scanf("%d", &p->atm.pinCode);break;
                case 6: printf("\n%s's account is successfully updated.", p->atm.accountName);system("pause");break;
                default: printf("\nSelect 1-6 only\n");system("pause");
            }
        }
    }
}

void deleteAccount(char n[31]){
    LIST *p, *q;
    p=q=L;
    while(p!=NULL && strcmp (n, p->atm.accountName)!=0){
        q=p;
        p=p->next;
    }
    if (p==NULL){
        printf("Not found.\n");system("pause");
    }else{
        //prompt dito ng "do you really want to fucking delete your acc" answerable by yes or no bago mag if else
        if (p==L){//if first element
           L=p->next;
        }else{
           q->next=p->next;
        }free(p);printf("%s's account is successfully deleted.\n",n);system("pause");
    }
}

int menu(){
    int UserNum;
    printf("Choose Module: \n");
    printf("[1] REGISTRATION MODULE\n");
    printf("[2] TRANSACTION MODULE\n");
    printf("[3] EXIT\n");
    printf("\nEnter your choice 1-3: ");
    scanf("%d", &UserNum);
    return UserNum;
}
int otherTransactionMenu(){
    REC other;
    int UserNum;
    printf("Choose Transaction: \n");
    printf("[1] Update Account\n");
    printf("[2] Delete Account\n");
    printf("[3] Back\n");
    printf("\nEnter your choice 1-3: ");
    scanf("%d", &UserNum);
    switch(UserNum){
        case 1: system("cls");
                //gusto ko pa sana maglagay dito ng "Enter your pin code" if same continue else back
                printf("Name of student you want to update: "); scanf(" %[^\n]s",other.accountName);
                updateAccount(other.accountName);break;
        case 2: system("cls");
                //gusto ko pa sana maglagay dito ng "Enter your pin code" if same continue else back
                printf("Name of student you want to delete: "); scanf(" %[^\n]s",other.accountName);
                deleteAccount(other.accountName);break;
        case 3: system("cls");break;
        default:system("cls");break;
    }
}
int transactionMenu(){
    int UserNum;
    printf("Choose Transaction: \n");
    printf("[1] Balance Inquiry\n");
    printf("[2] Withdraw\n");
    printf("[3] Deposit\n");
    printf("[4] Funnd Transfer (for enrolled accounts only)\n");
    printf("[5] Change PIN Code\n");
    printf("[6] Other Transactions\n");
    printf("[7] Exit\n");
    printf("\nEnter your choice 1-6: ");
    scanf("%d", &UserNum);
    if(UserNum!=6){
        return UserNum;
    }else{
        otherTransactionMenu();
    }
}
int main(){
    REC bdo;
    insertcard();
    makenull();
    while(1){
        system ("cls");
        switch(menu()){
            case 1: system("cls"); printf("REGISTRATION MODULE\n"); printf("Please fill out the following informations: \n\n");
                    printf("\nAccount Number (5 Digits): ");scanf("%d", &bdo.accountNumber);
                    printf("\nAccount Name: "); scanf(" %[^\n]s",bdo.accountName);
                    printf("\nBirthday (MM/DD/YY): "); scanf(" %[^\n]s",bdo.birthday);
                    printf("\nContact Number: ");scanf("%d", &bdo.accountNumber);
                    printf("\nInitial Deposit (Min. 5,000): ");scanf("%d", &bdo.initialDeposit);
                    printf("\nPIN Code: ");scanf("%d", &bdo.pinCode);
                    addNewATMaccount(bdo);
                    printf("\nRegistration Successfull\nCongratulations %s! Welcome to Bank Rupt.\n", bdo.accountName);
                    system("pause"); break;
            case 2: system("cls"); printf("TRANSACTION MODULE\n\n");
                    while(1){
                        switch(transactionMenu()){
                            case 1: break;
                            default: break;
                        }
                    }
                    /*printf("Name of student you want to delete: "); scanf(" %[^\n]s",sr.name);
                    del(sr.name);*/break;
            case 3: exit(0);break;
            default: printf("Invalid input. Try again."); system("pause\n");
        }
    }
}
