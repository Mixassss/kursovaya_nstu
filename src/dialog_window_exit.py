from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_Dialog(object):
    def setupUi(self, Dialog):
        Dialog.setObjectName("Dialog")
        Dialog.setFixedSize(350, 100)
        self.frame = QtWidgets.QFrame(Dialog)
        self.frame.setGeometry(QtCore.QRect(-10, 0, 501, 161))
        self.frame.setStyleSheet("background-color: rgb(36, 31, 49);")
        self.frame.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame.setObjectName("frame")
        
        self.label = QtWidgets.QLabel(self.frame)
        self.label.setGeometry(QtCore.QRect(10, -10, 431, 81))
        font = QtGui.QFont()
        font.setPointSize(12)
        self.label.setFont(font)
        self.label.setObjectName("label")
        
        self.No = QtWidgets.QPushButton(self.frame)
        self.No.setGeometry(QtCore.QRect(70, 60, 87, 27))
        self.No.setObjectName("No")
        
        self.Yes = QtWidgets.QPushButton(self.frame)
        self.Yes.setGeometry(QtCore.QRect(230, 60, 87, 27))
        self.Yes.setObjectName("Yes")

        self.retranslateUi(Dialog)
        QtCore.QMetaObject.connectSlotsByName(Dialog)

    def retranslateUi(self, Dialog):
        _translate = QtCore.QCoreApplication.translate
        Dialog.setWindowTitle(_translate("Dialog", "Обучающая система"))
        self.label.setText(_translate("Dialog", "Вы действительно хотите выйти из системы?"))
        self.No.setText(_translate("Dialog", "Нет"))
        self.Yes.setText(_translate("Dialog", "Да"))


if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    Dialog = QtWidgets.QDialog()
    ui = Ui_Dialog()
    ui.setupUi(Dialog)
    Dialog.show()
    sys.exit(app.exec_())
