#include "bits/stdc++.h"
using namespace std;

char nextLetter(char c) {
	if (c=='a') return 'z';
	else return c-1;
}

string nxt(string s) {
	string res = "";
	for (char c : s) {
		res+=nextLetter(c);
	}
	return res;
}

int countRs(string s) {
	int res = 0;
	for (char c : s) {
		if (c=='r') res++;
	}
	return res;
}

int main() {
	string s; cin>>s;
	long long n; cin>>n;

	vector<int> count;
	for (int i=0; i<26; i++) {
		count.push_back(countRs(s));
		s = nxt(s);
	}

	long long res = 0;
	for (int i=0; i<26; i++) {
		if (n-1 - i < 0) break;
		long long occurrences = (n-1 - i)/26+1;
		res += occurrences * count[i];
	}

	cout<<res<<'\n';

}
