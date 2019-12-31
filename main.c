//
//  main.c
//  页面置换算法(新)
//
//  Created by 李若白 on 2019/12/5.
//  Copyright © 2019 李若白. All rights reserved.
//
//由于昨天的失败经历，我决定重新写一个，这次应该有一个更加完整，更加好的方案，我同样采取头文件库式编程，将所有的东西放进j一个或几个文件里


#include "sequence_list_option.h"
#include "main_option.h"
#include <string.h>


int main(int argc, const char * argv[]) {
    int option_number;
    progress_list_type pro_tab;
    page_table_type page_tab;
    //phe_block_table_type phe_block_tab;
    init_page_table(&page_tab);
    init_progress_tab(&pro_tab);
    while(1){
        option_number = menu();
        if(option_number==1){
            write_option(&pro_tab, &page_tab);
        }else if(option_number==5){
            output_option(&pro_tab, &page_tab);
        }else if (option_number==6){
            delete_pro(&pro_tab, &page_tab);
        }else if(option_number==7){
            break;
        }else if(option_number==2){
            LRU_option(&pro_tab, &page_tab);
        }else if(option_number==3){
            LFU_option(&pro_tab, &page_tab);
        }
    }
    
    
    return 0;
}
