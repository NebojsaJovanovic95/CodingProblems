#include <iostream>
#include <vector>
#include <utility>
#include <queue>

using namespace std;

int getSecondsRequired(int R, int C, vector<vector<char> > G) {
    pair<int, int> current;
    vector<vector<pair<int, int> > > map(26, vector<pair<int, int> >());
    for (size_t row = 0; row < G.size(); row ++)
        for (size_t col = 0; col < G[row].size(); col ++)
            if (G[row][col] == 'S')
                current = make_pair(row, col);
            else if (G[row][col] != '#' && G[row][col] != '.' &&  G[row][col] != 'E')
                map[G[row][col] - 'a'].push_back(make_pair(row, col));
    /*for (size_t i = 0; i < 26; i ++)
        for (auto & [row, col] : map[i])
            cout << i << " " << row << " " << col  << "\n";
    */
    // we start from S and look around where we can go and add those cordinates to our queue
    vector<vector<int> > visited(G.size(), vector<int>(G[0].size(), 0));
    for (size_t i = 0; i < G.size(); i ++)
        for (size_t j = 0; j < G[i].size(); j ++)
            visited[i][j] = 0;
    queue<pair<int, int> > move;
    queue<int> time_q;
    int time = 0;
    while (true) {
        auto [row, col] = current;
        visited[row][col] = 1;

        if (G[row][col] == 'E')
            break;
        // list the connections to the current into the queue
        if (row - 1 >= 0 && G[row - 1][col] != '#' && visited[row - 1][col] == 0)
            move.push(make_pair(row - 1, col)), time_q.push(time + 1), visited[row - 1][col] = 1;
        if (row + 1 < G.size() && G[row + 1][col] != '#' && visited[row + 1][col] == 0)
            move.push(make_pair(row + 1, col)), time_q.push(time + 1), visited[row + 1][col] = 1;
        if (col - 1 >= 0 && G[row][col - 1] != '#' && visited[row][col - 1] == 0)
            move.push(make_pair(row, col - 1)), time_q.push(time + 1), visited[row][col - 1] = 1;
        if (col + 1 < G[row].size() && G[row][col + 1] != '#' && visited[row][col + 1] == 0)
            move.push(make_pair(row, col + 1)), time_q.push(time + 1), visited[row][col + 1] = 1;
        if (G[row][col] - 'a' >= 0 && G[row][col] - 'a' < 26) {
            // we add the portals in
            for (auto & [move_r, move_c] : map[G[row][col] - 'a'])
                if ((move_r != row || move_c != col) && visited[move_r][move_c] == 0)
                    move.push(make_pair(move_r, move_c)), time_q.push(time + 1), visited[move_r][move_c] = 1;
        }
        // cout << row << " " << col  << " " << time << " " << move.size() << " " << G[row][col] - 'a' <<"\n";
        if (move.empty())
            break;
        // take from queue and repeat
        current = move.front();
        move.pop();
        time = time_q.front();
        time_q.pop();
    }
    auto [row, col] = current;
    if (G[row][col] == 'E') return time;
    else //*/
        return -1;
}


int main() {
    int R, C;
    cin >> R >> C;
    vector<vector<char> > G(R, vector<char>(C));
    for (size_t i = 0; i < R; i ++)
        for (size_t j = 0; j < C; j ++)
            cin >> G[i][j];
    cout << getSecondsRequired(R, C, G);
}