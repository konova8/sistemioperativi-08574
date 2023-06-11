import os
import sys

def main():
    syscall = []
    file = open("/usr/include/x86_64-linux-gnu/asm/unistd_64.h")
    for arg in file:
        if arg.find("__NR") != -1:
            arg = arg[len("#define __NR_"):]
            arg = arg.split(" ")
            arg[1]=int(arg[1].split("\n")[0])
            syscall.append(arg)
    programm = """#include <stdio.h>\n#include <stdlib.h>\n#include <string.h>\n\tchar *syscall_name[] = {\n"""
    i = 0
    j = 0
    for i in range(0, syscall[-1][1] - 1):
        if syscall[j][1] == i:
            programm += f'\t\t"{syscall[j][0]}",\n'
            j+=1
        else:
            programm += f'\t\t"undefined",\n'
    programm = programm[:-2]
    programm += "\n\t};\n"
    file_c = os.open("syscall_name_created.c", os.O_RDWR|os.O_CREAT)
    os.write(file_c, programm.encode())
    os.close(file_c)


if __name__ == '__main__':
    main()
