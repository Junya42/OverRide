# OVERRIDE

## level05

```sh
(gdb) info functions
All defined functions:

Non-debugging symbols:
0x080482f8  _init
0x08048340  printf
0x08048340  printf@plt
0x08048350  fgets
0x08048350  fgets@plt
0x08048360  __gmon_start__
0x08048360  __gmon_start__@plt
0x08048370  exit
0x08048370  exit@plt
0x08048380  __libc_start_main
0x08048380  __libc_start_main@plt
0x08048390  _start
0x080483c0  __do_global_dtors_aux
0x08048420  frame_dummy
0x08048444  main        # <-------
0x08048520  __libc_csu_init
0x08048590  __libc_csu_fini
0x08048592  __i686.get_pc_thunk.bx
0x080485a0  __do_global_ctors_aux
0x080485cc  _fini
```

```sh
(gdb) disas main
Dump of assembler code for function main:
   0x08048444 <+0>:     push   %ebp
   0x08048445 <+1>:     mov    %esp,%ebp
   0x08048447 <+3>:     push   %edi
   0x08048448 <+4>:     push   %ebx
   0x08048449 <+5>:     and    $0xfffffff0,%esp
   0x0804844c <+8>:     sub    $0x90,%esp
                                                        # 0x28(%esp)  char buf[100]
                                                        # 0x8c(%esp)  int i
   0x08048452 <+14>:    movl   $0x0,0x8c(%esp)           # i = 0
   0x0804845d <+25>:    mov    0x80497f0,%eax            # stdin
   0x08048462 <+30>:    mov    %eax,0x8(%esp)
   0x08048466 <+34>:    movl   $0x64,0x4(%esp)           # 100
   0x0804846e <+42>:    lea    0x28(%esp),%eax
   0x08048472 <+46>:    mov    %eax,(%esp)
   0x08048475 <+49>:    call   0x8048350 <fgets@plt>     # fgets(buf, 100, stdin)
   0x0804847a <+54>:    movl   $0x0,0x8c(%esp)           # i = 0
   0x08048485 <+65>:    jmp    0x80484d3 <main+143>
   0x08048487 <+67>:    lea    0x28(%esp),%eax
   0x0804848b <+71>:    add    0x8c(%esp),%eax
   0x08048492 <+78>:    movzbl (%eax),%eax
   0x08048495 <+81>:    cmp    $0x40,%al                 # 'A'-1
   0x08048497 <+83>:    jle    0x80484cb <main+135>
   0x08048499 <+85>:    lea    0x28(%esp),%eax
   0x0804849d <+89>:    add    0x8c(%esp),%eax
   0x080484a4 <+96>:    movzbl (%eax),%eax
   0x080484a7 <+99>:    cmp    $0x5a,%al                 # 'Z'
   0x080484a9 <+101>:   jg     0x80484cb <main+135>
   0x080484ab <+103>:   lea    0x28(%esp),%eax           # 'A'..'Z'
   0x080484af <+107>:   add    0x8c(%esp),%eax
   0x080484b6 <+114>:   movzbl (%eax),%eax
   0x080484b9 <+117>:   mov    %eax,%edx
   0x080484bb <+119>:   xor    $0x20,%edx                # to lowercase
   0x080484be <+122>:   lea    0x28(%esp),%eax
   0x080484c2 <+126>:   add    0x8c(%esp),%eax
   0x080484c9 <+133>:   mov    %dl,(%eax)
   0x080484cb <+135>:   addl   $0x1,0x8c(%esp)
   0x080484d3 <+143>:   mov    0x8c(%esp),%ebx
   0x080484da <+150>:   lea    0x28(%esp),%eax
   0x080484de <+154>:   movl   $0xffffffff,0x1c(%esp)
   0x080484e6 <+162>:   mov    %eax,%edx
   0x080484e8 <+164>:   mov    $0x0,%eax
   0x080484ed <+169>:   mov    0x1c(%esp),%ecx
   0x080484f1 <+173>:   mov    %edx,%edi
   0x080484f3 <+175>:   repnz scas %es:(%edi),%al        # strlen(buf)
   0x080484f5 <+177>:   mov    %ecx,%eax
   0x080484f7 <+179>:   not    %eax
   0x080484f9 <+181>:   sub    $0x1,%eax
   0x080484fc <+184>:   cmp    %eax,%ebx
   0x080484fe <+186>:   jb     0x8048487 <main+67>       # while i < strlen(buf)
   0x08048500 <+188>:   lea    0x28(%esp),%eax
   0x08048504 <+192>:   mov    %eax,(%esp)
   0x08048507 <+195>:   call   0x8048340 <printf@plt>    # printf(buf)  ← format string
   0x0804850c <+200>:   movl   $0x0,(%esp)
   0x08048513 <+207>:   call   0x8048370 <exit@plt>
End of assembler dump.
```

