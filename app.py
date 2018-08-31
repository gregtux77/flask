#!flask/bin/python
from flask import Flask,jsonify,json,request
import serial
import time

from functools import wraps

def check_auth(username, password):
    return username == 'admin' and password == 'secret'

def authenticate():
    message = {'message': "Authenticate."}
    resp = jsonify(message)

    resp.status_code = 401
    resp.headers['WWW-Authenticate'] = 'Basic realm="Example"'

    return resp

def requires_auth(f):
    @wraps(f)
    def decorated(*args, **kwargs):
        auth = request.authorization
        if not auth: 
            return authenticate()

        elif not check_auth(auth.username, auth.password):
            return authenticate()
        return f(*args, **kwargs)

    return decorated


arduino = serial.Serial('COM4',9600,timeout=1)
#arduino = serial.Serial('/dev/ttyACM0',9600,timeout=1)
time.sleep(4)
init = arduino.readline()
print(init)

# Port série ttyACM0
# Vitesse de baud : 9600
# Timeout en lecture : 1 sec
# Timeout en écriture : 1 sec
app = Flask(__name__)


@app.route('/messages', methods = ['GET','POST'])
@requires_auth
def api_message():
    if request.method == 'GET':
        if 'temperature' in request.args:
            function=chr(123)+chr(34)+'function_name'+chr(34)+':'+chr(34)+'temperature'+chr(34)+chr(125)+chr(37)
           
        elif 'lumiere' in request.args:
            function=chr(123)+chr(34)+'function_name'+chr(34)+':'+chr(34)+'lumiere'+chr(34)+chr(125)+chr(37)
           
        else:
            return "400 Unsupported function"+"\n"
        
        arduino.write(function.encode('utf-8'))
        print(function)
        time.sleep(1)
        donnee=str(arduino.readline())
        print(donnee)
        donnee= donnee.split(',')[1]
        donnee = donnee.split('}')[0]
        return "ECHO: " + donnee+"\n"
    elif request.method == 'POST':
        if 'code' in request.args:

            function=chr(123)+chr(34)+'function_name'+chr(34)+':'+chr(34)+'SendRadioCode'+chr(34)+','+chr(34)+'code'+chr(34)+':'+chr(34)+request.args['code'] +chr(34)+chr(125)+chr(37)

            arduino.write(function.encode('utf-8'))

            print(function)

            time.sleep(2)
            donnee=str(arduino.readline())
            print(donnee)
        return "ECHO: " + donnee+"\n"

    else:
        return "415 Unsupported Media Type ;)"+"\n"





#@app.route('/todo/api/v1.0/tasks', methods=['GET'])
#def get_tasks():
#      return jsonify({'tasks': tasks})
if __name__ == '__main__':
         app.run(host='localhost')
