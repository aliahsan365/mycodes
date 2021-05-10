#include <iostream>
#include <vector>
#include <queue>
using namespace std;


typedef vector<vector<char>> mapa;
typedef vector<vector<bool>> mapa_visited;


// ok jutge : P70690


void read_map(mapa& mp) {

	int n = mp.size();
	int m = mp[0].size();

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			cin >> mp[i][j];
		}
	}
}


bool check_bounds(int n, int m, int x, int y) {
	return x >= 0 and x < n and y >= 0 and y < m;

}



bool bfs_mapa(const mapa& mp, int r, int c) {

	int n,m;
	
	n = mp.size(); // rows
	m = mp[0].size(); // columns

	pair<int,int> p_inicial = make_pair(r,c);
    mapa_visited mp_visited = vector<vector<bool>> (n,vector<bool>(m,false));
    
    queue<pair<int,int>> q;

	q.push(p_inicial);
    
	while (!q.empty()) {
		
		pair<int,int> pos = q.front();
		
		q.pop();
		
		int x,y;
		x = pos.first;
		y = pos.second;

		//cout << x << " " << y << endl;

		mp_visited[x][y] = true;

		if (mp[x][y] == 't') {
			return true;
		}

		//top
		if (check_bounds(n,m,x-1,y)) {
			if (mp[x-1][y] != 'X' and not mp_visited[x-1][y]) {
				q.push(make_pair(x-1,y));
			}

		}
        //bottom
		if (check_bounds(n,m,x+1,y)) {
			if (mp[x+1][y] != 'X' and not mp_visited[x+1][y]){
				q.push(make_pair(x+1,y));
			}
		}
        //left
		if (check_bounds(n,m,x,y-1) ) {
			if (mp[x][y-1] != 'X' and not mp_visited[x][y-1]) {
				q.push(make_pair(x,y-1));
			}
		}
        //right
		if (check_bounds(n,m,x,y+1)) {
			if (mp[x][y+1] != 'X' and not mp_visited[x][y+1]) {
				q.push(make_pair(x,y+1));
			}
		}
	}
	return false;
}


int main()
{

	int n,m;
	cin >> n >> m;
	mapa mp = vector<vector<char>> (n,vector<char>(m));
	read_map(mp);
	int r,c;
	cin >> r >> c;

	if(bfs_mapa(mp,r-1,c-1)) {
		cout << "yes" << endl;
	}
	else {
		cout << "no" << endl;
	}

}



