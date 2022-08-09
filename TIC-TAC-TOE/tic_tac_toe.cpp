#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
int  is_filled(char  arr[3][3]){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(arr[i][j]=='-'){
                return 0;
            }
        }
    }
    return 1;
}
int are_equal(char  arr[3]){
    
    for(int i=1;i<3;i++){
        if(arr[i]!= arr[i-1]){
            return 0;
        }
    }
    if(arr[0] != '-'){
        return 1;
    }
    return 0;
}
int are_equal(char a, char b, char c){
    if(a==b && a==c && a!= '-'){
        return 1;
    }
    return 0;
}
class tic_tac_toe{
   private:
    std::pair<int,std::string> player_1={0,""};
    std::pair<int,std::string> player_2={1,""};
    char  play_board[3][3];
    public:
    tic_tac_toe(){
        for(int i=0;i<3;i++){
            std::fill(play_board[i],play_board[i]+3,'-');
        }
    }
    void display();
    void reset();
    void insert(int player);
    void master();
    void get_name();
    int game_cond();
    void start();
};
void tic_tac_toe::start(){
   while(1){
    std::cout<<std::setw(15)<<"* * *  * * *  * * *      * * *    *    * * *      * * *  * * *  * * *  "<<std::endl;
    std::cout<<std::setw(15)<<"  *      *    *            *     * *   *            *    *   *  *      "<<std::endl;
    std::cout<<std::setw(15)<<"  *      *    *      **    *    * * *  *      **    *    *   *  * * *  "<<std::endl;
    std::cout<<std::setw(15)<<"  *      *    *            *    *   *  *            *    *   *  *      "<<std::endl;
    std::cout<<std::setw(15)<<"  *    * * *  * * *        *    *   *  * * *        *    * * *  * * *  "<<std::endl;
    std::cout<<std::endl;
    int choice;
    std::cout<<"1. New game\n2. Quit"<<std::endl;
    do{
        std::cin>>choice;
    switch (choice)
    {
        
    case 1: master();
        break;
    case 2:return;
    default:
    std::cout<<"Invalid input! try again"<<std::endl;
          choice=0;
        break;
    }
    }while(choice==0);
   }
}
int tic_tac_toe::game_cond(){
    for(int i=0;i<3;i++){
        if(are_equal(play_board[i])){
               return 1;
        }
        if(are_equal(play_board[0][i],play_board[1][i],play_board[2][i])){
            return 1;
        }
    }

    if(are_equal(play_board[0][0],play_board[1][1],play_board[2][2])){
                return 1;
    }
    if(are_equal(play_board[0][2],play_board[1][1],play_board[2][0])){
        return 1;
    }
    if(is_filled(play_board)){
        return 2;
    }
    return 0;
    
}
void tic_tac_toe::get_name(){
    std::cout<<"Name of player 1: ";
    std::cin>>player_1.second;
    std::cout<<"Name of player 2: ";
    std::cin>>player_2.second;
    std::cout<<std::endl;
}
void tic_tac_toe::insert(int player){
    int val;
    char * pos;
    if(!player){
        std::cout<<player_1.second<<"'s turn: ";
        std::cin>>val;
        
        if(val%3){
           pos= (*(play_board + val/3) + val%3-1);
        }
        else{
            pos=(*(play_board + val/3 -1) + 2);
        }
        if(*pos != '-'){
            std::cout<<"Error! try again"<<std::endl;
            insert(player);
        }
        else{
                *pos='X';
        }
        
        
    }
    else{
        std::cout<<player_2.second<<"'s turn: ";
        std::cin>>val;
        
        if(val%3){
           pos= (*(play_board + val/3) + val%3-1);
        }
        else{
            pos=(*(play_board + val/3 -1) + 2);
        }
        if(*pos != '-'){
            std::cout<<"Error! Already occupied! try again"<<std::endl;
            insert(player);
        }
        else{
                *pos='O';
        }
    }
}
void tic_tac_toe::master(){
    int flag=0;
    get_name();
    std::cout<<"Instruction: Enter the index of the position[1 - 9]"<<std::endl;
    while(flag== 0){
        display();
        flag=game_cond();
        if(flag==1){
            std::cout<<player_2.second<<" Wins!\n\n";
            return;
        }
        if(flag==2){
            std::cout<<"It ended in a draw!\n\n";
            return;
        }
        insert(0);
        display();
        flag=game_cond();
        if(flag==1){
            std::cout<<player_1.second<<" Wins!\n\n";
            return;
        }
        if(flag==2){
            std::cout<<"It ended in a draw!\n\n";
            return;
        }
        
        insert(1);
    }
}
void tic_tac_toe::display(){
    for(int i=0;i<3;i++){
        std::cout<<std::setw(15);
        for(int j=0;j<3;j++){
            std::cout<<play_board[i][j]<<std::setw(6);
        }
        std::cout<<"\n\n";
    }
}
void tic_tac_toe::reset(){
    for(int i=0;i<3;i++){
            std::fill(play_board[i],play_board[i]+3,'-');
        }
}
int main(){
    tic_tac_toe game;
    game.start();
    
}