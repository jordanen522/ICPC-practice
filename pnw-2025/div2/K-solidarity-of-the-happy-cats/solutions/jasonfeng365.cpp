#include "bits/stdc++.h"
using namespace std;

typedef long long ll;


int numWires, numSignals;
vector<vector<int>> rangeSignalPairs;
vector<string> compatible;
vector<ll> positions;

int main() {
	cin>>numWires>>numSignals;

	rangeSignalPairs = vector<vector<int>>(numWires);
	positions = vector<ll>(numWires);
	compatible = vector<string>(numSignals);
	

	for (int i = 0; i < numWires; i++) {
		int range, signal;
		cin>>range>>signal;
		rangeSignalPairs[i] = {range, signal-1};
	}

	for (int i = 0; i < numSignals; i++) {
		cin>>compatible[i];
	}

	

	// curPos is, where can I put a wire?
	// Next available index.
	ll curPos = 0;
	for (int i = 0; i < numWires; i++) {
		int range = rangeSignalPairs[i][0];
		int signal = rangeSignalPairs[i][1];

		// cout<<"Start at "<<i<<": "<<range<<' '<<signal<<'\n';
		for (int l=0; l<i; l++) {
			int lrange = rangeSignalPairs[l][0];
			int lsignal = rangeSignalPairs[l][1];
			
			if (compatible[lsignal][signal]=='0') {
				curPos = max(curPos, positions[l] + range+1);
			}
			if (compatible[signal][lsignal]=='0') {
				curPos = max(curPos, positions[l] + lrange+1);
			}

			// cout<<l<<": "<<lrange<<' '<<lsignal<<' '<<curPos<<'\n';
		}
		positions[i] = curPos;
		curPos++;
	}

	// for (int i=0; i<positions.size(); i++) cout<<positions[i]<<' '; cout<<'\n';
	
	
	cout<<curPos<<'\n';
}
