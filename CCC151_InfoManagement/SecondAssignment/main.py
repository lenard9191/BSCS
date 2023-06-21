import sys
from PyQt5.QtWidgets import QApplication, QMainWindow, QTabWidget, QWidget, QVBoxLayout, QLabel, QLineEdit, QPushButton, \
    QTableWidget, QTableWidgetItem, QMessageBox ,QInputDialog
from PyQt5.QtCore import Qt
import sqlite3


class StudentInfoTab(QWidget):
    def __init__(self, parent):
        super().__init__(parent)
        self.initialize_ui()

    def initialize_ui(self):
        self.lblID = QLabel("ID:", self)
        self.txtID = QLineEdit(self)

        self.lblName = QLabel("Name:", self)
        self.txtName = QLineEdit(self)

        self.lblCourse = QLabel("Course Code:", self)
        self.txtCourse = QLineEdit(self)

        self.lblAge = QLabel("Age:", self)
        self.txtAge = QLineEdit(self)

        self.btnAdd = QPushButton("Add Student", self)
        self.btnAdd.clicked.connect(self.parent().add_student)

        self.btnEdit = QPushButton("Edit Student", self)
        self.btnEdit.clicked.connect(self.parent().edit_student)

        self.btnDelete = QPushButton("Delete Student", self)
        self.btnDelete.clicked.connect(self.parent().delete_student)

        self.btnSearch = QPushButton("Search Student", self)
        self.btnSearch.clicked.connect(self.parent().search_student)

        self.btnListStudents = QPushButton("List Students", self)
        self.btnListStudents.clicked.connect(self.parent().list_students)

        self.tblData = QTableWidget(self)
        self.tblData.setColumnCount(4)
        self.tblData.setHorizontalHeaderLabels(["ID", "Name", "Course Code", "Age"])

        self.layout = QVBoxLayout()
        self.layout.addWidget(self.lblID)
        self.layout.addWidget(self.txtID)
        self.layout.addWidget(self.lblName)
        self.layout.addWidget(self.txtName)
        self.layout.addWidget(self.lblCourse)
        self.layout.addWidget(self.txtCourse)
        self.layout.addWidget(self.lblAge)
        self.layout.addWidget(self.txtAge)
        self.layout.addWidget(self.btnAdd)
        self.layout.addWidget(self.btnEdit)
        self.layout.addWidget(self.btnDelete)
        self.layout.addWidget(self.btnSearch)
        self.layout.addWidget(self.btnListStudents)
        self.layout.addWidget(self.tblData)

        self.setLayout(self.layout)

    def clear_fields(self):
        self.txtID.clear()
        self.txtName.clear()
        self.txtCourse.clear()
        self.txtAge.clear()

    def display_data(self, data):
        self.tblData.setRowCount(0)
        for row_number, row_data in enumerate(data):
            self.tblData.insertRow(row_number)
            for column_number, data in enumerate(row_data):
                self.tblData.setItem(row_number, column_number, QTableWidgetItem(str(data)))


class CourseInfoTab(QWidget):
    def __init__(self, parent):
        super().__init__(parent)
        self.initialize_ui()

    def initialize_ui(self):
        self.lblCourseCode = QLabel("Course Code:", self)
        self.txtCourseCode = QLineEdit(self)

        self.btnAddCourse = QPushButton("Add Course", self)
        self.btnAddCourse.clicked.connect(self.parent().add_course)

        self.btnEditCourse = QPushButton("Edit Course", self)
        self.btnEditCourse.clicked.connect(self.parent().edit_course)

        self.btnDeleteCourse = QPushButton("Delete Course", self)
        self.btnDeleteCourse.clicked.connect(self.parent().delete_course)

        self.btnSearchCourse = QPushButton("Search Course", self)
        self.btnSearchCourse.clicked.connect(self.parent().search_course)

        self.btnListCourses = QPushButton("List Courses", self)
        self.btnListCourses.clicked.connect(self.parent().list_courses)

        self.tblData = QTableWidget(self)
        self.tblData.setColumnCount(2)
        self.tblData.setHorizontalHeaderLabels(["Course Code", "Course Name"])
        

        self.layout = QVBoxLayout()
        self.layout.addWidget(self.lblCourseCode)
        self.layout.addWidget(self.txtCourseCode)
        self.layout.addWidget(self.btnAddCourse)
        self.layout.addWidget(self.btnEditCourse)
        self.layout.addWidget(self.btnDeleteCourse)
        self.layout.addWidget(self.btnSearchCourse)
        self.layout.addWidget(self.btnListCourses)
        self.layout.addWidget(self.tblData)

        self.setLayout(self.layout)

    def clear_fields(self):
        self.txtCourseCode.clear()

    def display_data(self, data):
        self.tblData.setRowCount(0)
        for row_number, row_data in enumerate(data):
            self.tblData.insertRow(row_number)
            for column_number, data in enumerate(row_data):
                self.tblData.setItem(row_number, column_number, QTableWidgetItem(str(data)))

    def display_data(self, data):
        self.tblData.setRowCount(0)
        for row_number, row_data in enumerate(data):
            self.tblData.insertRow(row_number)
            for column_number, data in enumerate(row_data):
                self.tblData.setItem(row_number, column_number, QTableWidgetItem(str(data)))


class StudentManagementSystem(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Student Management System")
        self.setFixedSize(600, 600)
        self.initialize_ui()
        self.connect_db()

    def initialize_ui(self):
        self.tabs = QTabWidget(self)
        self.tabStudentInfo = StudentInfoTab(self)
        self.tabCourseInfo = CourseInfoTab(self)

        self.tabs.addTab(self.tabStudentInfo, "Student Info")
        self.tabs.addTab(self.tabCourseInfo, "Courses")

        self.setCentralWidget(self.tabs)

    def connect_db(self):
        self.connection = sqlite3.connect("students1.db")
        self.cursor = self.connection.cursor()
        self.create_tables()

    def create_tables(self):
        self.cursor.execute(
            "CREATE TABLE IF NOT EXISTS students (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, course_id INTEGER, age INTEGER)")
        self.cursor.execute("CREATE TABLE IF NOT EXISTS courses (id INTEGER PRIMARY KEY AUTOINCREMENT, code TEXT, name TEXT)")
        self.connection.commit()

    def get_or_create_course(self, course_code):
        self.cursor.execute("SELECT id, name FROM courses WHERE code=?", (course_code,))
        course_data = self.cursor.fetchone()

        if course_data:
            return course_data[0]
        else:
            msg_box = QMessageBox()
            msg_box.setWindowTitle("Course Not Found")
            msg_box.setText(f"The course with code '{course_code}' is not found.")
            msg_box.setInformativeText("Do you want to add it?")
            msg_box.setStandardButtons(QMessageBox.Yes | QMessageBox.No)
            response = msg_box.exec_()

            if response == QMessageBox.Yes:
                course_name, ok = QInputDialog.getText(self, "Add Course", "Enter the course name:")
                if ok:
                    self.cursor.execute("INSERT INTO courses (code, name) VALUES (?, ?)", (course_code, course_name))
                    self.connection.commit()
                    return self.cursor.lastrowid
                else:
                    return None
            else:
                return None

    def add_student(self):
        id_input = self.tabStudentInfo.txtID.text()
        name = self.tabStudentInfo.txtName.text()
        course_code = self.tabStudentInfo.txtCourse.text()
        age = self.tabStudentInfo.txtAge.text()

        if id_input and name and course_code and age:
            course_id = self.get_or_create_course(course_code)
            if course_id is not None:
                self.cursor.execute("INSERT INTO students (id, name, course_id, age) VALUES (?, ?, ?, ?)",
                                    (id_input, name, course_id, age))
                self.connection.commit()
                QMessageBox.information(self, "Success", "Student added successfully.")
                self.tabStudentInfo.clear_fields()
        else:
            QMessageBox.warning(self, "Error", "Please fill in all the fields.")

    def edit_student(self):
        id_input = self.tabStudentInfo.txtID.text()
        name = self.tabStudentInfo.txtName.text()
        course_code = self.tabStudentInfo.txtCourse.text()
        age = self.tabStudentInfo.txtAge.text()

        if id_input and name and course_code and age:
            course_id = self.get_or_create_course(course_code)
            self.cursor.execute("UPDATE students SET name=?, course_id=?, age=? WHERE id=?",
                                (name, course_id, age, id_input))
            self.connection.commit()
            if self.cursor.rowcount > 0:
                QMessageBox.information(self, "Success", "Student edited successfully.")
            else:
                QMessageBox.warning(self, "Error", "Student not found.")
            self.tabStudentInfo.clear_fields()
        else:
            QMessageBox.warning(self, "Error", "Please fill in all the fields.")

    def delete_student(self):
        id_input = self.tabStudentInfo.txtID.text()

        if id_input:
            self.cursor.execute("DELETE FROM students WHERE id=?", (id_input,))
            self.connection.commit()
            if self.cursor.rowcount > 0:
                QMessageBox.information(self, "Success", "Student deleted successfully.")
            else:
                QMessageBox.warning(self, "Error", "Student not found.")
            self.tabStudentInfo.clear_fields()
        else:
            QMessageBox.warning(self, "Error", "Please enter the ID of the student to delete.")

    def search_student(self):
        search_input = self.tabStudentInfo.txtID.text()

        if search_input:
            self.cursor.execute(
                "SELECT students.id, students.name, courses.code, students.age FROM students INNER JOIN courses ON students.course_id=courses.id WHERE students.id=? OR students.name=?",
                (search_input, search_input))
            data = self.cursor.fetchall()
            self.tabStudentInfo.display_data(data)
        else:
            QMessageBox.warning(self, "Error", "Please enter the ID or the name of the student to search.")

    def list_students(self):
        self.cursor.execute("""
            SELECT students.id, students.name, courses.code, students.age
            FROM students
            LEFT JOIN courses ON students.course_id = courses.id
        """)
        data = self.cursor.fetchall()
        self.tabStudentInfo.display_data(data)

    def add_course(self):
        course_code = self.tabCourseInfo.txtCourseCode.text()

        if course_code:
            self.cursor.execute("INSERT INTO courses (code) VALUES (?)", (course_code,))
            self.connection.commit()
            QMessageBox.information(self, "Success", "Course added successfully.")
            self.tabCourseInfo.clear_fields()
        else:
            QMessageBox.warning(self, "Error", "Please enter the course code.")

    def edit_course(self):
        course_code = self.tabCourseInfo.txtCourseCode.text()

        if course_code:
            self.cursor.execute("UPDATE courses SET code=? WHERE code=?", (course_code, course_code))
            self.connection.commit()
            if self.cursor.rowcount > 0:
                QMessageBox.information(self, "Success", "Course edited successfully.")
            else:
                QMessageBox.warning(self, "Error", "Course not found.")
            self.tabCourseInfo.clear_fields()
        else:
            QMessageBox.warning(self, "Error", "Please enter the course code.")

    def delete_course(self):
        course_code = self.tabCourseInfo.txtCourseCode.text()

        if course_code:
            self.cursor.execute("DELETE FROM courses WHERE code=?", (course_code,))
            self.connection.commit()
            if self.cursor.rowcount > 0:
                QMessageBox.information(self, "Success", "Course deleted successfully.")
            else:
                QMessageBox.warning(self, "Error", "Course not found.")
            self.tabCourseInfo.clear_fields()
        else:
            QMessageBox.warning(self, "Error", "Please enter the course code.")

    def search_course(self):
        search_input = self.tabCourseInfo.txtCourseCode.text()

        if search_input:
            self.cursor.execute("SELECT code FROM courses WHERE code=?", (search_input,))
            data = self.cursor.fetchall()
            self.tabCourseInfo.display_data(data)
        else:
            QMessageBox.warning(self, "Error", "Please enter the course code to search.")

    def list_courses(self):
        self.cursor.execute("SELECT code, name FROM courses")
        data = self.cursor.fetchall()
        self.tabCourseInfo.display_data(data)

    def closeEvent(self, event):
        self.connection.close()


if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = StudentManagementSystem()
    window.show()
    sys.exit(app.exec_())
