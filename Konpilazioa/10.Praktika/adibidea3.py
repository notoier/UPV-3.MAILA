y = 1
def f():
	global x
	x = 2
	print(" x = " , x)
def g():
	x = 3
	print(" x = " , x)
f()
g()
print(" x = " , x)
print(" y = " , y)
