#include <bits/stdc++.h>
using namespace std;

class Node{

public:

    static int node_count;

    int id, x_cord, y_cord, parent_id;

    // maybe store F, G, H? look up more explanation.

    Node(){}
    Node(int x, int y){
        id = ++node_count;
        x_cord = x;
        y_cord = y;
    }

    float G(int x, int y){
        return (float) sqrt(pow(x_cord - x, 2) + pow(y_cord - y, 2));
    }
    float H(int x, int y){
        return abs(x_cord - x) + abs(y_cord - y);
    }
};

int Node::node_count = 0;

void print_grid(char grid[10][10]){
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++)
            cout << grid[i][j];
        cout << "\n";
    }
}

Node choose_current(vector<Node>& o, vector<Node>& c, int xs, int ys, int xt, int yt){
    Node current;
    current = o[0];
    for (int i = 0; i < o.size(); i++){
        if (current.G(xs, ys) + current.H(xt, yt) > o[i].G(xs, ys) + o[i].H(xt, yt)){
            current = o[i];
        }
    }
    c.push_back(current);
    for (int i = 0; i < o.size(); i++){
        if (o[i].id == current.id){
            o.erase(o.begin() + i);
        }
    }
    return current;
}

void generate_successors(vector<Node>& o, vector<Node>& c, int xs, int ys, int xt, int yt, Node &curr, char grid[10][10]){
    Node succ[4];
    for (int i = 0; i < 4; i++){
        Node s(curr.x_cord, curr.y_cord);
        succ[i] = s;
    }
    if (curr.x_cord > 0)succ[0].x_cord--;
    if (curr.x_cord < 10)succ[1].x_cord++;
    if (curr.y_cord > 0) succ[2].y_cord--;
    if (curr.y_cord < 10) succ[3].y_cord++;


    for (int i = 0; i < 4; i++){
        bool closed = false, opened = false;

        if (grid[succ[i].x_cord][succ[i].y_cord] == 'H') continue;
        for (int j = 0; j < c.size(); j++){
            if (c[j].x_cord == succ[i].x_cord && c[j].y_cord == succ[i].y_cord){
                closed = true;
                break;
            }

        }
        if (closed) continue;

        //
        // adjust this part to ensure calculation of shortest path...
        //

        for (int j = 0; j < o.size(); j++){
            if (o[j].x_cord == succ[i].x_cord && o[j].y_cord == succ[i].y_cord){
                if (succ[i].G(xs, ys) < o[j].G(xs, ys)){
                    o[j].parent_id = curr.id;
                    opened = true;
                }
                break;
            }
        }
        if (opened) continue;

        //
        //
        //

        succ[i].parent_id = curr.id;
        o.push_back(succ[i]);
    }
}

int main(){
    char grid[10][10] = {' '};

    bool found = false;

    vector<Node> open;
    vector<Node> close;

    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            grid[i][j] = ' ';


    grid[5][5] = 'H';
    grid[6][5] = 'H';
    grid[7][5] = 'H';
    grid[8][5] = 'H';

    grid[4][6] = 'H';
    grid[3][6] = 'H';

    // grid[5][7] = 'H';
    grid[5][6] = 'H';


    int start_x = 1;
    int start_y = 1;

    int target_x = 7;
    int target_y = 9;

    grid[start_x][start_y] = 'C';

    print_grid(grid);

    cout << "select target x coordinate (0-9): "; cin >> target_x;
    cout << "select target y coordinate (0-9): "; cin >> target_y;

    grid[target_x][target_y] = 'T';
    print_grid(grid);

    cout << "calculating shortest path...\n";
    Node s(start_x, start_y);
    s.parent_id = 0;
    open.push_back(s);

    Node current;

    while (!found){
        current = choose_current(open, close, start_x, start_y,target_x, target_y);
        if (current.x_cord == target_x && current.y_cord == target_y){
            found = true;
            break;
        }
        generate_successors(open, close, start_x, start_y, target_x, target_y, current, grid);
        if (open.size() < 1) break;
    }

    if (found){
        /*
        for (int i = 0; i < close.size(); i++){
            if (grid[close[i].x_cord][close[i].y_cord] == ' ') grid[close[i].x_cord][close[i].y_cord] = 'X';
        }
        */
        while (1){
            if (grid[current.x_cord][current.y_cord] == ' ') grid[current.x_cord][current.y_cord] = 'O';
            if (current.parent_id == 0) break;
            for (int i = 0; i < close.size(); i++){
                if (current.parent_id == close[i].id){
                    current = close[i];
                    break;
                }
            }
        }

    }
    print_grid(grid);
    return 0;
}
