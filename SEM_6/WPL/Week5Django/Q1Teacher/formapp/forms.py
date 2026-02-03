from django import forms

class StudentForm(forms.Form):
    name = forms.CharField(max_length=100)
    dob = forms.DateField(widget=forms.DateInput(attrs={'type': 'date'}))
    address = forms.CharField(widget=forms.Textarea(attrs={'rows': 3}))
    contact = forms.CharField(max_length=15)
    email = forms.EmailField()

    english = forms.IntegerField(min_value=0, max_value=100)
    physics = forms.IntegerField(min_value=0, max_value=100)
    chemistry = forms.IntegerField(min_value=0, max_value=100)
