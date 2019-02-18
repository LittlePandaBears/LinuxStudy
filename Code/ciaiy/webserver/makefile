server : test_httpd.cpp httpd.h httpd.cpp tool.h tool.cpp
	g++ test_httpd.cpp httpd.h httpd.cpp tool.h tool.cpp -o server -lpthread
client : tool.h tool.cpp test.cpp
	g++ tool.h tool.cpp test.cpp -o client