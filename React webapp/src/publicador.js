const mqtt = require('mqtt')
const pub = mqtt.connect('ws://localhost:3000')
pub.on('connect', ()=> {
    console.log("conectado")});
    temp = Math.random()*40
    hum = Math.random()*40
    pub.publish('temp/tdp2', `{\"temperatura\":${temp}}`)
    pub.publish('hum/tdp2', `{\"humedad\":${hum}}`)