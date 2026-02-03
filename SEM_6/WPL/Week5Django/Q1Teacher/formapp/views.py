from django.shortcuts import render
from .forms import StudentForm

def index(request):
    form = StudentForm()
    details = ""
    percentage = None

    if request.method == "POST":
        form = StudentForm(request.POST)
        if form.is_valid():
            data = form.cleaned_data

            total = data['english'] + data['physics'] + data['chemistry']
            percentage = total / 3

            details = (
                f"Name: {data['name']}\n"
                f"DOB: {data['dob']}\n"
                f"Address: {data['address']}\n"
                f"Contact: {data['contact']}\n"
                f"Email: {data['email']}\n"
                f"English: {data['english']}\n"
                f"Physics: {data['physics']}\n"
                f"Chemistry: {data['chemistry']}\n"
            )

    return render(request, "formapp/index.html", {
        "form": form,
        "details": details,
        "percentage": percentage
    })
