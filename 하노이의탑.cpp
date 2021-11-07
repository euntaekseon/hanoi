#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <bangtal>
using namespace bangtal;

ScenePtr scene;
ObjectPtr board[3][5], button[3];
TimerPtr timer;
int arr[3][5] = { 0 };

int index_to_x(int index) {
    return 140 - (index * 15);
}

int index_to_y(int index) {
    return 350 - (index * 40);
}

int button_x(int index) {
    return (index * 270) + 140;
}


bool check_finish() {
    int i;
    for ( i = 0;i < 5;i++) {
        if (arr[2][i] == 0) return false;
    }
    if (arr[2][i] == 1) return true;//끝까지 다 1이 채워졌으면 성공
}

void init_game() {

    scene = Scene::create("하노이의 탑", "Images/하노이배경.png");
    showMessage("아래 버튼을 클릭해서 원반을 움직이세요.");

    char path[50];
    for (int i = 0;i < 5;i++) {//배열 첫 번째는 1로 채우고, 두번째/세번째는 0으로
        arr[0][i] = 1;

        sprintf(path, "Images/원반%d.png", i + 1);
        board[0][i] = Object::create(path, scene, index_to_x(i), index_to_y(i));
        board[1][i] = Object::create(path, scene, index_to_x(i) + 270, index_to_y(i));
        board[2][i] = Object::create(path, scene, index_to_x(i) + 540, index_to_y(i));
        board[1][i]->hide(); board[2][i]->hide();
    }

    int flag = 0;//0이면 hide, 1이면 show
    int disk = -1;//flag가 1이라서 원반을 보여줄 때, 보여줘야 할 disk의 위치

    timer = Timer::create(2.0f);
    for (int i = 0;i < 3;i++) {
        sprintf(path, "Images/버튼%d.jpg", i + 1);
        button[i] = Object::create(path, scene, button_x(i), 120);
        button[i]->setScale(1.3f);
        button[i]->setOnMouseCallback([&, i](auto, auto, auto, auto)->bool {
            
            timer->start();

            int j;
            int check = -1;

            if (flag == 0) {//원반 줍고(hide), 다음 버튼 클릭
                for (j = 0;j < 5; j++) {//최상위에 있는 원반 찾음
                    if (arr[i][j] == 1) {
                        arr[i][j] = 0;
                        board[i][j]->hide();
                        flag = 1; disk = j;
                        break;
                    }
                }
            }
            else if (flag == 1) {//원반 보여줄 차례 - 위에 arr에 이미 1이 있다면 메세지로 옮길 수 없습니다 출력
                for (j = 0;j < disk;j++) {
                    if (arr[i][j] == 1) {//원반을 옮기지 못 하는 경우
                        showMessage("원반을 옮길 수 없습니다."); 
                        break;
                    }
                }
                if (arr[i][j] == 0 && arr[i][disk] == 0) {
                    arr[i][disk] = 1;
                    board[i][disk]->show();
                    flag = 0; disk = -1;
                }
            }

            if (check_finish()) {
                showMessage("성공!");
            }

            return true;
            });

        
    }
    startGame(scene);
}


int main()
{
    srand((unsigned int)time(NULL));

    setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
    setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);

    init_game();

 

    return 0;
}
