numWires, numSignals = map(int, input().split())
# (range, signal)
wires = [tuple(map(int, input().split())) for _ in range(numWires)]
pos = [0] * numWires
# signal i is compatible with signals comp[i]
comp = [None for _ in range(numSignals)]
for i in range(numSignals):
	comp[i] = list(map(int, input()))


curPos = 0
# Iterate through previous wires
# For each signal, if not compatible with current signal...
# "push" current wire to the right.
def incompatible(idx):
	res = curPos
	curRange, curSignal = wires[idx]
	curSignal-=1
	for i in range(idx):
		prevRange, prevSignal = wires[i]
		prevSignal-=1
		if not comp[prevSignal][curSignal]:
			res = max(res, pos[i]+curRange)
		if not comp[curSignal][prevSignal]:
			res = max(res, pos[i]+prevRange)
	return res

for i in range(1, numWires):
	curPos = incompatible(i)
	curPos+=1
	pos[i] = curPos

# print(pos)
print(pos[-1]+1)