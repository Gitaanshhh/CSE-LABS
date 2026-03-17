from django.shortcuts import render

# Create your views here.

def register(request):
    if request.method == "POST":
        username = request.POST.get('username')
        email = request.POST.get('email')
        contact = request.POST.get('contact')

        context = {
            'username': username,
            'email': email,
            'contact': contact
        }

        return render(request, 'success.html', context)

    return render(request, 'register.html')


def success(request):
    return render(request, 'success.html')