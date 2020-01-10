#include "QuestionFile.h"
#include "AppSettings.h"
#include "DataManager/DbManager.h"

extern AppSettings* sett;
extern DbManager* db;

QuestionFile::QuestionFile(QString file)
{
    filename = sett->savePath()->rawValue().toString() + "/" + file;
    questions = *new QList<QString>();
    names = *new QList<QString>();
    questionsCombo = *new QList<QString>();
    namesCombo = *new QList<QString>();
    selected = *new QList<int>();
    answers = *new QList<QList<QString>>();
    defaultAnswer = *new QList<QString>();

}

QList<QString> QuestionFile::getQuestions() {
    return questions;
}

QList<QString> QuestionFile::getNames(){
    return names;
}

QList<int> QuestionFile::getSelected(){
    return selected;
}

QList<QList<QString>> QuestionFile::getAnswers(){
    return answers;
}


QList<QString> QuestionFile::getQuestionsCombo() {
    return questionsCombo;
}

QList<QString> QuestionFile::getNamesCombo(){
    return namesCombo;
}

QList<QString> QuestionFile::getDefaultAnswer(){
    return defaultAnswer;
}

void QuestionFile::setQuestions(QList<QString> quest) {
    questions.clear();
    questions.append(quest);
}

void QuestionFile::setDefaultAnswer(QList<QString> ans) {
    defaultAnswer.clear();
    defaultAnswer.append(ans);
}

void QuestionFile::setNames(QList<QString> newNames){
    names.clear();
    names.append(newNames);
}

void QuestionFile::setQuestionsCombo(QList<QString> quest){
    questionsCombo.clear();
    questionsCombo.append(quest);
}

void QuestionFile::setSelected(QList<int> sel) {
    selected.clear();
    selected.append(sel);
}

void QuestionFile::setNamesCombo(QList<QString> names){
    namesCombo.clear();
    namesCombo.append(names);
}

void QuestionFile::setAnswers(QList<QList<QString>> newAnswers){
    answers.clear();
    answers.append(newAnswers);
}

void QuestionFile::save() {
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << file.errorString();
        return;
    }
    QTextStream outStream(&file);

    for(int i = 0; i < names.length(); i++) {
        outStream << names[i] << ';' << questions[i] << ";0;" << defaultAnswer[i] << ';' << '0' << endl;
    }
    for(int i = 0; i < namesCombo.length(); i++) {
        outStream << namesCombo[i] << ';' << questionsCombo[i] << ";0;" << selected[i] << ';' << '1';
        for(QString foo : answers.at(i)) {
            outStream << ';' << foo;
        }
        outStream << endl;
    }
}

void QuestionFile::load() {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << file.errorString();
        return;
    }

    while (!file.atEnd()) {
        QByteArray line = file.readLine();
        //if there is a \n, then we jump it
        if(line.length() < 2) {
            continue;
        }
        QList<QByteArray> lineParse = line.split(';');
        if (QString(lineParse[4]) == '1') {
            namesCombo.append(lineParse[0]);
            questionsCombo.append(lineParse[1]);
            int bar = lineParse[3].toInt();
            selected.append(bar);
            QList<QString> foo = *new QList<QString>();
            for(int i = 5; i < lineParse.length(); i++) {
                foo.append(lineParse[i]);
            }
            answers.append(foo);
        }
        else {
            names.append(lineParse[0]);
            questions.append(lineParse[1]);
            defaultAnswer.append(lineParse[3]);
        }
        if(QString(lineParse[2]) == '1'){
            db->addQuestion(lineParse[0]);
        }
    }
}


void QuestionFile::setTest() {
    questions.append("truc");
    names.append("trucN");
    questionsCombo.append("trucC");
    namesCombo.append("trucNC");
    selected.append(0);
    defaultAnswer.append("trucD");
    answers.append({"truc1", "truc2"});


    questions.append("trucB");
    names.append("trucBN");
    questionsCombo.append("trucBC");
    namesCombo.append("trucBNC");
    selected.append(1);
    answers.append({"truc3", "truc4", "truc5"});
    defaultAnswer.append("trucD2");
}


