from django.shortcuts import render

# Create your views here.

def feedback(request):

    message = ""

    if request.method == "POST":
        name = request.POST.get('name')
        message = "Thanks " + name + " for your feedback."

    return render(request, "feedback.html", {"message": message})