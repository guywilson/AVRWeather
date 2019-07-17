import json
from django.shortcuts import render
from django.http import HttpResponse
from django.template import loader
from django.views.decorators.csrf import csrf_exempt
from django.views.decorators.clickjacking import xframe_options_exempt
from .models import TPH

minTemperature = None
avgTemperature = None
maxTemperature = None

minPressure = None
avgPressure = None
maxPressure = None

minHumidity = None
avgHumidity = None
maxHumidity = None

@xframe_options_exempt
def index(request):
    global minTemperature
    global avgTemperature
    global maxTemperature
    
    global minPressure
    global avgPressure
    global maxPressure

    global minHumidity
    global avgHumidity
    global maxHumidity

    template = loader.get_template('weather/index.html')

    context = {
        'minTemperature': minTemperature,
        'avgTemperature': avgTemperature,
        'maxTemperature': maxTemperature,
        'minPressure': minPressure,
        'avgPressure': avgPressure,
        'maxPressure': maxPressure,
        'minHumidity': minHumidity,
        'avgHumidity': avgHumidity,
        'maxHumidity': maxHumidity,
    }

    return HttpResponse(template.render(context, request))

@xframe_options_exempt
def charts(request):
    template = loader.get_template('weather/charts.html')
    period = request.GET.get('period', '24h')

    readings = list()
    xLabels = []

    if period == '24h':
        xLabels = ['23', '22', '21', '20', '19', '18', '17', '16', '15', '14', '13', '12', '11', '10', '9', '8', '7', '6', '5', '4', '3', '2', '1', '0']
        chartXLabel = 'Previous 24h'
        chartTempTitle = 'Temperature last 24h'
        chartPresTitle = 'Air Pressure last 24h'
        chartHumiTitle = 'Humidity last 24h'

        readings = TPH.objects.filter(loadType = 'AVG').order_by('-loadTimestamp')[:24][::-1]

    elif period == '7d':
        xLabels = ['7.18', '7.12', '7.06', '7.00', '6.18', '6.12', '6.06', '6.00', '5.18', '5.12', '5.06', '5.00', '4.18', '4.12', '4.06', '4.00', '3.18', '3.12', '3.06', '3.00', '2.18', '2.12', '2.06', '2.00', '1.18', '1.12', '1.06', '1.00']
        chartXLabel = 'Previous 7d'
        chartTempTitle = 'Temperature last 7d'
        chartPresTitle = 'Air Pressure last 7d'
        chartHumiTitle = 'Humidity last 7d'

        readings = TPH.objects.filter(loadType = 'AVG').filter(loadTimestamp__hour__in = [0, 6, 12, 18]).order_by('-loadTimestamp')[:28][::-1]
    
    elif period == '28d':
        xLabels = ['27', '26', '25', '24', '23', '22', '21', '20', '19', '18', '17', '16', '15', '14', '13', '12', '11', '10', '9', '8', '7', '6', '5', '4', '3', '2', '1', '0']
        chartXLabel = 'Previous 28d'
        chartTempTitle = 'Temperature last 28d'
        chartPresTitle = 'Air Pressure last 28d'
        chartHumiTitle = 'Humidity last 28d'

        readings = TPH.objects.filter(loadType = 'AVG').filter(loadTimestamp__hour = 12).order_by('-loadTimestamp')[:28][::-1]
    
    tempReadings = list()
    pressureReadings = list()
    humidityReadings = list()

    for i in readings:
        tempReadings.append(str(i.temperature))
        pressureReadings.append(str(i.pressure))
        humidityReadings.append(str(i.humidity))

    context = {
        'xLabels': ','.join(xLabels),
        'tempReadings': ','.join(tempReadings),
        'pressureReadings': ','.join(pressureReadings),
        'humidityReadings': ','.join(humidityReadings),
        'chartXLabel': chartXLabel,
        'chartTempTitle': chartTempTitle,
        'chartPresTitle': chartPresTitle,
        'chartHumiTitle': chartHumiTitle,
    }

    return HttpResponse(template.render(context, request))

@csrf_exempt
def jsonAvgData(request):
    global avgTemperature
    global avgPressure
    global avgHumidity

    if request.method == 'POST':
        dct = dict()

        dct = json.loads(request.body)

        sentTPH = TPH()
        sentTPH.loadTimestamp = dct['time']
        sentTPH.loadType = 'AVG'
        sentTPH.temperature = dct['temperature']
        sentTPH.pressure = dct['pressure']
        sentTPH.humidity = dct['humidity']

        avgTemperature = sentTPH.temperature
        avgPressure = sentTPH.pressure
        avgHumidity = sentTPH.humidity

        if dct['save'] == 'true':
            sentTPH.save()

    return HttpResponse(json.dumps("OK"))

@csrf_exempt
def jsonMinData(request):
    global minTemperature
    global minPressure
    global minHumidity

    if request.method == 'POST':
        dct = dict()

        dct = json.loads(request.body)

        sentTPH = TPH()
        sentTPH.loadTimestamp = dct['time']
        sentTPH.loadType = 'AVG'
        sentTPH.temperature = dct['temperature']
        sentTPH.pressure = dct['pressure']
        sentTPH.humidity = dct['humidity']

        minTemperature = sentTPH.temperature
        minPressure = sentTPH.pressure
        minHumidity = sentTPH.humidity
        
        if dct['save'] == 'true':
            sentTPH.save()

    return HttpResponse(json.dumps("OK"))

@csrf_exempt
def jsonMaxData(request):
    global maxTemperature
    global maxPressure
    global maxHumidity

    if request.method == 'POST':
        dct = dict()

        dct = json.loads(request.body)

        sentTPH = TPH()
        sentTPH.loadTimestamp = dct['time']
        sentTPH.loadType = 'AVG'
        sentTPH.temperature = dct['temperature']
        sentTPH.pressure = dct['pressure']
        sentTPH.humidity = dct['humidity']

        maxTemperature = sentTPH.temperature
        maxPressure = sentTPH.pressure
        maxHumidity = sentTPH.humidity
        
        if dct['save'] == 'true':
            sentTPH.save()

    return HttpResponse(json.dumps("OK"))

