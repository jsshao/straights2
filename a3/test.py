import random

data = range(1000)
random.shuffle(data)
with open('test', 'w') as f:
    f.write(str(len(data)))
    f.write(' ')
    for num in data:
        f.write(str(num))
        f.write(' ')
