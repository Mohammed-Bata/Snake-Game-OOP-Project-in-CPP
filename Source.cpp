#include<iostream>
#include<conio.h>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<chrono>
#include<thread>

using namespace std;

#define RESET   "\033[0m"
#define RED "\033[31m"
#define GREEN   "\033[32m"
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define z 122
const int width {80};
const int height{ 35 };

class snake {
public:
    snake(int x, int y) {
        body.push_back(make_pair(x, y));
        body.push_back(make_pair(x-1, y));
        body.push_back(make_pair(x-2, y));
        cur_direction = KEY_RIGHT;
    }
    void move_snake() {
        pair<int, int>head = body.front();
        switch (cur_direction) {
        case KEY_UP:
            body.insert(body.begin(),make_pair(head.first, head.second - 1));
            break;
        case KEY_DOWN:
            body.insert(body.begin(),make_pair(head.first, head.second + 1));
            break;
        case KEY_LEFT:
            body.insert(body.begin(),make_pair(head.first-1, head.second));
            break;
        case KEY_RIGHT:
            body.insert(body.begin(),make_pair(head.first+1, head.second));
           
            break;
        }
        body.pop_back();
    }
    void grow_snake() {
        body.push_back(make_pair(--body.back().first,body.back().second));
    }
    void set_direction(int x) {
        cur_direction=x;
    }
    vector<pair<int, int>>get_body() {
        return body;
    }
    bool isBody(pair<int, int>pos) {
        for (int i = 1; i < body.size(); ++i) {
            if (pos == body[i]) {
                return true;
            }
        }
        return false;
    }
    int get_score() {
        return score;
    }
    void edit_score(int e) {
        score += e;
    }
private:
    int cur_direction;
    int score = 0;
    vector<pair<int, int>>body;
};

class food {
public:
    food() {
        location.second= rand() % height;
        location.first = rand() % width;
    }
    void generate() {
         location.second=rand() % height;
        location.first=rand() % width;
  
    }
    pair<int, int>get_location() {
        return location;
    }
private:
    pair<int, int>location;
};

class game {
public:
    game() :snk(width / 2, height / 2), isGameover(false) {};
    void draw_game() {
        system("cls");
        for (int i = 0; i < height+1 ; ++i) {
            for (int j = 0; j < width+1 ; ++j) {
                pair<int,int>pos=make_pair(j, i);
                if (i == 0 || j == 0 || i == height || j == width) {
                    cout <<"#";
                }
               else {
                   if (pos==fruit.get_location()) {
                        cout << "F";
                    }
                    else if (snk.get_body().front() == pos) {
                        cout <<RED<<"O"<<RESET;
                   }
                    else if (snk.isBody(pos)) {
                       cout <<RED<< "o"<<RESET;
                   }
                    else{
                       cout <<GREEN << " "<<RESET;
                    }
                }
            }
            cout << endl;
        }
        snk.edit_score(1);
        cout << "SCore: " << snk.get_score();
    }
    void update() {
        snk.move_snake();
        vector<pair<int, int>> sss = snk.get_body();
        pair<int, int> head = sss.front();
        if (head.first > width || head.second > height || head.first <= 0 || head.second <= 0) {
            isGameover = true;
            return;
        }
        if (snk.get_body().front() == fruit.get_location()) {
            snk.grow_snake();
            snk.edit_score(3);
            fruit.generate(); 
        }
        for (int i = 1; i < snk.get_body().size(); ++i) {
            if (snk.get_body()[i] == head) {
                isGameover = true;
                return;
             }
        }   
    }

    bool isover() const{
        return isGameover;
    }
    void input() {
        if (_kbhit()) {
            int c = _getch();
            switch (c) {
            case KEY_UP:
                snk.set_direction(KEY_UP);
                break;
            case KEY_DOWN:
                snk.set_direction(KEY_DOWN);
                break;
            case KEY_LEFT:
                snk.set_direction(KEY_LEFT);
                break;
            case KEY_RIGHT:
                snk.set_direction(KEY_RIGHT);
                break;
            case z:
                isGameover = true;
                break;
            }
        }
    }

private:
    snake snk;
    food fruit;
    bool isGameover;
};
class user {
public:
    void play_game(game& gm) {
        while (!gm.isover()) {
            gm.draw_game();
            gm.input();
            gm.update();
        
            this_thread::sleep_for(std::chrono::milliseconds(300));
        }
        cout <<endl<< "game over";
    }
};

int main() {    
    srand(static_cast<unsigned>(time(nullptr)));
    game sn;
    user us;
    us.play_game(sn);

}