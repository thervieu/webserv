import requests

def simple_get_index(port: int) -> str:
	r = requests.get("http://localhost:" + str(port) + "/")
	if (r.status_code != 200):
		return "Bad status code"
	if (r.text != "Hello World"):
		return "Bad Content"
	if (r.headers['Content-Length'] != 11):
		return "Bad Content-Length"
	return ""

def get_autoindex_subdir(port: int) -> str:
	r = requests.get("http://localhost:" + str(port) + "/auto")
	if (r.status_code != 200):
		return "Bad status code"
	if (r.text.find(0, len(r.text), "Index of /auto") == -1):
		return "Bad Content"
	return ""
