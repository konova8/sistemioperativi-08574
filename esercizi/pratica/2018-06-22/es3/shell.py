import subprocess

user_input = ''
while (user_input != 'logout'):
    try:
        user_input = input().split(' ')
    except:
        break
    #print(user_input)
    subprocess.run(user_input, shell=False)
    
