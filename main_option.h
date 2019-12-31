//
//  main_option.h
//  页面置换算法(新)
//
//  Created by 李若白 on 2019/12/6.
//  Copyright © 2019 李若白. All rights reserved.
//

#ifndef main_option_h
#define main_option_h
#include "sequence_list_option.h"

void write_option(progress_list_type* pro_tab,page_table_type* page_tab){
    progress_e new_pro;
    int longth,pro_id,j;
    printf("请输入进程名");
    scanf("%s",new_pro.name);
    pro_id=add_pro(pro_tab, new_pro);
    printf("请输入页表长度");
    scanf("%d",&longth);
    for(j=0;j<longth;j++){
        page_tab->page_table[page_tab->num].mast_pro=pro_id;
        page_tab->page_table[page_tab->num].page_num_in_pro=j;
        page_tab->num++;
    }
}
void output_option(progress_list_type* pro_tab,page_table_type* page_tab){
    int n;
    printf("进程表\n");
    print_pro(pro_tab);
    printf("请输入查询的进程号：");
    scanf("%d",&n);
    print_page_of_a_pro(page_tab, n);
}

void delete_pro(progress_list_type* pro_tab,page_table_type* page_tab){
    int num;
    printf("请输入要删除的进程号\n");
    scanf("%d",&num);
    del_pro(pro_tab, num);
    del_out_page(page_tab, num);
    return;
}
void LRU_option(progress_list_type* pro_tab,page_table_type* page_tab){
    int p_num,b_long;
    phe_block_table_type p_block_tab;
    phe_block_e one_phe_block;
    page_e dcl_page;
    int add,i,flag=0;
    print_pro(pro_tab);
    printf("请输入要运行的进程");
    scanf("%d",&p_num);
    printf("请输入分配的物理块区大小");
    scanf("%d",&b_long);
    init_phe_block(&p_block_tab, b_long);//物理块表已经创造好
    printf("一切就绪，进入页面调用操做\n");
    while(1){
        flag=0;
        printf("请输入调取地址\n");
        scanf("%d",&add);
        dcl_page=find_page_use_ad(add, page_tab);
        if(add==-2){//紧急停止
            break;
        }
        if(dcl_page.mast_pro!=p_num){
            printf("掉入了错误的区块，区块不属于进程\n");
        }else{//否则进行正常的调度
            one_phe_block.end_ad=dcl_page.end_ad;
            one_phe_block.mast_pro=dcl_page.mast_pro;
            one_phe_block.page_num_in_pro=dcl_page.page_num_in_pro;
            one_phe_block.real_page_num=dcl_page.real_page_num;
            one_phe_block.star_ad=dcl_page.star_ad;
            one_phe_block.yxj=0;
            i=0;
            for(;i<p_block_tab.blank;i++){
                if(p_block_tab.block_tab[i].page_num_in_pro==one_phe_block.page_num_in_pro){
                    p_block_tab.block_tab[i].yxj=0;
                    flag=1;
                    break;
                }
            }
            if(flag==1){
                printf("表已存在!\n");
                
                print_block_tab(&p_block_tab);
                continue;
            }
            if(add_new_block(one_phe_block, &p_block_tab)){//如果找到了一个添加，那么成功添加
                print_block_tab(&p_block_tab);
            }else{
                del_block(&p_block_tab);
                add_new_block(one_phe_block, &p_block_tab);
                print_block_tab(&p_block_tab);
            }
        }
        time_refresh(&p_block_tab);
    }
}


void LFU_option(progress_list_type* pro_tab,page_table_type* page_tab){
    int p_num,b_long;
    phe_block_table_type p_block_tab;
    phe_block_e one_phe_block;
    page_e dcl_page;
    int add,i,flag=0;
    print_pro(pro_tab);
    printf("请输入要运行的进程");
    scanf("%d",&p_num);
    printf("请输入分配的物理块区大小");
    scanf("%d",&b_long);
    init_phe_block(&p_block_tab, b_long);//物理块表已经创造好
    printf("一切就绪，进入页面调用操做\n");
    while(1){
        flag=0;
        printf("请输入调取地址\n");
        scanf("%d",&add);
        dcl_page=find_page_use_ad(add, page_tab);
        if(add==-2){
            break;
        }
        if(dcl_page.mast_pro!=p_num){
            printf("掉入了错误的区块，区块不属于进程\n");
        }else{//否则进行正常的调度
            one_phe_block.end_ad=dcl_page.end_ad;
            one_phe_block.mast_pro=dcl_page.mast_pro;
            one_phe_block.page_num_in_pro=dcl_page.page_num_in_pro;
            one_phe_block.real_page_num=dcl_page.real_page_num;
            one_phe_block.star_ad=dcl_page.star_ad;
            one_phe_block.yxj=100;
            i=0;
            for(;i<p_block_tab.blank;i++){
                if(p_block_tab.block_tab[i].page_num_in_pro==one_phe_block.page_num_in_pro){
                    p_block_tab.block_tab[i].yxj--;
                    flag=1;
                    break;
                }
            }
            if(flag==1){
                printf("表已存在!\n");
                print_block_tab(&p_block_tab);
                continue;
            }
            if(add_new_block(one_phe_block, &p_block_tab)){//如果找到了一个添加，那么成功添加
                print_block_tab(&p_block_tab);
            }else{
                del_block(&p_block_tab);
                add_new_block(one_phe_block, &p_block_tab);
                print_block_tab(&p_block_tab);
            }
        }
        //time_refresh(&p_block_tab);
    }
}




#endif /* main_option_h */
