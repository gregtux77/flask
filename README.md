# flask
FLASK_APP=app.py flask run


curl -H "Content-type: application/json" -X POST http://127.0.0.1:5000/messages -d '{"function_name":"temperature"}'





curl -v -u "admin:secret" -X POST http://127.0.0.1:5000/messages?code=10


curl -H "Content-type: application/json" -X GET http://127.0.0.1:5000/messages?temperature
curl -H "Content-type: application/json" -X GET http://127.0.0.1:5000/messages?lumiere


curl -H "Content-type: application/json" -X POST http://127.0.0.1:5000/messages?code=2
curl -H "Content-type: application/json" -X POST http://127.0.0.1:5000/messages?code=4
