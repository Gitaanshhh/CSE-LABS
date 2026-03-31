from django.shortcuts import render, redirect, get_object_or_404
from .models import Human

def human_page(request):
    humans = Human.objects.all()

    selected_human = None


    # Create (Add new human)
    if request.method == 'POST' and 'add' in request.POST:
        Human.objects.create(
            first_name=request.POST['first_name'],
            last_name=request.POST['last_name'],
            phone=request.POST['phone'],
            address=request.POST['address'],
            city=request.POST['city']
        )
        return redirect('/')

    # When dropdown selection happens
    if request.method == 'GET' and 'human_id' in request.GET:
        selected_human = Human.objects.get(id=request.GET['human_id'])

    # Update
    if request.method == 'POST' and 'update' in request.POST:
        human = Human.objects.get(id=request.POST['human_id'])
        human.first_name = request.POST['first_name']
        human.last_name = request.POST['last_name']
        human.phone = request.POST['phone']
        human.address = request.POST['address']
        human.city = request.POST['city']
        human.save()
        return redirect('/')

    # Delete
    if request.method == 'POST' and 'delete' in request.POST:
        human = Human.objects.get(id=request.POST['human_id'])
        human.delete()
        return redirect('/')

    return render(request, 'human.html', {
        'humans': humans,
        'selected': selected_human
    })
