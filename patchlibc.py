#! /bin/python3

import os, sys

archs = ['32', '64']
vers = ['2.23', '2.27', '2.31', '2.34']

if len(sys.argv) < 2:
    print("[x] Please give the elf file first!")
    exit(-1)

filename = sys.argv[1]

os.system(f"rm {filename}_patched")
print("[+] Created a patched elf file")
os.system(f"cp {filename} {filename}_patched")


arch = input("[?] What is the arch of the libc? (32/64) ")
if arch not in archs:
    print("[x] Invalid arch type!")
    exit(-1)

ver = input("[?] What is the version of the libc? (2.23/2.27/2.31/2.34) ")
if ver not in vers:
    print("[x] Invalid libc version!")
    exit(-1)
cwd = os.getcwd()
print(cwd)
# patch file
print(f"patchelf set-interpreter libc.so.6  ~/tools/glibc-all-in-one/libs/x{arch}_{ver}/ld-{ver}.so {cwd}/{filename}_patched")
os.system(f"patchelf --set-interpreter ~/tools/glibc-all-in-one/libs/x{arch}_{ver}/ld-{ver}.so {cwd}/{filename}_patched")
os.system(f"patchelf --set-rpath ~/tools/glibc-all-in-one/libs/x{arch}_{ver} {cwd}/{filename}_patched")