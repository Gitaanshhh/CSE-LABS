from django.shortcuts import render
from .forms import loginForm
from .models import loginModel


def index(request):
    """
    GET: user opens page -> show blank form.
    POST: user submits form -> validate and save.
    """
    if request.method == "POST":
        # Bind submitted HTML data to form fields.
        form = loginForm(request.POST)
        if form.is_valid():
            form.save()                     # inserts row in loginModel table.
            form = loginForm()              # New blank form after successful submit.
            return render(request, "index.html", {"form": form, "success": True})
    else:
        # First page load (GET) still needs a response, so we render the same page with empty form.
        form = loginForm()

    return render(request, "index.html", {"form": form})


def all_data(request):
    """
    Fetch all saved rows to display in a table.
    """
    records = loginModel.objects.all().order_by("-id")
    return render(request, "all_data.html", {"records": records})