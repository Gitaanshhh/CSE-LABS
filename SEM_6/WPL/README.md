# Django Lab Cheat Sheet (Current Project)

## Starting a new project
```bash
django-admin startproject sample
cd sample
python manage.py startapp webapp 
```
### sample/settings.py : 
add webapp to installed_apps

### sample/urls.py
```python
from django.contrib import admin
from django.urls import path, include
urlpatterns = [
    path('admin/', admin.site.urls),
    path('', include('webapp.urls')),
]
```

### webapp/urls.py
```python
from django.urls import path, re_path
from . import views

urlpatterns = [
    path('', views.index, name='index'),
    path('<int:year>/<int:month>/', views.cal, name='cal'),
]
```

### webapp/views.py
```python
def index(req):
    return HttpResponse("<H2>Hey! Welcome! </H2>")

def login(request):
    username = 'not logged in'

    if request.method == 'POST':
        MyLoginForm = LoginForm(request.POST)
        if MyLoginForm.is_valid():
            username = MyLoginForm.cleaned_data['username']
            request.session['username'] = username
    else:
        MyLoginForm = LoginForm()

    return render(request, 'loggedin.html', {"username": username})
```

### webapp/forms.py
```python
from django import forms

class RegForm(forms.Form):
    title = forms.CharField()
    description = forms.CharField()
    views = forms.IntegerField()
    available = forms.BooleanField()

class LoginForm(forms.Form):
    username = forms.CharField(max_length = 100) 
    password = forms.CharField(widget = forms.PasswordInput())
```

### webapp/models.py
```python
from django.db import models
from django import forms

class BlogPost(models.Model):
    title = models.CharField(max_length=150)
    body = models.TextField()
    timestamp = models.DateTimeField(auto_now_add=True)

    class Meta:
        ordering = ['-timestamp']

class BlogPostForm(forms.ModelForm):
    class Meta:
        model = BlogPost
        fields = ['title', 'body']   # cleaner than exclude
```

### webapp/admin.py
```python
from django.contrib import admin
from .models import BlogPost

class BlogPostAdmin(admin.ModelAdmin):
    list_display = ('title', 'timestamp')

admin.site.register(BlogPost, BlogPostAdmin)
```

### webapp/templates/*.html
```html
<form action="{% url 'create_blogpost' %}" method="post">
    {% csrf_token %}
    {{ form.as_p }}
    <button type="submit">Submit</button>
</form>
{% for post in posts %}
    <h2>{{ post.title }}</h2>
    <p><strong>{{ post.timestamp }}</strong></p>
    <p>{{ post.body }}</p>
    <hr>
{% empty %}
    <p>No posts yet.</p>
{% endfor %}
```

### Running 
```bash
python manage.py makemigrations
python manage.py migrate
python manage.py runserver
```

## Flow to Remember
1. Model defines DB table.
2. Form validates user input.
3. View handles GET/POST.
4. Template shows HTML form/table.
5. URL maps browser path to view.

## Model -> ModelForm (connected)
```python
# models.py
class loginModel(models.Model):
    username = models.CharField(max_length=100)
    password = models.CharField(max_length=100)
```

```python
# forms.py
class loginForm(forms.ModelForm):
    class Meta:
        model = loginModel
        fields = ["username", "password"]
        widgets = {"password": forms.PasswordInput()}
```

## View with GET + POST
```python
def index(request):
    if request.method == "POST":
        form = loginForm(request.POST)
        if form.is_valid():
            form.save()
    else:
        form = loginForm()
    return render(request, "index.html", {"form": form})
```

## Template form basics
```html
<form action="{% url 'index' %}" method="POST">
    {% csrf_token %}
    {{ form.as_p }}
    <button type="submit">Save</button>
</form>
```

## Meaning of key tags
1. `{% csrf_token %}`: Cross-Site Request Forgery protection.
2. `method="POST"`: use for create/update/delete operations.
3. `action="{% url 'index' %}"`: submit to URL named `index` (safe if path changes).

## Forms without models (possible)
```python
class SimpleLoginForm(forms.Form):
    username = forms.CharField(max_length=100)
    password = forms.CharField(widget=forms.PasswordInput())
```

Use when you only need validation or custom processing and do not directly save with `form.save()`.

## Creating a superuser (admin)
```bash
python manage.py createsuperuser
```
The enter the username and password