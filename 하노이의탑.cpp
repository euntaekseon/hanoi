#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <bangtal>
using namespace bangtal;

ScenePtr scene_1;
ObjectPtr easy_1, hard_1, button_1[3], board1_1[3][4], board2_1[3][5], restart_1;

int mode_1;//4 - easy, 5 - hard
int count_1 = 0, limit_1;//count - 이용자, limit - 최대 이동 가능 횟수
int arr1_1[3][4] = { 0 }, arr2_1[3][5] = { 0 }, order_1[3];//arr - 이동가능한 원반 위치 알려줌, order - 원반이 이동할 때 세로 위치 알려줌
char path_1[50] = { 0 }, result_1[50] = { 0 };
int flag_1 = 0, disk_1 = -1;//flag가 1이라서 원반을 보여줄 때, 보여줘야 할 disk의 위치(= j값 저장용)

int index_to_x_1(int index) {
    return 215 - (index * 17);
}

int index_to_y_1(int index, int num) {
    if (num == 4) {
        return 440 - (index * 50) - 50;
    }
    else if (num == 5) {
        return 440 - (index * 50);
    }
}

int button_x_1(int index) {
    return (index * 390) + 200;
}

bool check_finish_1(int num) {

    int i_1;
    if (num == 4) {
        for (i_1 = 0; i_1 < num; i_1++) {
            if (arr1_1[2][i_1] == 0) return false;
        }
        if (arr1_1[2][i_1] == 1) return true;//끝까지 다 1이 채워졌으면 성공
    }
    else if (num == 5) {
        for (i_1 = 0; i_1 < num; i_1++) {
            if (arr2_1[2][i_1] == 0) return false;
        }
        if (arr2_1[2][i_1] == 1) return true;//끝까지 다 1이 채워졌으면 성공
    }
}

void start_game_1() {//실제 원반이 이동되는 함수 - 실질적 게임 진행 화면

    restart_1 = Object::create("Images/restart.jpg", scene_1, 900, 570);
    restart_1->setScale(0.8f);
    restart_1->setOnMouseCallback([&](auto, auto, auto, auto)->bool {//원반, restart hide + init으로 돌아감 
        for (int i_1 = 0;i_1 < 3;i_1++) {
            if (mode_1 == 4) {
                for (int j_1 = 0;j_1 < 4;j_1++) {
                    board1_1[i_1][j_1]->hide();
                }
            }
            else if (mode_1 == 5) {
                for (int k_1 = 0;k_1 < 5;k_1++) {
                    board2_1[i_1][k_1]->hide();
                }
            }
            button_1[i_1]->hide();
        }
        restart_1->hide();
        init_game_1();
        return true;
        });

    //원반 이동
    for (int i_1 = 0; i_1 < 3; i_1++) {
        button_1[i_1]->setOnMouseCallback([&, i_1](auto, auto, auto, auto)->bool {
            int j_1; int check_1 = -1;

            if (mode_1 == 4) {
                if (flag_1 == 0) {//원반 줍고(hide), 다음 버튼 클릭
                    for (j_1 = 0; j_1 < 4; j_1++) {//최상위에 있는 원반 찾음
                        if (arr1_1[i_1][j_1] == 1) {
                            arr1_1[i_1][j_1] = 0;
                            board1_1[i_1][j_1]->hide();
                            flag_1 = 1; disk_1 = j_1; order_1[i_1] += 1;
                            break;
                        }
                    }
                }
                else if (flag_1 == 1) {//원반 보여줄 차례 - 위에 arr에 이미 1이 있다면 메세지로 옮길 수 없습니다 출력
                    for (j_1 = 0; j_1 < disk_1; j_1++) {
                        if (arr1_1[i_1][j_1] == 1) {//원반을 옮기지 못 하는 경우
                            showMessage("원반을 옮길 수 없습니다.");
                            break;
                        }
                    }
                    if (arr1_1[i_1][j_1] == 0) {
                        arr1_1[i_1][disk_1] = 1;
                        board1_1[i_1][disk_1]->locate(scene_1, index_to_x_1(disk_1) + 370 * i_1, index_to_y_1(order_1[i_1], 4));
                        board1_1[i_1][disk_1]->show();
                        order_1[i_1] -= 1;//다음에 위치할 축으로 위치 조정
                        flag_1 = 0; disk_1 = -1; count_1++;
                        printf("\nnow count: %d", count_1);
                    }
                }
            }

            else if (mode_1 == 5) {
                if (flag_1 == 0) {//원반 줍고(hide), 다음 버튼 클릭
                    for (j_1 = 0; j_1 < 5; j_1++) {//최상위에 있는 원반 찾음

                        if (arr2_1[i_1][j_1] == 1) {
                            arr2_1[i_1][j_1] = 0;
                            board2_1[i_1][j_1]->hide();
                            flag_1 = 1; disk_1 = j_1; order_1[i_1] += 1;
                            break;
                        }
                    }
                }
                else if (flag_1 == 1) {//원반 보여줄 차례 - 위에 arr에 이미 1이 있다면 메세지로 옮길 수 없습니다 출력
                    for (j_1 = 0; j_1 < disk_1; j_1++) {
                        if (arr2_1[i_1][j_1] == 1) {//원반을 옮기지 못 하는 경우
                            showMessage("원반을 옮길 수 없습니다.");
                            break;
                        }
                    }
                    if (arr2_1[i_1][j_1] == 0) {
                        arr2_1[i_1][disk_1] = 1;
                        board2_1[i_1][disk_1]->locate(scene_1, index_to_x_1(disk_1) + 370 * i_1, index_to_y_1(order_1[i_1], 5));
                        board2_1[i_1][disk_1]->show();
                        order_1[i_1] -= 1;//다음에 위치할 축으로 위치 조정
                        flag_1 = 0; disk_1 = -1; count_1++;
                        printf("\nnow count: %d", count_1);
                    }
                }

            }

            if (check_finish_1(4) || check_finish_1(5)) {
                sprintf(result_1, "성공!(이동횟수: %d)", count_1);
                showMessage(result_1);
            }
            if (count_1 > limit_1) {
                sprintf(result_1, "이동횟수 초과(이동횟수: %d번)", count_1);
                showMessage(result_1);
            }
            return true;
            });
    }

}

void init_game_1() {//start_game함수에서 restart를 눌러 초기화 된 상태 - 게임 실행 전 세팅하는 부분

    scene_1->setImage("Images/배경.jpg");
    showMessage("게임 모드를 선택하세요");

    //게임에 사용할 변수들 초기화 - restart될 경우까지 생각해서 init_game에서 초기화
    count_1 = 0; flag_1 = 0; disk_1 = -1;
    for (int i_1 = 0;i_1 < 3;i_1++) {//arr1/arr2 싹 다 0으로 채움
        for (int j_1 = 0;j_1 < 4;j_1++) {
            arr1_1[i_1][j_1] = 0;
        }
        for (int k_1 = 0;k_1 < 5;k_1++) {
            arr2_1[i_1][k_1] = 0;
        }
    }

    //easy, hard -> 원반, button 생성 -> 일단 생성하고, start_game에서 보여줌
    for (int i_1 = 0; i_1 < 3; i_1++) {
        sprintf(path_1, "Images/버튼%d.jpg", i_1 + 1);
        button_1[i_1] = Object::create(path_1, scene_1, button_x_1(i_1), 120);
        button_1[i_1]->setScale(1.7f);
        button_1[i_1]->hide();
    }
    
    easy_1 = Object::create("Images/easy.jpg", scene_1, 220, 250);
    easy_1->setOnMouseCallback([&](auto, auto, auto, auto)->bool {
        scene_1->setImage("Images/하노이배경.jpg");
        easy_1->hide(); hard_1->hide();
        mode_1 = 4; limit_1 = 18;
        order_1[0] = -1; order_1[1] = 3; order_1[2] = 3;
        for (int i_1 = 0;i_1 < 3;i_1++) {//일단 arr1 싹 다 0으로 채움
            button_1[i_1]->show();//button 보여주기
        }
        for (int i_1 = 0; i_1 < 4; i_1++) {//배열 첫 번째는 1로 채우고, 두번째/세번째는 0으로
            arr1_1[0][i_1] = 1;
            sprintf(path_1, "Images/원반%d.png", i_1 + 1);
            board1_1[0][i_1] = Object::create(path_1, scene_1, index_to_x_1(i_1), index_to_y_1(i_1, 4));
            board1_1[1][i_1] = Object::create(path_1, scene_1, index_to_x_1(i_1) + 370, index_to_y_1(i_1, 4));
            board1_1[2][i_1] = Object::create(path_1, scene_1, index_to_x_1(i_1) + 740, index_to_y_1(i_1, 4));
            board1_1[1][i_1]->hide(); board1_1[2][i_1]->hide();
        }
        showMessage("아래 버튼을 클릭해서 원반을 움직이세요(1번에서 3번으로)");
        printf("\neasy mode start");
        start_game_1();
        return true;
        });

    hard_1 = Object::create("Images/hard.jpg", scene_1, 680, 250);
    hard_1->setOnMouseCallback([&](auto, auto, auto, auto)->bool {
        scene_1->setImage("Images/하노이배경.jpg");
        easy_1->hide(); hard_1->hide();
        mode_1 = 5; limit_1 = 37;
        order_1[0] = -1; order_1[1] = 4; order_1[2] = 4;
        for (int i_1 = 0;i_1 < 3;i_1++) {//button 보여주기
            button_1[i_1]->show();//button 보여주기
        }
        for (int i_1 = 0; i_1 < 5; i_1++) {//배열 첫 번째는 1로 채우고, 두번째/세번째는 0으로
            arr2_1[0][i_1] = 1;
            sprintf(path_1, "Images/원반%d.png", i_1 + 1);
            board2_1[0][i_1] = Object::create(path_1, scene_1, index_to_x_1(i_1), index_to_y_1(i_1, 5));
            board2_1[1][i_1] = Object::create(path_1, scene_1, index_to_x_1(i_1) + 370, index_to_y_1(i_1, 5));
            board2_1[2][i_1] = Object::create(path_1, scene_1, index_to_x_1(i_1) + 740, index_to_y_1(i_1, 5));
            board2_1[1][i_1]->hide(); board2_1[2][i_1]->hide();
        }
        showMessage("아래 버튼을 클릭해서 원반을 움직이세요(1번에서 3번으로)");
        printf("\nhard mode start");
        start_game_1();
        return true;
        });

}

int main() {

    setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
    setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);
    
    scene_1 = Scene::create("", "Images/배경.jpg");
    init_game_1();
    startGame(scene_1);

    return 0;
}
