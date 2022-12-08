import React, { useState } from "react";
import ReactSwitch from "react-switch";
import Container from 'react-bootstrap/Container';
import Col from 'react-bootstrap/Col';
import Card from 'react-bootstrap/Card';
import './styles.css'
import { Row } from "react-bootstrap";

const mqtt = require('mqtt/dist/mqtt')
const pub = mqtt.connect('ws://192.168.137.106:9001')


export function Switch(){
  const [redLED, setRedLED] = useState(false);
  const [blueLED, setBlueLED] = useState(false);
  const [greenLED, setGreenLED] = useState(false);
  
  const redChange = () => {
    pub.publish('arduino/control', "{\"led_encendido\":"+!redLED.toString()+"}")
    console.log("enviado " + !redLED)  
    setRedLED(!redLED)
      
  }
  const blueChange = () => {
    setBlueLED(!blueLED)
  }




  return (
    <div>
      <Row>
      <Col sm={6}>
      <Card bg={"dark"} border="secondary" >
     <Card.Title><h3>Raspberry</h3></Card.Title>
     <Card.Body>LED Verde <ReactSwitch
        checked={greenLED}
        className="react-switch"
        disabled="true"
      />
      </Card.Body>
      </Card>
      </Col>
      <Col>
      <Card bg={"dark"} border="secondary">
      <Card.Title><h3>Arduino</h3></Card.Title>
      <Card.Body>
      <Row>
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
      <Col>
     <label>LED Azul<ReactSwitch
        onChange={() => blueChange()}
        checked={blueLED}
        onColor="#0000FF"
        className="react-switch"
      /></label>
      </Col>
      </Row>
      </Card.Body>
      </Card>
      </Col>
      </Row>
     
    </div>
  )
}