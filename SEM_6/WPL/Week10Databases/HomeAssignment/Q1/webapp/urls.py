from django.urls import path
from . import views

urlpatterns = [
    path('institutes/', views.institute_list, name='institute_list'),
]