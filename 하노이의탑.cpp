#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <bangtal>
using namespace bangtal;

ScenePtr scene;
ObjectPtr easy, hard, button[3], board1[3][4], board2[3][5];

int mode;//4 - easy, 5 - hard
int count = 0, total;//최소 카운트 횟수
int arr1[3][4] = { 0 }, arr2[3][5] = { 0 }, order[3];
char path[50], result[50];
int flag = 0, disk = -1;//flag가 1이라서 원반을 보여줄 때, 보여줘야 할 disk의 위치 = j = disk의 종류

int index_to_x(int index) {
    return 215 - (index * 17);
}

int index_to_y(int index, int num) {
    if (num == 4) {
        return 440 - (index * 50) - 50;
    }
    else if (num == 5) {
        return 440 - (index * 50);
    }
}

int button_x(int index) {
    return (index * 390) + 200;
}

bool check_finish(int num) {

    int i;
    if (num == 4) {
        for (i = 0;i < num;i++) {
            if (arr1[2][i] == 0) return false;
        }
        if (arr1[2][i] == 1) return true;//끝까지 다 1이 채워졌으면 성공
    }
    else if (num == 5) {
        for (i = 0;i < num;i++) {
            if (arr2[2][i] == 0) return false;
        }
        if (arr2[2][i] == 1) return true;//끝까지 다 1이 채워졌으면 성공
    }
}

void init_game() {

    for (int i = 0;i < 3;i++) {
        button[i]->setOnMouseCallback([&, i](auto, auto, auto, auto)->bool {
            int j; int check = -1;

            if (mode == 4) {
                if (flag == 0) {//원반 줍고(hide), 다음 버튼 클릭
                    for (j = 0;j < 4; j++) {//최상위에 있는 원반 찾음
                        if (arr1[i][j] == 1) {
                            arr1[i][j] = 0;
                            board1[i][j]->hide();
                            flag = 1; disk = j; order[i] += 1;
                            break;
                        }
                    }
                }
                else if (flag == 1) {//원반 보여줄 차례 - 위에 arr에 이미 1이 있다면 메세지로 옮길 수 없습니다 출력
                    for (j = 0;j < disk;j++) {
                        if (arr1[i][j] == 1) {//원반을 옮기지 못 하는 경우
                            showMessage("원반을 옮길 수 없습니다.");
                            break;
                        }
                    }
                    if (arr1[i][j] == 0 && arr1[i][disk] == 0) {
                        arr1[i][disk] = 1;
                        board1[i][disk]->locate(scene, index_to_x(disk) + 370 * i, index_to_y(order[i], 4));
                        board1[i][disk]->show();
                        order[i] -= 1;//다음에 위치할 축으로 위치 조정
                        flag = 0; disk = -1; count++;
                    }
                }
            }

            else if (mode == 5) {
                if (flag == 0) {//원반 줍고(hide), 다음 버튼 클릭
                    for (j = 0;j < 5; j++) {//최상위에 있는 원반 찾음

                        if (arr2[i][j] == 1) {
                            arr2[i][j] = 0;
                            board2[i][j]->hide();
                            flag = 1; disk = j; order[i] += 1;
                            break;
                        }
                    }
                }
                else if (flag == 1) {//원반 보여줄 차례 - 위에 arr에 이미 1이 있다면 메세지로 옮길 수 없습니다 출력
                    for (j = 0;j < disk;j++) {
                        if (arr2[i][j] == 1) {//원반을 옮기지 못 하는 경우
                            showMessage("원반을 옮길 수 없습니다.");
                            break;
                        }
                    }
                    if (arr2[i][j] == 0 && arr2[i][disk] == 0) {
                        arr2[i][disk] = 1;
                        board2[i][disk]->locate(scene, index_to_x(disk) + 370 * i, index_to_y(order[i], 5));
                        board2[i][disk]->show();
                        order[i] -= 1;//다음에 위치할 축으로 위치 조정
                        flag = 0; disk = -1; count++;
                    }
                }

            }

            if (check_finish(4) || check_finish(5)) {
                sprintf(result, "성공!(이동횟수: %d)", count);
                    showMessage(result);
            }
            if (count > total) {
                sprintf(result, "이동횟수 초과(이동횟수: %d번)", count);
                    showMessage(result);
            }

            return true;
        });

    }
    
    startGame(scene);
}

void show_game(int num) {
    
    if (num == 4) {
        for (int i = 0;i < 4;i++) {
            board1[0][i]->show();
        }
    }
    else if (num == 5) {
        for (int i = 0;i < 5;i++) {
            board2[0][i]->show();
        }
    }

    for (int i = 0;i < 3;i++) {
        button[i]->show();
    }
    showMessage("아래 버튼을 클릭해서 원반을 움직이세요(1번에서 3번으로)");
}

int main() {

    setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
    setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);

    scene = Scene::create("", "Images/배경.jpg");
    showMessage("게임 모드를 선택하세요");

    for (int i = 0;i < 3;i++) {
        sprintf(path, "Images/버튼%d.jpg", i + 1);
        button[i] = Object::create(path, scene, button_x(i), 120);
        button[i]->setScale(1.7f);
        button[i]->hide();
    }

    easy = Object::create("Images/easy.jpg", scene, 220, 250);
    easy->setOnMouseCallback([&](auto, auto, auto, auto)->bool {
        scene->setImage("Images/하노이배경.jpg");
        easy->hide(); hard->hide();
        mode = 4; total = 18;
        order[0] = -1; order[1] = 3; order[2] = 3;
        for (int i = 0;i < 4;i++) {//배열 첫 번째는 1로 채우고, 두번째/세번째는 0으로
            arr1[0][i] = 1;
            sprintf(path, "Images/원반%d.png", i + 1);
            board1[0][i] = Object::create(path, scene, index_to_x(i), index_to_y(i, 4));
            board1[1][i] = Object::create(path, scene, index_to_x(i) + 370, index_to_y(i, 4));
            board1[2][i] = Object::create(path, scene, index_to_x(i) + 740, index_to_y(i, 4));
            board1[0][i]->hide(); board1[1][i]->hide(); board1[2][i]->hide();
        }
        show_game(4);
        return true;
        });

    hard = Object::create("Images/hard.jpg", scene, 680, 250);
    hard->setOnMouseCallback([&](auto, auto, auto, auto)->bool {
        scene->setImage("Images/하노이배경.jpg");
        easy->hide(); hard->hide();
        mode = 5; total = 37;
        order[0] = -1; order[1] = 4; order[2] = 4;
        for (int i = 0;i < 5;i++) {//배열 첫 번째는 1로 채우고, 두번째/세번째는 0으로
            arr2[0][i] = 1;
            sprintf(path, "Images/원반%d.png", i + 1);
            board2[0][i] = Object::create(path, scene, index_to_x(i), index_to_y(i, 5));
            board2[1][i] = Object::create(path, scene, index_to_x(i) + 370, index_to_y(i, 5));
            board2[2][i] = Object::create(path, scene, index_to_x(i) + 740, index_to_y(i, 5));
            board2[0][i]->hide(); board2[1][i]->hide(); board2[2][i]->hide();
        }
        show_game(5);
        return true;
        });

    init_game();

    return 0;
}
