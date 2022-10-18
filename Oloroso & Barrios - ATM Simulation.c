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
    int pinCode;
}REC;
typedef struct node{
    REC atm;
    struct node* next;
}LIST; LIST *L;

void insertcard(){
    FILE *fp;
    do{ system("cls");
        printf("Please insert card...");
        fp=fopen("f:\mypin.txt","r");
    } while(fp==NULL);
    fclose(fp);
    printf("Thank you. Please enter PIN: ");
    pin();
}

void pin(){
    int i;
    for (i = 0;i<6;i++){
        PIN[i]=getch();
        putchar('*');
    } PIN[i]='\0';
}

void makenull(){
    L=NULL;
}

void addNewATMaccount(REC x){
    LIST *p,*q,*temp;
    q=p=L;
    temp = (LIST*) ((malloc(sizeof(LIST))));
    temp->atm = x;
    while (p!=NULL && strcmp (x.name, p->atm.name)>=0){
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
    int p = locate(n);
    if (p<0){
        cout <<"Not found."<<endl;
        system("pause");
    } else {
        while(x!=4){
            system("cls");
            cout<<"Student updating: "<<endl;
            cout<<"Name: "<<n<<endl;
            cout<<"Quiz 1: "<<L.sRec[p].q1<<endl;
            cout<<"Quiz 2: "<<L.sRec[p].q2<<endl;
            cout<<"Quiz 3: "<<L.sRec[p].q3<<endl;
            cout<<endl<<"Update: "<<endl<<endl;
            cout<<"[1] Quiz 1"<<endl;
            cout<<"[2] Quiz 2"<<endl;
            cout<<"[3] Quiz 3"<<endl;
            cout<<"[4] Return to menu"<<endl<<endl;
            cout<<"Enter a Number: "; cin>>x;
            switch(x){
                case 1: cout<<"Input new score: ";cin>>L.sRec[p].q1;break;
                case 2: cout<<"Input new score: ";cin>>L.sRec[p].q2;break;
                case 3: cout<<"Input new score: ";cin>>L.sRec[p].q3;break;
                case 4: cout<<n<<" record is successfuly updated."<<endl;system("pause");break;
                default: cout<<"Select 1-4 only."<<endl;system("pause");
            }
        }
    }
}

void deleteAccount(char n[31]){
    LIST *p, *q;
    p=q=L;
    while(p!=NULL && strcmp (n, p->atm.name)!=0){
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
        case 1: system("cls");break;
        case 2: system("cls");
                //gusto ko pa sana maglagay dito ng "Enter your pin code" if same continue else back
                printf("Name of student you want to delete: "); scanf(" %[^\n]s",other.accountName);
                deleteAccount(other.accountName);break;
        case 3: system("cls");break;
        default:system("cls");break;
    }
}
int transactionMenu()[
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
]
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
                            default:
                        }
                    }
                    /*printf("Name of student you want to delete: "); scanf(" %[^\n]s",sr.name);
                    del(sr.name);*/break;
            case 3: exit(0);break;
            default: printf("Invalid input. Try again."); system("pause\n");
        }
    }
}
