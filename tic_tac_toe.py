import os
import curses


class tic_tac_toe:
    def __init__(self) -> None:
        self.players = [{"name" : "", "sign" : 'X'}, {"name" : "", "sign" : 'O'}]
        self.play_board = ["---", "---", "---"]
        self.option = [int(0), int(0)]

    def start(self, stdscr):
        os.system("clear")
        options = ["| New Game", "| Quit"]
        while (True):
            attributes = {}
            curses.init_pair(1, curses.COLOR_WHITE, curses.COLOR_BLACK)
            attributes['normal'] = curses.color_pair(1)
            curses.init_pair(2, curses.COLOR_BLACK, curses.COLOR_WHITE)
            attributes['highlighted'] = curses.color_pair(2)
            
            c = 0
            option = 0
            while c != 10:
                stdscr.addstr("   ▄      ▀                    ▄                           ▄                 \n")
                stdscr.addstr(" ▄▄█▄▄  ▄▄▄     ▄▄▄          ▄▄█▄▄   ▄▄▄    ▄▄▄          ▄▄█▄▄   ▄▄▄    ▄▄▄  \n")
                stdscr.addstr("   █      █    █▀  ▀           █    ▀   █  █▀  ▀           █    █▀ ▀█  █▀  █ \n")
                stdscr.addstr("   █      █    █       ▀▀▀     █    ▄▀▀▀█  █       ▀▀▀     █    █   █  █▀▀▀▀ \n")
                stdscr.addstr("   ▀▄▄  ▄▄█▄▄  ▀█▄▄▀           ▀▄▄  ▀▄▄▀█  ▀█▄▄▀           ▀▄▄  ▀█▄█▀  ▀█▄▄▀ \n\n")                                                                          
            
                for i in range(0, 2):
                    if i == option:
                        attr = attributes['highlighted']
                    else:
                        attr = attributes['normal']
                    stdscr.addstr(options[i] + '\n', attr | curses.A_BOLD)
                c = stdscr.getch()
                if c == curses.KEY_UP and option > 0:
                    option -= 1
                elif c == curses.KEY_DOWN and option < len(options) - 1:
                    option += 1
                stdscr.erase()
            
            if (option == 0):
               self.master(stdscr) 
            else:
                return






    def reset(self):
        self.play_board = ["---", "---", "---"]
                


    def is_filled(self, stdscr)->bool:
        for row in self.play_board:
            c = row.find('-')
            if (row.find('-') != int(-1)):
                return False
        return True

    def insert(self, stdscr, player):
       while (True):
                
            attributes = {}
            curses.init_pair(1, curses.COLOR_WHITE, curses.COLOR_BLACK)
            attributes['normal'] = curses.color_pair(1)
            curses.init_pair(2, curses.COLOR_BLACK, curses.COLOR_WHITE)
            attributes['highlighted'] = curses.color_pair(2)
                
            c = 0
            while c != 10:
                if (c == 'q' or c == 'Q'):
                    return [False, 0]
                stdscr.erase()
                stdscr.addstr("Player " + str(player + 1)+ "'s turn:\n\n", curses.A_BOLD)
                for i in range(0, 3):
                    for j in range(0, 3):
                            if ([i, j] == self.option):
                                attr = attributes['highlighted']
                            else:
                                attr = attributes['normal']
                            stdscr.addstr(" " + self.play_board[i][j] + " ", attr | curses.A_BOLD)
                            stdscr.addstr("  ")
                    stdscr.addstr("\n\n")
                c = stdscr.getch()
                if c == curses.KEY_UP and self.option[0] > 0:
                        self.option[0] -= 1
                elif c == curses.KEY_DOWN and self.option[0] < 2:
                    self.option[0] += 1
                elif c == curses.KEY_LEFT and self.option[1] > 0:
                        self.option[1] -= 1
                elif c == curses.KEY_RIGHT and self.option[1] < 2:
                    self.option[1] += 1
            if (self.play_board[self.option[0]][self.option[1]] != '-'):
                continue
            else:
                if (player == 0):
                    list1 = list(self.play_board[self.option[0]])
                    list1[self.option[1]] = 'X'
                    self.play_board[self.option[0]] = ''.join(list1)
                else:
                    list1 = list(self.play_board[self.option[0]])
                    list1[self.option[1]] = '0'
                    self.play_board[self.option[0]] = ''.join(list1)
                return [True, self.option[0] * 3 + self.option[1]]
        
            


    def master(self, stdscr):
        self.reset()
        stdscr.clear()
        # self.get_name(stdscr)
        player_idx = int(0)
        while (True):
            curr_cond = self.insert(stdscr, player_idx)
            if (curr_cond[0] is not True):
                stdscr.erase()
                return
            if (self.game_cond(int(curr_cond[1])) is True):
                stdscr.erase()
                stdscr.addstr("Player " + str(player_idx + 1) + " Wins!\n\n", curses.A_ITALIC | curses.A_BOLD  )
                return
            if (self.is_filled(stdscr) is True):
                stdscr.erase()
                stdscr.addstr("It ended in a draw!\n\n", curses.A_ITALIC | curses.A_BOLD)
                return
            player_idx = (player_idx + 1) % 2


    def get_name(self, stdscr):
        stdscr.addstr("Name of Player 1: ")
        self.players[0]["name"] = stdscr.getstr()
        stdscr.addstr("Name of Player 2: ")
        self.players[1]["name"] = stdscr.getstr()
    
    def game_cond(self, index):
       row = int(index / 3)
       col = int(index % 3)
       if (are_equal(self.play_board[row][0], self.play_board[row][1], self.play_board[row][2])):
           return True

       if (are_equal(self.play_board[0][col], self.play_board[1][col], self.play_board[2][col])):
           return True

       if (are_equal(self.play_board[0][0], self.play_board[1][1], self.play_board[2][2])):
           return True
        
       if (are_equal(self.play_board[0][2], self.play_board[1][1], self.play_board[2][0])):
           return True

       return False


def are_equal(val1, val2, val3):
    return (val1 == val2) and (val1 == val3) and (val1 != '-')


def main(stdscr):
    game = tic_tac_toe()
    game.start(stdscr)
    stdscr.erase()
    stdscr.addstr("Press any key to exit", curses.A_ITALIC | curses.A_BOLD)
    stdscr.getch()
    


curses.wrapper(main)
