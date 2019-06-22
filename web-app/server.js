const express = require('express');
const bodyParser = require('body-parser');
const request = require('request');
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

function getChartLabels() {
	var query = {
		timestamp: {$gte:'2019-06-21 00:00:00'},
		timestamp: true
	};

	var options = {
		"limit": 8
	};
	
	MongoClient.connect(mongoURL, function(error, client) {
		if (error) {
			throw err;
		}
		
		var db = client.db('WeatherDB');

		var collection = db.collection('AverageTPH');
		
		collection.find({}, options).toArray((error, items) => {
			if (error) {
				throw error;
			}
			
			console.log(items)
			return items;
		});
	
		client.close();
	});
}

/*
function getChartLabels(collection, callback) {
	var queryLabels = {
		timestamp: {$gte:'2019-06-21 00:00:00'},
		timestamp: true
	};

	var options = {
		"limit": 2880
	};
	
	collection.find({}, options).toArray(function (error, results) {
		if (error) {
			throw error;
		}
		
		if (results.length > 0) {
			callback(results);
		}
	});
}
*/

function getChartData() {
	MongoClient.connect(mongoURL, function(error, client) {
		if (error) {
			throw err;
		}
		
		var query = {
			timestamp: {$gte:'2019-06-21 00:00:00'},
			temperature: true
		};
	
		var options = {
			"limit": 8
		};
	
		var db = client.db('WeatherDB');

		var collection = db.collection('AverageTPH');
		
		collection.find({}, options).toArray((error, items) => {
			if (error) {
				throw error;
			}
			
			console.log(items)
			return items;
		});
	
		client.close();
	});
}

/*
function getChartData(collection, callback) {
	var query = {
		timestamp: {$gte:'2019-06-21 00:00:00'},
		temperature: true
	};

	var options = {
		"limit": 2880
	};
	
	collection.find({}, options).toArray(function (error, results) {
		if (error) {
			throw error;
		}
		
		if (results.length > 0) {
			callback(results);
		}
	});
}
*/

/*
** Render charts page...
*/
app.get('/charts', function (req, res) {
	var xLabels = [];
	var tempReadings = [];

	MongoClient.connect(mongoURL, function(error, client) {
		if (error) {
			throw err;
		}
		
		var query = {
			timestamp: {$gte:'2019-06-21 00:00:00'},
			timestamp: true
		};
	
		var options = {
			"limit": 8
		};
	
		var db = client.db('WeatherDB');

		var collection = db.collection('AverageTPH');
		
		collection.find({}, options).toArray((error, items) => {
			if (error) {
				throw error;
			}
			
			xLabels = items;
		});
	
		client.close();
	});

	MongoClient.connect(mongoURL, function(error, client) {
		if (error) {
			throw err;
		}
		
		var query = {
			timestamp: {$gte:'2019-06-21 00:00:00'},
			temperature: true
		};
	
		var options = {
			"limit": 8
		};
	
		var db = client.db('WeatherDB');

		var collection = db.collection('AverageTPH');
		
		collection.find({}, options).toArray((error, items) => {
			if (error) {
				throw error;
			}
			
			tempReadings = items;
		});
	
		client.close();
	});

/*
	getChartLabels(function(items) {
		console.info('The promise was fulfilled with items!', items);
		xLabels = xLabels.concat(results);
	}, function(err) {
		console.error('The promise was rejected', err, err.stack);
	});

	getChartData(function(items) {
		console.info('The promise was fulfilled with items!', items);
		tempReadings = tempReadings.concat(results);
	}, function(err) {
		console.error('The promise was rejected', err, err.stack);
	});
*/
	
	res.render(
			'charts',
			{
				xLabels: xLabels,
				tempReadings: tempReadings
			});
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
		console.log('Saving average TPH data to database');
		
		MongoClient.connect(mongoURL, function(error, client) {
			if (error) {
				throw err;
			}
			
			var db = client.db('WeatherDB');
			
		    db.collection('AverageTPH').insertOne({
		        timestamp: timestamp,
		        temperature: avgTemperature,
				pressure: avgPressure,
				humidity: avgHumidity
		    });
	
			client.close();
		});
	}
	 	
	console.log('Received TPH data. T = ' + avgTemperature + ' P = ' + avgPressure + ' H = ' + avgHumidity);
	
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
		console.log('Saving minimum TPH data to database');
		
		MongoClient.connect(mongoURL, function(error, client) {
			if (error) {
				throw err;
			}
			
			var db = client.db('WeatherDB');
			
		    db.collection('MinimumTPH').insertOne({
		        timestamp: timestamp,
		        temperature: minTemperature,
				pressure: minPressure,
				humidity: minHumidity
		    });
	
			client.close();
		});
	}
	
	console.log('Received TPH data. T = ' + minTemperature + ' P = ' + minPressure + ' H = ' + minHumidity);
	
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
		console.log('Saving maximum TPH data to database');
		
		MongoClient.connect(mongoURL, function(error, client) {
			if (error) {
				throw err;
			}
			
			var db = client.db('WeatherDB');
			
		    db.collection('MaximumTPH').insertOne({
		        timestamp: timestamp,
		        temperature: maxTemperature,
				pressure: maxPressure,
				humidity: maxHumidity
		    });
	
			client.close();
		});
	}
	
	console.log('Received TPH data. T = ' + maxTemperature + ' P = ' + maxPressure + ' H = ' + maxHumidity);
	
	res.json(["OK", ""]);
})

app.listen(3000, function () {
  console.log('Weather app listening on port 3000!');
})