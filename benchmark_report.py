import matplotlib.pyplot as plt

a=[]

avg=sum(a)/len(a)
plt.plot(a)
plt.plot([avg for x in range(len(a))])
plt.show()
