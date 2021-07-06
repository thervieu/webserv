import requests
import threading
import os

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
	for i in range(10):
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

def wrong_method(port: int) -> str:
	r = requests.post("http://localhost:" + str(port))
	if (r.status_code != 405):
		return "Bad status code"
	return ""

def simple_post(port:int) -> str:
	payload = "a"
	r = requests.post("http://localhost:" + str(port) + "/post/", data=payload)
	if (r.status_code != 200):
		return "Bad status code."
	return ""


def post_too_big(port:int) -> str:
	payload = "a" * 1025
	r = requests.post("http://localhost:" + str(port) + "/post/", data=payload)
	if (r.status_code != 413):
		return "Bad status code."
	return ""

def post_with_upload(port:int) -> str:
	payload = "fname=test_fname&lname=test_lname"
	r = requests.post("http://localhost:" + str(port) + "/post_upload/index.html", data=payload)
	if (r.status_code != 201):
		return "Bad status code."
	filename = "./upload/index.html"
	with open(filename) as f:
		content = f.readlines()
	if (content[0] != "fname=test_fname&lname=test_lname"):
		return "upload_file has wrong text"
	return ""

def delete(port: int) -> str:
	filename = "/delete_folder/index.html"
	if (os.path.isfile("." + filename)):
		print("File exists")
	r = requests.delete("http://localhost:" + str(port) + filename)
	if (r.status_code != 204):
		return "Bad status code for DELETE."
	if (os.path.isfile("." + filename)):
		return "File still exists"
	return ""

def delete_already_deleted(port: int) -> str:
	filename = "/delete_folder/index.html"
	if (os.path.isfile("." + filename) == False):
		print("File doesn't exist")
	r = requests.delete("http://localhost:" + str(port) + filename)
	if (r.status_code != 404):
		return "Bad status code for DELETE."
	return ""

def server_name(port: int) -> str:
	r = requests.get("http://webserv:" + str(port))
	if (r.status_code != 200):
		return "Bad status code"
	if (r.text != "Hello World !\n"):
		return "Bad Content"
	if (r.headers['Content-Length'] != "14"):
		return "Bad Content-Length"
	return ""

def cgi_tester_get(port: int) -> str:
	r = requests.get("http://localhost:" + str(port) + "/cgi/file.tester")
	if (r.status_code != 200):
		return "Bad status code"
	return ""



def cgi_tester_post(port: int) -> str:
	payload = "args=oui&args2=non"
	r = requests.post("http://localhost:" + str(port) + "/cgi/file.tester", data=payload)
	if (r.status_code != 200):
		return "Bad status code"
	if (r.text != "ARGS=OUI&ARGS2=NON"):
		return "Bad content"
	print("HERE")
	return ""

""" 20 workers doing 100 GET requests on /"""

def one_hundred_get_requests(port: int, nb: int) -> None:
	if nb % 2 == 0:
		port += 1
	for i in range(100):
		r = requests.get("http://localhost:" + str(port))
		if (r.status_code != 200):
			print("worker" + i + ": Bad status code")
		if (r.text != "Hello World !\n"):
			print("worker" + i + ": Bad Content")
		if (r.headers['Content-Length'] != "14"):
			print("worker" + i + ": Bad Content-Length")
	print("worker {} has finished all his tasks".format(str(nb)))

def stress_test1(port: int) -> str:
	print("Please wait a few seconds for the stress test to finish ...")
	threads = []

	for i in range(25):
		thread = threading.Thread(target=one_hundred_get_requests, args=(port, i))
		threads.append(thread)
		thread.start()
	for thread in threads:
		thread.join()
	return ""


def one_hundred_post_requests(port: int, nb: int) -> None:
	for i in range(100000, 1000001, 100000):
		payload = "a" * i
		r = requests.post("http://localhost:" + str(port) + "/post_upload/index.html", data=payload)
		if (r.status_code != 200 and r.status_code != 201):
			print("worker" + str(i) + ": Bad status code: " + str(r.status_code))
		filename = "./upload/index.html"
		with open(filename) as f:
			content = f.readlines()
		if (len(content[0]) != i):
			print("Bad size")
	print("worker {} has finished all his tasks".format(str(nb)))

def stress_test2(port: int) -> str:
	print("Please wait a few seconds for the stress test to finish ...")
	threads = []

	for i in range(20):
		thread = threading.Thread(target=one_hundred_post_requests, args=(port, i))
		threads.append(thread)
		thread.start()
	for thread in threads:
		thread.join()
	return ""

def one_hundred_post_cgi_requests(port: int, nb: int) -> None:
	for i in range(20):
		payload = "a" * 1000000
		r = requests.post("http://localhost:" + str(port) + "/cgi/file.tester", data=payload)
		if (r.status_code != 200):
			print("Bad status code {}".format(r.status_code))
		if (len(r.text) != 1000000):
			print("Bad content")
	print("worker {} has finished all his tasks".format(str(nb)))

def stress_test3(port: int) -> str:
	print("Please wait a few seconds for the stress test to finish ...")
	threads = []

	for i in range(5):
		thread = threading.Thread(target=one_hundred_post_cgi_requests, args=(port, i))
		threads.append(thread)
		thread.start()
	for thread in threads:
		thread.join()
	return ""

def gen():
	yield "a" * 100
	yield "b" * 100

def chunked_post_size_two_k(port: int) -> str:
	print('before request')
	# g = gen()
	# print(next(g))
	# print(next(g))
	r = requests.post("http://localhost:" + str(port) + "/cgi/file.tester", data=gen())
	print('after request')
	
	return ""
