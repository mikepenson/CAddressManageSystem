#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <dos.h>
#include <string.h>
#define LEN sizeof(struct addritem) //addritem所占用内存字节数
#define FORMAT "%-10s%-15s%-14s%-20s%-20s\n"    //规定了输出的格式
#define DATA addrinfo[i].name,addrinfo[i].occu,addrinfo[i].tel,addrinfo[i].email,addrinfo[i].address
struct addritem{
    char name[10];//姓名
    char occu[10];//按职业
    char tel[15];//电话
    char email[25];//电邮
    char address[30];//地址
};

struct addritem addrinfo[100];
void input();
void search();
void update();
void del();
void display();
void sort();
void menu();//生成系统的主功能菜单

void menu(){
    system("cls");
    printf("\n\n\n\n\n");
    printf("\t\t|---------------------CONCACT------------------------\n");
    printf("\t\t| 0.exit                                            |\n");
    printf("\t\t| 1.input record                                    |\n");
    printf("\t\t| 2.search record                                   |\n");
    printf("\t\t| 3.update record                                   |\n");
    printf("\t\t| 4.delete record                                   |\n");
    printf("\t\t| 5.sort                                            |\n");
    printf("\t\t| 6.display                                         |\n");
    printf("\t\t|---------------------------------------------------|\n\n");
    printf("\t\t\tchoose(0-6):");
}

int main(){
    int n;
    menu();//生成系统主菜单
    scanf("%d",&n);
    while(n){//n值为0退出循环
        switch(n){
            case 1:input();
                break;
            case 2:search();
                break;
            case 3:update();
                break;
            case 4:del();
                break;
            case 5:sort();
                break;
            case 6:display();
                break;
            default:
                break;
        }
        getch();//直接获取键值不等回车，常用于暂停程序运行，按任意键继续
        menu();//再次显示功能菜单等待用户输入
        scanf("%d",&n);
    }
    return 0;
}

void input(){
    int i,count=0;
    char ch[2];//记录用户的输入
    FILE *fp;//指向文件的变量
    //fopen(文件路径以及文件名，流的形态：以附加的方式打开文件，不存在新建，存在就写入文件尾部)
    if((fp=fopen("data.txt","a+"))==NULL){
        printf("can not open\n");
        return;
    }
    //feof函数：检测文件流上的结束符，文本文件结束标志是EOF
    while(!feof(fp)){
        //fread函数将文件中存放的记录一条一条读取到结构体数组addrinfo
        //参数1：指定接收数据的内存地址
        //参数2：指定了每一个数据项的字节数
        //参数3：指定每次只读取一条记录
        //参数4：代表输入流
        if(fread(&addrinfo[count],LEN,1,fp)==1){
            count++;
        }
    }
    fclose(fp);
    if(count==0){
        printf("No contact record!\n");
    }else{
        system("cls");//清屏
        display();
    }

    //以只写的方式打开txt文件
    if((fp=fopen("data.txt","wb"))==NULL){
        printf("can not open address list!\n");
        return;
    }
    for(i=0;i<count;i++){
        fwrite(&addrinfo[i],LEN,1,fp);
    }
    printf("please input(y/n):");
    scanf("%s",ch);
    while(strcmp(ch,"Y")==0||strcmp(ch,"y")==0){
        printf("name:");
        scanf("%s",&addrinfo[count].name);
        //比较用户输入的姓名是否已经存在
        for(i=0;i<count;i++)
            if(strcmp(addrinfo[i].name,addrinfo[count].name)==0){
                printf("The name  already exits,press any key to continue.");
                getch();
                fclose(fp);
                return;
            }
        //确定是新输入的名字，接着补充其他信息
        printf("occupation:");
        scanf("%s",addrinfo[count].occu);
        printf("telephone:");
        scanf("%s",addrinfo[count].tel);
        printf("email:");
        scanf("%s",addrinfo[count].email);
        printf("address:");
        scanf("%s",addrinfo[count].address);
        //写入失败
        if(fwrite(&addrinfo[count],LEN,1,fp)!=1){
            printf("can not save the record!");
            getch();
        }else{
            printf("%s saved!\n",addrinfo[count].name);
            count++;
        }
        printf("continue?(y/n):");
        scanf("%s",ch);
    }
    fclose(fp);
    printf("OK!\n");
}

void search(){
    FILE *fp;
    int i,count=0;
    char ch[2],name[15];
    //指定二进制形式打开文件
    if((fp=fopen("data.txt","rb"))==NULL){
        printf("can not open\n");
        return;;
    }
    //判断是否到达文件的尾部
    while(!feof(fp)){
        if(fread(&addrinfo[count],LEN,1,fp)==1)
            count++;//当所有记录读取完成，count就是读取的总数
    }
    fclose(fp);
    if(count==0){
        printf("no record!\n");
        return;
    }
    printf("please input the name:");
    scanf("%s",name);
    for(i=0;i<count;i++)
        if(strcmp(name,addrinfo[i].name)==0){
            printf("find the contact,display?(y/n)");
            scanf("%s",ch);
            if(strcmp(ch,"Y")==0||strcmp(ch,"y")==0){
                printf("name     occupation     telephone     email               address\t\n");
                printf(FORMAT,DATA);
            }
            break;
        }
    if(i==count)
        printf("can not find the contact!\n");
}

void update(){
    FILE *fp;
    int i,j,count=0;
    char name[15];
    //1.打开txt文件，将联系人信息都存在内存中
    if((fp=fopen("data.txt","r+"))==NULL){//以r+方式打开文件
        printf("can not open.\n");
    }
    while(!feof(fp))
        if(fread(&addrinfo[count],LEN,1,fp))
            count++;
    if(count==0){
        printf("no record!\n");
        fclose(fp);
        return;
    }
    display();
    printf("please input the name of the contact which you want to update!\n");
    printf("update name:");
    scanf("%s",&name);
    for(i=0;i<count;i++){
        if(strcmp(name,addrinfo[i].name)==0){//find the contact
            printf("find the contact!you can update!\n");
            printf("name:");
            scanf("%s",addrinfo[i].name);
            printf("occupation:");
            scanf("%s",addrinfo[i].occu);
            printf("telephone:");
            scanf("%s",addrinfo[i].tel);
            printf("email:");
            scanf("%s",addrinfo[i].email);
            printf("address:");
            scanf("%s",addrinfo[i].address);
            printf("update successful!");
            if((fp=fopen("data.txt","wb"))==NULL){
                printf("can not open\n");
                return;
            }
            for(j=0;j<count;j++){
                if(fwrite(&addrinfo[j],LEN,1,fp)!=1){
                    printf("can not save!\n");
                    getch();
                }
            }
            fclose(fp);
            return;
        }
    }
    //没有找到联系人信息
    printf("not find the contact!\n");
}

//根据姓名删除指定的联系人
void del(){
    FILE *fp;
    int i,j,count=0;
    char ch[2];//输入
    char name[15];//输入

    //1.判断能否打开
    if((fp=fopen("data.txt","r+"))==NULL){
        printf("can not open\n");//提示用户没有正常打开
        return;
    }
    //2.磁盘文件读取到内存中
    while(!feof(fp))
        //将磁盘的文件读到内存结构体数组addinfo中
        if(fread(&addrinfo[count],LEN,1,fp)==1)
            count++;//循环结束后count的值就是记录数
    fclose(fp);//读取结束关闭流
    if(count==0){//通讯录为空
        printf("no record!\n");
        return;
    }
    //3.显示通讯录中当前所有的联系人
    display();
    //4.开始删除，输入要删除联系人的姓名
    printf("please input the name:");
    scanf("%s",name);
    //5.在通讯录中找到要删除联系人的同名联系人，执行删除操作
    for(i=0;i<count;i++){
        if(strcmp(name,addrinfo[i].name)==0){
            printf("find the contact,del?(y/n)");
            scanf("%s",ch);
            if(strcmp(ch,"Y")==0||strcmp(ch,"y")==0)
                //数组元素i后面的元素往前面移动
                for(j=i;j<count;j++)
                    addrinfo[j]=addrinfo[j+1];
            count--;//删除完成，总数减1
            //6.在磁盘中删除
            //6-1.只写方式打开文件
            if((fp=fopen("data.txt","wb"))==NULL){
                printf("can not open\n");
                return;
            }
            //6-2.addrinfo记录逐条写入文件
            for(j=0;j<count;j++)
                if(fwrite(&addrinfo[j],LEN,1,fp)!=1){
                    printf("can not save!\n");
                    getch();
                }
            fclose(fp);
            printf("del successful!\n");
            return;
        }
    }
    printf("not find the contact!\n");
}

void sort(){
    FILE *fp;
    struct addritem temp;//缓冲区
    int i=0,j=0,count=0,k;

    if((fp=fopen("data.txt","r+"))==NULL){
        printf("can not open!\n");
        return;
    }

    while(!feof(fp))
        if(fread(&addrinfo[count],LEN,1,fp)==1)
            count++;
    if(count==0){
        printf("no record!\n");
        return;
    }

    //选择法排序
    for(i=0;i<count-1;i++){
        k=i;//最小值下标
        for(j=i+1;j<count;j++)
            if(strcmp(addrinfo[k].name,addrinfo[j].name)>0)
                k=j;
        if(k!=i){
            temp=addrinfo[k];
            addrinfo[k]=addrinfo[i];
            addrinfo[i]=temp;
        }
    }

    //写入磁盘文件
    if((fp=fopen("data.txt","wb"))==NULL){
        printf("can not open\n");
        return;
    }
    for(i=0;i<count;i++)
        if(fwrite(&addrinfo[i],LEN,1,fp)!=1){//写入失败！
            printf("can not save!\n");
            getch();
        }
    fclose(fp);
    printf("save successfully!\n");
}

void display(){
    FILE *fp;
    int i,count=0;
    fp=fopen("data.txt","rb");
    while(!feof(fp)){
        if(fread(&addrinfo[count],LEN,1,fp)==1)
            count++;
    }
    fclose(fp);
    printf("name     occupation     telephone     email               address\t\n");
    for(i=0;i<count;i++)
        printf(FORMAT,DATA);
}


















