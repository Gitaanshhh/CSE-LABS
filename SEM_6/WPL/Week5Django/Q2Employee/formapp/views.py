from django.shortcuts import render
from .forms import PromotionForm
from datetime import date

def promotion(request):
    form = PromotionForm()
    result = None

    if request.method == "POST":
        form = PromotionForm(request.POST)
        if form.is_valid():
            doj = form.cleaned_data['doj']
            today = date.today()

            years = today.year - doj.year - (
                (today.month, today.day) < (doj.month, doj.day)
            )

            result = "YES" if years > 5 else "NO"

    return render(request, "formapp/promotion.html", {
        "form": form,
        "result": result
    })
