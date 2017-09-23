var five = require('johnny-five');
var express = require('express');
var socket = require('socket.io');

var app = express();
var server = app.listen(3000);
var io = socket(server);

app.use(express.static('public'));

var board = new five.Board({
    port: 'COM7'
});

var pinzaAbierta = true;

// 85 cerrado
// 0 abierto

board.on('ready', function () {

    console.log("arduino listo");

    var servo1 = new five.Servo(3);
    var servo2 = new five.Servo(5);
    var servo3 = new five.Servo(6);
    var servo4 = new five.Servo(9);
    var servo5 = new five.Servo(10);
    var servo6 = new five.Servo(11);

    //led.on();
    servo1.to(0); // 31 a 90
    servo2.to(180);
    servo3.to(90); // 0 a 134
    servo4.to(90); // invertir
    servo5.to(90); 
    servo6.to(0);

    io.sockets.on('connection', function (socket) {
        socket.on('move', function (servo, angle){
            if(servo == 0){
                servo1.to(angle);
                invertedAngle = 180 - angle;
                servo2.to(invertedAngle);
            }
            else if(servo == 2){
                servo3.to(angle);
            }
            else if(servo == 3){
                invertedAngle = 180 - angle;
                servo4.to(invertedAngle);
            }
            else if(servo == 4){
                servo5.to(angle);
            }
            else if(servo == 5){
                
                if(pinzaAbierta){
                    servo6.to(85);
                }
                else{
                    servo6.to(0);
                }
                pinzaAbierta = !pinzaAbierta;
                console.log(pinzaAbierta);
                console.log("boton pisado");
            }

            console.log("servo: " + servo + " angulo: " + angle);
        });
    });
});

console.log("conectado");