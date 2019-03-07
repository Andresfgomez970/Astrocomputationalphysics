# -*- coding: utf-8 -*-
import numpy as np 
import matplotlib.pyplot as plt
# la rutina polyfit le hace un ajuste lineal en una linea

def calmin(xr,yr):
    xr2 = xr**2
    xryr = xr*yr
    yr2 = yr**2
    #(1)                                                                                                             
    sxr = xr.sum()
    #(2)                                                                                                             
    syr = yr.sum()
    #(3)                                                                                                             
    sxr2 = xr2.sum()
    #(4)                                                                                                             
    sxryr= xryr.sum()
    #(6)                                                                                                             
    syr2 = yr2.sum()
    #defining a and b                                                                                                
    #b = (syr*sxr2-sxr*sxryr)/(len(xr)*sxr2-sxr**2)
    m = (len(xr)*sxryr-sxr*syr)/(len(xr)*sxr2-sxr**2)
    b = (syr-m*sxr)/len(xr)
    #(5)                                                                                                             
    eq = (yr-b-m*xr)**2
    seq = eq.sum()
    #def S                                                                                                          
    S = np.sqrt(seq/(len(xr)-2))
    #defining delta(a) and delta(b)                                                                                  
    erb = np.sqrt(sxr2/(len(xr)*sxr2-sxr**2))*S
    erm = np.sqrt(len(xr)/(len(xr)*sxr2-sxr**2))*S
    return m,b,erm,erb #b: intercept, m: slope, erb:error b , erm: error m    

# Graph to ilustrate the fractal structure 
def plt1():
    plt.plot(range(200),h,'r',label = 'Estructura Fractal')
    plt.ylim(0,60)
    plt.xlim(0,200)
    #plt.title(r'Técnica de conteo en cajas')
    plt.legend(loc='best')
    plt.savefig('Graph2.jpg')
    plt.show()
    plt.close()


# Graph to ilustrate the lineal adjustement by least squares mede to obtain 
# the fratal dimension
def plt2():
    plt.figure()
    plt.plot(lmm2,lbox2,'ro',label='Datos')
    plt.plot(xs,ys,'b-',label = u'Dimensión fractal (pendiente) ≈ %.3f'%(m))
    plt.xlabel(r'Log(1/$\epsilon$)')
    plt.ylabel(r'Log( N($\epsilon$) ) ')
    plt.xlim(1.6,3.2)
    plt.title("Determinación de dimensión fractal")
    plt.legend(loc='best')
    plt.grid()
    plt.savefig('Graph1.jpg')
    plt.show()
    plt.close()


#Depostion made to get the fractal structure taking the values that are 
# at the upper part.

length = 200   
n = 5000
h = np.zeros(length)
maxim = []
INDEX = []
H = []

for i in range(n):
    index = np.random.randint(0,200)
    if index == 0:
        if h[index+1]>h[index]:
            h[index]=h[index+1]
        else:
            h[index] += 1
    elif index == 199:
        if h[index-1]>h[index]:
            h[index]=h[index-1]
        else:
            h[index] += 1
    else:
        if h[index]<h[index+1] and h[index]<h[index-1]:
            h[index] = np.max([h[index+1],h[index-1]])
        else:
            h[index] += 1

MM = range(5,25)
Boxes = []

plt.figure()

for M in MM:
    boxes = 0
    for j in range(M):
        dx = 200./M
        dy = 60./M

        if M == MM[-1]:
            plt.plot([0,200],[dy*(j+1),dy*(j+1)],'k-')      #Horizontal lines
            plt.plot([dx*(j+1),dx*(j+1)],[0,60],'k-')       #Vertical lines
        for m in range(M):
            for i in range(int(m*dx),int((m+1)*dx)):
                if h[i]<60-dy*j and h[i]>60-dy*(j+1):
                    boxes+=1
                    break

    Boxes.append(boxes)


plt1()

lmm2 = np.log(MM)
lbox2 = np.log(Boxes)

####### Slope using least squares ->  Fractal dimension

m,b,erm,erb = calmin(lmm2,lbox2)
xs = np.linspace(min(lmm2)-0.2,max(lbox2),3)
ys = m*xs +b

plt2()