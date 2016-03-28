all : make_my_files

make_my_files : clean_up cart_prod

clean_up:
	rm -rf cart_prod

peer_utils : cart_prod.c
	gcc cart_prod.c -o cart_prod
