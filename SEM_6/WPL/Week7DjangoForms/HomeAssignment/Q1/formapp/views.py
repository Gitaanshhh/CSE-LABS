# groceryapp/views.py
from django.shortcuts import render

ITEMS = {
    'Wheat': 40,
    'Jaggery': 60,
    'Dal': 80,
}

def grocery(request):
    selected_items = {}

    if request.method == "POST":
        chosen = request.POST.getlist('items')
        for item in chosen:
            selected_items[item] = ITEMS[item]

    context = {
        'items': ITEMS,
        'selected_items': selected_items
    }
    return render(request, 'grocery.html', context)