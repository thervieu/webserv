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
	
	print("test : {:35} | result : {} {}".format(name_test, check, str_result))


def run(port: int) -> None:
	"""run tests"""
	check_test(port, "GET / ", simple_get_index)
	check_test(port, "GET /auto ", get_autoindex_subdir)
	check_test(port, "GET /forbidden ", get_forbidden_dir)
	check_test(port, "GET / ports 8080 and 8081", get_index_two_ports)
	check_test(port, "GET / 50 times ", fifty_get_root)
	check_test(port, "POST / (method not authorized) ", wrong_method)

if (__name__ == "__main__"):
	if (len(sys.argv) != 2):
		print("Usage: python3 main.py tests.py [port]")
		exit(1)
	try:
		port = int(sys.argv[1])
	except:
		print("please input a valid port (int)")
		exit(1)
	run(port)
