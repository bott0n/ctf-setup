# Crack/Hash
    cyberChef: https://gchq.github.io/CyberChef/
    cracksataion: https://crackstation.net/
    john:
        ssh2john
        zip2john
    hashcat
# Reserve/Pwn/binary
    binaryNinja
    Disasmbly:
        IDA
        Hopper
        gdb
        redare2
    ROPgadget
    libc-database: https://libc.blukat.me/
    glibc-all-in-one
    patchelf:
        Change libc:
        patchelf --set-rpath ~/utils/glibc-all-in-one/libs/
        patchelf --set-interpreter ~/utils/glibc-all-in-one/libs/$ld
        

# Web
    burpsuite
    hookbin - http capture and inspect
    Playload:
        https://github.com/swisskyrepo/PayloadsAllTheThings
        https://github.com/w181496/Web-CTF-Cheatsheet

# Forensics
    Network:
        wireshark - pcap file
    Disk:
        testdisk
        photorec (image recover)
    DNS/HOST/Cert:
        censys.io: https://censys.io/certificates?q=jctf.pro

# Misc
    Docker
    Image:
        steghide
        stegsolve
        steganography decode - http://stylesuxx.github.io/steganography/
        exiftool  
        binwalk - analyzing, reverse engineering, and extracting firmware images
            foremost
    Memory:
        volatility - Volatile memory extraction utility framework
# Pentest
    Windows:
        Remmina - MSRDP
        winpeas - Scan vlun in windows: https://github.com/carlospolop/privilege-escalation-awesome-scripts-suite/tree/master/winPEAS
    Wordlists:
        /usr/share/dirb/wordlists
        /usr/share/dirbuster/wordlists
        rockyou.txt

    Priv:
        GTFOBins - https://gtfobins.github.io/

    Enum scan:
        nmap - port
        dirbuster/dirb/gobuster - web directory
        nikto - web
        hydra - login system

