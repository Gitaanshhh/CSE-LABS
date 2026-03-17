from django.shortcuts import render

# Create your views here.
from django.shortcuts import redirect

def page1(request):

    if request.method == "POST":
        name = request.POST.get('name')
        marks = request.POST.get('marks')

        cgpa = float(marks) / 50

        # Store in session
        request.session['name'] = name
        request.session['cgpa'] = cgpa

        return redirect('page2')

    return render(request, 'page1.html')


def page2(request):

    name = request.session.get('name')
    cgpa = request.session.get('cgpa')

    return render(request, 'page2.html', {'name': name, 'cgpa': cgpa})