# Week 5: Django

## Virtual Environment

### Create

```
python -m venv dj-env
```

### Activate

```
source dj-env/bin/activate
```

---

## Creating a Project

### Create Project

```
django-admin startproject myproject
```

### Create App

```
python manage.py startapp webapp
```

Add `'webapp'` under `INSTALLED_APPS` in `settings.py` after running the command.

---

## Django Architecture

```
                Templates (Client Side)
------------------------------------------------
                |                    |
        Application Logic         View Logic
                |          (Django Framework)
------------------------------------------------
                    Model (Server Side)
                  (Persistent Data)
```

---

## Project Structure

`myproject` is the name of the project created.
The following files are created inside the directory:

```
myproject/
├─ manage.py              # CLI utility to interact with the Django project
├─ myproject/             # Actual Python package for the project
│  ├─ __init__.py         # Marks directory as a Python package
│  ├─ settings.py         # Manages all project settings
│  ├─ urls.py             # Main controller; maps URLs to apps
│  └─ wsgi.py              # Entry point for WSGI-compatible web servers
```

---

## Notes

* **WSGI** → Web Server Gateway Interface

---

## URL Routing Flow

**Project `urls.py`**

> “Which app handles this prefix?”

```
'' (project) + '' (app) = /
```

**App `urls.py`**

> “Which view handles the rest?”

```
'webapp/' + '' = /webapp/
```

---


## Sessions
Sessions are a way for Django to **store and remember data across multiple HTTP requests** for the same user.

HTTP is **stateless**, meaning:
- Each request is independent
- Django does not automatically remember previous requests

Sessions solve this by allowing Django to **associate data with a user over time**.

Sessions persist until:

- The browser is closed (default), or
- The session expires based on settings
- Expiry can be configured in settings.py

---

### Significance

Without sessions:
- Django cannot remember login status
- Django cannot count attempts (e.g., captcha failures)
- Django cannot track user-specific data across pages

Sessions allow Django to:
- Remember values like counters, flags, or user choices
- Maintain state without using custom database models

---

### Working

1. When a user visits a page, Django creates a **session ID**
2. This session ID is stored in the **browser cookie**
3. The actual session data is stored on the **server**
4. On every request:
   - Browser sends the session ID
   - Django retrieves the corresponding session data
   - Data is available via `request.session`

---

### Using

run 

``` python manage.py migrate ```

This creates the required `django_session` table.