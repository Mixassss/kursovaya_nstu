from PyQt5 import QtCore, QtGui, QtWidgets
import sys


class Ui_Dialog(object):
    def setupUi(self, Dialog):
        self.dialog = Dialog  # Сохраняем ссылку на диалог
        Dialog.setObjectName("Dialog")
        Dialog.setFixedSize(800, 720)
        Dialog.setStyleSheet("background-color: rgb(36, 31, 49);")
        self.pushButton = QtWidgets.QPushButton(Dialog)
        self.pushButton.setGeometry(QtCore.QRect(320, 660, 171, 41))
        self.pushButton.setObjectName("pushButton")
        self.pushButton.clicked.connect(self.exit_application)
        self.frame_4 = QtWidgets.QFrame(Dialog)
        self.frame_4.setGeometry(QtCore.QRect(0, 0, 801, 641))
        self.frame_4.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_4.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_4.setObjectName("frame_4")
        self.frame_5 = QtWidgets.QFrame(self.frame_4)
        self.frame_5.setGeometry(QtCore.QRect(0, 120, 801, 521))
        self.frame_5.setAutoFillBackground(False)
        self.frame_5.setStyleSheet("background-color: rgb(119, 118, 123);")
        self.frame_5.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_5.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_5.setObjectName("frame_5")
        self.label_14 = QtWidgets.QLabel(self.frame_5)
        self.label_14.setGeometry(QtCore.QRect(0, 0, 711, 61))
        font = QtGui.QFont()
        font.setFamily("LM Roman 8")
        font.setPointSize(13)
        self.label_14.setFont(font)
        self.label_14.setObjectName("label_14")
        self.label_18 = QtWidgets.QLabel(self.frame_5)
        self.label_18.setGeometry(QtCore.QRect(10, 150, 751, 61))
        font = QtGui.QFont()
        font.setFamily("LM Roman 8")
        font.setPointSize(13)
        self.label_18.setFont(font)
        self.label_18.setObjectName("label_18")
        self.pushButton_6 = QtWidgets.QPushButton(self.frame_5)
        self.pushButton_6.setGeometry(QtCore.QRect(670, 470, 87, 27))
        self.pushButton_6.setEnabled(False)  # Деактивируем кнопку изначально
        self.pushButton_6.clicked.connect(self.check_answers)  # Подключаем кнопку к функции проверки ответов
        self.pushButton_6.setStyleSheet("background-color: rgb(28, 113, 216);")
        self.pushButton_6.setObjectName("pushButton_6")
        self.label_19 = QtWidgets.QLabel(self.frame_5)
        self.label_19.setGeometry(QtCore.QRect(10, 310, 461, 61))
        font = QtGui.QFont()
        font.setFamily("LM Roman 8")
        font.setPointSize(13)
        self.label_19.setFont(font)
        self.label_19.setObjectName("label_19")
        self.groupBox_2 = QtWidgets.QGroupBox(self.frame_5)
        self.groupBox_2.setGeometry(QtCore.QRect(20, 210, 121, 111))
        self.groupBox_2.setTitle("")
        self.groupBox_2.setObjectName("groupBox_2")
        self.label_15 = QtWidgets.QLabel(self.groupBox_2)
        self.label_15.setGeometry(QtCore.QRect(30, 1, 81, 31))
        font = QtGui.QFont()
        font.setFamily("LM Roman 8")
        self.label_15.setFont(font)
        self.label_15.setObjectName("label_15")
        self.label_16 = QtWidgets.QLabel(self.groupBox_2)
        self.label_16.setGeometry(QtCore.QRect(30, 30, 51, 21))
        font = QtGui.QFont()
        font.setFamily("LM Roman 8")
        self.label_16.setFont(font)
        self.label_16.setObjectName("label_16")
        self.label_17 = QtWidgets.QLabel(self.groupBox_2)
        self.label_17.setGeometry(QtCore.QRect(30, 50, 71, 31))
        font = QtGui.QFont()
        font.setFamily("LM Roman 8")
        self.label_17.setFont(font)
        self.label_17.setObjectName("label_17")
        self.label_20 = QtWidgets.QLabel(self.groupBox_2)
        self.label_20.setGeometry(QtCore.QRect(30, 80, 51, 21))
        font = QtGui.QFont()
        font.setFamily("LM Roman 8")
        self.label_20.setFont(font)
        self.label_20.setObjectName("label_20")
        self.AnswerA_2 = QtWidgets.QRadioButton(self.groupBox_2)
        self.AnswerA_2.setGeometry(QtCore.QRect(10, 10, 16, 16))
        self.AnswerA_2.setStyleSheet("color: rgb(224, 27, 36);")
        self.AnswerA_2.setText("")
        self.AnswerA_2.setObjectName("AnswerA_2")
        self.AnswerB_2 = QtWidgets.QRadioButton(self.groupBox_2)
        self.AnswerB_2.setGeometry(QtCore.QRect(10, 30, 20, 21))
        self.AnswerB_2.setStyleSheet("color: rgb(224, 27, 36);")
        self.AnswerB_2.setObjectName("AnswerB_2")
        self.AnswerC_2 = QtWidgets.QRadioButton(self.groupBox_2)
        self.AnswerC_2.setGeometry(QtCore.QRect(10, 50, 16, 31))
        self.AnswerC_2.setStyleSheet("color: rgb(224, 27, 36);")
        self.AnswerC_2.setObjectName("AnswerC_2")
        self.AnswerD_2 = QtWidgets.QRadioButton(self.groupBox_2)
        self.AnswerD_2.setGeometry(QtCore.QRect(10, 80, 16, 21))
        self.AnswerD_2.setStyleSheet("color: rgb(224, 27, 36);")
        self.AnswerD_2.setText("")
        self.AnswerD_2.setObjectName("AnswerD_2")
        self.groupBox_3 = QtWidgets.QGroupBox(self.frame_5)
        self.groupBox_3.setGeometry(QtCore.QRect(20, 360, 261, 111))
        self.groupBox_3.setTitle("")
        self.groupBox_3.setObjectName("groupBox_3")
        self.label_27 = QtWidgets.QLabel(self.groupBox_3)
        self.label_27.setGeometry(QtCore.QRect(30, 10, 211, 16))
        font = QtGui.QFont()
        font.setFamily("LM Roman 8")
        self.label_27.setFont(font)
        self.label_27.setObjectName("label_27")
        self.label_28 = QtWidgets.QLabel(self.groupBox_3)
        self.label_28.setGeometry(QtCore.QRect(30, 30, 211, 21))
        font = QtGui.QFont()
        font.setFamily("LM Roman 8")
        self.label_28.setFont(font)
        self.label_28.setObjectName("label_28")
        self.label_29 = QtWidgets.QLabel(self.groupBox_3)
        self.label_29.setGeometry(QtCore.QRect(30, 50, 211, 31))
        font = QtGui.QFont()
        font.setFamily("LM Roman 8")
        self.label_29.setFont(font)
        self.label_29.setObjectName("label_29")
        self.label_30 = QtWidgets.QLabel(self.groupBox_3)
        self.label_30.setGeometry(QtCore.QRect(30, 80, 181, 21))
        font = QtGui.QFont()
        font.setFamily("LM Roman 8")
        self.label_30.setFont(font)
        self.label_30.setObjectName("label_30")
        self.AnswerA_3 = QtWidgets.QRadioButton(self.groupBox_3)
        self.AnswerA_3.setGeometry(QtCore.QRect(10, 10, 16, 16))
        self.AnswerA_3.setStyleSheet("color: rgb(224, 27, 36);")
        self.AnswerA_3.setObjectName("AnswerA_3")
        self.AnswerB_3 = QtWidgets.QRadioButton(self.groupBox_3)
        self.AnswerB_3.setGeometry(QtCore.QRect(10, 31, 16, 20))
        self.AnswerB_3.setStyleSheet("color: rgb(224, 27, 36);")
        self.AnswerB_3.setObjectName("AnswerB_3")
        self.AnswerC_3 = QtWidgets.QRadioButton(self.groupBox_3)
        self.AnswerC_3.setGeometry(QtCore.QRect(10, 51, 16, 31))
        self.AnswerC_3.setStyleSheet("color: rgb(224, 27, 36);")
        self.AnswerC_3.setObjectName("AnswerC_3")
        self.AnswerD_3 = QtWidgets.QRadioButton(self.groupBox_3)
        self.AnswerD_3.setGeometry(QtCore.QRect(10, 80, 16, 21))
        self.AnswerD_3.setStyleSheet("color: rgb(224, 27, 36);")
        self.AnswerD_3.setText("")
        self.AnswerD_3.setObjectName("AnswerD_3")
        self.groupBox = QtWidgets.QGroupBox(self.frame_5)
        self.groupBox.setGeometry(QtCore.QRect(10, 40, 551, 111))
        self.groupBox.setTitle("")
        self.groupBox.setObjectName("groupBox")
        self.label_13 = QtWidgets.QLabel(self.groupBox)
        self.label_13.setGeometry(QtCore.QRect(30, 10, 481, 19))
        font = QtGui.QFont()
        font.setFamily("LM Roman 8")
        self.label_13.setFont(font)
        self.label_13.setObjectName("label_13")
        self.label_23 = QtWidgets.QLabel(self.groupBox)
        self.label_23.setGeometry(QtCore.QRect(30, 80, 511, 31))
        font = QtGui.QFont()
        font.setFamily("LM Roman 8")
        self.label_23.setFont(font)
        self.label_23.setObjectName("label_23")
        self.label_22 = QtWidgets.QLabel(self.groupBox)
        self.label_22.setGeometry(QtCore.QRect(30, 60, 521, 19))
        font = QtGui.QFont()
        font.setFamily("LM Roman 8")
        self.label_22.setFont(font)
        self.label_22.setObjectName("label_22")
        self.label_21 = QtWidgets.QLabel(self.groupBox)
        self.label_21.setGeometry(QtCore.QRect(30, 30, 521, 31))
        font = QtGui.QFont()
        font.setFamily("LM Roman 8")
        self.label_21.setFont(font)
        self.label_21.setObjectName("label_21")
        self.AnswerA = QtWidgets.QRadioButton(self.groupBox)
        self.AnswerA.setGeometry(QtCore.QRect(10, 10, 16, 20))
        self.AnswerA.setStyleSheet("color: rgb(224, 27, 36);")
        self.AnswerA.setText("")
        self.AnswerA.setObjectName("AnswerA")
        self.AnswerB = QtWidgets.QRadioButton(self.groupBox)
        self.AnswerB.setGeometry(QtCore.QRect(10, 30, 16, 31))
        self.AnswerB.setStyleSheet("color: rgb(224, 27, 36);")
        self.AnswerB.setText("")
        self.AnswerB.setObjectName("AnswerB")
        self.AnswerC = QtWidgets.QRadioButton(self.groupBox)
        self.AnswerC.setGeometry(QtCore.QRect(10, 60, 20, 21))
        self.AnswerC.setStyleSheet("color: rgb(224, 27, 36);")
        self.AnswerC.setText("")
        self.AnswerC.setObjectName("AnswerC")
        self.AnswerD = QtWidgets.QRadioButton(self.groupBox)
        self.AnswerD.setGeometry(QtCore.QRect(10, 85, 20, 21))
        self.AnswerD.setStyleSheet("color: rgb(224, 27, 36);")
        self.AnswerD.setText("")
        self.AnswerD.setObjectName("AnswerD")
        self.frame_6 = QtWidgets.QFrame(self.frame_4)
        self.frame_6.setGeometry(QtCore.QRect(0, 70, 801, 51))
        self.frame_6.setStyleSheet("background-color: rgb(224, 27, 36);")
        self.frame_6.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_6.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_6.setObjectName("frame_6")
        self.label_24 = QtWidgets.QLabel(self.frame_6)
        self.label_24.setGeometry(QtCore.QRect(10, 20, 211, 19))
        font = QtGui.QFont()
        font.setFamily("LM Roman 8")
        font.setPointSize(15)
        font.setBold(True)
        font.setWeight(75)
        self.label_24.setFont(font)
        self.label_24.setObjectName("label_24")
        self.label_25 = QtWidgets.QLabel(self.frame_6)
        self.label_25.setGeometry(QtCore.QRect(740, 10, 66, 31))
        font = QtGui.QFont()
        font.setFamily("Serif")
        font.setPointSize(20)
        font.setBold(True)
        font.setWeight(75)
        self.label_25.setFont(font)
        self.label_25.setObjectName("label_25")
        self.label_26 = QtWidgets.QLabel(self.frame_4)
        self.label_26.setGeometry(QtCore.QRect(10, 20, 491, 41))
        font = QtGui.QFont()
        font.setFamily("LM Roman 8")
        font.setPointSize(20)
        font.setBold(True)
        font.setWeight(75)
        self.label_26.setFont(font)
        self.label_26.setObjectName("label_26")
        # Подключаем радиокнопки к методу проверки
        self.AnswerA.toggled.connect(self.update_submit_button_state)
        self.AnswerB.toggled.connect(self.update_submit_button_state)
        self.AnswerC.toggled.connect(self.update_submit_button_state)
        self.AnswerD.toggled.connect(self.update_submit_button_state)
        self.AnswerA_2.toggled.connect(self.update_submit_button_state)
        self.AnswerB_2.toggled.connect(self.update_submit_button_state)
        self.AnswerC_2.toggled.connect(self.update_submit_button_state)
        self.AnswerD_2.toggled.connect(self.update_submit_button_state)
        self.AnswerA_3.toggled.connect(self.update_submit_button_state)
        self.AnswerB_3.toggled.connect(self.update_submit_button_state)
        self.AnswerC_3.toggled.connect(self.update_submit_button_state)
        self.AnswerD_3.toggled.connect(self.update_submit_button_state)

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

        third_question_answered = (
            self.AnswerA_3.isChecked() or
            self.AnswerB_3.isChecked() or
            self.AnswerC_3.isChecked() or
            self.AnswerD_3.isChecked()
        )
        
        # Активируем кнопку, если оба вопроса отвечены
        self.pushButton_6.setEnabled(first_question_answered and second_question_answered and third_question_answered)

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
        if self.AnswerA_2.isChecked():  # Правильный ответ A
            score += 2
            self.AnswerA_2.setStyleSheet("color: rgb(224, 27, 36); background-color: rgb(0, 255, 0);")  # Зеленый фон для правильного ответа
        else:
            # Если выбран неверный ответ, меняем фон на красный
            if self.AnswerB_2.isChecked():
                self.AnswerB_2.setStyleSheet("color: rgb(224, 27, 36); background-color: rgb(255, 0, 0);")
            elif self.AnswerC_2.isChecked():
                self.AnswerC_2.setStyleSheet("color: rgb(224, 27, 36); background-color: rgb(255, 0, 0);")
            elif self.AnswerD_2.isChecked():
                self.AnswerD_2.setStyleSheet("color: rgb(224, 27, 36); background-color: rgb(255, 0, 0);")

        # Проверяем третий вопрос
        if self.AnswerA_3.isChecked():  # Правильный ответ A
            score += 1
            self.AnswerA_3.setStyleSheet("color: rgb(224, 27, 36); background-color: rgb(0, 255, 0);")  # Зеленый фон для правильного ответа
        else:
            # Если выбран неверный ответ, меняем фон на красный
            if self.AnswerB_3.isChecked():
                self.AnswerB_3.setStyleSheet("color: rgb(224, 27, 36); background-color: rgb(255, 0, 0);")
            elif self.AnswerC_3.isChecked():
                self.AnswerC_3.setStyleSheet("color: rgb(224, 27, 36); background-color: rgb(255, 0, 0);")
            elif self.AnswerD_3.isChecked():
                self.AnswerD_3.setStyleSheet("color: rgb(224, 27, 36); background-color: rgb(255, 0, 0);")

        # Блокируем радиокнопки после выбора ответа
        self.AnswerA.setEnabled(False)
        self.AnswerB.setEnabled(False)
        self.AnswerC.setEnabled(False)
        self.AnswerD.setEnabled(False)
        self.AnswerA_2.setEnabled(False)
        self.AnswerB_2.setEnabled(False)
        self.AnswerC_2.setEnabled(False)
        self.AnswerD_2.setEnabled(False)
        self.AnswerA_3.setEnabled(False)
        self.AnswerB_3.setEnabled(False)
        self.AnswerC_3.setEnabled(False)
        self.AnswerD_3.setEnabled(False)

        # Деактивируем кнопку "Ответить" после проверки
        self.pushButton_6.setEnabled(False)


    def retranslateUi(self, Dialog):
        _translate = QtCore.QCoreApplication.translate
        Dialog.setWindowTitle(_translate("Dialog", "Обучающая система"))
        self.pushButton.setText(_translate("Dialog", "Вернуться на главную"))
        self.label_14.setText(_translate("Dialog", "1.  Какое из следующих утверждений о локальных и глобальных именах верно?"))
        self.label_18.setText(_translate("Dialog", "2.  Какой из следующих операторов позволяет гарантировать, что тело цикла \n"
"выполнится хотя бы один раз?"))
        self.pushButton_6.setText(_translate("Dialog", "Ответить"))
        self.label_19.setText(_translate("Dialog", "3.  Какой принцип обслуживания реализует стек?"))
        self.label_15.setText(_translate("Dialog", "A) do while"))
        self.label_16.setText(_translate("Dialog", "B) for"))
        self.label_17.setText(_translate("Dialog", "C) while"))
        self.label_20.setText(_translate("Dialog", "D) if"))
        self.AnswerB_2.setText(_translate("Dialog", "RadioButton"))
        self.AnswerC_2.setText(_translate("Dialog", "RadioButton"))
        self.label_27.setText(_translate("Dialog", "A) LIFO (Last In, First Out)"))
        self.label_28.setText(_translate("Dialog", "B) FIFO (First In, First Out)"))
        self.label_29.setText(_translate("Dialog", "C) FILO (First In, Last Out)"))
        self.label_30.setText(_translate("Dialog", "D) FAL (First And Last)"))
        self.AnswerA_3.setText(_translate("Dialog", "RadioButton"))
        self.AnswerB_3.setText(_translate("Dialog", "RadioButton"))
        self.AnswerC_3.setText(_translate("Dialog", "RadioButton"))
        self.label_13.setText(_translate("Dialog", "A) Локальные имена доступны из любой части программы"))
        self.label_23.setText(_translate("Dialog", "D) Глобальные имена не могут быть использованы в функциях"))
        self.label_22.setText(_translate("Dialog", "C) Локальные имена всегда имеют приоритет над глобальными"))
        self.label_21.setText(_translate("Dialog", "B) Глобальные имена могут быть скрыты локальными именами"))
        self.label_24.setText(_translate("Dialog", "Условие заданий"))
        self.label_25.setText(_translate("Dialog", "4Б"))
        self.label_26.setText(_translate("Dialog", "2. Вопросы средней сложности"))


if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    Dialog = QtWidgets.QDialog()
    ui = Ui_Dialog()
    ui.setupUi(Dialog)
    Dialog.show()
    sys.exit(app.exec_())