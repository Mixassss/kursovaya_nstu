from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(800, 598)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setStyleSheet("background-color: rgb(36, 31, 49);")
        self.centralwidget.setObjectName("centralwidget")
        self.main_layout = QtWidgets.QVBoxLayout(self.centralwidget)

        self.frame = QtWidgets.QFrame(self.centralwidget)
        self.frame.setStyleSheet("gridline-color: rgb(229, 165, 10);")
        self.frame.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame.setObjectName("frame")

        self.frame_layout = QtWidgets.QVBoxLayout(self.frame)

        self.label = QtWidgets.QLabel(self.frame)
        font = QtGui.QFont()
        font.setFamily("Utopia")
        font.setPointSize(15)
        font.setBold(True)
        font.setWeight(75)
        self.label.setFont(font)
        self.label.setStyleSheet("background-color: rgba(255, 255, 255, 0);")
        self.label.setAlignment(QtCore.Qt.AlignCenter) 
        self.frame_layout.addWidget(self.label)

        self.label_2 = QtWidgets.QLabel(self.frame)
        font = QtGui.QFont()
        font.setFamily("LM Roman 8")
        font.setPointSize(25)
        font.setBold(True)
        font.setWeight(75)
        self.label_2.setFont(font)
        self.label_2.setStyleSheet("background-color: rgba(255, 255, 255, 0);")
        self.label_2.setAlignment(QtCore.Qt.AlignCenter) 
        self.frame_layout.addWidget(self.label_2)

        self.frame_2 = QtWidgets.QFrame(self.frame)
        self.frame_2.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_2.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_layout.addWidget(self.frame_2)
        self.button_layout = QtWidgets.QHBoxLayout(self.frame_2)
        self.button_layout.addStretch(1) 
        self.pushButton = QtWidgets.QPushButton(self.frame_2)
        font = QtGui.QFont()
        font.setFamily("LM Roman 8")
        font.setPointSize(15)
        font.setBold(True)
        font.setWeight(75)
        self.pushButton.setFont(font)
        self.pushButton.setStyleSheet("background-color: rgb(38, 162, 105);")
        self.pushButton.setFixedSize(200, 60)
        self.button_layout.addWidget(self.pushButton)

        self.button_layout.addStretch(1)
        self.pushButton_2 = QtWidgets.QPushButton(self.frame_2)
        font = QtGui.QFont()
        font.setFamily("Utopia")
        font.setPointSize(14)
        font.setBold(True)
        font.setWeight(75)
        self.pushButton_2.setFont(font)
        self.pushButton_2.setStyleSheet("background-color: rgb(224, 27, 36);")
        self.pushButton_2.setFixedSize(200, 60)
        self.button_layout.addWidget(self.pushButton_2)
        self.button_layout.addStretch(1)
        self.main_layout.addWidget(self.frame)

        MainWindow.setCentralWidget(self.centralwidget)

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "Обучающая система"))
        self.label.setText(_translate("MainWindow", "Обучающая система с тестированием по программированию"))
        self.label_2.setText(_translate("MainWindow", "Авторизация"))
        self.pushButton.setText(_translate("MainWindow", "Войти"))
        self.pushButton_2.setText(_translate("MainWindow", "Выход"))


if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    MainWindow = QtWidgets.QMainWindow()
    ui = Ui_MainWindow()
    ui.setupUi(MainWindow)
    MainWindow.show()
    sys.exit(app.exec_())
