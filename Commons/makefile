install:
	gcc -Wall *.c -shared -o "libutilstp.so" -lcommons
	sudo cp -u libutilstp.so /usr/lib
	sudo mkdir /usr/include/utilstp
	sudo cp -r * /usr/include/utilstp/

uninstall:
	sudo rm /usr/lib/libutilstp.so
	sudo rm -r /usr/include/utilstp/

