import matplotlib.pyplot as plt

w = open('mfcc.dat')
d = w.read()

plt.plot(list(map(lambda x: float(x), d.split('\n')[:-1])))
plt.show()