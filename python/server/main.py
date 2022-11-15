from flask import Flask, redirect, url_for, render_template, request, flash
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
        cursor.execute(f"UPDATE pedidos SET estado = 'TERMINADO' WHERE mesa = {mesa_value}")
        cursor.connection.commit()
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

if __name__ == '__main__':
    app.run(host='0.0.0.0', debug=True)