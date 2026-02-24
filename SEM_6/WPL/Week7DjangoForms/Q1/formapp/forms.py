# carapp/forms.py
from django import forms

class CarForm(forms.Form):
    manufacturer = forms.ChoiceField(choices=[
        ('Toyota', 'Toyota'),
        ('Honda', 'Honda'),
        ('Ford', 'Ford'),
    ])
    model = forms.CharField(max_length=50)