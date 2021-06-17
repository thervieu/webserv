from tests import *
from typing import Callable

import os
import sys

def check_test(port: int, name_test: str, test: Callable) -> None:
	try:
		str_result = name_test(port)
	except:
		str_result = "couldn't connect"

	if (len(str_result) == 0):
		check = ✅
	else:
		check = ❌
	
	print("test : {} | result : {} {}".format(name_test, check, str_result))


def run(port: int) -> None:
	"""run tests"""
	check_test(port, "GET / ", simple_get_index)
	check_test(port, "GET /auto ", get_autoindex_subdir)




if (__name__ == "__main__"):
	if (len(sys.argv) != 2):
		print("Usage: python3 main.py tests.py [port]")
		exit(1)
	try:
		port = int(sys.argv[1])
	except:
		print("please input a valid port (int)")
		exit(1)
	os.system("rm -rf ./documents/tmp/*")
	run(port)
