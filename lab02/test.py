import numpy as np
import matplotlib.pyplot as plt

plt.figure(figsize=(13,13),dpi=80)
x_list=[]
y_list=[]
file=open("/Users/kylinchan/Documents/AlgorithmLab/lab04_KylinChen/OUT.txt")
list=file.readlines()
for i in list:
    tmp=i.split()
    for j in range(len(tmp)):
        if j%2==0:
            x_list.append(tmp[j].strip(',').strip('(').strip(')'))
        else:
            y_list.append(tmp[j].strip(',').strip('(').strip(')'))


plt.grid()

plt.plot(x_list, y_list,lw=2)

plt.show()