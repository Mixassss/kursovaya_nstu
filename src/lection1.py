from PyQt5 import QtCore, QtGui, QtWidgets

class Ui_Dialog(object):
    def setupUi(self, Dialog):
        self.dialog = Dialog  # Сохраняем ссылку на диалог
        Dialog.setObjectName("Dialog")
        Dialog.resize(805, 600)
        Dialog.setStyleSheet("background-color: rgb(36, 31, 49);")

        self.verticalLayout = QtWidgets.QVBoxLayout(Dialog)
        self.verticalLayout.setContentsMargins(20, 20, 20, 20)
        self.verticalLayout.setSpacing(15)

        # Верхняя панель с заголовком
        self.label_2 = QtWidgets.QLabel("Лекция №1. Описания и константы", Dialog)
        self.label_2.setSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Fixed)
        font = QtGui.QFont()
        font.setFamily("LM Roman 8")
        font.setPointSize(20)
        font.setBold(True)
        self.label_2.setFont(font)
        self.label_2.setAlignment(QtCore.Qt.AlignCenter)
        self.verticalLayout.addWidget(self.label_2)

        # Основной контейнер с кнопками
        self.frame_2 = QtWidgets.QFrame(Dialog)
        self.frame_2.setStyleSheet("background-color: rgb(119, 118, 123);")
        self.frame_2.setSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Expanding)
        self.gridLayout = QtWidgets.QGridLayout(self.frame_2)
        self.gridLayout.setContentsMargins(20, 20, 20, 20)
        self.gridLayout.setSpacing(20)

        # Кнопки
        self.pushButton = QtWidgets.QPushButton("Область видимости, объекты и адреса", self.frame_2)
        self.pushButton_2 = QtWidgets.QPushButton("Имена, типы и указатели", self.frame_2)
        self.pushButton_6 = QtWidgets.QPushButton("Структуры", self.frame_2)
        self.pushButton_3 = QtWidgets.QPushButton("Функции", self.frame_2)
        self.pushButton_4 = QtWidgets.QPushButton("Просмотреть всю лекцию", self.frame_2)
        self.pushButton_5 = QtWidgets.QPushButton("Вернуться на главную", Dialog)

        buttons = [self.pushButton, self.pushButton_2, self.pushButton_6, self.pushButton_3]
        for button in buttons:
            button.setSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Fixed)
            button.setStyleSheet("background-color: rgb(51, 209, 122); color: rgb(0, 0, 0); font-size: 13px; padding: 20px;")
        
        self.pushButton_4.setSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Fixed)
        self.pushButton_4.setStyleSheet("background-color: rgb(53, 132, 228); color: white; font-size: 14px; padding: 16px;")
        
        self.gridLayout.addWidget(self.pushButton, 0, 0)
        self.gridLayout.addWidget(self.pushButton_2, 1, 0)
        self.gridLayout.addWidget(self.pushButton_6, 0, 1)
        self.gridLayout.addWidget(self.pushButton_3, 1, 1)
        self.gridLayout.addWidget(self.pushButton_4, 2, 0, 1, 2)
        self.verticalLayout.addWidget(self.frame_2)

        self.pushButton_5.setSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Fixed)
        self.pushButton_5.setStyleSheet("background-color: rgb(36, 31, 49); color: white; font-size: 14px; padding: 9px;")
        self.pushButton_5.clicked.connect(self.exit_application)
        self.verticalLayout.addWidget(self.pushButton_5)

        # Настройка системного трея
        self.trayIcon = QtWidgets.QSystemTrayIcon(Dialog)
        self.trayIcon.setIcon(QtGui.QIcon("icon.png"))
        self.trayMenu = QtWidgets.QMenu()
        self.toggleFullScreenAction = self.trayMenu.addAction("Переключить полноэкранный режим")
        self.toggleFullScreenAction.triggered.connect(self.toggleFullScreen)
        self.trayIcon.setContextMenu(self.trayMenu)
        self.trayIcon.show()

        # Добавление иконки в заголовок окна
        Dialog.setWindowFlags(Dialog.windowFlags() | QtCore.Qt.WindowMinMaxButtonsHint)
        
        self.retranslateUi(Dialog)
        QtCore.QMetaObject.connectSlotsByName(Dialog)

    def toggleFullScreen(self):
        if self.Dialog.isFullScreen():
            self.Dialog.showNormal()
        else:
            self.Dialog.showFullScreen()

    def retranslateUi(self, Dialog):
        _translate = QtCore.QCoreApplication.translate
        Dialog.setWindowTitle(_translate("Dialog", "Обучающая система"))

    def exit_application(self):
        # Закрываем диалог
        self.dialog.close()

if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    Dialog = QtWidgets.QDialog()
    ui = Ui_Dialog()
    ui.setupUi(Dialog)
    Dialog.show()
    sys.exit(app.exec_())