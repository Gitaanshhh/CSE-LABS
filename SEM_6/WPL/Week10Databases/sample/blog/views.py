from django.shortcuts import render, redirect
from .models import BlogPost, BlogPostForm

def archive(request):
    posts = BlogPost.objects.all()[:10]
    form = BlogPostForm()

    return render(request, 'archive.html', {
        'posts': posts,
        'form': form
    })


def create_blogpost(request):
    if request.method == 'POST':
        form = BlogPostForm(request.POST)
        if form.is_valid():
            form.save()
            return redirect('archive')

    return redirect('archive')