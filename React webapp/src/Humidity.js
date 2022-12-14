import GaugeChart from 'react-gauge-chart';
import React, {useEffect, useState} from "react";
import { Card } from 'react-bootstrap';

const chartStyle = {
    height: '75%',
    width: '75%'
  }

export function Humidity(){
  const [humedad, setHumedad] = useState(70)

  var json = {humedad}
    
  useEffect(()=>{
      const mqtt = require('mqtt/dist/mqtt')
      const pub = mqtt.connect('ws://localhost:3000')
      pub.on('connect', ()=> {
          console.log("conectado");
          pub.subscribe('hum/tdp2')})
      pub.on("message", (topic, payload) => {
          json = JSON.parse(payload)
          setHumedad(json.humedad.toString())
          console.log(payload.toString())})
  }, [])

    return(
        <div>
          <Card bg={"dark"} border="secondary" style={{padding: '10px'}}>
          <Card.Title><h3>Humedad</h3></Card.Title>
          <Card.Body>
          <GaugeChart id="gauge-chart3"
            nrOfLevels={30}
            arcWidth={0.3}
            hideText={false}
            percent={humedad/100}
            needleBaseColor="lightblue"
            needleColor='white'
            colors={["#FFFFFF", "#111111"]}
            marginInPercent={0.01} />
            </Card.Body>
            </Card>
            </div>
            
    
    );
}