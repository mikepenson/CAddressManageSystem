---
title: C编程：通讯录管理系统
date: 2016-04-30 14:49:28
tags: [项目,C文件操作]
categories: C
---
> 这几天重温C，依然是谭浩强的《C语言程序设计》，把书中的代码都差不多打了一遍，收获颇丰。为了巩固，特地跟着极客学院的视频来了一次编程实战。

## 需求分析

- 通讯录管理系统可以实现对联系人信息的管理，包含添加、保存、修改和删除联系人的相关信息。
- 具有六项主要功能，包括：
 - 创建通讯录
 - 查询通讯录
 - 修改通讯录
 - 删除通讯录
 - 按姓名排序 
 - 显示通讯录

##系统设计

###设计目的
- 通讯录管理系统是一个小型的实用管理系统，它主要用于存储用户的联系 方式以及一些简单的信息。
- 该系统能够实现对客户、朋友、同事等个人信息的存储和快速查询功能，有效地减少查找的时间，提高查找效率。

###设计思路
- 定义结构体来保存通讯录中联系人的信息
- 使用主菜单实现对通讯录主要功能的管理，不同功能对应着不同的编号
- 使用结构体数组来存储多个联系人
- 采用文件来保存联系人的数据，提高操作效率
- 系统数据的输入包括输入功能编号以及联系人的各项信息。数据输出主要指显示联系人的信息

###模块划分
可以将整个系统划分为七个模块：

- **主模块**：该模块主要用来完成整个系统的流程。在主模块中调用其他函数，实现整个系统的功能。
- **新增联系人信息模块**：该模块根据提示信息分别输入联系人的姓名、职业、电话、电子邮件和地址，输入结束后自动将联系人信息保存到磁盘文件中
- **查询联系人信息模块**：该模块用于在通讯录中根据**姓名**查找指定的联系人，并根据系统提示决定是否显示该信息
- **修改联系人信息模块**：该模块用来修改通讯录中指定联系人的信息
- **删除联系人信息模块**:该模块将指定联系人的信息从通讯录中删除
- **排序模块**:该模块将通讯录中的所有联系人按照**姓名的字母**顺序进行排序
- **显示联系人信息模块**：该模块用来显示通讯录中所有的联系人信息

> 系统结构图如下：

![系统结构图](http://7xtdsw.com2.z0.glb.clouddn.com/C%E8%AF%AD%E8%A8%80%E7%BC%96%E7%A8%8B%E5%AE%9E%E8%B7%B5%EF%BC%9A%E9%80%9A%E8%AE%AF%E5%BD%95%E7%AE%A1%E7%90%86%E7%B3%BB%E7%BB%9F/1.png)

###主功能菜单设计
- 运行通讯录管理系统后，首先进入的是主功能菜单。在主功能菜单中列出了系统的所有功能以及各个功能相应的编号。用户可以根据需要自己选择输入相应的功能编号，就可以进入对应的子功能中
- 主菜单图
![主菜单图](http://7xtdsw.com2.z0.glb.clouddn.com/C%E8%AF%AD%E8%A8%80%E7%BC%96%E7%A8%8B%E5%AE%9E%E8%B7%B5%EF%BC%9A%E9%80%9A%E8%AE%AF%E5%BD%95%E7%AE%A1%E7%90%86%E7%B3%BB%E7%BB%9F/2.png)

###数据结构设计
- 结构体

```C

 	struct addritem			/*定义通讯录条目结构体*/
	{ 
	  char name[30];		 	/*联系人姓名*/
	  char occu[30];     	 		/*联系人职业*/
	  char tel[15];  				/*联系人电话*/
	  char email[30];       		/*联系人电子邮件*/
	  char address[30];    		/*联系人地址*/
    };
```

- 结构体数组

```C

	struct addritem addrinfo[100];
```

###格式化输出
- 使用宏定义对输出格式进行规定

```C

	#define FORMAT "%-10s%-10s%-15s%-25s%-30s\n"
	#define DATA addrinfo[i].name, addrinfo[i].occu, addrinfo[i].tel,
	addrinfo[i].email, addrinfo[i].address

```

##编码实战

###主函数设计

- 调用menu函数显示主功能选择菜单，在**switch**多分支选择结构中调用各个子函数以实现新增、查询、修改、删除和显示等功能。
- 实现代码：

> 主函数代码

```C

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
```

> 菜单函数

```C

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
```

###新增联系人信息
- 该模块根据输入信息保存到磁盘文件中
- 文件处理函数
 1. fopen
 2. feof
 3. fread
 4. fclose
 5. fw
- 字符串处理函数
- 实现过程：
 - 首先显示文件内容(读文件)
   1. 以附加方式打开文件，不存在则新建文件
   2. 将磁盘文件读入内存中
   3. 调用display函数显示文件，不存在文件输出No contact record!
 - 往文件中新添加记录（写文件）
  - 以只写方式打开文件
  - 往内存写name，对比已存在记录，若是新的则输入其他信息，否则返回

```C

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
```
###查询联系人信息模块
- 该模块用于在通讯录中根据姓名查找指定的联系人，并根据系统提示决定是否显示该信息
- 逻辑很简单，输入name，往内存（addinfo）中查找，找到打印输出

```C

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
```
###修改联系人信息
- 该模块用来修改通讯录中指定联系人的信息
 - 首先读取磁盘文件，如果没有记录直接返回
 - 其次display记录
 - 接着查询输入的name，查询成功则继续输入其他信息写入文件中
 
```C

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
```

###删除联系人信息

> 流程跟update差不多，只不过删除的时候注意数组长度-1

```C

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
```

###排序模块
- 该模块将通讯录中的所有联系人按照姓名的字母顺序进行排序
- 思想：先读，排序，后写入（其实文件操作的流程都是这样子的）

> 只贴选择排序和写入的代码，在最后会有github的链接

```C

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
```
###显示联系人信息模块
- 该模块用来显示通讯录中所有的联系人信息
- 这个模块在这个程序中唯一体现代码复用的特点。。

```C

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
```

##总结
1. 这个程序中代码冗余的比较多，读取文件的操作重复较多，不够精炼
2. 新学会C的一些文件操作。相比面向对象语言，C的异常是通过if..else..语句来实现，动作模块和异常模块混合在一块，对代码阅读多多少少有点影响，毕竟判断文件有没有打开、是否读取成功、是否写入成功这些动作不是我们的主要目的，还不如像Java一样都放在一个catch块中呢。
3. C中的结构体有点面向对象的意思，都是一些封装实体的特性，需要的时候再初始化（实例化），只不过想没有面向对象那样封装一些动作。
4. getchar()和getch():前者控制台输入一个字符回车才生效，后者输入一个键值就程序就继续执行，所以getch用在这里暂停程序。
5. 该系统的数据持久化在data.txt文件中，读取时先一条一条读入内存，即结构体数组中，每条记录长度为
> \#define LEN sizeof(struct addritem)