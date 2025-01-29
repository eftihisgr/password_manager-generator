import tkinter as tk
from tkinter import ttk
import random
import string
from datetime import datetime

# Function to generate a random password
def generate_password():
    length = int(length_var.get())
    include_special = special_var.get()

    lower_case = string.ascii_lowercase
    upper_case = string.ascii_uppercase
    digits = string.digits
    symbols = '!@#$%^&*()-_=+[{]}\\|;:\'",<.>/?' if include_special else ''

    all_chars = lower_case + upper_case + digits + symbols
    password = ''.join(random.choice(all_chars) for _ in range(length))
    password_var.set(password)

# Function to save data to a file and clear all textboxes
def save_data():
    title = title_entry.get()
    email = email_entry.get()
    username = username_entry.get()
    password = password_var.get()

    # Save data to file
    with open("passwords.txt", "a") as f:
        f.write(f"Title: {title}\n")
        f.write(f"Email: {email}\n")
        f.write(f"Username: {username}\n")
        f.write(f"Password: {password}\n")
        f.write(f"Time: {datetime.now().strftime('%d-%m-%Y %H:%M:%S')}\n")
        f.write("==========================================\n")

    # Clear all textboxes
    title_entry.delete(0, tk.END)
    email_entry.delete(0, tk.END)
    username_entry.delete(0, tk.END)
    password_var.set("")
    length_var.set("12")
    special_var.set(False)
    save_label.config(text="Saved Successfully!", foreground="green")

# Function to toggle password visibility
def toggle_password_visibility():
    if password_entry.cget("show") == "*":
        password_entry.config(show="")
        toggle_button.config(text="Hide Password")
    else:
        password_entry.config(show="*")
        toggle_button.config(text="Show Password")

# Initialize Tkinter
root = tk.Tk()
root.title("Password Manager | By eftihis")

# Create and place labels and entries
title_label = ttk.Label(root, text="Title:")
title_label.grid(row=0, column=0, padx=10, pady=5, sticky="w")
title_entry = ttk.Entry(root, width=30)
title_entry.grid(row=0, column=1, padx=10, pady=5)

email_label = ttk.Label(root, text="Email:")
email_label.grid(row=1, column=0, padx=10, pady=5, sticky="w")
email_entry = ttk.Entry(root, width=30)
email_entry.grid(row=1, column=1, padx=10, pady=5)

username_label = ttk.Label(root, text="Username:")
username_label.grid(row=2, column=0, padx=10, pady=5, sticky="w")
username_entry = ttk.Entry(root, width=30)
username_entry.grid(row=2, column=1, padx=10, pady=5)

password_label = ttk.Label(root, text="Password:")
password_label.grid(row=3, column=0, padx=10, pady=5, sticky="w")
password_var = tk.StringVar()
password_entry = ttk.Entry(root, textvariable=password_var, width=30, show='*')
password_entry.grid(row=3, column=1, padx=10, pady=5)

toggle_button = ttk.Button(root, text="Show Password", command=toggle_password_visibility)
toggle_button.grid(row=3, column=2, padx=10, pady=5)

# Generate password settings
settings_label = ttk.Label(root, text="Password Settings:")
settings_label.grid(row=4, column=0, padx=10, pady=5, sticky="w")

length_label = ttk.Label(root, text="Length:")
length_label.grid(row=5, column=0, padx=10, pady=5, sticky="w")
length_var = tk.StringVar(value="12")  # Default length
length_entry = ttk.Entry(root, textvariable=length_var, width=5)
length_entry.grid(row=5, column=1, padx=10, pady=5, sticky="w")

special_var = tk.BooleanVar()
special_checkbox = ttk.Checkbutton(root, text="Include special characters", variable=special_var)
special_checkbox.grid(row=6, column=0, columnspan=2, padx=10, pady=5, sticky="w")

generate_button = ttk.Button(root, text="Generate Password", command=generate_password)
generate_button.grid(row=7, column=0, columnspan=2, padx=10, pady=10)

# Save button
save_button = ttk.Button(root, text="Save", command=save_data)
save_button.grid(row=8, column=0, columnspan=2, padx=10, pady=10)

# Save status label
save_label = ttk.Label(root, text="")
save_label.grid(row=9, column=0, columnspan=2)

# Run the main loop
root.mainloop()
