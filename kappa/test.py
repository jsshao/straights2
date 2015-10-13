import subprocess

out1 = ""
out2 = ""

for i in range(-1, 1):
    for j in range(-1, 1):
        p = subprocess.Popen(["./a.out", str(i), str(j)], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        out1, poo = p.communicate()
        p = subprocess.Popen(["./correct2", str(i), str(j)], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        out2, poo = p.communicate()
        p = subprocess.Popen(["diff",  "out1",  "out2"], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        op, gg = p.communicate()
        print op, gg
