#from PyQt5.QtCore import *
#from PyQt5.QtGui import *
from PyQt5.QtWidgets import QMainWindow,QMessageBox,QTableWidgetItem,QApplication

import sqlite3
import sys

from PyQt5.uic import loadUiType

ui, _ = loadUiType('D:\gensin\Lenard\BSCS\CCC151_InfoManagement\SecondAssignment\main.ui')


class MainApp(QMainWindow, ui):
    def __init__(self):
        QMainWindow.__init__(self)
        self.setupUi(self)
        self.tabWidget.setCurrentIndex(0)

        self.connect_db()
        self.showStudentTab()
        self.buttonHandles()

        self.studentTable.itemSelectionChanged.connect(self.enableStudentDeleteButton)
        self.courseTable.itemSelectionChanged.connect(self.enableCourseDeleteButton)

    def buttonHandles(self):
        self.studentCourses.clicked.connect(self.showCourseTab)
        self.coursesStudent.clicked.connect(self.showStudentTab)
        self.studentAdd.clicked.connect(self.addStudent)
        self.courseAdd.clicked.connect(self.addCourse)

        self.studentDelete.clicked.connect(self.deleteStudent)
        self.courseDelete.clicked.connect(self.deleteCourse)

    def showCourseTab(self):
        self.updateCourseDisplay()
        self.tabWidget.setCurrentIndex(1)

    def showStudentTab(self):
        self.updateStudentDisplay()
        self.tabWidget.setCurrentIndex(0)

    def connect_db(self):
        self.connection = sqlite3.connect("students1.db")
        self.Cursor = self.connection.cursor()
        self.create_tables()


    def create_tables(self):
        self.Cursor.execute(
            "CREATE TABLE IF NOT EXISTS students (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, gender TEXT, course_id INTEGER, age INTEGER, yearlevel TEXT)")
        self.Cursor.execute(
            "CREATE TABLE IF NOT EXISTS courses (id INTEGER PRIMARY KEY AUTOINCREMENT, code TEXT, name TEXT)")
        self.connection.commit()

    def getOrCreateCourse(self, course):
        self.cursor.execute("SELECT id, name FROM courses WHERE code=?", (course,))
        course_data = self.cursor.fetchone()

        if course_data:
            return course_data[0]
        else:
            msg_box = QMessageBox()
            msg_box.setWindowTitle("Course not Found")
            msg_box.setText(f"The course with course code {course} is not found")
            msg_box.setInformativeText("Do you want to add the corresponding Course first?")
            msg_box.setStandardButtons(QMessageBox.Yes | QMessageBox.No)
            response = msg_box.exec_()

            if response == QMessageBox.Yes:
                self.showCourseTab()
            else:
                self.showStudentTab()

    def clearStudentField(self):
        self.studentName.clear()
        self.studentGender.clear()
        self.studentId.clear()
        self.studentCourse.clear()
        self.studentAge.clear()
        self.studentYear.clear()

    def addStudent(self):
        name = self.studentName.text()
        gender = self.studentGender.currentText()
        id = self.studentId.text()
        course = self.studentCourse.text()
        age = self.studentAge.text()
        yearlevel = self.studentYear.text()

        if name and gender and id and course and age and yearlevel:
            course_id = self.getOrCreateCourse(course)
            if course_id is not None:
                self.cursor.execute(
                    "INSERT INTO students (id, name, gender, course_id, age, yearlevel) VALUES (?, ?, ?, ?, ?, ?)",
                    (id, name, gender, course, age, yearlevel))
                self.connection.commit()
                QMessageBox.information(self, "Success", "Student added successfully.")
                self.clearStudentField()
                self.showStudentTab()
        else:
            QMessageBox.warning(self, "Error", "Please Enter All Fields")

    def clearCourseField(self):
        self.courseCode.clear()
        self.courseName.clear()

    def addCourse(self):
        course_code = self.courseCode.text()
        course_name = self.courseName.text()

        if course_code and course_name:
            self.cursor.execute("INSERT into courses (code, name) VALUES (?, ?)", (course_code, course_name))
            self.connection.commit()
            QMessageBox.information(self, "Success", "Course added successfully.")
            self.clearCourseField()
            self.showCourseTab()
        else:
            QMessageBox.warning(self, "Error", "Please enter the course code and course name.")

    def searchStudent(self):
        pass

    def displayCourseData(self, data):
        self.courseTable.setRowCount(0)
        for row_number, row_data in enumerate(data):
            self.courseTable.insertRow(row_number)
            for column_number, data in enumerate(row_data):
                self.courseTable.setItem(row_number, column_number, QTableWidgetItem(str(data)))

    def displayStudentData(self, data):
        self.studentTable.setRowCount(0)
        for row_number, row_data in enumerate(data):
            self.studentTable.insertRow(row_number)
            for column_number, data in enumerate(row_data):
                self.studentTable.setItem(row_number, column_number, QTableWidgetItem(str(data)))

    def updateStudentDisplay(self):
        self.Cursor.execute("SELECT * FROM students")
        data = self.Cursor.fetchall()
        self.displayStudentData(data)

    def updateCourseDisplay(self):
        self.Cursor.execute("SELECT * FROM courses ")
        data = self.Cursor.fetchall()
        self.displayCourseData(data)

    def enableStudentDeleteButton(self):
        selected_rows = self.studentTable.selectedItems()
        enable = len(selected_rows) > 0
        self.studentDelete.setEnabled(enable)

    def enableCourseDeleteButton(self):
        selected_rows = self.courseTable.selectedItems()
        enable = len(selected_rows) > 0
        self.courseDelete.setEnabled(enable)

    def deleteStudent(self):
        selected_rows = self.studentTable.selectedItems()
        if len(selected_rows) == 0:
            return

        row = selected_rows[0].row()
        student_id = self.studentTable.item(row, 0).text()

        msg_box = QMessageBox()
        msg_box.setWindowTitle("Delete Student")
        msg_box.setText(f"Are you sure you want to delete student with ID {student_id}?")
        msg_box.setStandardButtons(QMessageBox.Yes | QMessageBox.No)
        response = msg_box.exec_()

        if response == QMessageBox.Yes:
            self.cursor.execute("DELETE FROM students WHERE id=?", (student_id,))
            self.connection.commit()
            self.updateStudentDisplay()
            QMessageBox.information(self, "Success", "Student deleted successfully.")

    def deleteCourse(self):
        selected_rows = self.courseTable.selectedItems()
        if len(selected_rows) == 0:
            return

        row = selected_rows[0].row()
        course_id = self.courseTable.item(row, 0).text()

        msg_box = QMessageBox()
        msg_box.setWindowTitle("Delete Course")
        msg_box.setText(f"Are you sure you want to delete course with ID {course_id}?")
        msg_box.setStandardButtons(QMessageBox.Yes | QMessageBox.No)
        response = msg_box.exec_()

        if response == QMessageBox.Yes:
            self.cursor.execute("DELETE FROM courses WHERE id=?", (course_id,))
            self.connection.commit()
            self.updateCourseDisplay()
            QMessageBox.information(self, "Success", "Course deleted successfully.")

    def editCourse(self):
        pass

    def editStudent(self):
        pass

    def search(self):
        pass


def main():
    app = QApplication(sys.argv)
    window = MainApp()
    window.show()
    sys.exit(app.exec())


if __name__ == '__main__':
    main()
