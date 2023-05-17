zenb = 5
ae = 1
def fakt(x):
	global ae
	ae = ae + 1
	print( "ae: ", ae)
	y = 1
	y = y + 1
	print( "y: ", y)
	if x==1:
		return 1
	else:
		x=(x*fakt(x-1))
		return x

print(zenb, "zenbakiaren faktoriala ", fakt(zenb), "da")
