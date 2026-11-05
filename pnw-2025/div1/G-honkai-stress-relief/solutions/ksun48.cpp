#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(false), cin.tie(nullptr);
	int N;
	cin >> N;
	int A, B;
	cin >> A >> B;
	double nostress = 1.0;
	for(int i = 0; i < N; i++){
		int S, E;
		cin >> S >> E;
		nostress *= double(max(0, min(B, E) - max(A, S))) / double(B - A);
	}
	cout << fixed << setprecision(9);
	cout << (1.0 - nostress) << '\n';
}
