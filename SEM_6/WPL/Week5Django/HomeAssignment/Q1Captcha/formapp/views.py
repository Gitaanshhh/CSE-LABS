from django.shortcuts import render

CAPTCHA_TEXT = "X7P9K"

def captcha_view(request):
    if 'attempts' not in request.session:
        request.session['attempts'] = 0

    message = ""
    disabled = False

    if request.method == "POST":
        user_input = request.POST.get("captcha")

        if user_input == CAPTCHA_TEXT:
            message = "Captcha Matched"
            request.session['attempts'] = 0
        else:
            request.session['attempts'] += 1
            if request.session['attempts'] >= 3:
                message = "Too many failed attempts. Textbox disabled."
                disabled = True
            else:
                message = "Captcha Mismatch"

    if request.session['attempts'] >= 3:
        disabled = True

    return render(request, "formapp/captcha.html", {
        "captcha": CAPTCHA_TEXT,
        "message": message,
        "disabled": disabled
    })
