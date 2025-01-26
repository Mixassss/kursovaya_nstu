import sys
from PyQt5.QtWidgets import QApplication, QMainWindow, QDialog
from main_window import Ui_MainWindow
from dialog_window_exit import Ui_Dialog as ExitDialog  # Импортируем класс диалогового окна выхода
from autorization import Ui_Dialog as AuthDialog  # Импортируем класс диалогового окна авторизации

class LessonsSystem(QMainWindow):
    def __init__(self):
        super(LessonsSystem, self).__init__()
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)

        # Подключаем кнопку "Выход" к методу обработки
        self.ui.pushButton_2.clicked.connect(self.show_exit_dialog)
        # Подключаем кнопку "Войти" к методу обработки
        self.ui.pushButton.clicked.connect(self.show_authorization_dialog)

    def show_exit_dialog(self):
        dialog = QDialog(self)
        dialog_ui = ExitDialog()
        dialog_ui.setupUi(dialog)

        # Подключаем кнопки диалога к соответствующим методам
        dialog_ui.Yes.clicked.connect(self.accept_exit)
        dialog_ui.No.clicked.connect(dialog.reject)

        # Показываем диалог и ждем ответа пользователя
        dialog.exec_()

    def accept_exit(self):
        QApplication.quit()  # Закрываем приложение

    def show_authorization_dialog(self):
        dialog = QDialog(self)
        auth_dialog_ui = AuthDialog()
        auth_dialog_ui.setupUi(dialog)

        # Подключаем кнопку "Войти" к действию (например, можно добавить проверку логина/пароля)
        auth_dialog_ui.pushButton.clicked.connect(lambda: self.handle_login(dialog, auth_dialog_ui))
        auth_dialog_ui.pushButton_2.clicked.connect(dialog.reject)  # Кнопка "Назад" закрывает диалог

        # Показываем диалог авторизации
        dialog.exec_()

    def handle_login(self, dialog, auth_dialog_ui):
        # Здесь можно добавить логику проверки логина и пароля
        login = auth_dialog_ui.Login.text()
        password = auth_dialog_ui.Password.text()
        
        # Пример простой проверки (замените на вашу логику)
        if login == "admin" and password == "password":
            dialog.accept()  # Закрываем диалог, если логин и пароль верные


if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = LessonsSystem()
    window.show()

    sys.exit(app.exec())
