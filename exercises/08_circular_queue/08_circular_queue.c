#include <stdio.h>
#include <stdbool.h>

#define MAX_PEOPLE 50

typedef struct {
    int id;
} People;

typedef struct {
    People data[MAX_PEOPLE];
    int head;
    int tail;
    int count;
} Queue;

int main() {
    Queue q;
    int total_people=50;
    int report_interval=5;
    q.head = 0;
    q.tail = 49;

    
    for(int i = 0 ; i < total_people; i++){

        q.data[i].id = i;
    }
    q.count = q.tail - q.head + 1;
    //printf("q.count %d", q.count);
    int out_num = 0;
    while(q.count > 1){
        int find  = 0;
        while(find <  5){
            int j = out_num;
            while(q.data[j].id == -1){
                j++;
                out_num++;
                if(out_num > 49)
                out_num = 0;
                if (j > q.tail){
                    j = q.head;
                }
            }
            if (find != 4)
                out_num++;
            //这里找到的第五个就是最后应该被去除的所有当find = 4 时不要+ 1
            
            find++;
            if(out_num > 49)
            out_num = 0;
        }
        q.data[out_num].id = -1;
        printf("淘汰: %d \n", out_num + 1);
        out_num++;
        if(out_num > 49)
        out_num = 0;
        q.count--;
        
    }
    int j = 0;
    while(q.data[j].id == -1)
        j++;
    printf("最后剩下的人是: %d\n", q.data[j].id + 1);


    // TODO: 在这里添加你的代码
    
    
    //printf("最后剩下的人是: %d\n", q.data[q.head].id);

    return 0;
}