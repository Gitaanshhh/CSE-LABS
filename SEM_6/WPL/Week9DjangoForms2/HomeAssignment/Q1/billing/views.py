from django.shortcuts import render

# Create your views here.

def page1(request):
    return render(request, 'page1.html')


def bill(request):

    if request.method == "POST":
        brand = request.POST.get('brand')
        items = request.POST.getlist('item')
        qty = int(request.POST.get('qty'))

        # Simple price list
        price = 0

        if "Mobile" in items:
            price += 10000

        if "Laptop" in items:
            price += 40000

        total = price * qty

        context = {
            'brand': brand,
            'items': items,
            'qty': qty,
            'total': total
        }

        return render(request, 'bill.html', context)