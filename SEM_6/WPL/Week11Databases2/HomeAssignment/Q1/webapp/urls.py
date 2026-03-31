from django.urls import path
from . import views

urlpatterns = [
    path('', views.student_page, name='student_page'),
]