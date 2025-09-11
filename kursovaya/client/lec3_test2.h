#ifndef LEC3_TEST2_H
#define LEC3_TEST2_H

#include <QDialog>
#include <QGroupBox>
#include <QVector>
#include <QRadioButton>

namespace Ui {
class lec3_test2;
}

class lec3_test2 : public QDialog
{
    Q_OBJECT

public:
    explicit lec3_test2(QWidget *parent = nullptr);
    ~lec3_test2();

private:
    struct QuestionPair {
        QWidget* question;
        QWidget* answer;
        QWidget* explanation;
        QRadioButton* correctAnswer;
    };

    Ui::lec3_test2 *ui;

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

#endif // LEC3_TEST2_H
