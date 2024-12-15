#include "Snake.h"

// 打印测试结果的函数
void print_test_result(int condition, const char *test_name) {
    if (condition) {
        printf("\033[32m%s passed\033[0m\n", test_name); // 绿色
    } else {
        printf("\033[31m%s failed\033[0m\n", test_name); // 红色
    }
}

// 测试函数
void testrandInt() {

    int min = 1, max = 10;
    int result = 1;
    for(int i = 0 ;i<10000;i++){
        if(randInt(min,max)<min || randInt(min,max)>max){
            result = 0;
            break;
        }
    }

    print_test_result(result, "Tests From randInt : ");
}

void testSortPlayerList (){
    Player playerList[5] = {
            {"Alice", 150, 25},
            {"Bob", 200, 30},
            {"Charlie", 120, 15},
            {"David", 180, 20},
            {"Eve", 170, 22}
    };
    sortPlayerList (playerList , 5);

    int result = 1;
    for(int i=1 ; i<5 ; i++){
        if(playerList[i].high_score > playerList[i-1].high_score){
            result=0;
            break;
        }
    }
    print_test_result(result, "Tests From sortPlayerList : ");
}

void testGameOver1 (){
    head = malloc(sizeof(Snake));
    head->x = WIDTH - 1;
    head->y = 1;
    head->next = NULL;
    int result1 = ifGameOver();


    head->x = 0;
    head->y = 1;
    int result2 = ifGameOver();

    head->x = 2;
    head->y = HEIGHT - 1;
    int result3 = ifGameOver();

    head->x = 2;
    head->y = 0;
    int result4 = ifGameOver();

    int result = result1 && result2 && result3 && result4;

    print_test_result(result, "Tests From GameOver1 (head touched the boundary) : ");
    free(head);
}

void testGameOver2(){
    head = malloc(sizeof(Snake));
    head->next = NULL;

    iDifficulty = 3;
    obstacles = (Obstacle*)malloc(sizeof(Obstacle) * MAX_OBT);
    obstacles[0].x = 12;
    obstacles[0].y = 6;
    obstacles[1].x = 12;
    obstacles[1].y = 18;
    obstacles[2].x = 36;
    obstacles[2].y = 6;
    obstacles[3].x = 36;
    obstacles[3].y = 18;

    head->x = obstacles[0].x + 1;
    head->y = obstacles[0].y + 1;
    int result1 = ifGameOver();

    head->x = obstacles[1].x + 0;
    head->y = obstacles[1].y + 1;
    int result2 = ifGameOver();

    head->x = obstacles[2].x + 1;
    head->y = obstacles[2].y + 0;
    int result3 = ifGameOver();

    head->x = obstacles[3].x + 0;
    head->y = obstacles[3].y + 0;
    int result4 = ifGameOver();

    int result = result1 && result2 && result3 && result4;

    print_test_result(result, "Tests From GameOver2 (head touched the obstacles) : ");

    free(head);
    free(obstacles);
}

void testGameOver3(){
    Snake* Node = (Snake*) malloc(sizeof(Snake));
    head = malloc(sizeof(Snake));
    Node->x = 2;
    Node->y = 2;
    head->x = 2;
    head->y = 2;
    head->next = Node;

    int result = ifGameOver();

    print_test_result(result, "Tests From GameOver3 (head touched the body) : ");
    free(Node);
    free(head);
}

void testHeadChange(){
    int result1 = 1;
    int result2 = 1;
    int result3 = 1;
    int result4 = 1;
    head = malloc(sizeof(Snake));
    head->x = 3;
    head->y = 3;
    head->next = NULL;
    headChange(UP);
    if(head->x != 3 ||  head->y != 2){
        result1 = 0;
    }

    head->x = 3;
    head->y = 3;
    headChange(DOWN);
    if(head->x != 3 ||  head->y != 4){
        result2 = 0;
    }

    head->x = 3;
    head->y = 3;
    headChange(LEFT);
    if(head->x != 2 ||  head->y != 3){
        result3 = 0;
    }

    head->x = 3;
    head->y = 3;
    headChange(RIGHT);
    if(head->x != 4 ||  head->y != 3){
        result4 = 0;
    }

    int result = result1 && result2 && result3 && result4;

    print_test_result(result, "Tests From headChange : ");

    free(head);
}


void test_main() {
    //测试randInt函数
    testrandInt();

    //测试sortPlayerList函数
    testSortPlayerList();

    //测试ifGameOver函数
    testGameOver1();
    testGameOver2();
    testGameOver3();

    //测试headChange函数
    testHeadChange();

}

int main() {
    int choice;

    printf("Choose mode (1 for test, 2 for game): ");
    scanf("%d", &choice);
    fflush(stdin);

    if (choice == 1) {
        test_main();  // 执行测试代码
    } else if (choice == 2) {
        game_main();  // 执行游戏代码
    } else {
        printf("Invalid choice.\n");
    }

    return 0;
}

