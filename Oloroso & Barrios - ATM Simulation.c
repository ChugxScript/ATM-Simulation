/*Project 1 - ATM SIMULATION in C using linked list
by Andrew R. Oloroso and Armand Angelo C. Barrios*/
#include <stdio.h>
#include <conio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> //for isdigit()

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

char c,ping[7];
void insertcard(){
    FILE *fp;
    do{ system("cls");
        printf("Please insert card...");
        fp=fopen("F:\pakanangpakshet.txt","r+");
    } while(fp==NULL);
    fclose(fp);
    printf("\nCard inserted successfully.\n"); system("pause");
}

void USER(){
    int x;
    printf("\nAre you a NEW or EXISTING user?\n");
    printf(" [1] if NEW [2] if EXISTING."); scanf("%d", &x);
    if(x==1){
        regMode();
    }else{
        pin();
    }
}

void regMode(){
    REC bpi;
    system("cls"); printf("REGISTRATION MODULE\n"); printf("Please fill out the following informations: \n\n");
    printf("\nAccount Number (5 Digits): ");scanf("%d", &bpi.accountNumber);
    printf("\nAccount Name: "); scanf(" %[^\n]s",bpi.accountName);
    printf("\nBirthday (MM/DD/YY): "); scanf(" %[^\n]s",bpi.birthday);
    printf("\nContact Number: ");scanf("%d", &bpi.accountNumber);
    printf("\nInitial Deposit (Min. 5,000): ");scanf("%d", &bpi.initialDeposit);
    printf("\nPIN Code: ");scanf("%d", &bpi.pinCode);
    addNewATMaccount(bpi);
    printf("\nRegistration Successfull\nCongratulations %s! Welcome to Bank Rupt.\n", bpi.accountName);
    system("pause");
}

void checkPin(char n[31]){  //it looks like locate in array
    LIST *p, *q;
    p=q=L;
    while(p!=NULL && strcmp (n, p->atm.pinCode)!=0){
        q=p;
        p=p->next;
    }
    if (p==NULL){
        printf("\nWala ka pang Account tangina mo bat ka nag enter ng pin!?\n");
        printf("\nDo you want to create an Account?\n");
        printf(" [Y] if Yes. [N] if No.");
        c = getch();
        if(c == 'n' || c == 'N'){
            exit(0);
        }else{
            regMode();
        }
    }else{
        printf("\nWag ka mag wiwithdraw mauubos pera mo %s!",p->atm.accountName);system("pause");
    }
}

void encrypt(){
    int i=0;
    while(ping[i]!='\0'){
        ping[i]=ping[i] + 70;
        i++;
    }
}

void decrypt(){
    int i=0;
    while(ping[i]!='\0'){
        ping[i]=ping[i] - 70;
        i++;
    }
}

void pin(){
    REC x;
    int index =0;
    char ch;
    printf("Enter PIN: ");
    while((ch=getch())!=13 && index<5){
        if (index<0){
            index=0;
        }
        if(ch==8){  //backspace ascii is 8
            putch('\b'); putch(' ');
            putch('\b'); index--;
            continue;
        }
        if(isdigit(ch)){
         strcpy(x.pinCode[index++],ch);
         putchar('*');
        }
    }
    if (index==5){
        strcpy(x.pinCode[index++],ch);
    }strcpy(x.pinCode[index++],'\0');
    encrypt(); printf("\n\nEncrypted Pin Code = %s\n",x.pinCode); system("pause");
    decrypt(); printf("\nDecrypted Pin Code = %s\n",x.pinCode); system("pause");
    checkPin(x.pinCode);
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
            printf("\n[5] Back");
            printf("\n\nEnter a Number: ");scanf("%d", &x);
            switch(x){
                case 1: printf("\nInput new Account Number: ");scanf("%d", &p->atm.accountNumber);break;
                case 2: printf("\nInput new Account Name: ");scanf("%d",p->atm.accountName);break;
                case 3: printf("\nInput new Birthday: ");scanf("%d",p->atm.birthday);break;
                case 4: printf("\nInput new Contact Number: ");scanf("%d", &p->atm.contactNumber);break;
                case 5: printf("\n%s's account is successfully updated.", p->atm.accountName);system("pause");break;
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
    printf("[1] ACCOUNT\n");
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
    USER();
    makenull();
    while(1){
        system ("cls");
        switch(menu()){
            case 1: system("cls"); regMode(); break;
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
