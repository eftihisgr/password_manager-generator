# password_manager-generator

This is a C script with GUI that assist you manage your passwords. The user inputs a tittle, an email, username and the password they want to save. They have the option to leave an input blank. There is also a password generator that allows the user to random generate a strong password with the length they desire including special characters (!@#$%^&*()-_=+[{]}\\|;:\'",<.>/?) if the option is checked. The passwords are saved in a ```passwords.txt``` file which is going to be created in the same directory ```password_manager.c``` is compiled.

# WARNING
The script saves a ```passwords.txt``` file with the passwords **UNENCRYPTED**. This means that anyone who has access to the ```passwords.txt```file, will have access to passwords saved in the file

# Requirements
* Unix/linux enviroment
* GTK development libraries

# Notes
* There is a python version in the folder [python version](https://github.com/eftihisgr/password_manager-generator/tree/main/python%20version)
* The file ```password_manager``` in the main direcory, is a compiled version of the ```password_manager.c```

# How to run the code
Before running this program, you need to install GTK development libraries. On Linux, you can install them using:
```
sudo apt install libgtk-3-dev
```

Compile the program while you are in the same directory with the c file, by using:
```
gcc -o password_manager password_manager.c `pkg-config --cflags --libs gtk+-3.0`
```

Execute the programm with:
```
./password_manager
```
