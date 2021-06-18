import requests
import threading
import time

def simple_get_index(port: int) -> str:
	r = requests.get("http://localhost:" + str(port))
	if (r.status_code != 200):
		return "Bad status code"
	if (r.text != "Hello World !\n"):
		return "Bad Content"
	if (r.headers['Content-Length'] != "14"):
		return "Bad Content-Length"
	return ""

def get_index_two_ports(port: int) -> str:
	r = requests.get("http://localhost:" + str(port))
	if (r.status_code != 200):
		return "Bad status code"
	if (r.text != "Hello World !\n"):
		return "Bad Content"
	if (r.headers['Content-Length'] != "14"):
		return "Bad Content-Length"
	r = requests.get("http://localhost:" + str(port + 1))
	if (r.status_code != 200):
		return "Bad status code"
	if (r.text != "Hello World !\n"):
		return "Bad Content"
	if (r.headers['Content-Length'] != "14"):
		return "Bad Content-Length"
	return ""


def get_forbidden_dir(port: int) -> str:
	r = requests.get("http://localhost:" + str(port) + "/forbidden")
	if (r.status_code != 403):
		return "Bad status code"
	return ""

def get_404(port: int) -> str:
	r = requests.get("http://localhost:" + str(port) + "/nonsense")
	if (r.status_code != 404):
		return "Bad status code"
	if (r.text.find("This is a 404 error page") == -1):
		return "Bad Content"
	return ""

def get_autoindex_subdir(port: int) -> str:
	r = requests.get("http://localhost:" + str(port) + "/auto")
	if (r.status_code != 200):
		return "Bad status code"
	if (r.text.find("Index of /auto") == -1):
		return "Bad Content"
	return ""

def fifty_get_root(port: int) -> str:
	for i in range(50):
		r = requests.get("http://localhost:" + str(port))
		if (r.status_code != 200):
			return "Bad status code"
		if (r.text != "Hello World !\n"):
			return "Bad Content"
		if (r.headers['Content-Length'] != "14"):
			return "Bad Content-Length"
	return ""


""" 20 workers doing 100 GET requests on /"""

sem = threading.Semaphore()

def one_hundred_get_requests(port: int, nb: int) -> None:
	for i in range(100):
		# print("worker {} | test {}".format(str(nb), str(i)))
		sem.acquire()
		r = requests.get("http://localhost:" + str(port))
		if (r.status_code != 200):
			print("worker" + i + ": Bad status code")
		if (r.text != "Hello World !\n"):
			print("worker" + i + ": Bad Content")
		if (r.headers['Content-Length'] != "14"):
			print("worker" + i + ": Bad Content-Length")
		sem.release()
	print("worker {} has finished all his tasks".format(str(nb)))

def stress_test(port: int) -> str:
	threads = []

	for i in range(20):
		thread = threading.Thread(target=one_hundred_get_requests, args=(port, i))
		threads.append(thread)
		thread.start()
	for thread in threads:
		thread.join()
	return ""

def wrong_method(port: int) -> str:
	r = requests.post("http://localhost:" + str(port))
	if (r.status_code != 405):
		return "Bad status code"
	return ""
