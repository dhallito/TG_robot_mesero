from flask import Flask, redirect, url_for, render_template, request, flash, jsonify
from datetime import datetime
from flask_mysqldb import MySQL
import json

app = Flask(__name__)

app.secret_key = 'clave_secreta_flask'

# Conexion DB
app.config['MYSQL_HOST'] = 'localhost'
app.config['MYSQL_USER'] = 'root'
app.config['MYSQL_PASSWORD'] = ''
app.config['MYSQL_DB'] = 'restaurante_tg'

mysql = MySQL(app)

# Context processors

@app.context_processor
def date_now():
    return {
        'now': datetime.utcnow()
    }

# Endpoints

@app.route('/', methods=['GET', 'POST'])
def index():
    if request.method == 'POST':
        mesa = request.form['mesa']
        return redirect(url_for('menu', mesa = mesa))
    return render_template('index.html')

@app.route('/menu', methods=['GET', 'POST'])
@app.route('/menu/<mesa>', methods=['GET', 'POST'])
def menu(mesa = None):
    if mesa == None:
        return redirect(url_for('index'))
    cursor = mysql.connection.cursor()
    cursor.execute(f"SELECT * FROM productos")
    productos = cursor.fetchall()
    cursor.close()

    if request.method == 'POST':
        return redirect(url_for('ordenar', mesa = mesa))
    return render_template('menu.html', mesa=mesa, productos = productos)

@app.route('/ordenar', methods=['GET', 'POST'])
@app.route('/ordenar/<mesa>', methods=['GET', 'POST'])
def ordenar(mesa = None):
    if mesa == None:
        return redirect(url_for('index'))
    cursor = mysql.connection.cursor()
    cursor.execute("SELECT * FROM productos WHERE tipo = 0")
    alimentos = cursor.fetchall()
    cursor.execute("SELECT * FROM productos WHERE tipo = 1")
    bebidas = cursor.fetchall()
    cursor.close()
    if request.method == 'POST':
        return redirect(url_for('mi_orden', mesa = mesa))
    return render_template('ordenar.html', alimentos=alimentos, bebidas=bebidas, mesa = mesa)

@app.route('/ordenar_subir', methods=['GET', 'POST'])
@app.route('/ordenar_subir/<mesa>', methods=['GET', 'POST'])
def ordenar_subir(mesa = None):
    if mesa == None:
        return redirect(url_for('index'))
    if request.method == 'POST':
        alimento = request.form['alimento']
        bebida = request.form['bebida']
        json = '{"alimento":"'+ str(alimento) + '","bebida":"'+ str(bebida) + '"}'
        print(json)
        cursor = mysql.connection.cursor()
        cursor.execute("INSERT INTO pedidos VALUES(NULL, 'ENVIADO', %s, %s)", (mesa, json))
        cursor.connection.commit()
    return redirect(url_for('ordenar', mesa = mesa))

@app.route('/mi_orden', methods=['GET', 'POST'])
@app.route('/mi_orden/<mesa>', methods=['GET', 'POST'])
def mi_orden(mesa=None):
    if mesa == None:
        return redirect(url_for('index'))
    mesa_value = f"'{mesa}'"
    if request.method == 'POST':
        cursor = mysql.connection.cursor()
        cursor.execute(f"UPDATE pedidos SET estado = 'TERMINADO' WHERE mesa = {mesa_value} && estado = 'EN CAMINO'")
        cursor.connection.commit()
        cursor.close()
        return redirect(url_for('index'))
    cursor = mysql.connection.cursor()
    cursor.execute(f"SELECT estado, orden FROM pedidos WHERE estado != 'TERMINADO' && mesa = {mesa_value}")
    pedidos = cursor.fetchall()
    cursor.close()
    print(pedidos)
    pedidos_list = []
    for pedido in pedidos:
        pedidos_list.append([pedido[0], json.loads(pedido[1])])
    return render_template('mi_orden.html', pedidos=pedidos_list, mesa = mesa.replace("'",""))

@app.route('/contacto')
def contacto():
    return render_template('contacto.html')

@app.route('/obtener_orden/<mesa>', methods=['GET'])
def obtener_orden(mesa=None):
    pedidos_list = []
    if mesa == None:
        return jsonify({'pedidos':None})
    mesa_value = f"'{mesa}'"
    cursor = mysql.connection.cursor()
    cursor.execute(f"SELECT estado, orden FROM pedidos WHERE estado != 'TERMINADO' && mesa = {mesa_value}")
    pedidos = cursor.fetchall()
    cursor.close()    
    cursor = mysql.connection.cursor()
    cursor.execute(f"UPDATE pedidos SET estado = 'RECIBIDO' WHERE mesa = {mesa_value} && estado = 'ENVIADO'")
    cursor.connection.commit()
    cursor.close()
    for pedido in pedidos:
        pedidos_list.append(pedido[1])
    return jsonify({'pedidos':pedidos_list})

@app.route('/obtener_estado', methods=['GET'])
def obtener_estado():
    cursor = mysql.connection.cursor()
    cursor.execute(f"SELECT estado FROM pedidos WHERE estado != 'TERMINADO' && mesa = 'D'")
    pedidos = cursor.fetchall()
    if len(pedidos) > 0: estado_D = pedidos[0][0] 
    else: estado_D = 'TERMINADO'    

    cursor.execute(f"SELECT estado FROM pedidos WHERE estado != 'TERMINADO' && mesa = 'E'")
    pedidos = cursor.fetchall()
    if len(pedidos) > 0: estado_E = pedidos[0][0] 
    else: estado_E = 'TERMINADO' 

    cursor.execute(f"SELECT estado FROM pedidos WHERE estado != 'TERMINADO' && mesa = 'F'")
    pedidos = cursor.fetchall()
    if len(pedidos) > 0: estado_F = pedidos[0][0] 
    else: estado_F = 'TERMINADO' 

    cursor.execute(f"SELECT estado FROM pedidos WHERE estado != 'TERMINADO' && mesa = 'G'")
    pedidos = cursor.fetchall()
    if len(pedidos) > 0: estado_G = pedidos[0][0] 
    else: estado_G = 'TERMINADO' 

    cursor.execute(f"SELECT estado FROM pedidos WHERE estado != 'TERMINADO' && mesa = 'H'")
    pedidos = cursor.fetchall()
    if len(pedidos) > 0: estado_H = pedidos[0][0] 
    else: estado_H = 'TERMINADO' 
    cursor.close()    
    return jsonify({'D':estado_D,'E':estado_E,'F':estado_F,'G':estado_G,'H':estado_H})

@app.route('/cocinar_orden/<mesa>', methods=['GET'])
def cocinar_orden(mesa=None):
    if mesa == None:
        return jsonify({'resultado':'error'})
    mesa_value = f"'{mesa}'"
    cursor = mysql.connection.cursor()
    cursor.execute(f"UPDATE pedidos SET estado = 'EN COCINA' WHERE mesa = {mesa_value} && estado = 'RECIBIDO'")
    cursor.connection.commit()
    cursor.close()
    return jsonify({'resultado':'okey'})

@app.route('/montar_orden/<mesa>', methods=['GET'])
def montar_orden(mesa=None):
    if mesa == None:
        return jsonify({'resultado':'error'})
    mesa_value = f"'{mesa}'"
    cursor = mysql.connection.cursor()
    cursor.execute(f"UPDATE pedidos SET estado = 'EN CAMINO' WHERE mesa = {mesa_value} && estado = 'EN COCINA'")
    cursor.connection.commit()
    cursor.close()
    return jsonify({'resultado':'okey'})

if __name__ == '__main__':
    app.run(host='0.0.0.0', debug=True)