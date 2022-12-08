import GaugeChart from 'react-gauge-chart';
import React, { useEffect, useState } from "react";
import { Card } from 'react-bootstrap';

export function Gauge(){
    const [temperatura, setTemperatura] = useState(10)
    var json = {temperatura}
    
    useEffect(()=>{
        const mqtt = require('mqtt/dist/mqtt')
        const pub = mqtt.connect('ws://192.168.137.106:9001')
        pub.on('connect', ()=> {
            console.log("conectado");
            pub.subscribe('arduino/mediciones')})
        pub.on("message", (topic, payload) => {
            json = JSON.parse(payload)
            if (json.temperatura !== "fail") setTemperatura(json.temperatura.toString())
            console.log(payload.toString())})
    }, [])
    return(
        <div>
            <Card bg={"dark"} border="secondary" style={{padding: '10px'}}>
            <Card.Title><h3>Temperatura</h3></Card.Title>
            <Card.Body>
            <GaugeChart id="gauge-chart3"
            nrOfLevels={30}
            arcWidth={0.3}
            hideText={false}
            percent={ temperatura / 40}
            needleBaseColor="lightblue"
            needleColor='white'
            formatTextValue={() => parseInt(temperatura) + "°C"}
            marginInPercent={0.01}
            />
            </Card.Body>
            </Card>
            </div>
    
    );
}