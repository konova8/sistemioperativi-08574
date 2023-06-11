import os

process_list = {}

for s in os.listdir("/proc/"):
    try:
        s = int(s)
        process_list[s] = len(os.listdir(f"/proc/{s}/fd/"))
    except:
        pass

process_list = [(k, process_list[k]) for k in process_list.keys()]

process_list = sorted(process_list, key=lambda x: x[1], reverse=True)

for pair in process_list:
    print(f"Process with pid: {pair[0]} has {pair[1]} file descriptor")


