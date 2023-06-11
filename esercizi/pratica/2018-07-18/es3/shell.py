import os
import subprocess

user_input = ''
while (user_input != 'logout'):
    print(f'[{os.getcwd()}]$ ', end='')
    try:
        user_input = input()
    except:
        break
    user_input = user_input.split(' ')
    if user_input[0] == 'cd':
        os.chdir(user_input[1])
    else:
        subprocess.run(user_input, shell=False)
    
print()
