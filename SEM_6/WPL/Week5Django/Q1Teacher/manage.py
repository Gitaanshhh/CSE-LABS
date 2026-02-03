"""
Create a web form which allows the teacher to enter the student details like name,
date of birth, address, contact number, email id and marks of English, Physics and
Chemistry. After filling all the information and on clicking submit button, details
should be added to a textarea displayed on the same page. Display the total
percentage of marks obtained in a label.
"""


#!/usr/bin/env python
"""Django's command-line utility for administrative tasks."""
import os
import sys


def main():
    """Run administrative tasks."""
    os.environ.setdefault('DJANGO_SETTINGS_MODULE', 'Q1Teacher.settings')
    try:
        from django.core.management import execute_from_command_line
    except ImportError as exc:
        raise ImportError(
            "Couldn't import Django. Are you sure it's installed and "
            "available on your PYTHONPATH environment variable? Did you "
            "forget to activate a virtual environment?"
        ) from exc
    execute_from_command_line(sys.argv)


if __name__ == '__main__':
    main()
