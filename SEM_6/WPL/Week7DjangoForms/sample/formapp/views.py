from django.shortcuts import render

from django.http import HttpResponse
from django.contrib.auth import logout

# Create your views here.
from .forms import RegForm, LoginForm

"""
# def home_view(req):
#     context = {}
#     form = RegForm(req.POST or None)
#     context['form'] = form
#     return render(req, "home.html", context)

def login(request):
    if request.method == "POST":
        form = LoginForm(request.POST)
        if form.is_valid():
            username = form.cleaned_data['username']
            cn = form.cleaned_data['contact_num']
            return render(
                request,
                'loggedin.html',
                {'username': username, 'contact_num': cn}
            )
    else:
        form = LoginForm()

    # GET request OR invalid POST → show login form
    return render(request, 'login.html', {'form': form})
"""



def login(request):
    username = 'not logged in'

    if request.method == 'POST':
        MyLoginForm = LoginForm(request.POST)
        if MyLoginForm.is_valid():
            username = MyLoginForm.cleaned_data['username']
            request.session['username'] = username
    else:
        MyLoginForm = LoginForm()

    return render(request, 'loggedin.html', {"username": username})


def formView(request):
    if request.session.has_key('username'):
        username = request.session['username']
        return render(request, 'loggedin.html', {"username": username})
    else:
        return render(request, 'login.html', {})


def logout_view(request):
    try:
        del request.session['username']
    except KeyError:
        pass

    return HttpResponse("<strong>You are logged out.</strong>")