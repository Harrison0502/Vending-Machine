#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//////變數
int ncorrect=1;//判斷密碼是否符合之變數
char passwd[30];//密碼
int notend=1;//判斷是否結束程式變數
char product[20][50];//商品名稱陣列
int pricenum[50][2];//商品價格、數量陣列
int nameindex=0;//商品數量
int income=0;//收入

//////模式
void password();//更改密碼模式
void sellermode();//賣家模式
void buyermode();//買家模式
void new();//新增商品函式
void help();//顯示指令函式
void list();//排序函式 
void add();//增加庫存函式
void buy();//買家購買函式
void delete();
void buyerhelp();//列出買家指令
void sellerhelp();//列出賣家指令

//////功能函式
char *rtrim(char *str);
char *ltrim(char *str);
void trim(char *str);//去除首尾空格
void swapstr(char **str1_ptr,char **str2_ptr);//轉換str函式
void swapint(int* a ,int *b);//轉換int函式

//各式排序方法
void incname();
void decname();
void incprice();
void decprice();
void incnum();
void decnum();


/*****主程式*******/
int main(){
    password();
    sellermode();
    printf("END!\n");
    }


void password(){//換密碼函式
    do{
        int big=0,small=0,digit=0,mark=0,space=0,wrong=0;
        printf("Please set your password.\n");
        //printf("Password length is 6∼20 characters.\n");
        //printf("Acceptable characters for password are A-Z, a-z, 0-9, ∼, @, #, _, ^, *, %%, /, ., +, :, =\n");
        //printf("Password must contain A-Z,a-z,0~9,symbols.\n");
        scanf("%s",passwd);
        if(strlen(passwd)<6||strlen(passwd)>20){
            printf("Wrong password length\n");
            continue;
        }
        for(int i=0;i<=strlen(passwd);i++){//檢查每個字元
            if(isupper(passwd[i]))
                big++;
            else if(islower(passwd[i]))
                small++;
            else if(isdigit(passwd[i]))
                digit++;
            else if((passwd[i])=='@'||(passwd[i])=='~'||(passwd[i])=='#'||(passwd[i])=='_'||(passwd[i])=='^'||(passwd[i])=='*'||(passwd[i])=='%'||
            (passwd[i])=='/'||(passwd[i])=='.'||(passwd[i])=='+'||(passwd[i])==':'||(passwd[i])=='=')
                mark++;
            else if(iscntrl(passwd[i]))
                space++;
            else
                wrong++;
        }
        if(big>0&&small>0&&digit>0&&mark>0&&space==1&&wrong==0){//檢查是否包含大小寫、數字、符號、只有一個控制字元(\0)，若正確則設定完成。
                ncorrect=0;
                printf("Password setting up!\n");
            }
            else
                printf("Wrong type. Try again.\n");
     }while(ncorrect);
}



void sellermode(){
    char input[20];//判斷使用者輸入甚麼指令
    do{
        printf("Seller mode >\n");
        scanf("%s",input);
        if((strcmp(input,"new"))==0||strcmp(input,"\"new")==0||strcmp(input,"\"new\"")==0){
            new();
            memset(input,0,sizeof(char)*20);
        }
        else if((strcmp(input,"help"))==0||strcmp(input,"\"help")==0||strcmp(input,"\"help\"")==0||strcmp(input,"?")==0){
            sellerhelp();
            memset(input,0,sizeof(char)*20);
        }
        else if((strcmp(input,"income"))==0||strcmp(input,"\"income")==0||strcmp(input,"\"income\"")==0){
            printf("%d",income);
            memset(input,0,sizeof(char)*20);
        }
        else if((strcmp(input,"list"))==0||strcmp(input,"\"list")==0||strcmp(input,"\"list\"")==0){
            list();
            memset(input,0,sizeof(char)*20);
        }
        else if((strcmp(input,"delete"))==0||strcmp(input,"\"delete")==0||strcmp(input,"\"delete\"")==0){
            delete();
            memset(input,0,sizeof(char)*20);
        }
        else if((strcmp(input,"add"))==0||strcmp(input,"\"add")==0||strcmp(input,"\"add\"")==0){
            add();
            memset(input,0,sizeof(char)*20);
        }
        else if((strcmp(input,"buyermode"))==0||strcmp(input,"\"buyermode")==0||strcmp(input,"\"buyermode\"")==0){
            buyermode();
            memset(input,0,sizeof(char)*20);
        }
        else if((strcmp(input,"passwd"))==0||strcmp(input,"\"passwd")==0||strcmp(input,"\"passwd\"")==0){
            char tmpinput[30];//用於存放輸入密碼
            printf("Please input password:\n");
            scanf("%s",tmpinput);
            if(strcmp(tmpinput,passwd)==0)
                password();
            else{
                printf("Incorrect password!\n");
                continue;
                }
            memset(input,0,sizeof(char)*20);
        } 
        else if((strcmp(input,"exit"))==0||strcmp(input,"\"exit")==0||strcmp(input,"\"exit\"")==0){
            notend=0;
            memset(input,0,sizeof(char)*20);
        }
        else{
            printf("Command error!\n");
            memset(input,0,sizeof(char)*20);
        }
    }while(notend);     
}

void buyermode(){
    char input2[20];//判斷使用者輸入甚麼指令
    do{
        printf("Buyer mode >\n");
        scanf("%s",input2);
        if((strcmp(input2,"list"))==0||strcmp(input2,"\"list")==0||strcmp(input2,"\"list\"")==0){
            list();
            memset(input2,0,sizeof(char)*20);
        }
        else if((strcmp(input2,"buy"))==0||strcmp(input2,"\"buy")==0||strcmp(input2,"\"buy\"")==0){
            buy();
            memset(input2,0,sizeof(char)*20);
        }
        else if((strcmp(input2,"help"))==0||strcmp(input2,"\"help")==0||strcmp(input2,"\"help\"")==0||strcmp(input2,"?")==0){
            buyerhelp();
            memset(input2,0,sizeof(char)*20);
        }
        else if((strcmp(input2,"sellermode"))==0||strcmp(input2,"\"sellermode")==0||strcmp(input2,"\"sellermode\"")==0){
            char tmpinput[30];//用於存放輸入密碼
            printf("Please input password:\n");
            scanf("%s",tmpinput);
            if(strcmp(tmpinput,passwd)==0)
                sellermode();
            else{
                printf("Incorrect password!\n");
                continue;
                }
        }
        else{
            printf("Command error!\n");
            memset(input2,0,sizeof(char)*20);
        }
    }while(notend);     
    
}



void sellerhelp(){
    printf("       COMMAND              |           DESCRIPTION\n");
    printf("?                                   List all commands of this mode with a brief description.List all commands of this mode with a brief description.\n");
    printf("add <product> <num>                 Add item <product> by quantity <num>.\n");
    printf("buyer mode                          Enter buyer mode.\n");
    printf("delete <product>                    Remove the product item <product>.\n");
    printf("exit                                End the program.\n");
    printf("help                                List all commands of this mode with a brief description.List all commands of this mode with a brief description.\n");
    printf("income                              Print the current total income.\n");
    printf("list [inc|dec] [name|price|quantity]List the product list, including product name, price and inventory quantity.\n");
    printf("new <product> <price> [<num>]       Add product item.\n");
    printf("passwd                              Change Password.\n");
}

void buyerhelp(){
    printf("       COMMAND              |           DESCRIPTION\n");
    printf("?                                   List all commands of this mode with a brief description.List all commands of this mode with a brief description.\n");
    printf("buy <product> <num>                 Buying <product> by quantity <num>.\n");
    printf("help                                List all commands of this mode with a brief description.List all commands of this mode with a brief description.\n");
    printf("list [inc|dec] [name|price|quantity]List the product list, including product name, price and inventory quantity.\n");
    printf("seller mode                          Enter seller mode.(Will ask for the password first).\n");
}



void new(){
    char c;
    c=getchar();
    while(c==' ')//吃space直到第一個字符
        c=getchar();
    if(c=='\"'){//若空格後第一個字符為"
        scanf("%[^\"]",product[nameindex]);//把"前的字串存入product
        trim(product[nameindex]);//去除首尾空白
        getchar();//吃掉"
        scanf(" %d %d",&pricenum[nameindex][0],&pricenum[nameindex][1]);
        for(int i=0;i<nameindex;i++){//判斷此商品是否已經存在
            if(strcmp(product[nameindex],product[i])==0){//若商品已存在則清空，並跳出函式。
                printf("%s is already in product! Please use \"add\" command.\n",product[nameindex]);
                memset(product[nameindex],0,sizeof(char)*100);//清空
                return ;
            }
        }
        if((pricenum[nameindex][0]<=0&&pricenum[nameindex][1]<=0)||pricenum[nameindex][1]<0||pricenum[nameindex][1]<0){//當價格或數量<=0，判斷為輸入錯誤
            printf("Wrong type!%d %d\n",pricenum[nameindex][0],pricenum[nameindex][1]);
            memset(product[nameindex],0,sizeof(char)*100);//清空
            return ;
        }
        else{
            printf("Productname:%s,Price:%d,Num:%d\n",product[nameindex],pricenum[nameindex][0],pricenum[nameindex][1]);
            printf("Product set in!\n");
            nameindex++;
            return ;
        }
    }
    else{
        product[nameindex][0]=c;//如果c吃掉的不是",把c存入字串第0格
        scanf("%s",&product[nameindex][1]);//把剩下的從字串第1格存入
        trim(product[nameindex]);//去除首尾空白
        scanf(" %d %d",&pricenum[nameindex][0],&pricenum[nameindex][1]);
        for(int i=0;i<nameindex;i++){//判斷此商品是否存在
            if(strcmp(product[nameindex],product[i])==0){
                printf("%s is already in product! Please use \"add\" command.\n",product[nameindex]);
                memset(product[nameindex],0,sizeof(char)*100);
                return ;
            }
        }
        if(pricenum[nameindex][0]<=0&&pricenum[nameindex][1]<=0){//當價格與數量<=0，判斷為輸入錯誤
            printf("Wrong type!%d %d\n",pricenum[nameindex][0],pricenum[nameindex][1]);
            memset(product[nameindex],0,sizeof(char)*100);
            return ;
        }
        else{
            printf("Productname:%s,Price:%d,Num:%d\n",product[nameindex],pricenum[nameindex][0],pricenum[nameindex][1]);
            printf("Product set in!\n");
            nameindex++;
            return ;
        }

    }
    
}

void list(){//List函式
        char incdec[10];
        char NPQ[10];
        printf("Name  ||  Price  ||  Quantity\n");
        incprice();
        for(int i=0;i<nameindex;i++){
        printf("%s  ||  %d  ||  %d\n",product[i],pricenum[i][0],pricenum[i][1]);
       }
       return ;
}

void add(){//增加商品 函式
    char c;
    c=getchar();
    char addname[50];//存放欲添加的商品名
    int  addnum=0;//存放欲添加的數量
    int  addindex;//欲存放的商品所在index
    while(c==' ')//吃space直到第一個字符
        c=getchar();
    if(c=='\"'){//若有讀到"
        scanf("%[^\"]",addname);//把"前的字串存入addname
        trim(addname);//去除首尾空白
        getchar();//吃掉"
        scanf(" %d",&addnum);
        if(addnum<=0){
            printf("The number cannot be less than or equal to 0.\n");
            return;
        }
        for(int i=0;i<nameindex;i++){
            if(strcmp(addname,product[i])==0){
            pricenum[i][1]+=addnum;
            printf("\"%s\" +%d!\n",addname,addnum);
            break;
            }
            if(i==nameindex-1&&strcmp(addname,product[i])!=0){
                printf("\"%s\" does not exist\n",addname);
            }

        }
    }
    else{
        addname[0]=c;//如果c吃掉的不是",把c存入字串第0格
        scanf("%s",&addname[1]);//把剩下的從字串第1格存入
        trim(addname);//去除首尾空白
        scanf(" %d",&addnum);
        if(addnum<=0){
            printf("The number cannot be less than or equal to 0.\n");
            return;
        }
        for(int i=0;i<nameindex;i++){
            if(strcmp(addname,product[i])==0){
                pricenum[i][1]+=addnum;
                printf("\"%s\" +%d!\n",addname,addnum);
                break;
            }
            else if(i==nameindex-1&&strcmp(addname,product[i])!=0){
                printf("\"%s\" does not exist.\n",addname);
            }

    }
    }
}

void delete(){//刪除商品 函式
    char c;
    c=getchar();
    char deletename[50];//存放欲刪除的商品名
    while(c==' ')//吃space直到第一個字符
        c=getchar();
    if(c=='\"'){//若有讀到"
        scanf("%[^\"]",deletename);//把"前的字串存入addname
        trim(deletename);//去除首尾空白
        getchar();//吃掉"
        for(int i=0;i<nameindex;i++){
            if(i==nameindex-1&&strcmp(deletename,product[i])!=0){//找不到商品 則跳出
                printf("\"%s\" does not exist.\n",deletename);
                return;
            }
            else if(strcmp(deletename,product[i])==0){
                for(int j=i;j<nameindex;j++){//從index[i]以後的商品 往前一個index(欲刪除的商品會跑到最後一個)
                    swapstr(product[j],product[j+1]);
                    swapint(&pricenum[j][0],&pricenum[j+1][0]);
                    swapint(&pricenum[j][1],&pricenum[j+1][1]);
                }
                *product[nameindex]=0;
                pricenum[nameindex][0]=0;
                pricenum[nameindex][0]=0;
                nameindex--;
                printf("\"%s\" has been deleted.\n",deletename);
                return;
            }

        }
    }
    else{
        deletename[0]=c;//如果c吃掉的不是",把c存入字串第0格
        scanf("%s",&deletename[1]);//把剩下的從字串第1格存入
        trim(deletename);//去除首尾空白
        for(int i=0;i<nameindex;i++){
            if(i==nameindex-1&&strcmp(deletename,product[i])!=0){//找不到商品 則跳出
                printf("\"%s\" does not exist.\n",deletename);
                return;
            }
            else if(strcmp(deletename,product[i])==0){
                for(int j=i;j<nameindex;j++){//從index[i]以後的商品 往前一個index
                    swapstr(product[j],product[j+1]);
                    swapint(&pricenum[j][0],&pricenum[j+1][0]);
                    swapint(&pricenum[j][1],&pricenum[j+1][1]);
                }
                *product[nameindex]=0;
                pricenum[nameindex][0]=0;
                pricenum[nameindex][0]=0;
                nameindex--;
                printf("\"%s\" has been deleted.\n",deletename);
                return;
            }
    
        }
    }
}

void buy(){//購買商品 函式
    char c;
    c=getchar();
    char buyname[50];//存放欲添加的商品名
    int  buynum=0;//存放欲添加的數量
    while(c==' ')//吃space直到第一個字符
        c=getchar();
    if(c=='\"'){//若有讀到"
        scanf("%[^\"]",buyname);//把"前的字串存入addname
        trim(buyname);//去除首尾空白
        getchar();//吃掉"
        scanf(" %d",&buynum);
        if(buynum<=0){
            printf("The number cannot be less than or equal to 0.\n");
            return;
        }
        for(int i=0;i<nameindex;i++){
            if(strcmp(buyname,product[i])==0){
                if(pricenum[i][1]<buynum){//若庫存數小於購買數
                    printf("Out of stuck!");
                    return;
                    }
                else{
                    pricenum[i][1]-=buynum;
                    printf("Sold %d \"%s\"(s).\n",buynum,buyname);
                    income+=(pricenum[i][0]*buynum);
                    break;
                }
            }
            if(i==nameindex-1&&strcmp(buyname,product[i])!=0){
                printf("\"%s\" does not exist.\n",buyname);
            }

        }
    }
    else{
        buyname[0]=c;//如果c吃掉的不是",把c存入字串第0格
        scanf("%s",&buyname[1]);//把剩下的從字串第1格存入
        trim(buyname);//去除首尾空白
        scanf(" %d",&buynum);
        if(buynum<=0){
            printf("The number cannot be less than or equal to 0.\n");
            return;
        }
        for(int i=0;i<nameindex;i++){
            if(strcmp(buyname,product[i])==0){
                if(pricenum[i][1]<buynum){//若庫存數小於購買數則顯示庫存不足
                    printf("Out of stuck!\n");
                    return;
                 }
                else{
                    pricenum[i][1]-=buynum;//商品數量-購買數量=剩餘數量
                    printf("Sold %d \"%s\"(s).\n",buynum,buyname);
                    income+=(pricenum[i][0]*buynum);//收入為商品價格*購買數量
                    break;
                }
            }
            if(i==nameindex-1&&strcmp(buyname,product[i])!=0){//找不到商品 則跳出
                printf("\"%s\" does not exist.\n",buyname);
                return;
            }
        }
    }
}



///////以下為功能函式

void swapstr(char **str1_ptr,char **str2_ptr)//轉換字串函式
{
char *temp = *str1_ptr;
*str1_ptr = *str2_ptr;
*str2_ptr = temp;
}

void swapint(int* a ,int *b)//轉換int函式
{
int temp =*a;
*a = *b;
*b = temp;
}

char *rtrim(char *str) //去除尾部空格
{ 
    if (str == NULL || *str == '\0') 
    { 
        return str; 
    } 
    int len = strlen(str); 
    char *p = str + len - 1; 
    while (p >= str && isspace(*p)) 
    { 
        *p = '\0'; --p; 
    } 
    return str; 
} 

//去除首部空格 
char *ltrim(char *str){

if (str == NULL || *str == '\0')
	return str;
int len = 0;
char *p = str;
while (*p != '\0' && isspace(*p))
	++p; ++len;
memmove(str, p, strlen(str) - len + 1);
return str;
}

//去除首尾空格 
void trim(char *str)
{ 
    str = rtrim(str); 
    str = ltrim(str); 
    return ; 
}



void incname(){//依名稱小到大排序
     for(int i=0;i<nameindex-1;i++){
            for(int j=0;j<nameindex-i-1;j++){
                if (toupper(product[j][0])>toupper(product[j+1][0])){
                    swapstr(product[j],product[j+1]);
                    swapint(&pricenum[j][0],&pricenum[j+1][0]);
                    swapint(&pricenum[j][1],&pricenum[j+1][1]);
                }
            }
        }
}

void decname(){//依名稱大到小排序
     for(int i=0;i<nameindex;i++){
            for(int j=0;j<nameindex-i-1;j++){
                if (toupper(product[j][0])<toupper(product[j+1][0])){
                    swapstr(product[j],product[j+1]);
                    swapint(&pricenum[j][0],&pricenum[j+1][0]);
                    swapint(&pricenum[j][1],&pricenum[j+1][1]);
                }
            }
        }
    
}

void incprice(){//依價格低到高排序
    for(int i=0;i<nameindex-1;i++){
        for(int j=0;j<nameindex-i-1;j++){
            if (pricenum[j][0]>pricenum[j+1][0]){
                    swapstr(product[j],product[j+1]);
                    swapint(&pricenum[j][0],&pricenum[j+1][0]);
                    swapint(&pricenum[j][1],&pricenum[j+1][1]);
                }
            else if(pricenum[j][0]==pricenum[j+1][0]){//若價格一樣，則依照字典排序(0123AaBbCc)
                if (toupper(product[j][0])>toupper(product[j+1][0])){
                    swapstr(product[j],product[j+1]);
                    swapint(&pricenum[j][0],&pricenum[j+1][0]);
                    swapint(&pricenum[j][1],&pricenum[j+1][1]);
                }
                }
        }
    }
}

void deccprice(){//依價格高到低排序
    for(int i=0;i<nameindex-1;i++){
        for(int j=0;j<nameindex-i-1;j++){
            if (pricenum[j][0]<pricenum[j+1][0]){
                    swapstr(product[j],product[j+1]);
                    swapint(&pricenum[j][0],&pricenum[j+1][0]);
                    swapint(&pricenum[j][1],&pricenum[j+1][1]);
                }
            else if(pricenum[j][0]==pricenum[j+1][0]){//若價格一樣，則依照字典排序(0123AaBbCc)
                if (toupper(product[j][0])>toupper(product[j+1][0])){
                    swapstr(product[j],product[j+1]);
                    swapint(&pricenum[j][0],&pricenum[j+1][0]);
                    swapint(&pricenum[j][1],&pricenum[j+1][1]);
                }
                }
        }
    }
}

void incnum(){//依庫存數低到高排序
    for(int i=0;i<nameindex-1;i++){
        for(int j=0;j<nameindex-i-1;j++){
            if (pricenum[j][1]>pricenum[j+1][1]){
                    swapstr(product[j],product[j+1]);
                    swapint(&pricenum[j][0],&pricenum[j+1][0]);
                    swapint(&pricenum[j][1],&pricenum[j+1][1]);
                }
             else if(pricenum[j][0]==pricenum[j+1][0]){//若價格一樣，則依照字典排序(0123AaBbCc)
                if (toupper(product[j][0])>toupper(product[j+1][0])){
                    swapstr(product[j],product[j+1]);
                    swapint(&pricenum[j][0],&pricenum[j+1][0]);
                    swapint(&pricenum[j][1],&pricenum[j+1][1]);
                }
                }
        }
    }
}

void decnum(){//依庫存數高到低排序
    for(int i=0;i<nameindex-1;i++){
        for(int j=0;j<nameindex-i-1;j++){
            if (pricenum[j][1]<pricenum[j+1][1]){
                    swapstr(product[j],product[j+1]);
                    swapint(&pricenum[j][0],&pricenum[j+1][0]);
                    swapint(&pricenum[j][1],&pricenum[j+1][1]);
                }
             else if(pricenum[j][0]==pricenum[j+1][0]){//若價格一樣，則依照字典排序(0123AaBbCc)
                if (toupper(product[j][0])>toupper(product[j+1][0])){
                    swapstr(product[j],product[j+1]);
                    swapint(&pricenum[j][0],&pricenum[j+1][0]);
                    swapint(&pricenum[j][1],&pricenum[j+1][1]);
                }
                }
        }
    }
}