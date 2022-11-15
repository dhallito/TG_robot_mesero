import codecs
import serial
import time
import pandas as pd
import datetime
import keyboard

while True:
    if keyboard.is_pressed('s'):
        break
print('Inicio')
serial_object = serial.Serial('COM3', 115200, timeout=None)
time.sleep(1)
writer = pd.ExcelWriter('entrada_escalon_cambio10%_16khz.xlsx', engine='xlsxwriter')
data = []

while True:
    data_new = []
    if keyboard.is_pressed('q'):
        break
    elif serial_object.in_waiting > 0:
        data_now = serial_object.readline().decode().split(',')
        for i in data_now:
            data_new.append(float(i))
        data.append(data_new)
print(len(data))
print('Fin')

df = pd.DataFrame(data)

df.to_excel(writer, sheet_name='Sheet1', index=False)

writer.save()