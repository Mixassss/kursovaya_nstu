import sys
from PyQt5.QtWidgets import QApplication, QMainWindow, QDialog
from main_window import Ui_MainWindow
from dialog_window_exit import Ui_Dialog as ExitDialog
from autorization import Ui_Dialog as AuthDialog
from main_lection import Ui_Dialog as LecturesDialog
from no_login_or_password import Ui_Dialog as NoLoginDialog  # Импортируем класс диалогового окна ошибки

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
        dialog_ui.Yes.clicked.connect(self.accept_exit)
        dialog_ui.No.clicked.connect(dialog.reject)
        dialog.exec_()

    def accept_exit(self):
        QApplication.quit()  # Закрываем приложение

    def show_authorization_dialog(self):
        dialog = QDialog(self)
        auth_dialog_ui = AuthDialog()
        auth_dialog_ui.setupUi(dialog)
        auth_dialog_ui.pushButton.clicked.connect(lambda: self.handle_login(dialog, auth_dialog_ui))
        auth_dialog_ui.pushButton_2.clicked.connect(dialog.reject)  # Кнопка "Назад" закрывает диалог
        dialog.exec_()

    def handle_login(self, dialog, auth_dialog_ui):
        # Проверка логина и пароля
        login = auth_dialog_ui.Login.text()
        password = auth_dialog_ui.Password.text()
        
        if login == "stud" and password == "123":
            dialog.accept()  # Закрываем диалог, если логин и пароль верные
            self.open_lectures_window()  # Открываем окно лекций
        else:
            self.show_no_login_or_password_dialog()  # Показываем сообщение об ошибке
            auth_dialog_ui.Login.clear()  # Очищаем поле логина
            auth_dialog_ui.Password.clear()  # Очищаем поле пароля

    def show_no_login_or_password_dialog(self):
        dialog = QDialog(self)
        no_login_dialog_ui = NoLoginDialog()
        no_login_dialog_ui.setupUi(dialog)
        no_login_dialog_ui.pushButton.clicked.connect(dialog.accept)  # Закрываем диалог при нажатии "Ок"
        dialog.exec_()  # Показываем диалог ошибки

    def open_lectures_window(self):
        lectures_dialog = QDialog(self)
        lectures_ui = LecturesDialog()
        lectures_ui.setupUi(lectures_dialog)
        lectures_dialog.exec_()  # Показываем окно лекций
        


if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = LessonsSystem()
    window.show()
    sys.exit(app.exec())
