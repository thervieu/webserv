from tests import *
from typing import Callable

import os
import sys

DEFAULT = "\033[39m"
GREEN = "\033[32m"
RED = "\033[31m"


def check_test(port: int, name_test: str, test: Callable) -> None:
	try:
		str_result = test(port)
	except:
		str_result = "couldn't connect"

	if (len(str_result) == 0):
		check = GREEN + "V" + DEFAULT
	else:
		check = RED + "X" + DEFAULT
	
	print("test : {:50} | result : {} {}".format(name_test, check, str_result))


def run(port: int) -> None:
	"""run tests"""
	check_test(port, "GET / ", simple_get_index)
	check_test(port, "GET /auto autoindex", get_autoindex_subdir)
	check_test(port, "GET /forbidden (403) ", get_forbidden_dir)
	check_test(port, "GET non_existing_dir (404) ", get_404)
	check_test(port, "GET / ports 8080 and 8081", get_index_two_ports)
	check_test(port, "GET / 1 worker 50 times", fifty_get_root)
	check_test(port, "POST / method not authorized (405)  ", wrong_method)
	check_test(port, "POST /post ", simple_post)
	check_test(port, "POST /post request too big (413)", post_too_big)
	check_test(port, "POST /post_upload -> upload in /upload", post_with_upload)
	check_test(port, "DELETE /delete_folder/index.html", delete)

	#check_test(port, "GET / 10 workers 100 times", stress_test)

if (__name__ == "__main__"):
	if (len(sys.argv) != 2):
		print("Usage: python3 main.py tests.py [port]")
		exit(1)
	try:
		port = int(sys.argv[1])
	except:
		print("please input a valid port (int)")
		exit(1)
	os.chdir("tester_documents")
	os.system("rm -rf ./upload/*")
	os.system("echo \"Delete me please\" > ./delete_folder/index.html")
	run(port)
