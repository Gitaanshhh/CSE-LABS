from django import forms
from .models import Book, Author, Publisher

class BookForm(forms.ModelForm):
    class Meta:
        model = Book
        fields = ['title', 'publication_date', 'authors', 'publisher']
        widgets = {
            'publication_date': forms.DateInput(attrs={'type': 'date'}),
        }

class AuthorForm(forms.ModelForm):
    class Meta:
        model = Author
        fields = '__all__'


class PublisherForm(forms.ModelForm):
    class Meta:
        model = Publisher
        fields = '__all__'