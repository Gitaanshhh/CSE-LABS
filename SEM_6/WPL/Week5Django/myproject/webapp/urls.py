from django.urls import path, re_path

from . import views

urlpatterns = [
    path('', views.index, name='index'), #View referenced -> returns index (def in views.py)
    path('<int:year>/<int:month>/', views.cal, name='cal'),
]


# url pattern is in regular expression format where ^ stands for beginning of the string and $ stands for the end.

