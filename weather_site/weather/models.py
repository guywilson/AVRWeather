import json
from django.db import models

class TPH(models.Model):
    loadTimestamp = models.DateTimeField(db_column = 'ts')
    loadType = models.CharField(max_length = 3, db_column = 'type')
    temperature = models.DecimalField(max_digits = 8, decimal_places = 2, db_column = 'temperature')
    pressure = models.DecimalField(max_digits = 8, decimal_places = 2, db_column = 'pressure')
    humidity = models.DecimalField(max_digits = 8, decimal_places = 2, db_column = 'humidity')

    class Meta:
        db_table = "tph"

    def __str__(self):
        return str(self.temperature) + ' ' + str(self.pressure) + ' ' + str(self.humidity)

#    def __init__(self, json_data):
#        self.__dict__ = json.loads(json_data)