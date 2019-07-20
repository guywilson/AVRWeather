const express = require('express');
const bodyParser = require('body-parser');
const request = require('request');
const db = require('./db');

const app = express();

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

var chartXLabel = 'Previous 24h';
var chartTempTitle = 'Temperature last 24h';
var chartPresTitle = 'Air Pressure last 24h';
var chartHumiTitle = 'Humidity last 24h';

app.use(express.static('public'));
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true }));

app.set('view engine', 'ejs');

/*
** Render landing page...
*/
app.get('/weather', function (req, res) {
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

/*
** Render charts page...
*/
app.get('/weather/charts', function (req, res) {
	var xLabels = [];
	var tempReadings = [];
	var pressureReadings = [];
	var humidityReadings = [];

	if (req.query.period == '24h') {
		xLabels = ['23', '', '', '22', '', '', '21', '', '', '20', '', '', '19', '', '', '18', '', '', '17', '', '', '16', '', '', '15', '', '', '14', '', '', '13', '', '', '12', '', '', '11', '', '', '10', '', '', '9', '', '', '8', '', '', '7', '', '', '6', '', '', '5', '', '', '4', '', '', '3', '', '', '2', '', '', '1', '', '', ''];

		chartXLabel = 'Previous 24h';
		chartTempTitle = 'Temperature last 24h';
		chartPresTitle = 'Air Pressure last 24h';
		chartHumiTitle = 'Humidity last 24h';
		
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
						humidityReadings: humidityReadings,
						chartXLabel: chartXLabel,
						chartTempTitle: chartTempTitle,
						chartPresTitle: chartPresTitle,
						chartHumiTitle: chartHumiTitle
			});
		});
	}
	else if (req.query.period == '7d') {
		xLabels = ['7.18', '7.12', '7.06', '7.00', '6.18', '6.12', '6.06', '6.00', '5.18', '5.12', '5.06', '5.00', '4.18', '4.12', '4.06', '4.00', '3.18', '3.12', '3.06', '3.00', '2.18', '2.12', '2.06', '2.00', '1.18', '1.12', '1.06', '1.00'];

		chartXLabel = 'Previous 7d';
		chartTempTitle = 'Temperature last 7d';
		chartPresTitle = 'Air Pressure last 7d';
		chartHumiTitle = 'Humidity last 7d';

		db.getChartData_7d(function(items) {
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
						humidityReadings: humidityReadings,
						chartXLabel: chartXLabel,
						chartTempTitle: chartTempTitle,
						chartPresTitle: chartPresTitle,
						chartHumiTitle: chartHumiTitle
			});
		});
	}
	else if (req.query.period == '28d') {
		xLabels = [27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0];

		chartXLabel = 'Previous 28d';
		chartTempTitle = 'Temperature last 28d';
		chartPresTitle = 'Air Pressure last 28d';
		chartHumiTitle = 'Humidity last 28d';

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
						humidityReadings: humidityReadings,
						chartXLabel: chartXLabel,
						chartTempTitle: chartTempTitle,
						chartPresTitle: chartPresTitle,
						chartHumiTitle: chartHumiTitle
			});
		});
	}
})

/*
** Handle API post for average TPH data...
*/
app.post('/weather/api/avg-tph', function(req, res) {
	timestamp = req.body.time;
	doSave = req.body.save;
	avgTemperature = req.body.temperature;
	avgPressure = req.body.pressure;
	avgHumidity = req.body.humidity;

	if (doSave == 'true') {
		db.putChartData(timestamp, 'AVG', avgTemperature, avgPressure, avgHumidity);		
	}
	 	
	res.json(["OK", ""]);
})

/*
** Handle API post for min TPH data...
*/
app.post('/weather/api/min-tph', function(req, res) {
	timestamp = req.body.time;
	doSave = req.body.save;
	minTemperature = req.body.temperature;
	minPressure = req.body.pressure;
	minHumidity = req.body.humidity;

	if (doSave == 'true') {
		db.putChartData(timestamp, 'MIN', avgTemperature, avgPressure, avgHumidity);		
	}
				 
	res.json(["OK", ""]);
})

/*
** Handle API post for max TPH data...
*/
app.post('/weather/api/max-tph', function(req, res) {
	timestamp = req.body.time;
	doSave = req.body.save;
	maxTemperature = req.body.temperature;
	maxPressure = req.body.pressure;
	maxHumidity = req.body.humidity;

	if (doSave == 'true') {
		db.putChartData(timestamp, 'MAX', avgTemperature, avgPressure, avgHumidity);		
}
	 	
	res.json(["OK", ""]);
})

app.listen(3000, function () {
  console.log('Weather app listening on port 3000!');
})