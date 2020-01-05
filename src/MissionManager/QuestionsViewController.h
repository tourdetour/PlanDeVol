#ifndef QUESTIONSVIEWCONTROLLER_H
#define QUESTIONSVIEWCONTROLLER_H

#include "SqlCustomModel.hpp"

#include <QObject>



class QuestionsViewController : public QObject
{
    Q_OBJECT

public:
    explicit QuestionsViewController();
    ~QuestionsViewController();

    Q_INVOKABLE QStringList getQuestions(SqlCustomModel *model, int index);
    Q_INVOKABLE QStringList getAnswers(SqlCustomModel *model, int index);
    Q_INVOKABLE QStringList getComboQuestions(SqlCustomModel *model, int index);
    Q_INVOKABLE QVariantList getPossibleAnswers(SqlCustomModel *model, int index);
    Q_INVOKABLE QList<int>    getSelectedAnswers(SqlCustomModel *model, int index);
    Q_INVOKABLE void        deleteQuestion(SqlCustomModel *model, int i);
    Q_INVOKABLE void        addQuestion(SqlCustomModel *model, QString question, bool isMultipleChoices, QString choices);

    QStringList questions;
    QVariantList possibleAnswers;
    QList<int> selectedAnswers;
};

#endif // QUESTIONSVIEWCONTROLLER_H
