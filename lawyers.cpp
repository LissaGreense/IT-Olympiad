#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct timeOff {

	int start, end, id;

};

struct infoLeader {

	int time, who;
	
	bool operator> (const infoLeader& rhs)const{
		
		return time > rhs.time;
		
	}
	
	bool operator>= (const infoLeader& rhs)const{
	
		return time >= rhs.time;
	
	}
	
	bool operator<= (const infoLeader& rhs)const{
	
		return time <= rhs.time;
	
	}
	
	bool operator< (const infoLeader& rhs)const{
	
		return time < rhs.time;
	
	}
};

bool sortByStart(const timeOff &a, const timeOff &b){
	
    return a.start < b.start;
	
}

typedef vector <infoLeader> nums;

void insert( nums &cont, infoLeader leader) {
	
    nums::iterator it = lower_bound( cont.begin(), cont.end(), leader, greater<infoLeader>());
	
    cont.insert( it, leader );
}
	
int main() {
	
	ios_base::sync_with_stdio(0);

	cin.tie(0);
	
	int group, needed, maxY = 0, maxX = 0, actual = 0;

	cin >> group >> needed;

	vector <infoLeader> leaders(needed);
	
	vector <infoLeader> top(needed);
	
	struct timeOff layers[group];
	
	for (int i = 0; i < group; i++){

		cin >> layers[i].start >> layers[i].end;

		if (layers[i].end > maxY){
		
			maxY = layers[i].end;
			
		}
		
		layers[i].id = i + 1;

	}

	sort(layers, layers + group, sortByStart);

	for (int i = 0; i < maxY; i++){
		
		for (;layers[actual].start == i;){
		
			infoLeader tmp;
			
			tmp.time = layers[actual].end;
			tmp.who = layers[actual].id;
			
			insert(leaders, tmp);
			
			actual++;
		
		}
		
		if (actual >= needed){
		
			if (maxX < (leaders[(needed - 1)].time - i) ){
			
				maxX = leaders[(needed - 1)].time - i;
				
				top = leaders;
			
			}
		
		}
		
	}
	
	cout << maxX << "\n";
	
	for (int i = 0; i < needed ; i++){
	
		cout << top[i].who << " ";
	
	}
	
	return 0;
}
