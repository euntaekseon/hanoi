## hanoi 코드

전체적인 코드 실행 순서: main -> init_game -> start_game

1. main  
-> 역할 = 게임 시작  
: scene 생성(모드 선택 화면)  
: init_game  
: startGame  

2. init_game  
-> 역할 = restart 눌렀을 때 되돌아오는 화면, 게임에 필요한 button/원반 board 세팅    
: (모드 선택 화면으로 변경 - restart되었을 때 고려해서 추가)  
: 게임 한 턴에 사용하는 변수 초기화(count, flag, disk, arr1/arr2)  
: button 생성 -> 일단 숨김  
: easy/hard 버튼 생성 -> 클릭하면 start_game 실행(scene 이미지가 전환됨, 원반 board 생성 후 일단 숨김)  

3. start_game  
-> 역할 = 실질적으로 게임이 진행되는 부분(init_game에서 넘어올 때 scene 이미지가 전환되어 넘어옴)     
: restart 버튼 생성 -> 클릭하면 2번 init_game으로 이동  
: 실제 원반 이동(2번에서 hide했던 button/원반board[0]를 보여준 후에 게임 실행)  
