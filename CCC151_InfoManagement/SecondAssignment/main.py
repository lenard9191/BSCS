import sqlite3
import sys

from PyQt5.QtWidgets import *

from PyQt5.uic import loadUiType

ui, _ = loadUiType('main.ui')


class MainApp(QMainWindow, ui):
    def __init__(self):
        QMainWindow.__init__(self)
        self.setupUi(self)
        self.tabWidget.setCurrentIndex(0)

        self.connect_db()
        self.showStudentTab()
        self.buttonHandles()

        self.studentSearchLine.textChanged.connect(self.searchStudent)
        self.courseSearchLine.textChanged.connect(self.searchCourse)

        self.studentTable.itemSelectionChanged.connect(self.enableStudentDeleteButton)
        self.courseTable.itemSelectionChanged.connect(self.enableCourseDeleteButton)

        self.studentCancel.hide()
        self.courseCancel.hide()
        self.studentUpdate.hide()
        self.courseUpdate.hide()

    def buttonHandles(self):
        self.studentCourses.clicked.connect(self.showCourseTab)
        self.coursesStudent.clicked.connect(self.showStudentTab)
        self.studentAdd.clicked.connect(self.addStudent)
        self.courseAdd.clicked.connect(self.addCourse)

        self.studentDelete.clicked.connect(self.deleteStudent)
        self.courseDelete.clicked.connect(self.deleteCourse)

        self.studentEdit.clicked.connect(self.populateStudentFields)
        self.courseEdit.clicked.connect(self.populateCourseFields)


        self.courseUpdate.clicked.connect(self.updateCourse)
        self.studentUpdate.clicked.connect(self.updateStudent)

        self.studentCancel.clicked.connect(self.studentCancelButton)
        self.courseCancel.clicked.connect(self.courseCancelButton)


    def studentCancelButton(self):
        self.clearStudentField()
        self.showStudentTab()
        self.studentUpdate.hide()
        self.studentAdd.show()
        self.studentEdit.show()
        self.studentCancel.hide()

    def courseCancelButton(self):
        self.clearCourseField()
        self.showCourseTab()
        self.courseUpdate.hide()
        self.courseAdd.show()
        self.courseEdit.show()
        self.courseCancel.hide()
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
        try:
            self.Cursor.execute(
                "CREATE TABLE IF NOT EXISTS students (id TEXT PRIMARY KEY , name TEXT, gender TEXT, course_id INTEGER, age INTEGER, yearlevel TEXT)")
            self.Cursor.execute(
                "CREATE TABLE IF NOT EXISTS courses (code TEXT PRIMARY KEY, name TEXT)")
            self.connection.commit()
        except Exception as e:
            print("ERROR", str(e))

    def getOrCreateCourse(self, course):
        self.Cursor.execute("SELECT code FROM courses WHERE code=?", (course,))
        course_data = self.Cursor.fetchone()

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
        self.studentGender.setCurrentIndex(0)
        self.studentId.clear()
        self.studentCourse.clear()
        self.studentAge.clear()
        self.studentYear.setCurrentIndex(0)

    def addStudent(self):
        try:
            name = self.studentName.text()
            gender = self.studentGender.currentText()
            id = self.studentId.text()
            course = self.studentCourse.text()
            age = self.studentAge.text()
            yearlevel = self.studentYear.currentText()

            if name and gender and id and course and age and yearlevel:
                course_id = self.getOrCreateCourse(course)
                if course_id is not None:
                    # Check if the student with the same ID or name already exists
                    self.Cursor.execute("SELECT * FROM students WHERE id=? OR name=?", (id, name))
                    existing_student = self.Cursor.fetchone()

                    if existing_student:
                        QMessageBox.warning(self, "Error", "Student with the same ID or name already exists.")
                    else:
                        self.Cursor.execute(
                            "INSERT INTO students (id, name, gender, course_id, age, yearlevel) VALUES (?, ?, ?, ?, ?, ?)",
                            (id, name, gender, course_id, age, yearlevel))
                        self.connection.commit()
                        QMessageBox.information(self, "Success", "Student added successfully.")
                        self.clearStudentField()
                        self.showStudentTab()
            else:
                QMessageBox.warning(self, "Error", "Please Enter All Fields")
        except Exception as e:
            print("ERROR", str(e))

    def clearCourseField(self):
        self.courseCode.clear()
        self.courseName.clear()

    def addCourse(self):
        course_code = self.courseCode.text()
        course_name = self.courseName.text()

        if course_code and course_name:
            # Check if the course code already exists
            self.Cursor.execute("SELECT code FROM courses WHERE code=?", (course_code,))
            existing_course = self.Cursor.fetchone()

            if existing_course:
                QMessageBox.warning(self, "Error", "Course with the same code already exists.")
            else:
                self.Cursor.execute("INSERT INTO courses (code, name) VALUES (?, ?)", (course_code, course_name))
                self.connection.commit()
                QMessageBox.information(self, "Success", "Course added successfully.")
                self.clearCourseField()
                self.showCourseTab()
        else:
            QMessageBox.warning(self, "Error", "Please enter the course code and course name.")


    def displayCourseData(self, data):
        self.courseTable.setRowCount(0)
        for row_number, row_data in enumerate(data):
            self.courseTable.insertRow(row_number)
            for column_number, data in enumerate(row_data):
                self.courseTable.setItem(row_number, column_number, QTableWidgetItem(str(data)))

    def displayStudentData(self, data):
        self.studentTable.clearContents()
        self.studentTable.setRowCount(0)
        for row_number, row_data in enumerate(data):
            self.studentTable.insertRow(row_number)
            for column_number, data in enumerate(row_data):
                if data is None:
                    data = "None"
                self.studentTable.setItem(row_number, column_number, QTableWidgetItem(str(data)))

    def updateStudentDisplay(self):
        self.Cursor.execute("SELECT students.id, students.name, students.gender, courses.code, students.age, students.yearlevel FROM students LEFT JOIN courses ON students.course_id=courses.code")
        data = self.Cursor.fetchall()
        self.displayStudentData(data)

    def updateCourseDisplay(self):
        self.Cursor.execute("SELECT * FROM courses")
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
    def populateStudentFields(self):
        try:
            self.studentEdit.hide()
            self.studentAdd.hide()
            self.studentCancel.show()
            selected_rows = self.studentTable.selectedItems()
            if len(selected_rows) == 0:
                return

            row = selected_rows[0].row()
            student_id = self.studentTable.item(row, 0).text()

            self.Cursor.execute("SELECT * FROM students WHERE id=?", (student_id,))
            student_data = self.Cursor.fetchone()

            if student_data:
                self.studentName.setText(student_data[1])
                self.studentGender.setCurrentText(student_data[2])
                self.studentId.setText(student_data[0])
                self.studentCourse.setText(student_data[3])
                self.studentAge.setText(str(student_data[4]))
                self.studentYear.setCurrentText(student_data[5])

                self.studentUpdate.show()
        except Exception as e:
            print("ERROR", str(e))

    def populateCourseFields(self):
        try:
            self.courseEdit.hide()
            self.courseAdd.hide()
            self.courseCancel.show()
            selected_rows = self.courseTable.selectedItems()
            if len(selected_rows) == 0:
                return

            row = selected_rows[0].row()
            course_code = self.courseTable.item(row, 0).text()

            self.Cursor.execute("SELECT * FROM courses WHERE code=?", (course_code,))
            course_data = self.Cursor.fetchone()

            if course_data:
                self.courseCode.setText(course_data[0])
                self.courseName.setText(course_data[1])

                self.courseUpdate.show()
        except Exception as e:
            print("ERROR", str(e))

    def updateStudent(self):
        try:
            name = self.studentName.text()
            gender = self.studentGender.currentText()
            id = self.studentId.text()
            course = self.studentCourse.text()
            age = self.studentAge.text()
            yearlevel = self.studentYear.currentText()

            if name and gender and id and course and age and yearlevel:
                course_id = self.getOrCreateCourse(course)
                if course_id is not None:
                    # Check if there's another student with the same ID or name
                    self.Cursor.execute("SELECT * FROM students WHERE (id=? OR name=?) AND id!=?", (id, name, id))
                    existing_student = self.Cursor.fetchone()

                    if existing_student:
                        QMessageBox.warning(self, "Error", "Another student with the same ID or name already exists.")
                    else:
                        self.Cursor.execute(
                            "UPDATE students SET name=?, gender=?, course_id=?, age=?, yearlevel=? WHERE id=?",
                            (name, gender, course_id, age, yearlevel, id))
                        self.connection.commit()
                        QMessageBox.information(self, "Success", "Student updated successfully.")
                        self.clearStudentField()
                        self.showStudentTab()
                        self.studentUpdate.hide()
                        self.studentAdd.show()
            else:
                QMessageBox.warning(self, "Error", "Please Enter All Fields")
        except Exception as e:
            print("ERROR", str(e))

    def updateCourse(self):
        try:
            code = self.courseCode.text()
            name = self.courseName.text()

            if code and name:
                # Check if the course code already exists (excluding the current course being updated)
                self.Cursor.execute("SELECT code FROM courses WHERE code=? AND code!=?", (code, code))
                existing_course = self.Cursor.fetchone()

                if existing_course:
                    QMessageBox.warning(self, "Error", "Another course with the same code already exists.")
                else:
                    self.Cursor.execute("UPDATE courses SET name=? WHERE code=?", (name, code))
                    self.connection.commit()
                    QMessageBox.information(self, "Success", "Course updated successfully.")
                    self.clearCourseField()
                    self.showCourseTab()
                    self.courseUpdate.hide()
                    self.courseAdd.show()
            else:
                QMessageBox.warning(self, "Error", "Please Enter All Fields")
        except Exception as e:
            print("ERROR", str(e))

    def deleteStudent(self):
        try:
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
                self.Cursor.execute("DELETE FROM students WHERE id=?", (student_id,))
                self.connection.commit()
                self.updateStudentDisplay()
                QMessageBox.information(self, "Success", "Student deleted successfully.")
        except Exception as e:
            print("ERROR", str(e))

    def deleteCourse(self):
        try:
            selected_rows = self.courseTable.selectedItems()
            if len(selected_rows) == 0:
                return

            row = selected_rows[0].row()
            course_code = self.courseTable.item(row, 0).text()

            msg_box = QMessageBox()
            msg_box.setWindowTitle("Delete Course")
            msg_box.setText(f"Are you sure you want to delete course with ID {course_code}?")
            msg_box.setStandardButtons(QMessageBox.Yes | QMessageBox.No)
            response = msg_box.exec_()

            if response == QMessageBox.Yes:
                # Check if any student has the course code
                self.Cursor.execute("SELECT * FROM students WHERE course_id=?", (course_code,))
                students_with_course = self.Cursor.fetchall()

                if students_with_course:
                    # Update course_id to None for students with the deleted course code
                    self.Cursor.execute("UPDATE students SET course_id=NULL WHERE course_id=?", (course_code,))

                self.Cursor.execute("DELETE FROM courses WHERE code=?", (course_code,))
                self.connection.commit()
                self.updateCourseDisplay()
                self.updateStudentDisplay()  # Update the student table to show "None" for deleted course code
                QMessageBox.information(self, "Success", "Course deleted successfully.")
        except Exception as e:
            print("ERROR", str(e))

    def searchStudent(self):
        try:
            search_text = self.studentSearchLine.text()
            if search_text:
                self.Cursor.execute('''SELECT * FROM students 
                                       WHERE students.id LIKE ? 
                                           OR students.name LIKE ? 
                                           OR students.gender LIKE ? 
                                           OR students.age LIKE ? 
                                           OR students.yearlevel LIKE ?
                                           OR students.course_id LIKE ?
                                       '''
                                    , ('%' + search_text + '%', '%' + search_text + '%', '%' + search_text + '%',
                                       '%' + search_text + '%', '%' + search_text + '%', '%' + search_text + '%'))
                data = self.Cursor.fetchall()
                self.displayStudentData(data)
            else:
                self.updateStudentDisplay()
        except Exception as e:
            print("ERROR", str(e))

    def searchCourse(self):
        try:
            search_text = self.courseSearchLine.text()
            if search_text:
                self.Cursor.execute('''SELECT * FROM courses 
                                       WHERE courses.code LIKE ? 
                                           OR courses.name LIKE ? 
                                       '''
                                    , ('%' + search_text + '%', '%' + search_text + '%'))
                data = self.Cursor.fetchall()
                self.displayCourseData(data)
            else:
                self.updateCourseDisplay()
        except Exception as e:
            print("ERROR", str(e))

def main():
    app = QApplication(sys.argv)
    window = MainApp()
    window.show()
    sys.exit(app.exec())


if __name__ == '__main__':
    main()
