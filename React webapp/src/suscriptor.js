const mqtt = require('mqtt')
const pub = mqtt.connect('ws://localhost:3000')
pub.on('connect', ()=> {
    console.log("conectado");
    pub.subscribe('temp/tdp2')})
pub.on("message", (topic, payload) => console.log(payload.toString()))