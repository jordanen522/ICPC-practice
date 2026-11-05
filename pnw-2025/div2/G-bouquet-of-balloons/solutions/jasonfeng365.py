n, d, m = map(int, input().split())
arr = list(map(int, input().split()))
arr.sort()

m *= d

sum=val=0
for i in range(n):
	val+=d-sum
	if val>=m:
		print(i+1)
		break
	sum+=arr[i]
else:
	print(-1)