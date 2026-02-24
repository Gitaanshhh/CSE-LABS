# sessionapp/views.py
from django.shortcuts import render, redirect

def first_page(request):
    if request.method == "POST":
        request.session['name'] = request.POST.get('name')
        request.session['roll'] = request.POST.get('roll')
        request.session['subject'] = request.POST.get('subject')

        return redirect('second')

    return render(request, 'firstPage.html')


def second_page(request):
    context = {
        'name': request.session.get('name'),
        'roll': request.session.get('roll'),
        'subject': request.session.get('subject'),
    }
    return render(request, 'secondPage.html', context)