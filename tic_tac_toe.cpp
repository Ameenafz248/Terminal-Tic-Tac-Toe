#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <algorithm>
bool  is_filled(const std::vector<std::string> board){
    for (const auto &row : board) {
        if (std::any_of(row.begin(), row.end(), [](const char &c) {
            return c == '-';
        })) {
            return false;
        }
    }
    return true;
}
int are_equal(const std::string &row){
    char c = row.front();
    return std::all_of(row.begin(), row.end(), [&c](const char &a) {
        return  a != '-' && a == c;
    });
}
int are_equal(const char &a, const char &b, const char &c){
    if(a==b && a==c && a!= '-'){
        return 1;
    }
    return 0;
}
class tic_tac_toe{
   private:
    struct Player {
        std::string name;
        char sign;
    };
    // char  play_board[3][3];
    // std::vector<std::vector<char>> play_board(3, std::vector<char>(3, '-'));
    std::vector<Player> players;
    std::vector<std::string> play_board;
    public:
    tic_tac_toe() : play_board(std::vector<std::string>(3, "---")), players(std::initializer_list<Player>{Player{"", 'X'}, Player{"", 'O'}}){}
    void display();
    void reset();
    std::pair<bool, int> insert(const Player &);
    void master();
    void get_name();
    bool game_cond(const int &);
    void start();
};
void tic_tac_toe::start(){
   std::system("clear");
   while(1){
    
std::cout <<"   ▄      ▀                    ▄                           ▄                 \n" 
          << " ▄▄█▄▄  ▄▄▄     ▄▄▄          ▄▄█▄▄   ▄▄▄    ▄▄▄          ▄▄█▄▄   ▄▄▄    ▄▄▄  \n"
          << "   █      █    █▀  ▀           █    ▀   █  █▀  ▀           █    █▀ ▀█  █▀  █ \n"
          << "   █      █    █       ▀▀▀     █    ▄▀▀▀█  █       ▀▀▀     █    █   █  █▀▀▀▀ \n"
          << "   ▀▄▄  ▄▄█▄▄  ▀█▄▄▀           ▀▄▄  ▀▄▄▀█  ▀█▄▄▀           ▀▄▄  ▀█▄█▀  ▀█▄▄▀ \n\n";                                                                          
                                                                        
    std::string choice;
    std::cout<<"1. New game\n2. Quit"<<std::endl;
    do{
        std::cin>>choice;
    if (choice.size() > 1) {
        std::cout << "Invalid input! try again\n";
        continue;
    }
    if ( choice.front() == '2') {
        return;
    }
    else if (choice.front() == '1') {
        master();
        break;
    }
    else {
        std::cout << "Invalid input! try again\n";
        continue;
    }
    }while(true);
   }
}
bool tic_tac_toe::game_cond(const int &idx){
    int row = idx / 3, col = idx % 3;
    if (are_equal(play_board[row])) {
        return true;
    }
    if (are_equal(play_board[0][col], play_board[1][col], play_board[2][col])) {
        return true;
    }
    if (idx == 4 && 
    (are_equal(play_board[0][0], play_board[1][1], play_board[2][2]) ||
     are_equal(play_board[0][2], play_board[1][1], play_board[2][0]))
    ) {
       return true; 
    }
    if ((idx == 0 || idx == 8) && are_equal(play_board[0][0], play_board[1][1], play_board[2][2])) {
        return true;
    }
    if ((idx == 2 || idx == 6) && are_equal(play_board[0][2], play_board[1][1], play_board[2][0])) {
        return true;
    }
    return false;
}
void tic_tac_toe::get_name(){
    std::cout<<"Name of player 1: ";
    std::cin>>players[0].name;
    std::cout<<"Name of player 2: ";
    std::cin>>players[1].name;
    std::cout<<std::endl;
}
std::pair<bool, int> tic_tac_toe::insert(const Player &player){
    std::string str;
    std::cout<<player.name<<"'s turn: ";
    std::cin>>str;
    char val = str.front();
    if (val == 'q' || val == 'Q') {
        return {false, 0};
    }
    if (str.size() != 1 || val < '1' || val > '9') {
        std::cout << "Invalid input, try again" << std::endl;
        return insert(player);
    }
    else {
        int idx = val - '0' - 1;
        char &pos = play_board[idx / 3][idx % 3];
        if (pos != '-') {
            std::cout<<"Error! Already occupied! try again"<<std::endl;
            insert(player);
        }
        else {
            pos = player.sign;
        }
        return {true, idx};
    }
    return {true, 0};
}
void tic_tac_toe::master(){
    std::system("clear");
    reset();
    get_name();
    std::cout<<"Instruction: Enter the index of the position[1 - 9]"<<std::endl;
    int player_idx = 0;
    while(true){
        display();
        auto cond = insert(players[player_idx]);
        if(!cond.first) {
            std::system("clear");
            return; 
        }
        if (game_cond(cond.second)) {
            std::system("clear");
            std::cout<<"\033[3;31m"<<players[player_idx].name<<" Wins!\n\n\033[0m";
            return;
        }
        if(is_filled(play_board)){
            std::system("clear");
            std::cout<<"It ended in a draw!\n\n";
            return;
        }
        player_idx = player_idx ? 0 : 1;
    }
}
void tic_tac_toe::display(){
    std::system("clear");
    std::cout << "Enter a number between 1 to 9 (Enter q to quit the game)\n\n";
    for(int i=0;i<3;i++){
        // std::cout<<std::setw(20);
        for(int j=0;j<3;j++){
            std::cout<<play_board[i][j]<<std::setw(6);
        }
        std::cout<<"\n\n";
    }
    
}

void tic_tac_toe::reset(){
    for (auto &row : play_board) {
        row = "---";
    }
}

int main(){
    tic_tac_toe game;
    game.start();
    std::system("clear");
    return 0;
}

