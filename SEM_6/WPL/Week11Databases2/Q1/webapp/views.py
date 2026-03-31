from django.shortcuts import render, redirect
from .forms import BookForm, AuthorForm, PublisherForm
from .models import Book

def add_book(request):
    if request.method == "POST":
        form = BookForm(request.POST)
        if form.is_valid():
            form.save()
            return redirect('book_list')
    else:
        form = BookForm()

    return render(request, 'add_book.html', {'form': form})


def book_list(request):
    books = Book.objects.all()
    return render(request, 'book_list.html', {'books': books})

def add_author(request):
    form = AuthorForm(request.POST or None)
    if form.is_valid():
        form.save()
        return redirect('add_book')
    return render(request, 'add_author.html', {'form': form})


def add_publisher(request):
    form = PublisherForm(request.POST or None)
    if form.is_valid():
        form.save()
        return redirect('add_book')
    return render(request, 'add_publisher.html', {'form': form})