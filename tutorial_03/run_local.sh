echo "Trying ./local using local address returned from function \"bad\"\n"
echo "./local 0"
./local 0
echo "\nTrying ./local overflowing VLA in function \"bad\"\n"
echo "./local 1"
./local 1
echo "\nTrying ./local using malloced addres from function \"better\"\n"
echo "./local 2"
./local 2
