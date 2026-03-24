from django.shortcuts import render
from .models import Institute

def institute_list(request):
    # Retrieve all institutes
    institutes = Institute.objects.all()
    return render(request, 'dbapp/institute_list.html', {'institutes': institutes})