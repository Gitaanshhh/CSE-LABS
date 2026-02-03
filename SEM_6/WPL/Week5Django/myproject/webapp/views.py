from django.shortcuts import render

from django.http import HttpResponse, Http404 
from datetime import date
import calendar
from calendar import HTMLCalendar


# Create your views here.

def index(req):
    return HttpResponse("<H2>Hey! Welcome! </H2>")

def cal(req, year, month):
    if month < 1 or month > 12:
        raise Http404("Invalid month")
    year = int(year)
    month = int(month)
    if year < 1900 or year > 2099:
        year = date.today().year
    month_name = calendar.month_name[month]
    title = "MyClub Event Calendar - %s %s" % (month_name, year)
    cal = HTMLCalendar().formatmonth(year, month)
    # return HttpResponse("<h1>%s</h1><p>%s</p>" % (title, cal))
    return render(req, 'base.html', {'title':title, 'cal':cal})