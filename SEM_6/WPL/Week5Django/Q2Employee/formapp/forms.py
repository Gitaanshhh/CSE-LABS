from django import forms

class PromotionForm(forms.Form):
    EMP_CHOICES = [
        ('E001', 'E001'),
        ('E002', 'E002'),
        ('E003', 'E003'),
        ('E004', 'E004'),
    ]

    employee_id = forms.ChoiceField(choices=EMP_CHOICES)
    doj = forms.DateField(
        label="Date of Joining",
        widget=forms.DateInput(attrs={'type': 'date'})
    )
