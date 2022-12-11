import './App.css';
import {Gauge} from './Gauge'
import {Humidity} from './Humidity'
import {Switch} from './Switch'
import Container from 'react-bootstrap/Container';
import Row from 'react-bootstrap/Row';
import Col from 'react-bootstrap/Col';
import Card from 'react-bootstrap/Card';


function App() {
  return (
    <div className="App">
      <div className="App-header">
      <Container>
        <Card 
        bg={"dark"}
        border="info"
        style={{ width: '65rem', padding: '20px'}}
        >
      <Row style={{margin:'35px'}}>
        <Switch></Switch>
      </Row>
    <Row>
        <Col><Gauge></Gauge></Col>
        <Col><Humidity></Humidity></Col>
      </Row>
      </Card>
    </Container>
      </div>
    </div>
  );
}

export default App;
