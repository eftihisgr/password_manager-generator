# password_manager-generator

This is a C script with GUI that assist you manage your passwords. 

# WARNING
The script saves a ```passwords.txt``` file with the passwords **UNENCRYPTED**. This means that anyone who has access to the ```passwords.txt```file, will have access to passwords saved in the file

# Requirements
* Unix/linux enviroment
* GTK development libraries


# How to run the code
Before running this program, you need to install GTK development libraries. On Linux, you can install them using:
```
sudo apt install libgtk-3-dev
```

Compile the program using:
```
gcc -o password_manager password_manager.c `pkg-config --cflags --libs gtk+-3.0`
```

Execute the programm with:
```
./password_manager
```
