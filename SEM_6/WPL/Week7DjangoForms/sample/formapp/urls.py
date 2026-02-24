from django.urls import path
from . import views

urlpatterns = [
    path('login/', views.login, name='login'),
    path('', views.formView, name='formView'),
    path('logout/', views.logout_view, name='logout'),
]