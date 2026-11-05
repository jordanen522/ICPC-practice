s, repeats = input(), int(input())

asciiA = ord('a')
def nxtLetter(c):
	minusOne = ord(c)-asciiA-1
	if minusOne==-1: return 'z'
	else: return chr(asciiA+minusOne)

def nxt(string):
	return "".join(nxtLetter(c) for c in string)

def countRs(string):
	return string.count("r")

cur = s
count = []
for i in range(26):
	count.append(countRs(cur))
	cur = nxt(cur)

res = 0
for i in range(26):
	occurrences = (repeats-1 - i)//26+1
	res += occurrences * count[i]
print(res)