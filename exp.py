from pwn import *

TARGET = './'
HOST = '127.0.0.1'
PORT = 1234
context.arch = 'amd64' # i386/amd64
context.log_level = 'debug'
elf = ELF(TARGET)

if len(sys.argv) > 1 and sys.argv[1] == 'remote':
    p = remote(HOST, PORT)
    # libc = ELF('')
else:
    p = process(TARGET)
    libc = elf.libc
    gdbscript = ''''''
    if len(sys.argv) > 1 and sys.argv[1] == 'gdb':
       gdb.attach(p, gdbscript=gdbscript)

#---

p.interactive()