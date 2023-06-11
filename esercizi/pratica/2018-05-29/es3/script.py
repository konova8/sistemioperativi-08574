import os

d = {}
for e in os.listdir('/proc/'):
    try:
        f = open(f'/proc/{e}/status', 'r')
        d[e] = [e for e in f.readlines() if e[0:4] == 'Uid:'][0]
    except:
        pass

print(d)

uid_reale = {}
uid_effettivo = {}
uid_salvato = {}
uid_fs = {}

all_uid = {}
for elem in d.values():
    elem = elem.replace('\n', '').replace('Uid:', '').split('\t')[1:]
    print(elem)
    all_uid[elem[0]] = 0
    all_uid[elem[1]] = 0
    all_uid[elem[2]] = 0
    all_uid[elem[3]] = 0

    uid_reale[elem[0]] = uid_reale.get(elem[0], 0) + 1
    uid_effettivo[elem[1]] = uid_effettivo.get(elem[1], 0) + 1
    uid_salvato[elem[2]] = uid_salvato.get(elem[2], 0) + 1
    uid_fs[elem[3]] = uid_fs.get(elem[3], 0) + 1

print(uid_reale)
print(list(all_uid.keys()))

for uid in all_uid.keys():
    print(f'{uid} {uid_reale[uid]} {uid_effettivo[uid]} {uid_salvato[uid]} {uid_fs[uid]}')
