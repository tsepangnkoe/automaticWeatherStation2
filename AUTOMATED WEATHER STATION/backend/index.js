const express = require('express');
const app = express();
const port = 3002

const login_model = require('./models/login')
const humidityAndTemp_model = require('./models/humidityAndTemp')
const getStations_model = require('./models/stations')

require('./models/fetchDataFromThingSpeak')


app.use(express.json())
app.use(function (req, res, next) {
  res.setHeader('Access-Control-Allow-Origin', 'http://localhost:3000');
  res.setHeader('Access-Control-Allow-Methods', 'GET,POST,PUT,DELETE,OPTIONS');
  res.setHeader('Access-Control-Allow-Headers', 'Content-Type, Access-Control-Allow-Headers');
  next();
});


app.get('/', (req, res) => {
  res.send('Hello, World!');
});

app.get('/users', (req, res) => {
  login_model.getUsers()
  .then(response => {
    res.status(200).send(response);
  })
  .catch(error => {
    res.status(500).send(error);
  })
});

app.get('/humidityAndTemp', (req, res) => {
  humidityAndTemp_model.getHumidityAndTemp()
  .then(response => {
    res.status(200).send(response);
  })
  .catch(error => {
    res.status(500).send(error);
  })
});

app.get('/stations', (req, res) => {
  getStations_model.getStations()
  .then(response => {
    res.status(200).send(response);
  })
  .catch(error => {
    res.status(500).send(error);
  })
});



app.listen(port, () => {
  console.log(`Server is running on http://localhost:${port}`);
});
