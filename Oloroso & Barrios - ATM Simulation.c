/*Project 1 - ATM SIMULATION in C using linked list
by Andrew R. Oloroso and Armand Angelo C. Barrios*/
#include <stdio.h>
#include <conio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

//tinanggal ko muna yung mga comments sa codes dati para makita mo yung mga kemeru, balik nalang siguro pag tapos na natin

/*
READ THIS SHITTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT BROOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO!
Mga Problema/Kulang:
1. Retrieve(); (ewan ko pano to)
2. Save();     (eto rin, ewan ko kung pano to)
3. Yung display ng birthday (tsaka yung sa update na birthday rin ata)
4. Contact No., need ata natin ma-ensure rito na 09-keme-keme ilalagay niya o wag na(??)
5. Pin Code sa regMode (dapat naka-char)
6. Palitan siguro yung initialDeposit na name tas gawing balance (suggestion lang, nakakalito kase) [goods na to fre]
7. Pagchecheck ng Pin Code (char kse eh so need ata natin i-compare every char)
8. Fund Transfer, di ko alam paano to gagawin
9. Yung decrypt (san banda to nakalagay)
10. Encrypt (san din to nakalagay)
11. Yung "Wrong Pin Code" sa Existing User na lumalabas pag hiningi yung pin
12. Yung sa update tas delete account pre, di na need yung name kasi bakit mo naman idedelete/i-uupdate account ng iba HAHAHA
    siguro tanong nalang yung pin, tas pag tama, g na yon.
13. pag pindot ko ng enter sa pincode nadadagdagan ng isang number

Addtl kineme:
Yung #11 ayusin ko na rin sana ngayon kaso inaantok nako HAHAHA.
Di ko pa masyado na-rurun and nachecheck yung mga nalagay ko so baka may mga bagong problems pa dyan HAHAHA. Check mo nalang kung trip mo.
delete mo nalang siguro yung mga keme na comments ko except dun sa listahan ng mga problema/kulang
Tulog pa ata ako habang binabasa mo to. HAHAHA.
*/

typedef struct details{
    char accountName[31];
    int accountNumber;
    int month,day,year;
    char contactNumber[12];
    int balance;
    char pinCode[7];
}REC;
typedef struct node{
    REC atm;
    struct node* next;
}LIST; LIST *L;

void makenull(){
    L=NULL;
}

int insertcard(){
    FILE *fp;
    do{
        system("cls");
        printf("Please insert card...");
        fp=fopen("D:\\Database.txt","w"); //in computer
        fp=fopen("F:\\Check.txt","w"); //in flashdrive
    }while(fp==NULL);
    fclose(fp);

    fp=fopen("F:\\ATM.txt","r");
    if(fp==NULL){
        printf("\nNOT YET REGISTERED\n"); system("pause");
        system("cls"); return 1;
    }else{
        printf("\nWELCOME\n");system("pause");
        system("cls"); return 2;
    }
    fclose(fp);
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
    if (p==L){
        L=temp;
    }else{
        q->next = temp;
    }temp->next = p;
}

void retrieve(){
    FILE *fp;
    REC z;
    fp=fopen("D:\\Database.txt","r+");
    if(fp==NULL){
        printf("File not found.\n");
        system("pause");
    }else{
        while(!feof(fp)){
            fscanf(fp,"%d",&z.accountNumber);
            fscanf(fp," %[ ^\t]s", z.accountName);
            fscanf(fp,"%d", &z.balance);
            fscanf(fp," %[ ^\t]s", z.pinCode);
            fscanf(fp,"%d %d %d", &z.month, &z.day, &z.year);
            fscanf(fp," %[ ^\n]s", z.contactNumber);
            addNewATMaccount(z);
        }fclose(fp);
    }
}

void birthDayy(REC *bday){
    printf("\nBirthday (MM/DD/YYYY)\n");
    a:
    printf("\nIf your birth month is January, enter 01");
    printf("\nEnter your birth month: ");scanf("%d",&bday->month);
    if(bday->month<=0 || bday->month>12){
        printf("\nInvalid Month.");system("pause");
        goto a;
    }
    b:
    printf("\nEnter your birth day: ");scanf("%d",&bday->day);
    if(bday->day<=0 || bday->day>31){
        printf("\nInvalid Day.");system("pause");
        goto b;
    }
    c:
    printf("\nEnter your birth year: ");scanf("%d",&bday->year);
    if(bday->year<=0 || bday->year>2022){
        printf("\nInvalid Year.");system("pause");
        goto c;
    }
}

int checkPin(char *n[7]){
    LIST *p, *q;
    p=q=L;
    printf("\n n=%s, pinCode=%s",n,p->atm.pinCode);system("pause");
    while(p!=NULL && strcmp (n, p->atm.pinCode)!=0){
        q=p;
        p=p->next;
    }
    if (p==NULL){
        printf("\nWrong PIN Code\n");system("pause");
        return 1;
    }else{
        printf("\nPIN verified.");system("pause");
        return 2;
    }
}

void pin(REC *x, int a){
    int index=0;
    int y=0,z=0;
    char ch;
    if(a==1){
        b:
        printf("\nPIN Code: ");
        while((ch=getch())!=13 && index<5){
            if (index<0){
                index=0;
            }
            if(ch==8){
                putch('\b'); putch(' ');
                putch('\b'); index--;
                continue;
            }
            if(isdigit(ch)){
                x->pinCode[index++]=ch;
                putchar('*');
            }
        }
        if (index==5){
            x->pinCode[index++]=ch;
            putchar('*');
        }x->pinCode[index]='\0';
        if(strlen(x->pinCode)<4){
            index=0;
            goto b;
        }
    }else if(a==2){
        do{
            c:
            index=0;
            system ("cls");
            printf("\nPIN Code: ");
            while((ch=getch())!=13 && index<5){
                if (index<0){
                    index=0;
                }
                if(ch==8){
                    putch('\b'); putch(' ');
                    putch('\b'); index--;
                    continue;
                }
                if(isdigit(ch)){
                 x->pinCode[index++]=ch;
                 putchar('*');
                }
            }
            if (index==5){
                x->pinCode[index++]=ch;
                putchar('*');
            }x->pinCode[index]='\0';
            if(strlen(x->pinCode)<4)
                goto c;
        }while(checkPin(&x->pinCode)==1);
    }

    /*printf("\n\nPin Code = %s\n",x.pinCode); system("pause");

    while(x->pinCode[y]!='\0'){
        x->pinCode[y]=x->pinCode[y] + 70;
        y++;
    }printf("\n\nEncrypted Pin Code = %s\n",x->pinCode); system("pause");

    while(x->pinCode[z]!='\0'){
        x->pinCode[z]=x->pinCode[z] - 70;
        z++;
    }printf("\nDecrypted Pin Code = %s\n",x->pinCode); system("pause");*/
}

void regMode(){
    REC bpi;
    char ch;
    int index=2;
    bpi.contactNumber[0]='0'; bpi.contactNumber[1]='9';
    bpi.accountNumber = rand() % 99999 + 10000; //10k para sure na 5 digits
    system("cls");
    printf("REGISTRATION MODULE\n");
    printf("Please fill out the following informations: \n\n");
    printf("\nAccount Number: %d",bpi.accountNumber);
    printf("\nAccount Name: ");scanf(" %[^\n]s",bpi.accountName);
    birthDayy(&bpi);system("cls");
    printf("REGISTRATION MODULE\n");
    printf("Please fill out the following informations: \n\n");
    printf("\nAccount Number: %d",bpi.accountNumber);
    printf("\nAccount Name: %s",bpi.accountName);
    printf("\nBirthdate (MM/DD/YYYY): %d / %d / %d",bpi.month,bpi.day,bpi.year);
    printf("\nContact Number: 09");
    a:
    while((ch=getch())!=13 && index<10){
        if (index<0){
            index=0;
        }
        if(ch==8){
            putch('\b'); putch(' ');
            putch('\b'); index--;
            continue;
        }
        if(isdigit(ch)){
         bpi.contactNumber[index++]=ch;
         putch('*');
        }
    }
    if (index==10){
        bpi.contactNumber[index++]=ch;
        putchar('*');
    }bpi.contactNumber[index]='\0';
    if(strlen(bpi.contactNumber)<11)
        goto a;
    printf("\nContact Number: %s",bpi.contactNumber);

    do{
        printf("\nInitial Deposit (Min. 5,000): ");scanf("%d", &bpi.balance);
        if(bpi.balance<5000)
            printf("Minimum deposit is 5000 petot, betch.\n");
    }while(bpi.balance<5000);
    pin(&bpi,1); printf("\nPIN Code: %s\n\n", bpi.pinCode);system("pause");
    addNewATMaccount(bpi);
}

void save(){
    FILE *fp;
    LIST *p; p=L;
    fp = fopen("D:\\Database.txt","w");
    if (fp==NULL){
        printf("Error 404. File not found.\n");
        system("pause");
    }
    else {
        while(p!=NULL){
        fprintf(fp,"%d %s\t%d %s\t%d %d %d %s\n",
                p->atm.accountNumber,p->atm.accountName,p->atm.balance,p->atm.pinCode,p->atm.month,p->atm.day,p->atm.year,p->atm.contactNumber);
        p=p->next;
        }fclose(fp);
    }
}
void saveFD(){
    FILE *fp;
    LIST *p; p=L;
    fp = fopen("F:\\ATM.txt","w");
    if (fp==NULL){
        printf("Error 404. File not found.\n");
        system("pause");
    }
    else {
        while(p!=NULL){
        fprintf(fp,"%d\t%s\t%d\t%s\n",p->atm.accountNumber,p->atm.accountName,p->atm.balance,p->atm.pinCode);
        p=p->next;
        }fclose(fp);
    }
}

int menu(){
    int UserNum;
    system("cls");
    printf("Choose Module: \n");
    printf("[1] ACCOUNT SETTINGS\n");
    printf("[2] TRANSACTION MODULE\n");
    printf("[3] EXIT\n");
    printf("\nEnter your choice 1-3: ");
    scanf("%d", &UserNum);
    return UserNum;
}
int AccountMenu(){
    system("cls");
    REC other;
    int UserNum;
    printf("Choose account option: \n");
    printf("[1] Update Account\n");
    printf("[2] Delete Account\n");
    printf("[3] Back\n");
    printf("\nEnter your choice 1-3: ");
    scanf("%d", &UserNum);
    return UserNum;
    //lalagay siguro rito ng function na checker sa pincode tapos isang tanungan nalang or bago mag Account Menu?
}
int transactionMenu(){
    int UserNum;
    while(1){
    system("cls");
    printf("Choose Transaction: \n");
    printf("[1] Balance Inquiry\n");
    printf("[2] Withdraw\n");
    printf("[3] Deposit\n");
    printf("[4] Fund Transfer\n");
    printf("[5] Other Transactions\n");
    printf("[6] Back\n");
    printf("\nEnter your choice 1-6: ");
    scanf("%d", &UserNum);
    return UserNum;
    }
}

void updateAccount(char n[31]){
    int marker=0;
    int x=0,y=0,z=0;
    LIST *p, *q;
    p=q=L;
    while(p!=NULL && strcmp (n, p->atm.accountName)!=0){
        q=p;
        p=p->next;
    }
    if(p==NULL){
            printf("Account not found.\n");system("pause");
    }else{
        while(x!=6){
            system("cls");
            printf("Updating Account: \n");
            printf("\nAccount Number: %d",p->atm.accountNumber);
            printf("\nAccount Name: %s",p->atm.accountName);
            printf("\nBirthday: %d / %d / %d",p->atm.month,p->atm.day,p->atm.year);
            printf("\nContact Number: %d",p->atm.contactNumber);
            printf("\nPIN Code: %d",p->atm.pinCode);
            printf("\nUPDATE: \n");
            printf("\n[1] Account Number");
            printf("\n[2] Account Name");
            printf("\n[3] Birthday");
            printf("\n[4] Contact Number");
            printf("\n[5] Change PIN Code");
            printf("\n[6] Back");
            printf("\n\nEnter a Number: ");scanf("%d", &x);
            switch(x){
                case 1: printf("\nInput new Account Number: ");scanf("%d", &p->atm.accountNumber);break;
                case 2: printf("\nInput new Account Name: ");scanf("%d",p->atm.accountName);break;
                case 3: while(marker!=1){
                            printf("\nInput new Birthday (MM/DD/YYYY)\n");
                            do{
                                printf("\nIf your birth month is January, enter 01");
                                printf("\nEnter your birth month: ");scanf("%d",&x);
                                system("cls");
                            }while(x>0 && x<=12); p->atm.month=x;
                            do{
                                printf("\nEnter your birth day: ");scanf("%d",&y);
                                system("cls");
                            }while(y>0 && y<=31); p->atm.day=y;
                            do{
                                printf("\nEnter your birth year: ");scanf("%d",&z);
                                system("cls");
                            }while(z>0 && z<=2023); p->atm.year=z; marker=1;
                        }break;
                case 4: printf("\nInput new Contact Number: ");scanf("%d", &p->atm.contactNumber);break;
                case 5: printf("\nEnter Pin: ");
                        scanf("%c",&p->atm.pinCode);
                        //checkPin(); kailangan i-compare to every lagay ng user
                        break;
                case 6: printf("\n%s's account is successfully updated.", p->atm.accountName);system("pause");break;
                default: printf("\nSelect 1-6 only\n");system("pause");
            }
        }
   }
}

void deleteAccount(char n[31]){
    int userChoice;
    LIST *p, *q;
    p=q=L;
    while(p!=NULL && strcmp (n, p->atm.accountName)!=0){
        q=p;
        p=p->next;
    }
    if (p==NULL){
        printf("Account not found.\n");system("pause");
    }else{
        printf("\n\nAre you sure you want to delete your account?\n");
        printf("[1]YES\n");
        printf("[2]NO\n");
        scanf("%d", &userChoice);
        if(userChoice==1){
            if (p==L){
            L=p->next;
            }else{
            q->next=p->next;
            }free(p);printf("%s's account is successfully deleted.\n",n);system("pause");
        }else{
            AccountMenu();
        }
    }
}

int main(){
    int withdraw,deposit;
    LIST *p;p=L;
    REC bdo;
    srand(time(NULL));
    makenull();
    switch(insertcard()){
        case 1: regMode();
                printf("\nREGISTRATION SUCCESSFULLY\n"); system("pause");
                break;
        case 2: retrieve();
                printf("\nbdo=%s,   atm=%s",bdo.pinCode,p->atm.pinCode);system("pause");
                pin(&bdo,2);
                printf("\n");
    }

    while(1){
        system ("cls");
        switch(menu()){
            case 1: system("cls"); printf("ACCOUNT SETTINGS\n\n");
                    while(1){
                        switch(AccountMenu()){
                            case 1: system("cls");
                                    printf("Input Account Name to be updated: ");scanf(" %[^\n]s",bdo.accountName);
                                    updateAccount(bdo.accountName);break;
                            case 2: system("cls");
                                    printf("Input Account Name to be deleted: ");scanf(" %[^\n]s",bdo.accountName);
                                    deleteAccount(bdo.accountName);break;
                            case 3: break;
                            default: printf("\nEnter 1-3 only.");system("pause");
                        }
                    }break;
            case 2: system("cls"); printf("TRANSACTION MODULE\n\n");
                    while(1){
                        switch(transactionMenu()){
                            case 1:printf("BALANCE INQUIRY\n");
                                   printf("Current Balance: %d", bdo.balance);system("pause");break;
                            case 2:printf("WITHDRAW MONEY\n");
                                   do{
                                   printf("Please input amount to withdraw: ");scanf("%d",&withdraw);
                                   if(withdraw>(bdo.balance))
                                        printf("\nInsufficient Balance.");
                                   }while(withdraw>(bdo.balance));
                                   bdo.balance-=withdraw;
                                   printf("\n\nWithdraw successful.");
                                   printf("\nYour new balance: %d", bdo.balance);system("pause");break;
                            case 3:printf("DEPOSIT MONEY\n");
                                   do{
                                   printf("Please input amount to deposit: ");scanf("%d",&deposit);
                                   if(deposit==0)
                                        printf("\nMinimum deposit amount is 1.");
                                   }while(deposit!=0);
                                   bdo.balance+=deposit;
                                   printf("\n\nDeposit successful.");
                                   printf("\nYour new balance: %d",bdo.balance);system("pause");break;
                            case 4:printf("FUND TRANSFER");system("pause");break;                   //di ko alam pano to gagawin
                            case 5:printf("PAY UTILITY BILLS");
                                   int Meralco,Maynilad;
                                   Meralco=rand()%1000 + 1;
                                   Maynilad=rand()%500 + 1;
                                   printf("Meralco Bill: %d\n", Meralco);
                                   printf("Maynilad Bill: %d\n", Maynilad);
                                   printf("\n\n");
                                   printf("Total Utility Bill: %d\n", Meralco+Maynilad);
                                   int userNum;
                                   while(1){
                                        printf("[1]Pay Utility Bills.\n");
                                        printf("[2]Back\n");
                                        scanf("%d", userNum);
                                        switch(userNum){
                                            case 1: if(bdo.balance>(Maynilad+Meralco)){
                                                        bdo.balance-(Maynilad+Meralco);
                                                        printf("\nPayment successful.");
                                                    }else
                                                        printf("\nInsufficient Balance.");
                                                    system("pause");break;
                                            case 2:transactionMenu();break;
                                            default:printf("Invalid input.\n");system("pause");
                                        }


                                   }
                                   break;
                            case 6:menu();break;
                            default:printf("Invalid input.\n");transactionMenu();
                        }
                    }break;
            case 3: save();saveFD();exit(0);break;
            default: printf("Invalid input. Try again."); system("pause\n");
        }
    }
}
