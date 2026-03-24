from django.shortcuts import render, redirect
from .models import Works, Lives
from .forms import CombinedForm, SearchForm

def index(request):
    return render(request, 'dbapp/index.html')

def add_data(request):
    if request.method == 'POST':
        form = CombinedForm(request.POST)

        if form.is_valid():
            person = form.cleaned_data['person_name']
            company = form.cleaned_data['company_name']
            salary = form.cleaned_data['salary']
            street = form.cleaned_data['street']
            city = form.cleaned_data['city']

            # Insert into WORKS (always)
            Works.objects.create(
                person_name=person,
                company_name=company,
                salary=salary
            )

            # Insert into LIVES (only if provided)
            if street and city:
                Lives.objects.create(
                    person_name=person,
                    street=street,
                    city=city
                )

            return redirect('index')

    else:
        form = CombinedForm()

    return render(request, 'dbapp/add_data.html', {'form': form})

# Search by company
def search_company(request):
    results = []

    if request.method == 'POST':
        form = SearchForm(request.POST)
        if form.is_valid():
            company = form.cleaned_data['company_name']

            works_people = Works.objects.filter(company_name=company)

            for w in works_people:
                try:
                    live = Lives.objects.get(person_name=w.person_name)
                    results.append({
                        'name': w.person_name,
                        'city': live.city
                    })
                except Lives.DoesNotExist:
                    results.append({
                        'name': w.person_name,
                        'city': 'Not Found'
                    })
    else:
        form = SearchForm()

    return render(request, 'dbapp/search.html', {
        'form': form,
        'results': results
    })