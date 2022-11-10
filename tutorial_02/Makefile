.PHONY: gets_pwn gets_protected clean

CFLAGS="-Wno-implicit-function-declaration" 

gets_pwn:
	gcc $(CFLAGS) -fno-stack-protector -o gets_pwn gets.c
	./gets_pwn

gets_protected:
	gcc $(CFLAGS) -o gets_protected gets.c
	./gets_protected

clean:
	rm -f gets_pwn gets_protected
