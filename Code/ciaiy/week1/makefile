dg_echo_server : dg_echo_server.c net.c net.h
	gcc dg_echo_server.c net.c net.h -o dg_echo_server

dg_echo_client : dg_echo_client.c net.c net.h
	gcc dg_echo_client.c net.c net.h -o dg_echo_client

clean : dg_echo_client dg_echo_server
	rm dg_echo_client dg_echo_server