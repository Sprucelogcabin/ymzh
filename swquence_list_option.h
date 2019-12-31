//
//  swquence_list_option.h
//  页面置换算法(新)
//
//  Created by 李若白 on 2019/12/6.
//  Copyright © 2019 李若白. All rights reserved.
//
//创建相应的类型，表与操作方法

//设计有：进程表->进程的添加，删除（定点删除）
//页表：页表是描述抽象的内存空间的标识，一页定为1KB，必须连续，以求简化，否则会存在动态分区的成分，使问题复杂
//页表包括一个页顺序表，包含创建与删除，在创建过程中可以离散的创建也就是单个创建，这样一来问题会急剧复杂化，会有动态分区的大部分成分，其实可以将二者合并甚至将所有x实验合并，后话了这是
//页表中包含：页表页码，视图页码，起始地址，结束地址，所属进程，总数标记，历史数标记
//方法目前仅提供查询，添加，不提供删除，否则可能写不出来，太复杂了
//块表：包含页表页码，起始结束标识，试图页面所属进程，总数标记，删除优先级标记，在删除时，优先级越h高越容易删除


#ifndef sequence_list_option_h
#define sequence_list_option_h
#include <stdio.h>

typedef struct{
    int pro_num;
    char name[5];
}progress_e;//进程元素

typedef struct{
    progress_e pro_tab[100];
    int all_num;
    int history;
}progress_list_type;

void init_progress_tab(progress_list_type* new_table){
    new_table->all_num=0;
    new_table->history=0;
}//初始化

int add_pro(progress_list_type* progress_table,progress_e new_pro){
    new_pro.pro_num=progress_table->history;
    progress_table->pro_tab[progress_table->all_num]=new_pro;
    progress_table->all_num++;
    progress_table->history++;//设定一个历史峰值，用于为新来的进程赋值，以进行不同进程的区分
    return new_pro.pro_num;
}//添加



void del_pro(progress_list_type* progress_table,int pro_num){//在删除时，只修改总数，不修改历史峰值
    int i=0,j;
    for(;i<progress_table->all_num;i++){
        if(pro_num==progress_table->pro_tab[i].pro_num){
            break;
        }
    }
    if(i==progress_table->all_num-1){
        progress_table->all_num--;
    }else if(i<progress_table->all_num-1){
        for(j=i;j<progress_table->all_num-1;j++){
            progress_table->pro_tab[j]=progress_table->pro_tab[j+1];
        }
        progress_table->all_num--;
    }else{
        printf("未找到");
    }
}
void print_pro(progress_list_type* progress_table){
    int i=0;
    printf("+-----+-----+\n");
    printf("|name | num |\n");
    for(;i<progress_table->all_num;i++){
        printf("+-----+-----+\n");
        printf("|%-5s|%-5d|\n",progress_table->pro_tab[i].name,progress_table->pro_tab[i].pro_num);
    }
    printf("+-----+-----+\n");
}
//以上是关于进程表的操作，包括增加和删除，而且d都能正常运行
//然后就是页表的定义
//页表页码，视图页码，起始地址，结束地址，所属进程，总数标记
typedef struct{
    int real_page_num;
    int page_num_in_pro;
    int star_ad;
    int end_ad;
    int mast_pro;
}page_e;
typedef struct{
    page_e page_table[128];
    int num;
}page_table_type;
void init_page_table(page_table_type* page_table){
    int i=0;
    for(;i<128;i++){
        page_table->page_table[i].real_page_num=i;
        page_table->page_table[i].star_ad=i*1024;
        page_table->page_table[i].end_ad=page_table->page_table[i].star_ad+1023;
        page_table->page_table[i].mast_pro=-1;
    }
    page_table->num=0;
    return;
}
void add_in_page(page_table_type* page_table,int pro_num,int longth){
    int i = page_table->num,j=0;
    int end = i+longth;
    for(;i<end;i++){
        page_table->page_table[i].mast_pro=pro_num;
        page_table->page_table[i].page_num_in_pro=j;
        j++;
    }
}
void del_out_page(page_table_type* page_table,int pro_num){
    int i=0;
    for(;i<128;i++){
        if(page_table->page_table[i].mast_pro==pro_num){
            page_table->page_table[i].mast_pro=-1;
        }
    }
    
}
void print_page_of_a_pro(page_table_type* page_table,int pro_num){
    int i=0;
    printf("+-----+-----+-----+-----+-----+\n");
    printf("|r_num|p_num|star |end  |pro_n|\n");
    for(;i<128;i++){
        if(page_table->page_table[i].mast_pro==pro_num){
            printf("+-----+-----+-----+-----+-----+\n");
            printf("|%-5d|%-5d|%-5d|%-5d|%-5d|\n",page_table->page_table[i].real_page_num,page_table->page_table[i].page_num_in_pro,page_table->page_table[i].star_ad,page_table->page_table[i].end_ad,page_table->page_table[i].mast_pro);
        }
    }printf("+-----+-----+-----+-----+-----+\n");
}

//k物理块
typedef struct{
    int real_page_num;
    int page_num_in_pro;
    int star_ad;
    int end_ad;
    int mast_pro;
    int yxj;
}phe_block_e;
typedef struct{
    phe_block_e block_tab[100];
    int blank;
}phe_block_table_type;
void init_phe_block(phe_block_table_type* phe_block_table,int longth){
    int i=0;
    for(;i<longth;i++){
        phe_block_table->block_tab[i].mast_pro=-1;
        phe_block_table->block_tab[i].yxj=-1;
    }
    phe_block_table->blank=longth;
}
int add_new_block(phe_block_e new_block,phe_block_table_type* phe_block_table){
    int i=0;
    for(;i<phe_block_table->blank;i++){
        if(phe_block_table->block_tab[i].mast_pro==-1){
            phe_block_table->block_tab[i]=new_block;
            return 1;
        }
    }
    return 0;//未找到
}//普通添加
void del_block(phe_block_table_type* phe_block_table){//删除一个优先级最高的
    int i,max=0;
    for(i=1;i<phe_block_table->blank;i++){
        if(phe_block_table->block_tab[i].yxj>phe_block_table->block_tab[max].yxj){
            max=i;
        }
    }
    //一轮循环后得到max
    phe_block_table->block_tab[max].mast_pro=-1;//删除标记
    return;
}

void print_block_tab(phe_block_table_type* phe_block_table){
    int i;
    printf("+-----+-----+-----+-----+\n");
    printf("|page |pro  |star |end  |\n");
    for(i=0;i<phe_block_table->blank;i++){
        if(phe_block_table->block_tab[i].mast_pro!=-1){
            printf("+-----+-----+-----+-----+\n"); printf("|%-5d|%-5d|%-5d|%-5d|\n",phe_block_table->block_tab[i].page_num_in_pro,phe_block_table->block_tab[i].mast_pro,phe_block_table->block_tab[i].star_ad,phe_block_table->block_tab[i].end_ad);
        }
        else{
            printf("+-----+-----+-----+-----+\n");
            printf("|     |     |     |     |\n");
        }
    }printf("+-----+-----+-----+-----+\n");
}


int menu(void){
    int option=-1;
    while(1){
        printf("1.新建进程\n");
        printf("2.LRU算法\n");
        printf("3.LFU算法\n");
        printf("4.FIFO算法\n");
        printf("5.显示信息\n");
        printf("6.删除进程\n");
        printf("7.退出系统\n");
        printf("请输入操作数:");
        scanf("%d",&option);
        if(option>=0&&option<=7){
            return option;
        }else{
            printf("错误的操作数");
        }
    }
   // return option;
}

page_e find_page_use_ad(int address,page_table_type* page_table){
    int i=0;
    page_e ode_page;
    page_e ERROR;
    ERROR.mast_pro=-2;
    for(;i<128;i++){
        if(address>=page_table->page_table[i].star_ad&&address<=page_table->page_table[i].end_ad){
            ode_page = page_table->page_table[i];
            return ode_page;
        }
    }
    return ERROR;
}

void time_refresh(phe_block_table_type* p_block_tab){
    int i;
    for(i=0;i<p_block_tab->blank;i++){
        p_block_tab->block_tab[i].yxj++;
    }
    return;
}



#endif /* swquence_list_option_h */
