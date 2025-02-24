from PyQt5 import QtCore, QtGui, QtWidgets
from dialog_window_exit import Ui_Dialog as ExitDialog  # Импортируем класс диалогового окна выхода
from main_zadania1 import Ui_Dialog as ZadaniaDialog1  # Импортируем класс из main_zadania1
from main_zadania2 import Ui_Dialog as ZadaniaDialog2  # Импортируем класс из main_zadania2
from main_zadania3 import Ui_Dialog as ZadaniaDialog3  # Импортируем класс из main_zadania3
from main_zadania4 import Ui_Dialog as ZadaniaDialog4  # Импортируем класс из main_zadania4
from lection1 import Ui_Dialog as Lection1Dialog  # Импортируем класс из lection1
from lection2 import Ui_Dialog as Lection2Dialog  # Импортируем класс из lection2
from lection2 import Ui_Dialog as Lection3Dialog  # Импортируем класс из lection3


class Ui_Dialog(object):
    def setupUi(self, Dialog):
        Dialog.setObjectName("Dialog")
        Dialog.resize(795, 600)
        font = QtGui.QFont()
        font.setPointSize(15)
        Dialog.setFont(font)
        Dialog.setStyleSheet("background-color: rgb(36, 31, 49);")
        self.frame_6 = QtWidgets.QFrame(Dialog)
        self.frame_6.setGeometry(QtCore.QRect(0, 10, 811, 201))
        self.frame_6.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_6.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_6.setObjectName("frame_6")
        self.frame = QtWidgets.QFrame(self.frame_6)
        self.frame.setGeometry(QtCore.QRect(0, 0, 801, 41))
        self.frame.setStyleSheet("background-color: rgb(224, 27, 36);")
        self.frame.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame.setObjectName("frame")
        self.Theory = QtWidgets.QLabel(self.frame)
        self.Theory.setGeometry(QtCore.QRect(10, 0, 221, 31))
        font = QtGui.QFont()
        font.setFamily("LM Roman 8")
        font.setPointSize(20)
        font.setBold(True)
        font.setWeight(75)
        self.Theory.setFont(font)
        self.Theory.setObjectName("Theory")
        self.frame_window_lection = QtWidgets.QFrame(self.frame_6)
        self.frame_window_lection.setGeometry(QtCore.QRect(0, 40, 821, 141))
        self.frame_window_lection.setStyleSheet("background-color: rgb(0, 0, 0);")
        self.frame_window_lection.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_window_lection.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_window_lection.setObjectName("frame_window_lection")
        self.Lection1 = QtWidgets.QCommandLinkButton(self.frame_window_lection)
        self.Lection1.clicked.connect(self.open_lecion1_window)  # Подключаем кнопку к методу
        self.Lection1.setGeometry(QtCore.QRect(10, 10, 371, 41))
        font = QtGui.QFont()
        font.setFamily("Utopia")
        font.setPointSize(13)
        self.Lection1.setFont(font)
        self.Lection1.setObjectName("Lection1")
        self.Lection2 = QtWidgets.QCommandLinkButton(self.frame_window_lection)
        self.Lection2.setGeometry(QtCore.QRect(10, 50, 691, 41))
        self.Lection2.clicked.connect(self.open_lecion2_window)  # Подключаем кнопку к методу
        font = QtGui.QFont()
        font.setFamily("Utopia")
        font.setPointSize(13)
        self.Lection2.setFont(font)
        self.Lection2.setObjectName("Lection2")
        self.Lection3 = QtWidgets.QCommandLinkButton(self.frame_window_lection)
        self.Lection3.setGeometry(QtCore.QRect(10, 90, 451, 41))
        font = QtGui.QFont()
        font.setFamily("Utopia")
        font.setPointSize(13)
        self.Lection3.setFont(font)
        self.Lection3.setObjectName("Lection3")
        self.Lection3.clicked.connect(self.open_lecion3_window)  # Подключаем кнопку к методу
        self.frame_itogtest = QtWidgets.QFrame(Dialog)
        self.frame_itogtest.setGeometry(QtCore.QRect(0, 420, 801, 201))
        self.frame_itogtest.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_itogtest.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_itogtest.setObjectName("frame_itogtest")
        self.frame_3 = QtWidgets.QFrame(self.frame_itogtest)
        self.frame_3.setGeometry(QtCore.QRect(0, 20, 801, 41))
        self.frame_3.setStyleSheet("background-color: rgb(224, 27, 36);")
        self.frame_3.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_3.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_3.setObjectName("frame_3")
        self.tests = QtWidgets.QLabel(self.frame_3)
        self.tests.setGeometry(QtCore.QRect(10, 0, 221, 31))
        font = QtGui.QFont()
        font.setFamily("LM Roman 8")
        font.setPointSize(20)
        font.setBold(True)
        font.setWeight(75)
        self.tests.setFont(font)
        self.tests.setObjectName("tests")
        self.frame_testing = QtWidgets.QFrame(self.frame_itogtest)
        self.frame_testing.setGeometry(QtCore.QRect(0, 60, 821, 61))
        self.frame_testing.setStyleSheet("background-color: rgb(0, 0, 0);")
        self.frame_testing.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_testing.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_testing.setObjectName("frame_testing")
        self.itogovoe_testirovanie = QtWidgets.QCommandLinkButton(self.frame_testing)
        self.itogovoe_testirovanie.setGeometry(QtCore.QRect(10, 10, 491, 41))
        font = QtGui.QFont()
        font.setPointSize(15)
        self.itogovoe_testirovanie.setFont(font)
        self.itogovoe_testirovanie.setObjectName("itogovoe_testirovanie")
        self.label = QtWidgets.QLabel(self.frame_testing)
        self.label.setGeometry(QtCore.QRect(700, 20, 66, 19))
        self.label.setText("")
        self.label.setObjectName("label")
        self.quit_system = QtWidgets.QPushButton(self.frame_itogtest)
        self.quit_system.setGeometry(QtCore.QRect(460, 140, 141, 27))
        self.quit_system.setObjectName("quit_system")
        self.quit_system.clicked.connect(self.show_exit_dialog)  # Подключаем кнопку выхода
        self.back = QtWidgets.QPushButton(self.frame_itogtest)
        self.back.setGeometry(QtCore.QRect(170, 140, 87, 27))
        self.back.setObjectName("back")
        self.back.clicked.connect(Dialog.reject)  # Закрываем текущее окно
        self.frame_question = QtWidgets.QFrame(Dialog)
        self.frame_question.setGeometry(QtCore.QRect(0, 250, 811, 171))
        self.frame_question.setStyleSheet("background-color: rgb(0, 0, 0);")
        self.frame_question.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_question.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_question.setObjectName("frame_question")
        self.question_withcode = QtWidgets.QCommandLinkButton(self.frame_question)
        self.question_withcode.setGeometry(QtCore.QRect(0, 120, 561, 41))
        font = QtGui.QFont()
        font.setFamily("Utopia")
        font.setPointSize(13)
        font.setBold(True)
        font.setWeight(75)
        self.question_withcode.setFont(font)
        self.question_withcode.setObjectName("question_withcode")
        self.easy_question = QtWidgets.QCommandLinkButton(self.frame_question)
        self.question_withcode.clicked.connect(self.open_zadania4_window) # Подключаем кнопку "Основы программирования. Работа с кодом к методу
        self.easy_question.setGeometry(QtCore.QRect(0, 0, 581, 41))
        font = QtGui.QFont()
        font.setFamily("Utopia")
        font.setPointSize(13)
        self.easy_question.setFont(font)
        self.easy_question.setObjectName("easy_question")
        self.middle_question = QtWidgets.QCommandLinkButton(self.frame_question)
        self.easy_question.clicked.connect(self.open_zadania_window) # Подключаем кнопку "Основы программирования. Вопросы легкой сложности" к методу
        self.middle_question.setGeometry(QtCore.QRect(0, 40, 601, 41))
        font = QtGui.QFont()
        font.setFamily("Utopia")
        font.setPointSize(13)
        self.middle_question.setFont(font)
        self.middle_question.setObjectName("middle_question")
        self.hard_question = QtWidgets.QCommandLinkButton(self.frame_question)
        self.middle_question.clicked.connect(self.open_zadania2_window) # Подключаем кнопку "Основы программирования. Вопросы средней сложности" к методу
        self.hard_question.setGeometry(QtCore.QRect(0, 80, 601, 41))
        font = QtGui.QFont()
        font.setFamily("Utopia")
        font.setPointSize(13)
        self.hard_question.setFont(font)
        self.hard_question.setObjectName("hard_question")
        self.hard_question.clicked.connect(self.open_zadania3_window) # Подключаем кнопку "Основы программирования. Вопросы средней сложности" к методу
        self.frame_zadania = QtWidgets.QFrame(Dialog)
        self.frame_zadania.setGeometry(QtCore.QRect(0, 210, 801, 41))
        self.frame_zadania.setStyleSheet("background-color: rgb(224, 27, 36);")
        self.frame_zadania.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_zadania.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_zadania.setObjectName("frame_zadania")
        self.zadanie = QtWidgets.QLabel(self.frame_zadania)
        self.zadanie.setGeometry(QtCore.QRect(10, 0, 221, 31))
        font = QtGui.QFont()
        font.setFamily("LM Roman 8")
        font.setPointSize(20)
        font.setBold(True)
        font.setWeight(75)
        self.zadanie.setFont(font)
        self.zadanie.setObjectName("zadanie")

        self.retranslateUi(Dialog)
        QtCore.QMetaObject.connectSlotsByName(Dialog)

    def open_zadania_window(self):
        self.zadania_dialog = QtWidgets.QDialog()  # Создаем новое окно для заданий
        self.zadania_ui = ZadaniaDialog1()
        self.zadania_ui.setupUi(self.zadania_dialog)  # Передаем ссылку на основной диалог
        self.zadania_dialog.exec_()  # Показываем новое окно


    def open_zadania2_window(self):
        self.zadania2_dialog = QtWidgets.QDialog() # Создаем новое окно для заданий
        self.zadania2_ui = ZadaniaDialog2()
        self.zadania2_ui.setupUi(self.zadania2_dialog) # Перердаем ссылку на основной диалог
        self.zadania2_dialog.exec_() # Показываем новое окно

    def open_zadania3_window(self):
        self.zadania3_dialog = QtWidgets.QDialog() # Создаем новое окно для заданий
        self.zadania3_ui = ZadaniaDialog3()
        self.zadania3_ui.setupUi(self.zadania3_dialog) # Перердаем ссылку на основной диалог
        self.zadania3_dialog.exec_() # Показываем новое окно

    def open_zadania4_window(self):
        self.zadania4_dialog = QtWidgets.QDialog() # Создаем новое окно для заданий
        self.zadania4_ui = ZadaniaDialog4()
        self.zadania4_ui.setupUi(self.zadania4_dialog)
        self.zadania4_dialog.exec_() # Показываем новое окно

    def open_lecion1_window(self):
        self.lecion1_dialog = QtWidgets.QDialog()  # Создаем новое окно для лекции 1
        self.lecion1_ui = Lection1Dialog()
        self.lecion1_ui.setupUi(self.lecion1_dialog)  # Передаем ссылку на основное диалоговое окно
        self.lecion1_dialog.exec_()  # Показываем новое окно

    def open_lecion2_window(self):
        self.lecion2_dialog = QtWidgets.QDialog()  # Создаем новое окно для лекции 2
        self.lecion2_ui = Lection2Dialog()
        self.lecion2_ui.setupUi(self.lecion2_dialog)  # Передаем ссылку на основное диалоговое окно
        self.lecion2_dialog.exec_()  # Показываем новое окно

    def open_lecion3_window(self):
        self.lecion3_dialog = QtWidgets.QDialog()  # Создаем новое окно для лекции 2
        self.lecion3_ui = Lection3Dialog()
        self.lecion3_ui.setupUi(self.lecion3_dialog)  # Передаем ссылку на основное диалоговое окно
        self.lecion3_dialog.exec_()  # Показываем новое окно

    def show_exit_dialog(self):
        dialog = QtWidgets.QDialog()
        dialog_ui = ExitDialog()
        dialog_ui.setupUi(dialog)

        # Подключаем кнопки диалога к соответствующим методам
        dialog_ui.Yes.clicked.connect(self.accept_exit)
        dialog_ui.No.clicked.connect(dialog.reject)

        # Показываем диалог и ждем ответа пользователя
        dialog.exec_()

    def accept_exit(self):
        QtWidgets.QApplication.quit()  # Закрываем приложение

    def retranslateUi(self, Dialog):
        _translate = QtCore.QCoreApplication.translate
        Dialog.setWindowTitle(_translate("Dialog", "Обучающая система"))
        self.Theory.setText(_translate("Dialog", "Теория"))
        self.Lection1.setText(_translate("Dialog", "Лекция №1. Описания и константы"))
        self.Lection2.setText(_translate("Dialog", "Лекция №2. Базовые конструкции структурного программирования"))
        self.Lection3.setText(_translate("Dialog", "Лекция №3. Описания и константы"))
        self.tests.setText(_translate("Dialog", "Тесты"))
        self.itogovoe_testirovanie.setText(_translate("Dialog", "Итоговое тестирование по программированию"))
        self.quit_system.setText(_translate("Dialog", "Выйти из системы"))
        self.back.setText(_translate("Dialog", "Назад"))
        self.question_withcode.setText(_translate("Dialog", "Основы программирования. Работа с кодом"))
        self.easy_question.setText(_translate("Dialog", "Основы программирования. Вопросы легкой сложности"))
        self.middle_question.setText(_translate("Dialog", "Основы программирования. Вопросы средней сложности"))
        self.hard_question.setText(_translate("Dialog", "Основы программирования. Вопросы высокой сложности"))
        self.zadanie.setText(_translate("Dialog", "Задания"))


if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    Dialog = QtWidgets.QDialog()
    ui = Ui_Dialog()
    ui.setupUi(Dialog)
    Dialog.show()
    sys.exit(app.exec_())