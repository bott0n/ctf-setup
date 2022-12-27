from pwn import *

TARGET = './'
HOST = '127.0.0.1'
PORT = 1234
context.arch = 'amd64' # i386/amd64
context.log_level = 'debug'
context.terminal = ['tmux','splitw','-h']
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

#--- helper functions
s       = lambda data               :p.send(data)        #in case that data is an int
sa      = lambda delim,data         :p.sendafter(delim, data) 
sl      = lambda data               :p.sendline(data) 
sla     = lambda delim,data         :p.sendlineafter(delim, data) 
r       = lambda numb=4096          :p.recv(numb)
ru      = lambda delims, drop=True  :p.recvuntil(delims, drop)
# misc functions
uu32    = lambda data   :u32(data.ljust(4, b'\x00'))
uu64    = lambda data   :u64(data.ljust(8, b'\x00'))
leak    = lambda name,addr :log.success('{} = {:#x}'.format(name, addr))
#---

p.interactive()