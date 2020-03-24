def fib(n , mem = {0:0,1:1}):
	if not n in mem.keys():
		mem[n] = fib(n-1) + fib(n-2)
	return mem[n]	


print(fib(40))











