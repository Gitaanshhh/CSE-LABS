from django import forms
from .models import Works, Lives

from django import forms

class CombinedForm(forms.Form):
    # WORKS fields
    person_name = forms.CharField(max_length=100)
    company_name = forms.CharField(max_length=100)
    salary = forms.IntegerField()

    # LIVES fields (optional)
    street = forms.CharField(max_length=200, required=False)
    city = forms.CharField(max_length=100, required=False)

class SearchForm(forms.Form):
    company_name = forms.CharField(max_length=100)