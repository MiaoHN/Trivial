#include <stdio.h>
#include <string.h>

struct student {
    char stuID[10];
    char name[20];
    char sex;
    int age;
};

void insert_student(struct student* s) {
    scanf("%s %s %c %d", s->stuID, s->name, &s->sex, &s->age);
}

void print_students(struct student* students, int count) {
    if (count == 0) {
        printf("null\n");
    } else {
        for (int i = 0; i < count; i++) {
            printf("%s %s %c %d\n", students[i].stuID, students[i].name, students[i].sex, students[i].age);
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);

    struct student students[100]; // 假设最多存储100个学生信息
    int count = 0; // 记录当前已插入的学生数量

    for (int i = 0; i < n; i++) {
        char operation;
        scanf(" %c", &operation);

        if (operation == 'i') {
            insert_student(&students[count]);
            count++;
        } else if (operation == 's') {
            print_students(students, count);
        }
    }

    return 0;
}