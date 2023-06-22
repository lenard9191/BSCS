import os

def editStudent():
    if os.path.exists("file.txt"):
        id_input = input("Enter the ID of the student to edit: ")
        with open("file.txt", "r") as file:
            lines = file.readlines()
        with open("file.txt", "w") as file:
            edited = False
            for line in lines:
                if id_input not in line.split(",")[1]:
                    file.write(line)
                else:
                    edited = True
                    name = input("Enter New Name: ")
                    id = input("Enter New ID-NO: ")
                    gender = input("Enter New Gender: ")
                    course = input("Enter New CourseCode: ")
                    createCourse(course)
                    age = input("Enter New Age: ")
                    file.write(f"{name}, {id}, {gender}, {course}, {age}\n")
                    print("Student edited successfully.")
            if not edited:
                print("Student not found.")
    else:
        print("No Student File Yet")

def addStudent():
    name = input("Enter Name: ")
    id = input("Enter ID-NO: ")
    gender = input("Enter Gender: ")
    course = input("Enter CourseCode: ")
    createCourse(course)
    age = input("Enter Age: ")
    
    with open("file.txt", "a") as file:
        file.write(f"{name}, {id}, {gender}, {course}, {age}\n")
        print("Student added successfully.")

def listStudent():
    if os.path.exists("file.txt"):
        with open("file.txt", "r") as file:
            print(file.read())
    else:
        print("File not found/No Student yet")


def deleteStudent():
    if os.path.exists("file.txt"):
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
    else:
        print("No File Yet")

def createCourse(course):
    if not os.path.exists("course.txt"):
        with open("course.txt", "w") as course_file:
            course_code = course
            course_name = input("Enter Course Name: ")
            course_file.write(f"{course_code},{course_name}\n")
            print("Course created successfully.")
    else:
        course_code = course
        with open("course.txt", "r") as course_file:
            courses = course_file.readlines()
            for line in courses:
                if course_code in line:
                    return
        course_name = input("Enter Course Name: ")
        with open("course.txt", "a") as course_file:
            course_file.write(f"{course_code},{course_name}\n")
            print("Course added successfully.")

def deleteCourse():
    if os.path.exists("course.txt"):
        course_code = input("Enter the CourseCode to Delete: ")
        with open("course.txt", "r") as file:
            lines = file.readlines()
        with open("course.txt", "w") as file:
            deleted = False
            for line in lines:
                if course_code not in line.split(",")[0]:
                    file.write(line)
                else:
                    deleted = True
            if deleted:
                print("CourseCode Deleted :")
            else:
                print("Course not FOund")
    else:
        print("No Course File Yet")
                

def editCourse():
    if os.path.exists("course.txt"):
        course_code = input("Enter the CourseCode to Edit: ")
        with open("course.txt", "r") as file:
            lines = file.readlines()
        with open("course.txt", "w") as file:
            edited = False
            for line in lines:
                if course_code not in line.split(",")[1]:
                    file.write(line)
                else:
                    edited = True
                    course_code = input("Enter New Name: ")
                    
                    course_name = input("Enter New CourseName: ")
                    
                    file.write(f"{course_code},{course_name}\n")
                    print("Course edited successfully.")
            if not edited:
                print("Course Not Found not found.")
    else:
        print("No Course File Yet")

def listCourse():
    if os.path.exists("course.txt"):
        with open("course.txt", "r") as file:
            print(file.read())
    else:
        print("File not found/No Courses yet.")


def searchStudent():
    if os.path.exists("file.txt"):
        search_input = input("Enter the ID or the NAME of the student to search: ")
        with open("file.txt", "r") as file:
            found = False
            for line in file:
                info = line.split(",")
                studentid = info[1].strip();
                studentname = info[2].strip();
                if search_input == studentid or search_input.lower() == studentname.lower():
                    print(line.strip())
                    found = True
                    break
            if not found:
                print("Student not found.")
    else:
        print("No Studnt File Yet")


while True:
    choice = input("Enter your Choice \n 1: Add Student \n 2: Edit Student \n 3: Delete Student \n 4: Search Student \n 5: List Student \n 6: Create Course \n 7: Edit Course \n 8: List Course \n 9: Delete Course \n 10: Quit \n Choice: ")
    if choice == "1":
        addStudent()
    elif choice == "2":
        editStudent()
    elif choice == "3":
        deleteStudent()
    elif choice == "4":
        searchStudent()
    elif choice == "5":
        listStudent()
    elif choice == "6":
        course = input("Enter CourseCode: ")
        createCourse(course)
    elif choice == "7":
        editCourse()
    elif choice == "8":
        listCourse()
    elif choice == "9":
        deleteCourse()
    elif choice == "10":
        break
    else:
        print("Wrong Choice")