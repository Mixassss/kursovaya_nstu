from PyQt5 import QtCore, QtGui, QtWidgets
import sys


class Ui_Dialog(object):
    def setupUi(self, Dialog):
        self.dialog = Dialog  # Сохраняем ссылку на диалог
        Dialog.setObjectName("Dialog")
        Dialog.setFixedSize(800, 600)
        Dialog.setStyleSheet("background-color: rgb(36, 31, 49);")
        self.frame_3 = QtWidgets.QFrame(Dialog)
        self.frame_3.setGeometry(QtCore.QRect(0, 0, 801, 491))
        self.frame_3.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_3.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_3.setObjectName("frame_3")
        self.frame_2 = QtWidgets.QFrame(self.frame_3)
        self.frame_2.setGeometry(QtCore.QRect(0, 120, 801, 371))
        self.frame_2.setAutoFillBackground(False)
        self.frame_2.setStyleSheet("background-color: rgb(119, 118, 123);")
        self.frame_2.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_2.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_2.setObjectName("frame_2")
        self.label_3 = QtWidgets.QLabel(self.frame_2)
        self.label_3.setGeometry(QtCore.QRect(0, 0, 711, 61))
        font = QtGui.QFont()
        font.setFamily("LM Roman 8")
        font.setPointSize(13)
        self.label_3.setFont(font)
        self.label_3.setObjectName("label_3")
        self.label_4 = QtWidgets.QLabel(self.frame_2)
        self.label_4.setGeometry(QtCore.QRect(10, 150, 751, 61))
        font = QtGui.QFont()
        font.setFamily("LM Roman 8")
        font.setPointSize(13)
        self.label_4.setFont(font)
        self.label_4.setObjectName("label_4")
        self.pushButton_4 = QtWidgets.QPushButton(self.frame_2)
        self.pushButton_4.setGeometry(QtCore.QRect(680, 330, 87, 27))
        self.pushButton_4.setStyleSheet("background-color: rgb(28, 113, 216);")
        self.pushButton_4.setObjectName("pushButton_4")
        self.pushButton_4.setEnabled(False)  # Деактивируем кнопку изначально
        self.pushButton_4.clicked.connect(self.check_answers)  # Подключаем кнопку к функции проверки ответов
        self.groupBox = QtWidgets.QGroupBox(self.frame_2)
        self.groupBox.setGeometry(QtCore.QRect(10, 40, 491, 111))
        self.groupBox.setTitle("")
        self.groupBox.setObjectName("groupBox")
        self.AnswerA = QtWidgets.QRadioButton(self.groupBox)
        self.AnswerA.setGeometry(QtCore.QRect(10, 10, 20, 20))
        self.AnswerA.setStyleSheet("color: rgb(224, 27, 36);")
        self.AnswerA.setObjectName("AnswerA")
        self.AnswerB = QtWidgets.QRadioButton(self.groupBox)
        self.AnswerB.setGeometry(QtCore.QRect(10, 30, 20, 31))
        self.AnswerB.setStyleSheet("color: rgb(224, 27, 36);")
        self.AnswerB.setObjectName("AnswerB")
        self.AnswerC = QtWidgets.QRadioButton(self.groupBox)
        self.AnswerC.setGeometry(QtCore.QRect(10, 60, 20, 21))
        self.AnswerC.setStyleSheet("color: rgb(224, 27, 36);")
        self.AnswerC.setObjectName("AnswerC")
        self.label_13 = QtWidgets.QLabel(self.groupBox)
        self.label_13.setGeometry(QtCore.QRect(30, 10, 461, 19))
        font = QtGui.QFont()
        font.setFamily("LM Roman 8")
        self.label_13.setFont(font)
        self.label_13.setObjectName("label_13")
        self.label_5 = QtWidgets.QLabel(self.groupBox)
        self.label_5.setGeometry(QtCore.QRect(30, 30, 461, 31))
        font = QtGui.QFont()
        font.setFamily("LM Roman 8")
        self.label_5.setFont(font)
        self.label_5.setObjectName("label_5")
        self.label_6 = QtWidgets.QLabel(self.groupBox)
        self.label_6.setGeometry(QtCore.QRect(30, 60, 371, 19))
        font = QtGui.QFont()
        font.setFamily("LM Roman 8")
        self.label_6.setFont(font)
        self.label_6.setObjectName("label_6")
        self.label_7 = QtWidgets.QLabel(self.groupBox)
        self.label_7.setGeometry(QtCore.QRect(30, 80, 421, 31))
        font = QtGui.QFont()
        font.setFamily("LM Roman 8")
        self.label_7.setFont(font)
        self.label_7.setObjectName("label_7")
        self.AnswerD = QtWidgets.QRadioButton(self.groupBox)
        self.AnswerD.setGeometry(QtCore.QRect(10, 80, 16, 31))
        self.AnswerD.setStyleSheet("color: rgb(224, 27, 36);")
        self.AnswerD.setObjectName("AnswerD")
        self.groupBox_2 = QtWidgets.QGroupBox(self.frame_2)
        self.groupBox_2.setGeometry(QtCore.QRect(10, 200, 131, 121))
        self.groupBox_2.setTitle("")
        self.groupBox_2.setObjectName("groupBox_2")
        self.AnswerA_2 = QtWidgets.QRadioButton(self.groupBox_2)
        self.AnswerA_2.setGeometry(QtCore.QRect(10, 0, 20, 31))
        self.AnswerA_2.setStyleSheet("color: rgb(224, 27, 36);")
        self.AnswerA_2.setObjectName("AnswerA_2")
        self.label_8 = QtWidgets.QLabel(self.groupBox_2)
        self.label_8.setGeometry(QtCore.QRect(30, 0, 66, 31))
        font = QtGui.QFont()
        font.setFamily("LM Roman 8")
        font.setPointSize(12)
        self.label_8.setFont(font)
        self.label_8.setObjectName("label_8")
        self.label_9 = QtWidgets.QLabel(self.groupBox_2)
        self.label_9.setGeometry(QtCore.QRect(30, 30, 66, 21))
        font = QtGui.QFont()
        font.setFamily("LM Roman 8")
        font.setPointSize(12)
        self.label_9.setFont(font)
        self.label_9.setObjectName("label_9")
        self.AnswerB_2 = QtWidgets.QRadioButton(self.groupBox_2)
        self.AnswerB_2.setGeometry(QtCore.QRect(10, 30, 16, 21))
        self.AnswerB_2.setStyleSheet("color: rgb(224, 27, 36);")
        self.AnswerB_2.setObjectName("AnswerB_2")
        self.label_10 = QtWidgets.QLabel(self.groupBox_2)
        self.label_10.setGeometry(QtCore.QRect(30, 50, 81, 31))
        font = QtGui.QFont()
        font.setFamily("LM Roman 8")
        font.setPointSize(12)
        self.label_10.setFont(font)
        self.label_10.setObjectName("label_10")
        self.label_11 = QtWidgets.QLabel(self.groupBox_2)
        self.label_11.setGeometry(QtCore.QRect(30, 80, 81, 21))
        self.label_11.setObjectName("label_11")
        self.AnswerC_2 = QtWidgets.QRadioButton(self.groupBox_2)
        self.AnswerC_2.setGeometry(QtCore.QRect(10, 56, 20, 20))
        self.AnswerC_2.setStyleSheet("color: rgb(224, 27, 36);")
        self.AnswerC_2.setObjectName("AnswerC_2")
        self.AnswerD_2 = QtWidgets.QRadioButton(self.groupBox_2)
        self.AnswerD_2.setGeometry(QtCore.QRect(10, 80, 16, 21))
        self.AnswerD_2.setStyleSheet("color: rgb(224, 27, 36);")
        self.AnswerD_2.setObjectName("AnswerD_2")
        self.frame = QtWidgets.QFrame(self.frame_3)
        self.frame.setGeometry(QtCore.QRect(0, 70, 801, 51))
        self.frame.setStyleSheet("background-color: rgb(224, 27, 36);")
        self.frame.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame.setObjectName("frame")
        self.label = QtWidgets.QLabel(self.frame)
        self.label.setGeometry(QtCore.QRect(10, 20, 211, 19))
        font = QtGui.QFont()
        font.setFamily("LM Roman 8")
        font.setPointSize(15)
        font.setBold(True)
        font.setWeight(75)
        self.label.setFont(font)
        self.label.setObjectName("label")
        self.label_12 = QtWidgets.QLabel(self.frame)
        self.label_12.setGeometry(QtCore.QRect(730, 0, 66, 51))
        font = QtGui.QFont()
        font.setFamily("Serif")
        font.setPointSize(20)
        font.setBold(True)
        font.setWeight(75)
        self.label_12.setFont(font)
        self.label_12.setObjectName("label_12")
        self.label_2 = QtWidgets.QLabel(self.frame_3)
        self.label_2.setGeometry(QtCore.QRect(10, 20, 491, 41))
        font = QtGui.QFont()
        font.setFamily("LM Roman 8")
        font.setPointSize(20)
        font.setBold(True)
        font.setWeight(75)
        self.label_2.setFont(font)
        self.label_2.setObjectName("label_2")
        self.pushButton = QtWidgets.QPushButton(Dialog)
        self.pushButton.setGeometry(QtCore.QRect(320, 530, 171, 41))
        self.pushButton.setObjectName("pushButton")
        self.pushButton.clicked.connect(self.exit_application)
        # Подключаем радиокнопки к методу проверки
        self.AnswerA.toggled.connect(self.update_submit_button_state)
        self.AnswerB.toggled.connect(self.update_submit_button_state)
        self.AnswerC.toggled.connect(self.update_submit_button_state)
        self.AnswerD.toggled.connect(self.update_submit_button_state)
        self.AnswerA_2.toggled.connect(self.update_submit_button_state)
        self.AnswerB_2.toggled.connect(self.update_submit_button_state)
        self.AnswerC_2.toggled.connect(self.update_submit_button_state)
        self.AnswerD_2.toggled.connect(self.update_submit_button_state)

        self.retranslateUi(Dialog)
        QtCore.QMetaObject.connectSlotsByName(Dialog)

    def update_submit_button_state(self):
        # Проверяем, выбраны ли ответы на оба вопроса
        first_question_answered = (
            self.AnswerA.isChecked() or
            self.AnswerB.isChecked() or
            self.AnswerC.isChecked() or
            self.AnswerD.isChecked()
        )
        
        second_question_answered = (
            self.AnswerA_2.isChecked() or
            self.AnswerB_2.isChecked() or
            self.AnswerC_2.isChecked() or
            self.AnswerD_2.isChecked()
        )
        
        # Активируем кнопку, если оба вопроса отвечены
        self.pushButton_4.setEnabled(first_question_answered and second_question_answered)

    def exit_application(self):
        # Закрываем диалог
        self.dialog.close()

    def check_answers(self):
        score = 0

        # Проверяем первый вопрос
        if self.AnswerB.isChecked():  # Правильный ответ B
            score += 1
            self.AnswerB.setStyleSheet("color: rgb(224, 27, 36); background-color: rgb(0, 255, 0);")  # Зеленый фон для правильного ответа
        else:
            # Если выбран неверный ответ, меняем фон на красный
            if self.AnswerA.isChecked():
                self.AnswerA.setStyleSheet("color: rgb(224, 27, 36); background-color: rgb(255, 0, 0);")
            elif self.AnswerC.isChecked():
                self.AnswerC.setStyleSheet("color: rgb(224, 27, 36); background-color: rgb(255, 0, 0);")
            elif self.AnswerD.isChecked():
                self.AnswerD.setStyleSheet("color: rgb(224, 27, 36); background-color: rgb(255, 0, 0);")

        # Проверяем второй вопрос
        if self.AnswerC_2.isChecked():  # Правильный ответ C
            score += 1
            self.AnswerC_2.setStyleSheet("color: rgb(224, 27, 36); background-color: rgb(0, 255, 0);")  # Зеленый фон для правильного ответа
        else:
            # Если выбран неверный ответ, меняем фон на красный
            if self.AnswerA_2.isChecked():
                self.AnswerA_2.setStyleSheet("color: rgb(224, 27, 36); background-color: rgb(255, 0, 0);")
            elif self.AnswerB_2.isChecked():
                self.AnswerB_2.setStyleSheet("color: rgb(224, 27, 36); background-color: rgb(255, 0, 0);")
            elif self.AnswerD_2.isChecked():
                self.AnswerD_2.setStyleSheet("color: rgb(224, 27, 36); background-color: rgb(255, 0, 0);")

        # Блокируем радиокнопки после выбора ответа
        self.AnswerA.setEnabled(False)
        self.AnswerB.setEnabled(False)
        self.AnswerC.setEnabled(False)
        self.AnswerD.setEnabled(False)
        self.AnswerA_2.setEnabled(False)
        self.AnswerB_2.setEnabled(False)
        self.AnswerC_2.setEnabled(False)
        self.AnswerD_2.setEnabled(False)

        # Деактивируем кнопку "Ответить" после проверки
        self.pushButton_4.setEnabled(False)

    
    def retranslateUi(self, Dialog):
        _translate = QtCore.QCoreApplication.translate
        Dialog.setWindowTitle(_translate("Dialog", "Обучающая система"))
        self.label_3.setText(_translate("Dialog", "1.  Что такое область видимости имени в программе? "))
        self.label_4.setText(_translate("Dialog", "2.  Какой оператор используется для разветвления процесса вычислений на \n"
"несколько направлений в C++?"))
        self.pushButton_4.setText(_translate("Dialog", "Ответить"))
        self.AnswerA.setText(_translate("Dialog", "RadioButton"))
        self.AnswerB.setText(_translate("Dialog", "RadioButton"))
        self.AnswerC.setText(_translate("Dialog", "RadioButton"))
        self.label_13.setText(_translate("Dialog", "A) Время, в течение которого имя существует в памяти"))
        self.label_5.setText(_translate("Dialog", "B) Часть программы, где имя может быть использовано"))
        self.label_6.setText(_translate("Dialog", "C) Место, где имя может быть использовано"))
        self.label_7.setText(_translate("Dialog", "D) Область памяти, выделенная для переменной"))
        self.AnswerD.setText(_translate("Dialog", "RadioButton"))
        self.AnswerA_2.setText(_translate("Dialog", "RadioButton"))
        self.label_8.setText(_translate("Dialog", "A) for"))
        self.label_9.setText(_translate("Dialog", "B) while"))
        self.AnswerB_2.setText(_translate("Dialog", "RadioButton"))
        self.label_10.setText(_translate("Dialog", "C) switch"))
        self.label_11.setText(_translate("Dialog", "D) do while"))
        self.AnswerC_2.setText(_translate("Dialog", "RadioButton"))
        self.AnswerD_2.setText(_translate("Dialog", "RadioButton"))
        self.label.setText(_translate("Dialog", "Условие заданий"))
        self.label_12.setText(_translate("Dialog", "2Б"))
        self.label_2.setText(_translate("Dialog", "1. Вопросы легкой сложности"))
        self.pushButton.setText(_translate("Dialog", "Вернуться на главную"))


if __name__ == "__main__":
    app = QtWidgets.QApplication(sys.argv)
    Dialog = QtWidgets.QDialog()
    ui = Ui_Dialog()
    ui.setupUi(Dialog)
    Dialog.show()
    sys.exit(app.exec_())