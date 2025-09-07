#ifndef LEC2_TEST4_H
#define LEC2_TEST4_H

#include <QDialog>
#include <QGroupBox>
#include <QVector>
#include <QRadioButton>

namespace Ui {
class lec2_test4;
}

class lec2_test4 : public QDialog
{
    Q_OBJECT

public:
    explicit lec2_test4(QWidget *parent = nullptr);
    ~lec2_test4();

private:
    struct QuestionPair {
        QWidget* question;
        QWidget* answer;
        QWidget* explanation;
        QRadioButton* correctAnswer;
    };

    Ui::lec2_test4 *ui;

    QVector<QuestionPair> group1Pairs;
    QVector<QuestionPair> group2Pairs;
    int currentPair1;
    int currentPair2;

    void initQuestionPairs();
    void hideAllGroupElements(QGroupBox* group);
    void showRandomQuestionPair(QGroupBox* group, const QVector<QuestionPair>& pairs);
    bool isGroupAnswered(QGroupBox* group);
    void connectRadioButtons(QGroupBox* group);
    void checkAnswers();
    bool checkGroupAnswer(QGroupBox* group, const QVector<QuestionPair>& pairs, int pairIndex);
    void setRadioButtonsEnabled(QGroupBox* group, bool enabled);
    void resetRadioButtons(QGroupBox* group);
    void startNewTest();
    void resetTest();

private slots:
    void onNextLectureClicked();
    void onAgreeClicked(int state);
    void onAnswerClicked();
    void onRetryClicked(int state);
};

#endif // LEC2_TEST4_H
