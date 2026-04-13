from django import forms
from django.core.validators import RegexValidator
from .models import loginModel

"""
Plain Django form (NOT tied to a model).
validation/processing and not directly save to DB.
"""
class SimpleLoginForm(forms.Form):
    username = forms.CharField(max_length=100)
    password = forms.CharField(widget=forms.PasswordInput())


class DemoValidationForm(forms.Form):
    name = forms.CharField(max_length=100, required=True)
    age = forms.IntegerField(min_value=1)
    phone = forms.CharField(
        max_length=10,
        validators=[RegexValidator(r"^\d{10}$", message="Enter exactly 10 digits.")],
    )
    # checkbox: must be checked only if required=True
    accept_terms = forms.BooleanField(required=True)
    gender = forms.ChoiceField(
        choices=[("M", "Male"), ("F", "Female"), ("O", "Other")],
        widget=forms.RadioSelect,
    )
    # empty string should not be allowed when submitted
    city = forms.CharField(required=True, strip=True)


class loginForm(forms.ModelForm):
    """
    ModelForm is tied to loginModel. Django auto-builds fields from the model.
    model -> chooses which table this form saves to
    fields -> chooses which model columns appear in HTML form
    widgets -> custom HTML input type (password box here)
    """
    class Meta:
        model = loginModel
        fields = ["username", "password"]
        widgets = {
            "password": forms.PasswordInput(),
        }

"""
ModelForm can also add validation/widgets for model-backed fields.
This is useful when the database table exists, but you still want stricter input rules.
"""
class loginFormWithValidation(forms.ModelForm):
    username = forms.CharField(required=True, strip=True, max_length=100)
    password = forms.CharField(widget=forms.PasswordInput(), required=True)

    class Meta:
        model = loginModel
        fields = ["username", "password"]