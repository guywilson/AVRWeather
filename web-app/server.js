const express = require('express');
const bodyParser = require('body-parser');
const request = require('request');
const MongoClient = require('mongodb').MongoClient;

const app = express();
const mongoURL = 'mongodb://localhost/WeatherDB';

var timestamp = '1900-01-01 00:00:00';

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
	res.render(
			'index', 
			{avgTemperature: avgTemperature, 
			 avgPressure: avgPressure, 
			 avgHumidity: avgHumidity,
			 minTemperature: minTemperature,
			 minPressure: minPressure,
			 minHumidity: minHumidity,
			 maxTemperature: maxTemperature,
			 maxPressure: maxPressure,
			 maxHumidity: maxHumidity});
})

/*
** Handle API post for average TPH data...
*/
app.post('/api/avg-tph', function(req, res) {
	timestamp = req.body.time;
	avgTemperature = req.body.temperature;
	avgPressure = req.body.pressure;
	avgHumidity = req.body.humidity;

	MongoClient.connect(url, function(err, db) {
	    db.collection('AverageTPH').insertOne({
	        timestamp: timestamp,
	        temperature: avgTemperature,
			pressure: avgPressure,
			humidity: avgHumidity
	    });
	});
	 	
	console.log('Received TPH data. T = ' + avgTemperature + ' P = ' + avgPressure + ' H = ' + avgHumidity);
	
	res.json(["OK", ""]);
})

/*
** Handle API post for min TPH data...
*/
app.post('/api/min-tph', function(req, res) {
	timestamp = req.body.time;
	minTemperature = req.body.temperature;
	minPressure = req.body.pressure;
	minHumidity = req.body.humidity;

	MongoClient.connect(url, function(err, db) {
	    db.collection('MinimumTPH').insertOne({
	        timestamp: timestamp,
	        temperature: minTemperature,
			pressure: minPressure,
			humidity: minHumidity
	    });
	});
	
	console.log('Received TPH data. T = ' + minTemperature + ' P = ' + minPressure + ' H = ' + minHumidity);
	
	res.json(["OK", ""]);
})

/*
** Handle API post for max TPH data...
*/
app.post('/api/max-tph', function(req, res) {
	timestamp = req.body.time;
	maxTemperature = req.body.temperature;
	maxPressure = req.body.pressure;
	maxHumidity = req.body.humidity;

	MongoClient.connect(url, function(err, db) {
	    db.collection('MaximumTPH').insertOne({
	        timestamp: timestamp,
	        temperature: maxTemperature,
			pressure: maxPressure,
			humidity: maxHumidity
	    });
	});
	
	console.log('Received TPH data. T = ' + maxTemperature + ' P = ' + maxPressure + ' H = ' + maxHumidity);
	
	res.json(["OK", ""]);
})

app.listen(3000, function () {
  console.log('Weather app listening on port 3000!');
})