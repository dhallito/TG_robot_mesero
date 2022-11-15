from algoritmo_a_estrella import *
from queue import Queue
###         'N':{'distancia':[A---,B---,C---,D---,E---,F---,G---,H---,I---],'angulo':[A---, B---, C---, D---, E---, F---, G---,H---,I---],'posicion':[x,y]}
grafico = { 'A':{'distancia':[None,None,1.00,None,None,None,None,None,None],'angulo':[None, None, 1.57, None, None, None, None,None,None],'x':0.00,'y':-0.70},
            'B':{'distancia':[None,None,1.00,None,1.00,None,None,None,None],'angulo':[None, None, 0.00, None, 1.57, None, None,None,None],'x':-1.00,'y':0.00},
            'C':{'distancia':[1.00,1.00,None,1.00,None,0.80,None,None,None],'angulo':[-1.57,3.14, None, 0.00, None, 1.57, None,None,None],'x':0.00,'y':0.00},
            'D':{'distancia':[None,None,1.00,None,None,None,1.20,None,None],'angulo':[None, None, 3.14, None, None, None, 1.57,None,None],'x':1.00,'y':0.00},
            'E':{'distancia':[None,1.00,None,None,None,None,None,1.00,None],'angulo':[None,-1.57, None, None, None, None, None,1.57,None],'x':-1.00,'y':1.00},
            'F':{'distancia':[None,None,0.80,None,None,None,None,None,1.20],'angulo':[None, None,-1.57, None, None, None, None,None,1.57],'x':0.00,'y':0.80},
            'G':{'distancia':[None,None,None,1.20,None,None,None,None,1.28],'angulo':[None, None, None,-1.57, None, None, None,None,2.47],'x':1.00,'y':1.20},
            'H':{'distancia':[None,None,None,None,1.00,None,None,None,1.00],'angulo':[None, None, None, None,-1.57, None, None,None,0.00],'x':-1.00,'y':2.00},
            'I':{'distancia':[None,None,None,None,None,1.20,1.28,1.00,None],'angulo':[None, None, None, None, None,-1.57,-0.67,3.14,None],'x':0.00,'y':2.00}
}

a_estrella = A_Estrella(grafico)
'''for i in grafico:
    for j in grafico:
        print(a_estrella.buscar_ruta(i,j, 3.14))'''
print(a_estrella.buscar_ruta('H','F', np.deg2rad(135), True))
#print(a_estrella.calcular_angulo(135,-90))