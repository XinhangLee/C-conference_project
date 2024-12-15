#include "Snake.h"

char cGameScene[HEIGHT][WIDTH];             // 设计游戏场景大小为 50 x 25
char cUserName[NAME_SIZE];
int iTotalScore;
int iLastScore;
int iTotalTimes = 0;

int iDifficulty = 1;
int iRefreshTimes[4] = { 50, 25, 5, 0 };
int iGameOver = 0;
int iFoodSpawned = 0;
char cControl;
Snake *head, *tail;
Food food;
int iCountObt = 1;
Obstacle *obstacles;


// 跨平台清屏
void clearScreen() {
#ifdef _WIN32
    system("cls"); // Windows 使用 cls
#else
    system("clear"); // Linux 使用 clear
#endif
}

// 跨平台 Sleep 函数，参数单位为毫秒
void crossPlatformSleep(int milliseconds) {
#ifdef _WIN32
    Sleep(milliseconds); // Windows 平台，单位为毫秒
#else
    struct timespec ts;
    ts.tv_sec = milliseconds / 1000;             // 秒部分
    ts.tv_nsec = (milliseconds % 1000) * 1000000; // 纳秒部分
    nanosleep(&ts, NULL); // 使用 nanosleep 进行休眠
#endif
}

char myGetch() {
    char ch;

#ifdef _WIN32
    // Windows平台，直接使用conio.h中的_getch()
    ch = _getch();
#else
    // Unix-like系统，使用termios配置终端属性
    struct termios oldt, newt;

    // 获取当前终端设置
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    // 禁用回显和行缓冲模式
    newt.c_lflag &= ~(ICANON | ECHO);

    // 应用新的终端设置
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    // 获取输入字符
    ch = getchar();

    // 恢复终端设置
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
#endif

    return ch;
}

// 跨平台实现的_kbhit函数
int myKbhit() {
#ifdef _WIN32
    return _kbhit(); // Windows系统直接使用_kbhit()
#else
    struct timeval tv;
    fd_set read_fds;

    // 设置等待时间为0（非阻塞模式）
    tv.tv_sec = 0;
    tv.tv_usec = 0;

    FD_ZERO(&read_fds); // 初始化文件描述符集合
    FD_SET(STDIN_FILENO, &read_fds); // 将标准输入加入集合

    // 使用select检查是否有输入
    return select(STDIN_FILENO + 1, &read_fds, NULL, NULL, &tv) > 0;
#endif
}

// 跨平台设置光标可见性
void setCursorVisibility(int visible) {
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor_info;

    // 获取当前光标信息
    GetConsoleCursorInfo(hConsole, &cursor_info);

    // 设置光标可见性
    cursor_info.bVisible = visible;
    cursor_info.dwSize = 1; // 设置光标大小
    SetConsoleCursorInfo(hConsole, &cursor_info);
#else
    if (visible) {
        printf("\033[?25h"); // 显示光标
    } else {
        printf("\033[?25l"); // 隐藏光标
    }
    fflush(stdout);
#endif
}

void game_main()
{
    setCursorVisibility(0); // 隐藏光标
	srand((unsigned int)time(0));
	enterUsername();
	while (1)
	{
		startMenu();

        clearScreen();
		initGame();

		gameLoop();
		gameOver();
        clearScreen();
	}
}

// 跨平台 gotoxy 函数，设置光标位置到 (x, y)
void gotoxy(int x, int y) {
#ifdef _WIN32
    // Windows 平台实现
    COORD pos = { (SHORT)x, (SHORT)y }; // 设置坐标
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); // 获取标准输出句柄
    SetConsoleCursorPosition(hOut, pos); // 移动光标位置
#else
    // Linux 平台实现，使用 ANSI 转义序列
    // ANSI 转义序列格式：\033[<y>;<x>H
    printf("\033[%d;%dH", y, x);
    fflush(stdout); // 确保输出立即生效
#endif
}

int randInt(int min, int max)
{
    //TODO
    //返回[min,max]的一个随机整数,注意区间左闭右闭
    return 0;
}

void enterUsername() {
    int iSelect;
    char cSearchName[NAME_SIZE], cName[NAME_SIZE];
    FILE *fp;
    int iScore;
    int iFound = 0;

    clearScreen();
    printf("====================================================\n");
    printf("#                                                  #\n");
    printf("#                                                  #\n");
    printf("#                  1. Create New Player            #\n");
    printf("#                  2. Load Saved Game              #\n");
    printf("#                                                  #\n");
    printf("#                                                  #\n");
    printf("====================================================\n");
    printf("                  Option: ");

    scanf("%d", &iSelect);
    getchar(); // 清理缓冲区中的换行符

    if (iSelect == 1) {
        clearScreen();
        printf("\t\tEnter username: ");
        fgets(cUserName, NAME_SIZE, stdin); // 使用 fgets 代替 gets
        cUserName[strcspn(cUserName, "\n")] = 0; // 移除 fgets 读取的换行符
    } else if (iSelect == 2) {
        clearScreen();
        if ((fp = fopen("scoreBoard.txt", "r")) == NULL) {
            printf("\t\tFailed to load save file. Please check game integrity.\n");
            printf("\t\tPress any key to exit the game.\n");
            myGetch();
            exit(1);
        }

        printf("\t\tEnter save name: ");
        fgets(cSearchName, NAME_SIZE, stdin); // 使用 fgets 代替 gets
        cSearchName[strcspn(cSearchName, "\n")] = 0; // 移除换行符

        while (fscanf(fp, "%s %d %d", cName, &iScore, &iTotalTimes) == 3) {
            if (strcmp(cSearchName, cName) == 0) {
                iFound = 1;
                strcpy(cUserName, cSearchName);
                iLastScore = iScore;
                printf("\t\tPlayer found: %s, Current Score: %d, Total Games Played: %d\n", cUserName, iLastScore, iTotalTimes);
                printf("\t\tPress any key to continue.\n");
                myGetch();
                break;
            }
        }

        if (iFound == 0) {
            printf("\t\tSave not found. Please check the save name and try again.\n");
            printf("                    Press any key to return to the main menu.\n");
            myGetch();
            enterUsername(); // 递归调用需要小心，防止无限递归
        }
        fclose(fp);
    } else {
        printf("                    Invalid Option\n");
        printf("                    Press any key to return to the main menu.\n");
        myGetch();
        enterUsername(); // 同样注意递归调用
    }
}


void startMenu()
{
	int iSelect;

    clearScreen();
    printf("====================================================\n");
    printf("#                                                  #\n");
    printf("#                  Snake Game Version Alpha        #\n");
    printf("#                                                  #\n");
    printf("#                1. Start Game                     #\n");
    printf("#                2. View Leaderboard               #\n");
    printf("#                3. View My Score                  #\n");
    printf("#                4. Switch Player                  #\n");
    printf("#                5. Exit Game                      #\n");
    printf("#                                                  #\n");
    printf("#                                                  #\n");
    printf("====================================================\n");

    printf("                  Option: ");
	scanf("%d", &iSelect);

    clearScreen();
	if (iSelect == 1)
	{
		chooseDifficulty();
		iTotalTimes += 1;
		printf("                  Good Luck ! ! !\n");
        crossPlatformSleep(2000);
	}
	else if (iSelect == 2)
	{
		displayScoreBoard();
        printf("                    Press any key to return to the main menu.\n");
		char ch = myGetch();
		startMenu();
	}
	else if (iSelect == 3)
	{
		myInfo();
        printf("                    Press any key to return to the main menu.\n");
		char ch = myGetch();
		startMenu();
	}
	else if (iSelect == 5)
	{
        printf("\t\tSaving your score to the leaderboard. Please do not close the game.\n");
        updateScoreBoard();
        crossPlatformSleep(500);
        printf("                    Press any key to exit the game.\n");
		char ch = myGetch();
		exit(1);
	}
	else if (iSelect == 4)
	{
		updateScoreBoard();
		enterUsername();
		startMenu();
	}
	else
	{
        printf("                    Invalid Option\n");
        printf("                    Press any key to return to the main menu.\n");
		fflush(stdin);
		char ch = myGetch();
		startMenu();
	}
}

void chooseDifficulty()
{
	int iSelect;

    printf("           1. Easy  2. Medium  3. Hard  4. Nightmare\n");
    printf("                  Option: ");
	scanf("%d", &iSelect);

	if (iSelect <= 4 && iSelect >= 1)
	{
		iDifficulty = iSelect;
		iCountObt = iDifficulty;
	}
	else
	{
        printf("             Please enter a valid option\n");
        printf("                    Press any key to reselect.\n");
		char ch = myGetch();
		chooseDifficulty();
	}
}

void displayScoreBoard()
{
	FILE *fp;
	char cName[NAME_SIZE];
	int iScore;
	int iTimes;

	if ((fp = fopen("scoreBoard.txt", "r+")) == NULL)
	{
        printf("\t\tFailed to load save file. Please check game integrity.\n");
        printf("\t\tPress any key to exit the game.\n");
		char ch = myGetch();
		exit(1);
	}

    clearScreen();
    printf("======================  Leaderboard  ====================\n");
	while (!feof(fp))
	{
		fscanf(fp, "%s%d%d\n", cName, &iScore, &iTimes);
		printf("               %s : %d\n", cName, iScore);
	}
	printf("====================================================\n");
	fclose(fp);
}

void sortPlayerList (Player * playerList , int iPlayerCount){
    //TODO
    //请根据high_score,对playerList数组进行降序排序
    //数组中的每个元素都是Player




}

void updateScoreBoard()
{
	FILE *fp;
	Player playerList[MAX_PLAYER];
	int iPlayerCount = 0;
	int iFound = 0;
	int i, j;


	if ((fp = fopen("scoreBoard.txt", "r+")) == NULL)
	{
        printf("\t\tFailed to load save file. Please check game integrity.\n");
        printf("\t\tPress any key to exit the game.\n");
		char ch = myGetch();
		exit(1);
	}

	while (!feof(fp))
	{
		fscanf(fp, "%s%d%d\n", playerList[iPlayerCount].name, &playerList[iPlayerCount].high_score, &playerList[iPlayerCount].play_times);
		if (strcmp(cUserName, playerList[iPlayerCount].name) == 0)
		{
			iFound = 1;
			if (iTotalScore > playerList[iPlayerCount].high_score)
			{
				playerList[iPlayerCount].high_score = iTotalScore;
			}
			playerList[iPlayerCount].play_times = iTotalTimes;
		}

		iPlayerCount++;
	}
	if (iFound == 0)
	{
		playerList[iPlayerCount].high_score = iTotalScore;
		strcpy(playerList[iPlayerCount].name, cUserName);
		playerList[iPlayerCount].play_times = iTotalTimes;
		iPlayerCount++;
	}


    sortPlayerList(playerList,iPlayerCount);


	i = 0;
	fseek(fp, 0, SEEK_SET);
	while (i < iPlayerCount)
	{
		fprintf(fp, "%s %d %d\n", playerList[i].name, playerList[i].high_score, playerList[i].play_times);
		i++;
	}
	fclose(fp);
}


void myInfo()
{
	int iScore;
	char cName[NAME_SIZE];
	FILE *fp;
	int iFound = 0;

	if ((fp = fopen("scoreBoard.txt", "r+")) == NULL)
	{
        printf("\t\tFailed to load save file. Please check game integrity.\n");
        printf("\t\tPress any key to exit the game.\n");
		char ch = myGetch();
		exit(1);
	}

	while (!feof(fp))
	{
		fscanf(fp, "%s%d\n", cName, &iScore);
		if (strcmp(cName, cUserName) == 0)
		{
			iFound = 1;
			iLastScore = iScore;
            printf("\t\tPlayer: %s,  High Score: %d,  Total Games Played: %d\n", cUserName, iLastScore, iTotalTimes);
            break;
        }
    }
    if (iFound == 0)
    {
        if (iFound == 0)
        {
            printf("\t\tPlayer: %s,  Current Total Score: %d,  Total Games Played: %d\n", cUserName, iTotalScore, iTotalTimes);
            printf("\t\tYour information has not been saved yet. Please wait...\n");
			updateScoreBoard();
            crossPlatformSleep(1000);
		}
	}
	fclose(fp);
}

void gameOver()
{
    clearScreen();
	printf("====================================================\n\n\n\n");
	printf("                      GAME OVER                     \n\n");
    printf("                  Total Score: %4d\n\n\n", iTotalScore);
	printf("====================================================\n");

	if (iTotalScore > iLastScore)
	{
		updateScoreBoard();
		iLastScore = iTotalScore;
	}
    printf("                    Press any key to return to the main menu.\n");
	char ch = myGetch();
	iFoodSpawned = 0;
	iTotalScore = 0;
}

void initGame()
{
	int i, j;

	for (i = 0; i < HEIGHT; i++)
	{
		for (j = 0; j < WIDTH; j++)
		{
			if (i == 0 || j == 0 || i == HEIGHT - 1 || j == WIDTH - 1)
			{
				cGameScene[i][j] = '#';
			}
			else
			{
				cGameScene[i][j] = ' ';
			}
		}
	}
	head = (Snake*)malloc(sizeof(Snake));
	head->x = 24;
	head->y = 12;
	head->next = (Snake*)malloc(sizeof(Snake));
	head->next->x = 23;
	head->next->y = 12;
	head->next->next = NULL;
	tail = head->next;
	cGameScene[head->y][head->x] = '@';
	cGameScene[tail->y][tail->x] = 'O';

	if (iDifficulty >= 3)
	{
		obstacles = (Obstacle*)malloc(sizeof(Obstacle) * MAX_OBT);
		obstacles[0].x = 12;
		obstacles[0].y = 6;
		obstacles[1].x = 12;
		obstacles[1].y = 18;
		obstacles[2].x = 36;
		obstacles[2].y = 6;
		obstacles[3].x = 36;
		obstacles[3].y = 18;
		for (i = 0; i < MAX_OBT; i++)
		{
			int k;
			for (j = 0; j < 2; j++)
			{
				for (k = 0; k < 2; k++)
				{
					cGameScene[obstacles[i].y + j][obstacles[i].x + k] = '#';
				}
			}
		}
	}
	for (i = 0; i < HEIGHT; i++)
	{
		for (j = 0; j < WIDTH; j++)
		{
			putchar(cGameScene[i][j]);
		}
		putchar('\n');
	}
}

void refreshScreen()
{
	int i, j;

	for (i = 1; i < HEIGHT - 1; i++)
	{
		for (j = 1; j < WIDTH - 1; j++)
		{
			gotoxy(j, i);
			putchar(cGameScene[i][j]);
		}
	}
	gotoxy(WIDTH + 5, 12);
	printf("score : %d", iTotalScore);
}

void updateSnakeShape()
{
	Snake *node = head;
	int x, y, preX = head->x, preY = head->y;
	int i, j;

	for (i = 1; i < HEIGHT - 1; i++)
	{
		for (j = 1; j < WIDTH - 1; j++)
		{
			if (cGameScene[i][j] != '*' && cGameScene[i][j] != '#')
			{
				cGameScene[i][j] = ' ';
			}
		}
	}
	if (head->next != NULL && (cControl == UP || cControl == DOWN || cControl == LEFT || cControl == RIGHT))
	{
		while (node != NULL)
		{
			x = node->x;
			y = node->y;
			node->x = preX;
			node->y = preY;
			preX = x;
			preY = y;
			node = node->next;
		}
	}
	node = head->next;
	while (node != NULL)
	{
		cGameScene[node->y][node->x] = 'O';
		node = node->next;
	}
}

int ifGameOver()
{
    //TODO
    //完成游戏终止的三种情况：1、蛇头撞到边界；2、iDifficulty >= 3时蛇头撞到中间障碍物（iDifficulty是难度系数，只有>=3时，才会出现中间障碍物）
    //                     3、蛇头撞到自己的身体（即head与身体的某一个Node的坐标相同，Snake结构体中的x、y相同）







    //蛇头撞到边界






    //iDifficulty >= 3时蛇头撞到中间障碍物






    //蛇头撞到自己的身体





	return 0;
}

void spawnFood()
{
	food.x = randInt(1, WIDTH - 2);
	food.y = randInt(1, HEIGHT - 2);
	food.score = iDifficulty;

	Snake *node = head;
	while (node != NULL)
	{
		if ((node->x == food.x && node->y == food.y) || (cGameScene[food.y][food.x] == '#'))
		{
			food.x = randInt(1, WIDTH - 2);
			food.y = randInt(1, HEIGHT - 2);
			node = head;
			continue;
		}
		node = node->next;
	}

	cGameScene[food.y][food.x] = '*';

	iFoodSpawned = 1;
}

void headChange(char cControl){
    //TODO
    //更改下一步蛇头的位置，注意横向向右为x轴正方向，竖向向下为y轴正方向
    //cControl取值为UP、DOWN、LEFT、RIGHT







}

void gameLoop()
{

    while (!ifGameOver())
	{
        crossPlatformSleep(iRefreshTimes[iDifficulty - 1]);
		if (myKbhit())
		{
			cControl = myGetch();
		}
		updateSnakeShape();

        headChange(cControl);

		cGameScene[head->y][head->x] = '@';

		if (iFoodSpawned == 0)
		{
			spawnFood();
		}

		if (head->x == food.x && head->y == food.y)
		{
			iTotalScore += iDifficulty + 1;
			tail->next = (Snake*)malloc(sizeof(Snake));
			switch (cControl)
			{
			case UP: tail->next->y = tail->y + 1; tail->next->x = tail->x; break;
			case DOWN: tail->next->y = tail->y - 1; tail->next->x = tail->x; break;
			case LEFT: tail->next->y = tail->y; tail->next->x = tail->x + 1; break;
			case RIGHT: tail->next->y = tail->y; tail->next->x = tail->x - 1; break;
			}
			tail = tail->next;
			tail->next = NULL;
			iFoodSpawned = 0;
		}
		refreshScreen();
	}
}