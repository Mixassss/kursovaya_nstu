from PyQt5 import QtCore, QtGui, QtWidgets

class Ui_Dialog(object):
    def setupUi(self, Dialog):
        Dialog.setObjectName("Dialog")
        Dialog.setFixedSize(300, 250)
        Dialog.setStyleSheet("background-color: rgb(36, 31, 49);")
        
        self.Login = QtWidgets.QLineEdit(Dialog)
        self.Login.setGeometry(QtCore.QRect(60, 50, 181, 27))
        self.Login.setObjectName("Login")
        self.Login.setMaxLength(15)
        
        self.Password = QtWidgets.QLineEdit(Dialog)
        self.Password.setGeometry(QtCore.QRect(60, 120, 181, 27))
        self.Password.setObjectName("Password")
        self.Password.setEchoMode(QtWidgets.QLineEdit.Password)
        self.Password.setMaxLength(15)

        self.pushButton = QtWidgets.QPushButton(Dialog)
        self.pushButton.setGeometry(QtCore.QRect(100, 170, 101, 27))
        self.pushButton.setObjectName("pushButton")
        self.pushButton.setEnabled(False)

        self.pushButton_2 = QtWidgets.QPushButton(Dialog)
        self.pushButton_2.setGeometry(QtCore.QRect(120, 210, 61, 27))
        self.pushButton_2.setObjectName("pushButton_2")
        
        self.label = QtWidgets.QLabel(Dialog)
        self.label.setGeometry(QtCore.QRect(120, 20, 66, 19))
        font = QtGui.QFont()
        self.label.setFont(font)
        self.label.setObjectName("label")
        
        self.label_2 = QtWidgets.QLabel(Dialog)
        self.label_2.setGeometry(QtCore.QRect(120, 90, 66, 19))
        self.label_2.setObjectName("label_2")

        self.retranslateUi(Dialog)
        QtCore.QMetaObject.connectSlotsByName(Dialog)

        self.Login.textChanged.connect(self.check_input)
        self.Password.textChanged.connect(self.check_input)

    def retranslateUi(self, Dialog):
        _translate = QtCore.QCoreApplication.translate
        Dialog.setWindowTitle(_translate("Dialog", "Авторизация"))
        self.pushButton.setText(_translate("Dialog", "Войти"))
        self.pushButton_2.setText(_translate("Dialog", "Назад"))
        self.label.setText(_translate("Dialog", "Логин"))
        self.label_2.setText(_translate("Dialog", "Пароль"))

    def check_input(self):
        if len(self.Login.text()) > 0 and len(self.Password.text()) > 0:
            self.pushButton.setEnabled(True)  
        else:
            self.pushButton.setEnabled(False)

if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    Dialog = QtWidgets.QDialog()
    ui = Ui_Dialog()
    ui.setupUi(Dialog)
    Dialog.show()
    sys.exit(app.exec_())
