import React, { useEffect, useState } from "react";
import ReactSwitch from "react-switch";
import Container from 'react-bootstrap/Container';
import Col from 'react-bootstrap/Col';
import Card from 'react-bootstrap/Card';
import './styles.css'
import { Row } from "react-bootstrap";


export function Switch(){
  const [whiteLED, setWhiteLED] = useState(false);
  const [greenLED, setGreenLED] = useState(false);
  const [redLED, setRedLED] = useState(false);
  const [button, setButton] = useState(false)
  
  
  const change = (color) => {
    const mqtt = require('mqtt/dist/mqtt')
    const pub = mqtt.connect('ws://192.168.137.106:9001')
    let state

    if (color === "verde"){
      state = !greenLED;
      setGreenLED(state)
    }
    else if (color === "blanco"){
      state = !whiteLED
      setWhiteLED(state)
    }
    pub.publish(`arduino/control/leds/${color}`, `{\"led_encendido\":${state}}`)
    console.log("enviado " + state)  
  }
  const redChange = () => {
    const mqtt = require('mqtt/dist/mqtt')
    const pub = mqtt.connect('ws://192.168.137.106:9001')
    let state = !redLED
    if (state) {
      pub.publish('raspberry/control/led', "ON")
    }
    else pub.publish('raspberry/control/led', "OFF")
    setRedLED(state)
  }

  useEffect(()=>{
      const mqtt = require ('mqtt/dist/mqtt')
      const sub = mqtt.connect('ws://192.168.137.106:9001')
      sub.on('connect', ()=> {
          console.log("conectado");
          sub.subscribe('raspberry/mediciones/boton')})
      sub.on("message", (topic, payload) => {
          let state = payload.toString()
          if (state === "PRESSED") setButton(true)
          else if (state === "RELEASED") setButton(false)
          console.log(state)})
  }, [])


  return (
    <div>
      <Row>
      <Col sm={6}>
      <Card bg={"dark"} border="secondary" >
     <Card.Title><h3>Raspberry</h3></Card.Title>
     <Card.Body><Row><Col>Botón<ReactSwitch
        checked={button}
        onChange = {()=>{}}
        className="react-switch"
        onColor="#DDDD00"
      />
      </Col>
      <Col>
     <label>LED Rojo<ReactSwitch
        onChange={() => 
          redChange()
        }
        checked={redLED}
        className="react-switch"
        onColor="#FF0000"
      />
      </label>
      </Col>
      </Row>
      </Card.Body>
      </Card>
      </Col>
      <Col>
      <Card bg={"dark"} border="secondary">
      <Card.Title><h3>Arduino</h3></Card.Title>
      <Card.Body>
      <Row>
        <Col>
     <label>LED Blanco<ReactSwitch
        onChange={() => 
          change("blanco")
        }
        checked={whiteLED}
        className="react-switch"
        onColor="#CCCCCC"
      />
      </label>
      </Col>
      <Col>
     <label>LED Verde<ReactSwitch
        onChange={() => 
          change("verde")
        }
        checked={greenLED}
        className="react-switch"
      />
      </label>
      </Col>
      </Row>
      </Card.Body>
      </Card>
      </Col>
      </Row>
     
    </div>
  )
}