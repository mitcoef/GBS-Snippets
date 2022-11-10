# gets
Looking at `man gets`, the first thing we read is "Never use this function".
This little example program shows us why this statement holds. Take a look
at the code in `gets.c` first and understand what the program does.

Now, compile and run with `make gets_pwn`. 
Supplying `admin123` gives, as expected, the room code. 
Now suppose we only have access to the binary and no knowledge of the 
password. Can we get access anyways? 

No problem! We as super hackers have looked at the binary using `objdumb` and
found the following:
`call   10b0 <gets@plt>`
Bingo, the unsafe function `gets` is used here! 
We also see:
`cmp    BYTE PTR [rbp-0x1],0x2b`
Ah, something is compared to `0x2b`. With some understanding of `ascii` we see
that this value corresponds to the character `+`.

We get an idea: Since `gets` will read an arbitrary amount of characters, disregarding
the size of the buffer, we can overflow the buffer and write `+`, which is `0x2b` in such
a way that the memory at location `rbp-0x1` is set to `0x2b` as well!

Let's try the following password:
`++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++`

Aaaaand BINGO! The password is leaked. Let's look at how the call stack of our main function looks like:

```
-----------
|  0x00   | 0 <- password
-----------
|  0x00   | 1
-----------
|  0x00   | ...
-----------
|  0x00   | 255
-----------
|  0x00   | <- status 
-----------
```

Since the memory-location of `status` is right after the last element of the `password` array,
if we write exactly 256 characters, the last character will overwrite the value inside `status`!
After we enter our password, this is what the stack looks like:
```
-----------
|  0x2b   | 0 <- password
-----------
|  0x2b   | 1
-----------
|  0x2b   | ...
-----------
|  0x2b   | 255
-----------
|  0x2b   | <- status 
-----------
```

For this reason, the room code is leaked.

Importantly, this kind of stack-smashing attack is well known and only works because we compile with
`-fno-stack-protector`. Try running `make gets_protected`  - hint: our attack no longer
works. If you wanna know why, google is your friend ;) Now make sure to *never* use `gets` in any of your programs!
