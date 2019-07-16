from django.urls import path

from . import views

urlpatterns = [
    path('', views.index, name='index'),
    path('charts', views.charts, name='charts'),
    path('api/avg-tph', views.jsonAvgData, name='avgAPI'),
    path('api/min-tph', views.jsonMinData, name='minAPI'),
    path('api/max-tph', views.jsonMaxData, name='maxAPI'),
]