from django.urls import path
from . import views

urlpatterns = [
    path('', views.index, name = 'index'),
    path('all-data/', views.all_data, name='all_data'),
]
