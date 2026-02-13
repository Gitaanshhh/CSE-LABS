from django.urls import path
from . import views

urlpatterns = [
    path('', views.home),
    path('metadata/', views.metadata),
    path('reviews/', views.reviews),
    path('publisher/', views.publisher),
]
