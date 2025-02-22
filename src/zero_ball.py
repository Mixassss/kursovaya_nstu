from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_Dialog(object):
    def __init__(self, main_dialog):
        self.main_dialog = main_dialog
    def setupUi(self, Dialog):
        Dialog.setObjectName("Dialog")
        Dialog.setFixedSize(511, 100)
        Dialog.setStyleSheet("background-color: rgb(36, 31, 49);")
        self.label = QtWidgets.QLabel(Dialog)
        self.label.setGeometry(QtCore.QRect(10, 10, 501, 41))
        font = QtGui.QFont()
        self.label.setFont(font)
        self.label.setObjectName("label")
        self.pushButton_2 = QtWidgets.QPushButton(Dialog)
        self.pushButton_2.setGeometry(QtCore.QRect(280, 60, 151, 27))
        self.pushButton_2.setObjectName("pushButton_2")
        self.pushButton = QtWidgets.QPushButton(Dialog)
        self.pushButton_2.clicked.connect(self.retry_test)
        self.pushButton.setGeometry(QtCore.QRect(50, 60, 161, 27))
        self.pushButton.setObjectName("pushButton")

        self.retranslateUi(Dialog)
        QtCore.QMetaObject.connectSlotsByName(Dialog)

    def retry_test(self):
        # Сбрасываем ответы в главном диалоге
        self.main_dialog.reset_answers()

        # Закрываем текущее окно
        self.dialog.close()

        # Открываем диалог снова для нового прохождения
        self.result_dialog = QtWidgets.QDialog()
        self.result_ui = self.__class__(self.main_dialog)  # Перезапускаем тот же диалог
        self.result_ui.setupUi(self.result_dialog)
        self.result_dialog.exec_()

    def retranslateUi(self, Dialog):
        _translate = QtCore.QCoreApplication.translate
        Dialog.setWindowTitle(_translate("Dialog", "Обучающая система"))
        self.label.setText(_translate("Dialog", "Вы заработали 0 баллов! Хотите вернуться к лекциям или попробовать \n"
"снова?"))
        self.pushButton_2.setText(_translate("Dialog", "Пройти ещё раз"))
        self.pushButton.setText(_translate("Dialog", "Вернуться к лекциям"))


if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    Dialog = QtWidgets.QDialog()
    ui = Ui_Dialog()
    ui.setupUi(Dialog)
    Dialog.show()
    sys.exit(app.exec_())
