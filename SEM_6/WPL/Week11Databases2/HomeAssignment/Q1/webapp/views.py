from django.shortcuts import render, redirect
from .forms import StudentForm
from .models import Student

def student_page(request):
    if request.method == 'POST':
        form = StudentForm(request.POST)
        if form.is_valid():
            form.save()
            return redirect('/')
    else:
        form = StudentForm()

    students = Student.objects.all()

    return render(request, 'students.html', {
        'form': form,
        'students': students
    })