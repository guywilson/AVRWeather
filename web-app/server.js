const express = require('express');
const bodyParser = require('body-parser');
const request = require('request');
const app = express();
const apiKey = 'b340cca5287ba875e11c7fa0a257926a';

var avgTemperature = '0.00';
var avgPressure = '0.00';
var avgHumidity = '0.00';

var minTemperature = '---';
var minPressure = '---';
var minHumidity = '---';

var maxTemperature = '---';
var maxPressure = '---';
var maxHumidity = '---';

app.use(express.static('public'));
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true }));

app.set('view engine', 'ejs');

app.get('/', function (req, res) {
	res.render('index', {avgTemperature: avgTemperature, avgPressure: avgPressure, avgHumidity: avgHumidity});
})

/*
** Handle API post for average TPH data...
*/
app.post('/api/avg-tph', function(req, res) {
	avgTemperature = req.body.temperature;
	avgPressure = req.body.pressure;
	avgHumidity = req.body.humidity;
	
	console.log('Received TPH data. T = ' + avgTemperature + ' P = ' + avgPressure + ' H = ' + avgHumidity);
	
	res.json(["OK", ""]);
})

/*
** Handle API post for min TPH data...
*/
app.post('/api/min-tph', function(req, res) {
	minTemperature = req.body.temperature;
	minPressure = req.body.pressure;
	minHumidity = req.body.humidity;
	
	console.log('Received TPH data. T = ' + minTemperature + ' P = ' + minPressure + ' H = ' + minHumidity);
	
	res.json(["OK", ""]);
})

/*
** Handle API post for max TPH data...
*/
app.post('/api/max-tph', function(req, res) {
	maxTemperature = req.body.temperature;
	maxPressure = req.body.pressure;
	maxHumidity = req.body.humidity;
	
	console.log('Received TPH data. T = ' + maxTemperature + ' P = ' + maxPressure + ' H = ' + maxHumidity);
	
	res.json(["OK", ""]);
})

app.listen(3000, function () {
  console.log('Weather app listening on port 3000!');
})