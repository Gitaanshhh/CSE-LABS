from django.urls import path
from . import views

urlpatterns = [
    path('', views.human_page, name='human_page'),
]