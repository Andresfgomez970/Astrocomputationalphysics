import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

def lineal(x, m, b):
	return m * x + b

data = np.loadtxt("data2.txt").transpose()

nV = 3
nI = 7

Vmag = data[nV:nV+1,:][0]
Imag = data[nI:nI+1,:][0]

########## contidions seeing graph
con1 = Vmag>18.5
con4 = Vmag<24
con2 = (Vmag-Imag)<1.5
con3 = (Vmag-Imag)>0.3
data2 = data[:,con1*con2*con3*con4]

VmagMS = data2[nV:nV+1,:][0]
ImagMS = data2[nI:nI+1,:][0]

### plot of the graph
plt.title("HR Diagram")
plt.ylim(10,25) 
plt.xlim(-0.5,3) 
plt.gca().invert_yaxis()
plt.plot(Vmag-Imag, Vmag,'.', label="All other stars")
plt.plot(VmagMS-ImagMS, VmagMS,'r.', label="Main Sequence Stars")
plt.legend(loc="best")
plt.xlabel("V-I")
plt.ylabel("V")
plt.savefig("MS_diagram.png")
plt.show()

d = 8.8e3
Ls = 10**( (4.83 - VmagMS + 5*np.log(d/10.)/np.log(10) )/(2.5) ) 
Ms = (Ls)**(1/3.5)
num_bins= int ( len(Ms)**(1/3.) ) 
n, bins, patches = plt.hist(Ms, 40, facecolor='blue', alpha=0.75, histtype="step")

minval = 12
print(bins[minval])
popt, pcov = curve_fit(lineal, np.log(bins[minval:-1])/np.log(10) , np.log(n[minval:])/np.log(10) )
print(popt[0], popt[1])
print(pcov[0][0]**0.5)
plt.plot( bins[minval:],  bins[minval:]**popt[0]*10**popt[1] , 'r-', label='fit from 0.6 Msun; γ =-2.2 +/- 0.1')


minval = 0
popt, pcov = curve_fit(lineal, np.log(bins[minval:-1])/np.log(10) , np.log(n[minval:])/np.log(10) )
print(popt[0], popt[1])
print(pcov[0][0]**0.5)
plt.title("Iinitial Mass Function Approximation")
plt.ylabel("Log( Nstars/dm[Msun] )")
plt.xlabel( "log(M [Msun]) " )
plt.plot( bins[minval:],  bins[minval:]**popt[0]*10**popt[1] , 'g-', label='general fit from 0.31 Msun; γ =-1.5 +/- 0.1')
plt.legend(loc="best")

print(bins[-1])
plt.xscale('log')
plt.yscale('log')
plt.savefig("IMF.png")

plt.show()
