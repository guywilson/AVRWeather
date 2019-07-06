const express = require('express');
const bodyParser = require('body-parser');
const request = require('request');
const db = require('./db');

const MongoClient = require('mongodb').MongoClient;

const app = express();
const mongoURL = 'mongodb://localhost';

var timestamp = '1900-01-01 00:00:00';

var doSave = 'false';

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

function getAllMongoData(callback) {
	MongoClient.connect(mongoURL, async function(error, client) {
		if (error) {
			throw err;
		}
	
		var db = client.db('WeatherDB');
		var collection = db.collection('AverageTPH');

		var query = {};
		
		await collection.find(query).toArray((error, items) => {
			if (error) {
				throw error;
			}
			
			return callback(items);
		});
	
		//client.close();
	});
}

function getChartData_24h(callback) {
	MongoClient.connect(mongoURL, function(error, client) {
		if (error) {
			throw err;
		}
	
		var db = client.db('WeatherDB');
		var collection = db.collection('AverageTPH');

		var query = {};
	
		var options = {
			"limit": 24
		};
		
		collection.find(query, options).sort({timestamp: -1}).toArray((error, items) => {
			if (error) {
				throw error;
			}
			
			return callback(items);
		});
	
		client.close();
	});
}

function getChartData_7d(callback) {
	MongoClient.connect(mongoURL, function(error, client) {
		if (error) {
			throw err;
		}
	
		var db = client.db('WeatherDB');
		var collection = db.collection('AverageTPH');

		var query = {
			"$or": [
				{ "timestamp": /.* 06:.*/ }, 
				{ "timestamp": /.* 12:.*/ }, 
				{ "timestamp": /.* 18:.*/ }, 
				{ "timestamp": /.* 00:.*/ }
			]
		};
	
		var options = {
			"limit": 28
		};
		
		/*
		** Get a reading 4 times a day at 06:xx, 12:xx, 18:xx, 00:xx for 7 days...
		*/
		collection.find(query, options).sort({timestamp: -1}).toArray((error, items) => {
			if (error) {
				throw error;
			}
			
			return callback(items);
		});
	
		client.close();
	});
}

function getChartData_28d(callback) {
	MongoClient.connect(mongoURL, function(error, client) {
		if (error) {
			throw err;
		}
	
		var db = client.db('WeatherDB');
		var collection = db.collection('AverageTPH');

		var query = {
			timestamp: "/.* 12:.*/"
		};
	
		var options = {
			"limit": 28
		};
		
		/*
		** Get a reading once a day at noon for 28 days...
		*/
		collection.find(query, options).sort({timestamp: -1}).toArray((error, items) => {
			if (error) {
				throw error;
			}
			
			return callback(items);
		});
	
		client.close();
	});
}

/*
** Render landing page...
*/
app.get('/', function (req, res) {
	res.render(
			'index', 
			{
				avgTemperature: avgTemperature, 
			 	avgPressure: avgPressure, 
			 	avgHumidity: avgHumidity,
			 	minTemperature: minTemperature,
			 	minPressure: minPressure,
			 	minHumidity: minHumidity,
			 	maxTemperature: maxTemperature,
			 	maxPressure: maxPressure,
			 	maxHumidity: maxHumidity
			});
})

app.get('/copy', function (req, res) {
	console.log('Copying data from MongoDB to Postgresql');

	getAllMongoData(function(items) {
		items.forEach(function(item, index) {
			Console.log('Got item: ' + item.temperature);
			db.putChartData(item.timestamp, 'AVG', item.temperature, item.pressure, item.humidity);
		});

		res.render('index');
	});
})

/*
** Render charts page...
*/
app.get('/charts', function (req, res) {
	var xLabels = [];
	var tempReadings = [];
	var pressureReadings = [];
	var humidityReadings = [];

	if (req.query.period == '24h') {
		xLabels = [23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0];

		db.getChartData_24h(function(items) {
			items.forEach(function(item, index) {
				tempReadings = tempReadings.concat(item.temperature);
				pressureReadings = pressureReadings.concat(item.pressure);
				humidityReadings = humidityReadings.concat(item.humidity);
			});
	
			/*
			** We want the readings the other way around, with the latest
			** reading last...
			*/
			tempReadings = tempReadings.reverse();
			pressureReadings = pressureReadings.reverse();
			humidityReadings = humidityReadings.reverse();
	
			res.render('charts', {
						xLabels: xLabels,
						tempReadings: tempReadings,
						pressureReadings: pressureReadings,
						humidityReadings: humidityReadings
			});
		});
	}
	else if (req.query.period == '7d') {
		xLabels = [6, 5, 4, 3, 2, 1, 0];

		db.getChartData_7d(function(items) {
			items.forEach(function(item, index) {
				console.log("Timestamp: " + item.timestamp);
				tempReadings = tempReadings.concat(item.temperature);
				pressureReadings = pressureReadings.concat(item.pressure);
				humidityReadings = humidityReadings.concat(item.humidity);
			});
	
			/*
			** We want the readings the other way around, with the latest
			** reading last...
			*/
			tempReadings = tempReadings.reverse();
			pressureReadings = pressureReadings.reverse();
			humidityReadings = humidityReadings.reverse();
	
			res.render('charts', {
						xLabels: xLabels,
						tempReadings: tempReadings,
						pressureReadings: pressureReadings,
						humidityReadings: humidityReadings
			});
		});
	}
	else if (req.query.period == '28d') {
		xLabels = [27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0];

		db.getChartData_28d(function(items) {
			items.forEach(function(item, index) {
				tempReadings = tempReadings.concat(item.temperature);
				pressureReadings = pressureReadings.concat(item.pressure);
				humidityReadings = humidityReadings.concat(item.humidity);
			});
	
			/*
			** We want the readings the other way around, with the latest
			** reading last...
			*/
			tempReadings = tempReadings.reverse();
			pressureReadings = pressureReadings.reverse();
			humidityReadings = humidityReadings.reverse();
	
			res.render('charts', {
						xLabels: xLabels,
						tempReadings: tempReadings,
						pressureReadings: pressureReadings,
						humidityReadings: humidityReadings
			});
		});
	}
})

/*
** Handle API post for average TPH data...
*/
app.post('/api/avg-tph', function(req, res) {
	timestamp = req.body.time;
	doSave = req.body.save;
	avgTemperature = req.body.temperature;
	avgPressure = req.body.pressure;
	avgHumidity = req.body.humidity;

	if (doSave == 'true') {
//		console.log('Saving average TPH data to database');
		db.putChartData(timestamp, 'AVG', avgTemperature, avgPressure, avgHumidity);		
	}
	 	
//	console.log('Received AVG TPH data. Save = ' + doSave + 'T = ' + avgTemperature + ' P = ' + avgPressure + ' H = ' + avgHumidity);
	
	res.json(["OK", ""]);
})

/*
** Handle API post for min TPH data...
*/
app.post('/api/min-tph', function(req, res) {
	timestamp = req.body.time;
	doSave = req.body.save;
	minTemperature = req.body.temperature;
	minPressure = req.body.pressure;
	minHumidity = req.body.humidity;

	if (doSave == 'true') {
//		console.log('Saving minimum TPH data to database');
		db.putChartData(timestamp, 'MIN', avgTemperature, avgPressure, avgHumidity);		
	}
				 
//	console.log('Received MIN TPH data. Save = ' + doSave + 'T = ' + avgTemperature + ' P = ' + avgPressure + ' H = ' + avgHumidity);
	
	res.json(["OK", ""]);
})

/*
** Handle API post for max TPH data...
*/
app.post('/api/max-tph', function(req, res) {
	timestamp = req.body.time;
	doSave = req.body.save;
	maxTemperature = req.body.temperature;
	maxPressure = req.body.pressure;
	maxHumidity = req.body.humidity;

	if (doSave == 'true') {
//		console.log('Saving maximum TPH data to database');
		db.putChartData(timestamp, 'MAX', avgTemperature, avgPressure, avgHumidity);		
}
	 	
//	console.log('Received MAX TPH data. Save = ' + doSave + 'T = ' + avgTemperature + ' P = ' + avgPressure + ' H = ' + avgHumidity);
	
	res.json(["OK", ""]);
})

app.listen(3000, function () {
  console.log('Weather app listening on port 3000!');
})