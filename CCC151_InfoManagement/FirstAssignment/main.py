import os


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

        deleted = False
        for line in lines:
            if id in line.split(",")[1]:
                confirm = input("Are you sure you want to delete this student? (y/n): ")
                if confirm.lower() == "y":
                    lines.remove(line)
                    deleted = True
                break

        if deleted:
            with open("file.txt", "w") as file:
                file.writelines(lines)
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
                    print("CourseCode Exist")
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

        deleted = False
        for line in lines:
            if course_code in line.split(",")[0]:
                confirm = input("Are you sure you want to delete this course? (y/n): ")
                if confirm.lower() == "y":
                    lines.remove(line)
                    deleted = True
                break

        if deleted:
            with open("course.txt", "w") as file:
                file.writelines(lines)
            print("Course deleted successfully.")
            with open("file.txt", "r") as student_file:
                lines = student_file.readlines()

            updated_lines = []
            for line in lines:
                student_info = line.split(", ")
                student_course = student_info[3].strip()
                if student_course == course_code:
                    student_info[3] = "None"
                updated_line = ", ".join(student_info)
                updated_lines.append(updated_line)

            with open("file.txt", "w") as student_file:
                student_file.writelines(updated_lines)
        else:
            print("Course not found.")
    else:
        print("No Course File Yet")


def editCourse():
    if os.path.exists("course.txt"):
        course_code = input("Enter the CourseCode to edit: ")
        with open("course.txt", "r") as file:
            lines = file.readlines()

        edited = False
        for index, line in enumerate(lines):
            if course_code == line.split(",")[0]:
                edited = True
                print("Enter new details for the course:")
                new_course_code = input("Enter New CourseCode: ")
                new_course_name = input("Enter New CourseName: ")

                # Check if the new course code is already taken
                for l in lines:
                    if new_course_code == l.split(",")[0]:
                        edited = False
                        print("Error: Course with the same code already exists.")
                        break

                if edited:
                    lines[index] = f"{new_course_code}, {new_course_name}\n"
                    break

        if edited:
            with open("course.txt", "w") as file:
                file.writelines(lines)
            print("Course edited successfully.")
        else:
            print("Course not found.")
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
                studentid = info[1].strip()
                studentname = info[0].strip()
                if search_input == studentid or search_input.lower() == studentname.lower():
                    print(line.strip())
                    found = True
                    break
            if not found:
                print("Student not found.")
    else:
        print("No Student File Yet")


def checkStudentExists(id):
    if os.path.exists("file.txt"):
        with open("file.txt", "r") as file:
            for line in file:
                student_id = line.split(",")[1].strip()
                if id == student_id:
                    return True
    return False


def checkCourseExists(course_code):
    if os.path.exists("course.txt"):
        with open("course.txt", "r") as file:
            for line in file:
                existing_course_code = line.split(",")[0].strip()
                if course_code == existing_course_code:
                    return True
    return False

def editStudent():
    if os.path.exists("file.txt"):
        student_id = input("Enter the STUDENT ID to edit: ")
        with open("file.txt", "r") as file:
            lines = file.readlines()

        edited = False
        for index, line in enumerate(lines):
            if student_id == line.split(",")[1].lstrip():
                edited = True
                print("Enter new details for the student:")
                name = input("Enter New StudentName: ")
                id = input("Enter New Student ID: ")
                gender = input("Enter New Student Gender: ")
                course = input("Enter New Student Course: ")
                age = input("Enter New Student Age: ")
                if not checkCourseExists(course):
                    print("Error: Course does not exist.")
                    return
                # Check if the new course code is already taken
                if checkStudentExists(id):
                    print("Error: Student with the same ID already exists.")
                    return

                if edited:
                    lines[index] = f"{name}, {id}, {gender}, {course}, {age}\n"
                    break

        if edited:
            with open("file.txt", "w") as file:
                file.writelines(lines)
            print("Student edited successfully.")
        else:
            print("Student not found.")
    else:
        print("No Student File Yet")

def addStudent():
    if not os.path.exists("file.txt"):
        open("file.txt", "w").close()  # Create an empty file if it doesn't exist

    name = input("Enter Name: ")
    id = input("Enter ID-NO: ")
    gender = input("Enter Gender: ")
    course = input("Enter CourseCode: ")
    if checkStudentExists(id):
        print("Error: Student with the same ID already exists.")
        return
    if not checkCourseExists(course):
        print("Error: Course does not exist.")
        return
    age = input("Enter Age: ")

    with open("file.txt", "a") as file:
        file.write(f"{name}, {id}, {gender}, {course}, {age}\n")
        print("Student added successfully.")




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