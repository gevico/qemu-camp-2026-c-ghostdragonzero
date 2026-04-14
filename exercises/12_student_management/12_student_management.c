#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char id[20];
    char name[50];
    int age;
} Student;

int main() {
    FILE *file = fopen("students.txt", "r");
    if (file == NULL) {
        printf("无法打开文件\n");
        return 1;
    }
    
    Student *students[3];
    //只是创建了一个指针
   // fread(students, sizeof(Student), 3, file);
   char line[100];

    for (int i = 0; i < 3; i++) 
    {
	    // TODO: 在这里添加你的代码
        fgets(line, 50, file);
        printf("%s", line);
        students[i] = malloc(sizeof(Student));
        //需要分配内存再能把数据拷贝进去 否则拷贝不了
        

        int count = sscanf(line, "%s %s %d",students[i]->id , students[i]->name,&(students[i]->age));
        printf("count %d\n", count);
        
    }

    fclose(file);
    
    for (int i = 0; i < 3; i++) 
    {
        printf("学号：%s, 姓名：%s, 年龄：%d\n", 
               students[i]->id, 
               students[i]->name, 
               students[i]->age);
    }
    
    for (int i = 0; i < 3; i++) 
    {
        free(students[i]);
    }
    
    return 0;
}