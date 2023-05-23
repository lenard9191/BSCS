import os
import sys
from PySide6.QtWidgets import QApplication, QWidget, QVBoxLayout, QLabel, QLineEdit, QPushButton

class StudentManagement(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Student Management")
        self.layout = QVBoxLayout()
        self.setup_ui()

    def setup_ui(self):
        add_button = QPushButton("Add Student")
        add_button.clicked.connect(self.add_student)
        self.layout.addWidget(add_button)

        delete_button = QPushButton("Delete Student")
        delete_button.clicked.connect(self.delete_student)
        self.layout.addWidget(delete_button)

        search_button = QPushButton("Search Student")
        search_button.clicked.connect(self.search_student)
        self.layout.addWidget(search_button)

        list_button = QPushButton("List Students")
        list_button.clicked.connect(self.list_students)
        self.layout.addWidget(list_button)

        quit_button = QPushButton("Quit")
        quit_button.clicked.connect(self.close)
        self.layout.addWidget(quit_button)

        self.setLayout(self.layout)

    def add_student(self):
        name, ok = QLineEdit.getText(QLineEdit("Enter Name"))
        if ok:
            while True:
                id, ok = QLineEdit.getText(QLineEdit("Enter ID-NO (in format xxxx-xxxx)"))
                if ok and len(id) == 9 and id[4] == "-":
                    break
                else:
                    print("Invalid ID-NO. Please enter in format xxxx-xxxx!")

            course, ok = QLineEdit.getText(QLineEdit("Enter Course"))
            if ok:
                age, ok = QLineEdit.getText(QLineEdit("Enter Age"))
                if ok:
                    with open("file.txt", "a") as file:
                        file.write(f"{name}, {id}, {course}, {age}\n")
                        print("Student added successfully.")

    def list_students(self):
        if os.path.exists("file.txt"):
            with open("file.txt", "r") as file:
                print(file.read())
        else:
            print("File not found/No students yet")

    def delete_student(self):
        id, ok = QLineEdit.getText(QLineEdit("Enter the ID of the student to delete"))
        if ok:
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

    def search_student(self):
        search_input, ok = QLineEdit.getText(QLineEdit("Enter the ID or NAME of the student to search"))
        if ok:
            with open("file.txt", "r") as file:
                found = False
                for line in file:
                    info = line.split(",")
                    student_id = info[1].strip()
                    student_name = info[0].strip()
                    if search_input == student_id or search_input.lower() == student_name.lower():
                        print(line.strip())
                        found = True
                        break
                if not found:
                    print("Student not found.")

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = StudentManagement()
    window.show()
    sys.exit(app.exec())
