import math

def isPrime(n):
	if n < 2: return False
	elif n == 2: return True
	if n%2 == 0: return False
	for i in range(3, int(math.sqrt(n))+1, 2):
		if n%i == 0: return False
	return True

def isPan(n):
	k = len(str(n))
	arr = [True]+[False]*k
	while n:
		i = n % 10
		if arr[i]:
			break
		else:
			arr[i] = True
			n //= 10
	else:
		return True
	return False

def genPrimes(lim):
	arr = [False]*2+[True]*(lim-2)
	i = 2
	sqrt = int(lim**0.5)
	while i < sqrt:
		if arr[i]:
			j = i+i
			while j < lim:
				arr[j] = False
				j += i
		i += 1
	ret = []
	for i,j in enumerate(arr):
		if j: ret.append(i)
	return ret

firstprimes = [2,3,5,7,11,13,17,19,23,29,31,37]	
base_range = [2047,1373653,25326001,3215031751,2152302898747,3474749660383,341550071728321,0,3825123056546413051,0,0,2**64]
def miller_rabin(n):
	if n <= firstprimes[-1]:
		return n in firstprimes
	for i in range(8):
		if n % firstprimes[i] == 0: return False
	
	d = n - 1
	s = 0
	while d%2==0:
		s += 1
		d //= 2
	rounds = 0
	while n >= base_range[rounds]: rounds += 1
	
	for base in range(rounds+1):
		a = firstprimes[base]
		x = pow(a,d,n)
		if x == 1:
			continue #probably prime
		for r in range(s):
			if x == n - 1:
				break #probably prime
			x = pow(x,2,n)
		else:
			return False #composite
	
	return True #tested all necessary bases. Prime.
		
def P(k,n):
	if k == 3: return n*(n+1)//2
	elif k == 4: return n*n
	elif k == 5: return n*(3*n-1)//2	
	elif k == 6: return n*(2*n-1)
	elif k == 7: return n*(5*n-3)//2
	elif k == 8: return n*(3*n-2)
	
	
	
	
	