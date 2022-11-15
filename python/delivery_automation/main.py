from tkinter import *

def intento():
    pass


ventana=Tk()

width = 1600
height = 800
font=("Helvetica", 16)

ventana.title('Restaurante David Cuscagua')
#ventana.geometry(f"{width}x{height}")
ventana.resizable(False, False)

########## ROBOT ##########
label_titulo_robot = Label(ventana, text="ROBOT", font=font, borderwidth=4, relief='groove')
label_titulo_robot.grid(column=0, row=0, columnspan=2, sticky=EW, padx=5, pady=5)

label_titulo_arriba = Label(ventana, text="Piso Arriba ->", font=font)
label_titulo_arriba.grid(column=0, row=1, sticky=EW, padx=5, pady=5)

label_pedido_arriba = Label(ventana, text="Mesa D", font=font)
label_pedido_arriba.grid(column=1, row=1, sticky=EW, padx=5, pady=5)

label_titulo_abajo = Label(ventana, text="Piso Abajo ->", font=font)
label_titulo_abajo.grid(column=0, row=2, sticky=EW, padx=5, pady=5)

label_pedido_abajo = Label(ventana, text="Mesa E", font=font)
label_pedido_abajo.grid(column=1, row=2, sticky=EW, padx=5, pady=5)

label_estado_robot = Label(ventana, text="Disponible", font=font)
label_estado_robot.grid(column=0, row=3, sticky=EW, padx=5, pady=5)

label_ubicacion_robot = Label(ventana, text="En D", font=font)
label_ubicacion_robot.grid(column=1, row=3, sticky=EW, padx=5, pady=5)

button_llamar = Button(ventana, text="Llamar Robot")
button_llamar.grid(column=0, row=4, columnspan=2, sticky=EW, padx=5, pady=5)

button_enviar = Button(ventana, text="Enviar Robot")
button_enviar.grid(column=0, row=5, columnspan=2, sticky=EW, padx=5, pady=5)

########## VER PEDIDO ##########
label_titulo_pedido = Label(ventana, text="PEDIDO MESA D", font=font, borderwidth=4, relief='groove')
label_titulo_pedido.grid(column=2, row=0, sticky=EW, padx=5, pady=5)

pedido = """Hamburguesa + Jugo
Pizza + Soda
Perro + Agua"""
label_info_pedido = Label(ventana, text=pedido, font=font)
label_info_pedido.grid(column=2, row=1, rowspan=4, sticky=NS, padx=5, pady=5)

button_actualizar = Button(ventana, text="Actualizar")
button_actualizar.grid(column=2, row=5, sticky=EW, padx=5, pady=5)

########## MESAS ##########
## Mesa D ##
label_titulo_D = Label(ventana, text="MESA D", font=font, borderwidth=4, relief='groove')
label_titulo_D.grid(column=3, row=0, columnspan=3, sticky=EW, padx=5, pady=5)

label_estado_D = Label(ventana, text="Terminado", font=font)
label_estado_D.grid(column=3, row=1, columnspan=3, sticky=EW, padx=5, pady=5)

button_ver_D = Button(ventana, text="Ver")
button_ver_D.grid(column=3, row=2, sticky=EW, padx=5, pady=5)

button_cocinar_D = Button(ventana, text="Cocinar")
button_cocinar_D.grid(column=4, row=2, sticky=EW, padx=0, pady=5)

button_montar_D = Button(ventana, text="Montar")
button_montar_D.grid(column=5, row=2, sticky=EW, padx=5, pady=5)

## Mesa E ##
label_titulo_E = Label(ventana, text="MESA E", font=font, borderwidth=4, relief='groove')
label_titulo_E.grid(column=3, row=3, columnspan=3, sticky=EW, padx=5, pady=5)

label_estado_E = Label(ventana, text="Terminado", font=font)
label_estado_E.grid(column=3, row=4, columnspan=3, sticky=EW, padx=5, pady=5)

button_ver_E = Button(ventana, text="Ver")
button_ver_E.grid(column=3, row=5, sticky=EW, padx=5, pady=5)

button_cocinar_E = Button(ventana, text="Cocinar")
button_cocinar_E.grid(column=4, row=5, sticky=EW, padx=0, pady=5)

button_montar_E = Button(ventana, text="Montar")
button_montar_E.grid(column=5, row=5, sticky=EW, padx=5, pady=5)

## Mesa F ##
label_titulo_F = Label(ventana, text="MESA F", font=font, borderwidth=4, relief='groove')
label_titulo_F.grid(column=6, row=0, columnspan=3, sticky=EW, padx=5, pady=5)

label_estado_F = Label(ventana, text="Terminado", font=font)
label_estado_F.grid(column=6, row=1, columnspan=3, sticky=EW, padx=5, pady=5)

button_ver_F = Button(ventana, text="Ver")
button_ver_F.grid(column=6, row=2, sticky=EW, padx=5, pady=5)

button_cocinar_F = Button(ventana, text="Cocinar")
button_cocinar_F.grid(column=7, row=2, sticky=EW, padx=0, pady=5)

button_montar_F = Button(ventana, text="Montar")
button_montar_F.grid(column=8, row=2, sticky=EW, padx=5, pady=5)

## Mesa G ##
label_titulo_G = Label(ventana, text="MESA G", font=font, borderwidth=4, relief='groove')
label_titulo_G.grid(column=6, row=3, columnspan=3, sticky=EW, padx=5, pady=5)

label_estado_G = Label(ventana, text="Terminado", font=font)
label_estado_G.grid(column=6, row=4, columnspan=3, sticky=EW, padx=5, pady=5)

button_ver_G = Button(ventana, text="Ver")
button_ver_G.grid(column=6, row=5, sticky=EW, padx=5, pady=5)

button_cocinar_G = Button(ventana, text="Cocinar")
button_cocinar_G.grid(column=7, row=5, sticky=EW, padx=0, pady=5)

button_montar_G = Button(ventana, text="Montar")
button_montar_G.grid(column=8, row=5, sticky=EW, padx=5, pady=5)

## Mesa H ##
label_titulo_H = Label(ventana, text="MESA H", font=font, borderwidth=4, relief='groove')
label_titulo_H.grid(column=9, row=0, columnspan=3, sticky=EW, padx=5, pady=5)

label_estado_H = Label(ventana, text="Terminado", font=font)
label_estado_H.grid(column=9, row=1, columnspan=3, sticky=EW, padx=5, pady=5)

button_ver_H = Button(ventana, text="Ver")
button_ver_H.grid(column=9, row=2, sticky=EW, padx=5, pady=5)

button_cocinar_H = Button(ventana, text="Cocinar")
button_cocinar_H.grid(column=10, row=2, sticky=EW, padx=0, pady=5)

button_montar_H = Button(ventana, text="Montar")
button_montar_H.grid(column=11, row=2, sticky=EW, padx=5, pady=5)

ventana.mainloop()