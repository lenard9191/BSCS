import os
def addStudent():
    with open("file.txt" , "a") as file:
        name = input("Enter Name: ")
        while True:
            id = input("Enter ID-NO (in format xxxx-xxxx): ")
            if len(id) == 9 and id[4] == "-":
                break
            else:
                print("Invalid ID-NO. Please enter in format xxxx-xxxx!")
        course = input("Enter Course: ")
        age = input("Enter Age: ")
        file.write(f"{name} , {id} , {course} , {age} \n")
        print("Student added successfully.")
        

def listStudent():
    if os.path.exists("file.txt"):
        with open("file.txt" , "r" ) as file:
            print(file.read())
    else:
        print("File not found/No Student yet")



def deleteStudent():
    id = input("Enter the ID of the student to delete: ")
    with open("file.txt", "r") as file:
        lines = file.readlines()
    with open("file.txt", "w") as file:
        deleted = False
        for line in lines:
            if id not in line.split(",")[1]:
                file.write(line)
            else:
                deleted = True
        if deleted:
            print("Student deleted successfully.")
        else:
            print("Student not found.")

def searchStudent():
    id = input("Enter the ID of the student to search: ")
    with open("file.txt", "r") as file:
        found = False
        for line in file:
            if id in line.split(",")[1]:
                print(line.strip())
                found = True
                break
        if not found:
            print("Student not found.")


while True:
    choice = input("Enter your Choice \n 1: Add Student \n 2: Delete Student \n 3: Search Student \n 4: List Student \n 5: Quit \n Choice: ")
    if choice == "1":
        addStudent()
    elif choice == "2":
        deleteStudent()
    elif choice == "3":
        searchStudent()
    elif choice == "4":
        listStudent()
    elif choice == "5":
        break
    else:
        print("Wrong Choice")