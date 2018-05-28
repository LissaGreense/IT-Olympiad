#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

#define _USE_MATH_DEFINES

struct coordinate{

	int x, y;
	double angle;
	
};

struct sortByAngle{

	inline bool operator() (const coordinate& a, const coordinate& b) const {
		
		return a.angle < b.angle;
    
	}

};

double toNorm(double angle){

	if (angle < 0.0){
	
		return ( angle + 360.0 );
	
	}
	
	if (angle > 360.0){ 
	
		return ( angle - 360.0 );
	
	}
	
	return angle;

}

void sortingUnique(vector <double> v){
	
	sort(v.begin(), v.end());
	
	v.erase(unique(v.begin(), v.end()), v.end());

}

int lengthVectors(vector <coordinate> list, int begin, int end){

	int x = 0, y = 0;
	
	for (int i = 0; i <= (end - begin); i++){
	
		x += list[(begin + i)].x;
		y += list[(begin + i)].y;
	
	}

	return ( (y * y) + (x * x));
}

int higher(double value, int begin, int end, vector <coordinate> list){

	if (begin > end){
	
		return -5;
	
	}
	
	int axis = begin + ( (end - begin) / 2);

	if (axis == 0){
	
		return 0;
		
	}
    else if( (list[axis].angle >= value) && (list[axis - 1].angle < value) ){
		
        return axis;
		
    }
	else if( list[axis].angle < value){
		
	    return higher( value, begin, (axis - 1), list);
		
    }

	return higher( value, (axis + 1), end, list);

}

int smaller(double value, int begin, int end, vector <coordinate> list){

	if (begin > end){
	
		return -5;
	
	}
	
	int axis = begin + ( (end - begin) / 2);

	if (axis == (list.size() - 1)){
	
		return (list.size() - 1);
		
	}
    else if( (list[axis].angle <= value) && (list[axis + 1].angle > value) ){
		
        return axis;
		
    }
	else if( list[axis].angle > value){
		
	    return higher( value, begin, (axis - 1), list);
		
    }

	return higher( value, (axis + 1), end, list);

}


int main() {
	
	ios_base::sync_with_stdio(0);
	
	cin.tie(0);

	int amount, maxLength = 0;

	cin >> amount;
	
	vector <double> limitValues(amount * 2);
	
	vector <coordinate> vectors(amount);
	
	for (int i = 0; i < amount; i++){
	
		cin >> vectors[i].x >> vectors[i].y;
		
		double angle = (atan2(vectors[i].y, vectors[i].x) * 180) / M_PI;
		
		vectors[i].angle = toNorm(angle);
		
		limitValues[(i * 2)] = toNorm((angle + 90.0));	
		limitValues[((i * 2) + 1)] = toNorm((angle - 90.0));
		
	}
	
	sortingUnique(limitValues);
	sort(vectors.begin(), vectors.end(), sortByAngle());
	
	double midpoint;
	
	if (limitValues.size() % 2 == 0){

		for (int i = 0; i < limitValues.size(); i++){
			
			midpoint = ( ( limitValues[(2 * i)] + limitValues[((2 * i) + 1)] )  / 2 );
			
			int min = higher(toNorm((midpoint - 90.0)), 0, (vectors.size() - 1), vectors);
			int max = smaller(toNorm((midpoint + 90.0)), 0, (vectors.size() - 1), vectors);
			
			if (max > min){
			
				int maxLengthTemp = lengthVectors(vectors, min, max);
				
				if (maxLength < maxLengthTemp){
				
					maxLength = maxLengthTemp;
				
				}
			
			}
			
		}

	}
	
	else{
	
		for (int i = 0; i < ((limitValues.size() / 2) - 1); i++){
			
			midpoint = ( ( limitValues[(2 * i)] + limitValues[((2 * i) + 1)] )  / 2 );
			
			int min = higher(toNorm((midpoint - 90.0)), 0, (vectors.size() - 1), vectors);
			int max = smaller(toNorm((midpoint + 90.0)), 0, (vectors.size() - 1), vectors);
			
			if ((max > min) && ((max != -5) || (min != -5))){
			
				int maxLengthTemp = lengthVectors(vectors, min, max);
				
				if (maxLength < maxLengthTemp){
				
					maxLength = maxLengthTemp;
				
				}
			
			}
			
		}
		
		midpoint = limitValues[((limitValues.size() / 2) - 1)];

		int min = higher(toNorm((midpoint - 90.0)), 0, (vectors.size() - 1), vectors);
		int max = smaller(toNorm((midpoint + 90.0)), 0, (vectors.size() - 1), vectors);

		if (max > min){

			int maxLengthTemp = lengthVectors(vectors, min, max);

			if (maxLength < maxLengthTemp){

				maxLength = maxLengthTemp;
			}
		}
		
		for (int i = (limitValues.size() / 2) ; i < limitValues.size(); i++){
			
			midpoint = ( ( limitValues[(2 * i)] + limitValues[((2 * i) + 1)] )  / 2 );
			
			int min = higher(toNorm((midpoint - 90.0)), 0, (vectors.size() - 1), vectors);
			int max = smaller(toNorm((midpoint + 90.0)), 0, (vectors.size() - 1), vectors);
			
			if ((max > min) && ((max != -5) || (min != -5))){
			
				int maxLengthTemp = lengthVectors(vectors, min, max);
				
				if (maxLength < maxLengthTemp){
				
					maxLength = maxLengthTemp;
				
				}
			
			}
			
		}
		
	}
	cout << maxLength;
	
	return 0;
}
