from django.urls import path
from . import views

urlpatterns = [
    path('', views.book_list, name='book_list'),
    path('add/', views.add_book, name='add_book'),
    path('add-author/', views.add_author, name='add_author'),
    path('add-publisher/', views.add_publisher, name='add_publisher'),
]