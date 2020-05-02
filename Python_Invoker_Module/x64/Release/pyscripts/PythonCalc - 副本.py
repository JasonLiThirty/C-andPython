import threading

count = 0
lock = threading.Lock()

def Counter():
	global count
	#lock.acquire()
	count += 1
	#lock.release()
	return count

def Run():
	for i in range(0, 1000):
		print(Counter())      

def Add(num1, num2):
	return num1+num2