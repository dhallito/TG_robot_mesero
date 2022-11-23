from tkinter import *
import requests
import json
from algoritmo_a_estrella import *
from queue import Queue

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

ip = "http://192.168.0.100:5000/"

ip_robot = "http://192.168.0.101/"

pedido = ""


global estados
global contador
global mesas_entregando
global estado_robot
global entregando_pedidos

entregando_pedidos = False


estado_robot = 'disponible'

def intento():
    pass

def actualizar_data():
    global estados
    global entregando_pedidos
    url = ip
    url += "obtener_estado"
    PARAMS = {}
    r = requests.get(url=url, params = PARAMS)
    estados = r.json()
    label_estado_D.config(text = estados['D'])
    label_estado_E.config(text = estados['E'])
    label_estado_F.config(text = estados['F'])
    label_estado_G.config(text = estados['G'])
    label_estado_H.config(text = estados['H'])
    pedidos_montados = ['','','','','']
    aux = 0
    for clave in estados:
        if estados[clave] == 'EN CAMINO':
            pedidos_montados[aux] = f'Mesa {clave}'
            aux += 1
    if entregando_pedidos == True:
        label_estado_robot.config(text = 'Ocupado')
    else:
        label_estado_robot.config(text = 'Disponible')
    url = ip_robot
    url += ""
    PARAMS = {'comando':'leer'}
    r = requests.get(url=url, params = PARAMS)
    variables = r.json()
    nodo_actual = variables['nodo_actual']
    label_ubicacion_robot.config(text = f"En {nodo_actual}")
    label_pedido_abajo.config(text = pedidos_montados[1])
    label_pedido_arriba.config(text = pedidos_montados[0])
    ventana.after(2000, actualizar_data)
    pass

def enviar_robot():
    global contador
    global mesas_entregando
    global estados
    global estado_robot
    global entregando_pedidos
    if entregando_pedidos == False:
        url = ip
        url += "obtener_estado"
        PARAMS = {}
        r = requests.get(url=url, params = PARAMS)
        estados = r.json()
        label_estado_D.config(text = estados['D'])
        label_estado_E.config(text = estados['E'])
        label_estado_F.config(text = estados['F'])
        label_estado_G.config(text = estados['G'])
        label_estado_H.config(text = estados['H'])
        mesas_entregando = []
        contador = -1
        for clave in estados:
            if estados[clave] == 'EN CAMINO':
                mesas_entregando.append(clave)
                contador += 1
                pass
        if contador >= 0:
            entregando_pedidos = True
        
    else:
        proximo_nodo = mesas_entregando[contador]
        if estados[proximo_nodo] == 'TERMINADO':
            contador += -1
            estado_robot = 'disponible'
            print(f"Pedido entregado mesa {proximo_nodo}")
        else:
            if estado_robot == 'disponible':
                print(f"Pedido enviado mesa {proximo_nodo}")
                url = ip_robot
                url += ""
                PARAMS = {'comando':'leer'}
                r = requests.get(url=url, params = PARAMS)
                variables = r.json()
                nodo_actual = variables['nodo_actual']
                angulo_absoluto = float(variables['angulo_absoluto'])
                ruta = a_estrella.buscar_ruta(nodo_actual, proximo_nodo, angulo_absoluto, True)['ruta']
                ruta_string = ""
                for i in ruta: ruta_string += i
                print(ruta_string)
                url = ip_robot
                url += ""
                PARAMS = {'comando':'escribir', 'cantidad': len(ruta_string), 'ruta': ruta_string}
                r = requests.get(url=url, params = PARAMS)
                estado_robot = 'ocupado'
            pass
        if contador == -1:
            entregando_pedidos = False
        ventana.after(3000, enviar_robot)

def llamar_robot():
    global contador
    global mesas_entregando
    global estados
    global estado_robot
    global entregando_pedidos
    if entregando_pedidos == False:
        print(f"Regresar a cocina")
        url = ip_robot
        url += ""
        PARAMS = {'comando':'leer'}
        r = requests.get(url=url, params = PARAMS)
        variables = r.json()
        nodo_actual = variables['nodo_actual']
        angulo_absoluto = float(variables['angulo_absoluto'])
        ruta = a_estrella.buscar_ruta(nodo_actual, 'A', angulo_absoluto, True)['ruta']
        ruta_string = ""
        for i in ruta: ruta_string += i
        print(ruta_string)
        url = ip_robot
        url += ""
        PARAMS = {'comando':'escribir', 'cantidad': len(ruta_string), 'ruta': ruta_string}
        r = requests.get(url=url, params = PARAMS)
        pass
    

#################### Ver ################

def ver_mesaD():
    url = ip
    url += "obtener_orden/D"
    PARAMS = {}
    r = requests.get(url=url, params = PARAMS)
    data_list = list(r.json()["pedidos"])
    pedido = ""
    for data in data_list:
        i =  json.loads(data)
        pedido += f"""{i["alimento"]} + {i["bebida"]}
"""
    label_titulo_pedido.config(text = "Pedido Mesa D")
    label_info_pedido.config(text=pedido)

def ver_mesaE():
    url = ip
    url += "obtener_orden/E"
    PARAMS = {}
    r = requests.get(url=url, params = PARAMS)
    data_list = list(r.json()["pedidos"])
    pedido = ""
    for data in data_list:
        i =  json.loads(data)
        pedido += f"""{i["alimento"]} + {i["bebida"]}
"""
    label_titulo_pedido.config(text = "Pedido Mesa E")
    label_info_pedido.config(text=pedido)

def ver_mesaF():
    url = ip
    url += "obtener_orden/F"
    PARAMS = {}
    r = requests.get(url=url, params = PARAMS)
    data_list = list(r.json()["pedidos"])
    pedido = ""
    for data in data_list:
        i =  json.loads(data)
        pedido += f"""{i["alimento"]} + {i["bebida"]}
"""
    label_titulo_pedido.config(text = "Pedido Mesa F")
    label_info_pedido.config(text=pedido)

def ver_mesaG():
    url = ip
    url += "obtener_orden/G"
    PARAMS = {}
    r = requests.get(url=url, params = PARAMS)
    data_list = list(r.json()["pedidos"])
    pedido = ""
    for data in data_list:
        i =  json.loads(data)
        pedido += f"""{i["alimento"]} + {i["bebida"]}
"""
    label_titulo_pedido.config(text = "Pedido Mesa G")
    label_info_pedido.config(text=pedido)

def ver_mesaH():
    url = ip
    url += "obtener_orden/H"
    PARAMS = {}
    r = requests.get(url=url, params = PARAMS)
    data_list = list(r.json()["pedidos"])
    pedido = ""
    for data in data_list:
        i =  json.loads(data)
        pedido += f"""{i["alimento"]} + {i["bebida"]}
"""
    label_titulo_pedido.config(text = "Pedido Mesa H")
    label_info_pedido.config(text=pedido)

################ Cocinar ####################

def cocinar_mesaD():
    url = ip
    url += "cocinar_orden/D"
    PARAMS = {}
    requests.get(url=url, params = PARAMS)

def cocinar_mesaE():
    url = ip
    url += "cocinar_orden/E"
    PARAMS = {}
    requests.get(url=url, params = PARAMS)

def cocinar_mesaF():
    url = ip
    url += "cocinar_orden/F"
    PARAMS = {}
    requests.get(url=url, params = PARAMS)

def cocinar_mesaG():
    url = ip
    url += "cocinar_orden/G"
    PARAMS = {}
    requests.get(url=url, params = PARAMS)

def cocinar_mesaH():
    url = ip
    url += "cocinar_orden/H"
    PARAMS = {}
    requests.get(url=url, params = PARAMS)

################ Montar ####################

def montar_mesaD():
    url = ip
    url += "montar_orden/D"
    PARAMS = {}
    requests.get(url=url, params = PARAMS)
    
def montar_mesaE():
    url = ip
    url += "montar_orden/E"
    PARAMS = {}
    requests.get(url=url, params = PARAMS)

def montar_mesaF():
    url = ip
    url += "montar_orden/F"
    PARAMS = {}
    requests.get(url=url, params = PARAMS)

def montar_mesaG():
    url = ip
    url += "montar_orden/G"
    PARAMS = {}
    requests.get(url=url, params = PARAMS)

def montar_mesaH():
    url = ip
    url += "montar_orden/H"
    PARAMS = {}
    requests.get(url=url, params = PARAMS)

#########################################

ventana=Tk()

width = 1600
height = 800
font=("Helvetica", 16)

ventana.title('Restaurante David Cuscagua')
#ventana.geometry(f"{width}x{height}")
ventana.resizable(False, False)
ventana.after(2000, actualizar_data)


########## ROBOT ##########
label_titulo_robot = Label(ventana, text="ROBOT", font=font, borderwidth=4, relief='groove')
label_titulo_robot.grid(column=0, row=0, columnspan=2, sticky=EW, padx=5, pady=5)

label_titulo_arriba = Label(ventana, text="Orden 1 ->", font=font)
label_titulo_arriba.grid(column=0, row=1, sticky=EW, padx=5, pady=5)

label_pedido_arriba = Label(ventana, text="", font=font)
label_pedido_arriba.grid(column=1, row=1, sticky=EW, padx=5, pady=5)

label_titulo_abajo = Label(ventana, text="Orden 2 ->", font=font)
label_titulo_abajo.grid(column=0, row=2, sticky=EW, padx=5, pady=5)

label_pedido_abajo = Label(ventana, text="", font=font)
label_pedido_abajo.grid(column=1, row=2, sticky=EW, padx=5, pady=5)

label_estado_robot = Label(ventana, text="Disponible", font=font)
label_estado_robot.grid(column=0, row=3, sticky=EW, padx=5, pady=5)

label_ubicacion_robot = Label(ventana, text="En D", font=font)
label_ubicacion_robot.grid(column=1, row=3, sticky=EW, padx=5, pady=5)

button_llamar = Button(ventana, text="Llamar Robot", command=llamar_robot)
button_llamar.grid(column=0, row=4, columnspan=2, sticky=EW, padx=5, pady=5)

button_enviar = Button(ventana, text="Enviar Robot", command=enviar_robot)
button_enviar.grid(column=0, row=5, columnspan=2, sticky=EW, padx=5, pady=5)

########## VER PEDIDO ##########
label_titulo_pedido = Label(ventana, text="PEDIDO MESA", font=font, borderwidth=4, relief='groove')
label_titulo_pedido.grid(column=2, row=0, sticky=EW, padx=5, pady=5)

label_info_pedido = Label(ventana, text=pedido, font=font)
label_info_pedido.grid(column=2, row=1, rowspan=4, sticky=NS, padx=5, pady=5)

button_actualizar = Button(ventana, text="Actualizar", command=actualizar_data)
button_actualizar.grid(column=2, row=5, sticky=EW, padx=5, pady=5)

########## MESAS ##########
## Mesa D ##
label_titulo_D = Label(ventana, text="MESA D", font=font, borderwidth=4, relief='groove')
label_titulo_D.grid(column=3, row=0, columnspan=3, sticky=EW, padx=5, pady=5)

label_estado_D = Label(ventana, text="TERMINADO", font=font)
label_estado_D.grid(column=3, row=1, columnspan=3, sticky=EW, padx=5, pady=5)

button_ver_D = Button(ventana, text="Ver", command=ver_mesaD)
button_ver_D.grid(column=3, row=2, sticky=EW, padx=5, pady=5)

button_cocinar_D = Button(ventana, text="Cocinar", command=cocinar_mesaD)
button_cocinar_D.grid(column=4, row=2, sticky=EW, padx=0, pady=5)

button_montar_D = Button(ventana, text="Montar", command=montar_mesaD)
button_montar_D.grid(column=5, row=2, sticky=EW, padx=5, pady=5)

## Mesa E ##
label_titulo_E = Label(ventana, text="MESA E", font=font, borderwidth=4, relief='groove')
label_titulo_E.grid(column=3, row=3, columnspan=3, sticky=EW, padx=5, pady=5)

label_estado_E = Label(ventana, text="TERMINADO", font=font)
label_estado_E.grid(column=3, row=4, columnspan=3, sticky=EW, padx=5, pady=5)

button_ver_E = Button(ventana, text="Ver", command=ver_mesaE)
button_ver_E.grid(column=3, row=5, sticky=EW, padx=5, pady=5)

button_cocinar_E = Button(ventana, text="Cocinar", command=cocinar_mesaE)
button_cocinar_E.grid(column=4, row=5, sticky=EW, padx=0, pady=5)

button_montar_E = Button(ventana, text="Montar", command=montar_mesaE)
button_montar_E.grid(column=5, row=5, sticky=EW, padx=5, pady=5)

## Mesa F ##
label_titulo_F = Label(ventana, text="MESA F", font=font, borderwidth=4, relief='groove')
label_titulo_F.grid(column=6, row=0, columnspan=3, sticky=EW, padx=5, pady=5)

label_estado_F = Label(ventana, text="TERMINADO", font=font)
label_estado_F.grid(column=6, row=1, columnspan=3, sticky=EW, padx=5, pady=5)

button_ver_F = Button(ventana, text="Ver", command=ver_mesaF)
button_ver_F.grid(column=6, row=2, sticky=EW, padx=5, pady=5)

button_cocinar_F = Button(ventana, text="Cocinar", command=cocinar_mesaF)
button_cocinar_F.grid(column=7, row=2, sticky=EW, padx=0, pady=5)

button_montar_F = Button(ventana, text="Montar", command=montar_mesaF)
button_montar_F.grid(column=8, row=2, sticky=EW, padx=5, pady=5)

## Mesa G ##
label_titulo_G = Label(ventana, text="MESA G", font=font, borderwidth=4, relief='groove')
label_titulo_G.grid(column=6, row=3, columnspan=3, sticky=EW, padx=5, pady=5)

label_estado_G = Label(ventana, text="TERMINADO", font=font)
label_estado_G.grid(column=6, row=4, columnspan=3, sticky=EW, padx=5, pady=5)

button_ver_G = Button(ventana, text="Ver", command=ver_mesaG)
button_ver_G.grid(column=6, row=5, sticky=EW, padx=5, pady=5)

button_cocinar_G = Button(ventana, text="Cocinar", command=cocinar_mesaG)
button_cocinar_G.grid(column=7, row=5, sticky=EW, padx=0, pady=5)

button_montar_G = Button(ventana, text="Montar", command=montar_mesaG)
button_montar_G.grid(column=8, row=5, sticky=EW, padx=5, pady=5)

## Mesa H ##
label_titulo_H = Label(ventana, text="MESA H", font=font, borderwidth=4, relief='groove')
label_titulo_H.grid(column=9, row=0, columnspan=3, sticky=EW, padx=5, pady=5)

label_estado_H = Label(ventana, text="TERMINADO", font=font)
label_estado_H.grid(column=9, row=1, columnspan=3, sticky=EW, padx=5, pady=5)

button_ver_H = Button(ventana, text="Ver", command=ver_mesaH)
button_ver_H.grid(column=9, row=2, sticky=EW, padx=5, pady=5)

button_cocinar_H = Button(ventana, text="Cocinar", command=cocinar_mesaH)
button_cocinar_H.grid(column=10, row=2, sticky=EW, padx=0, pady=5)

button_montar_H = Button(ventana, text="Montar", command=montar_mesaH)
button_montar_H.grid(column=11, row=2, sticky=EW, padx=5, pady=5)

ventana.mainloop()