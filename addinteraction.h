#ifndef ADDINTERACTION_H
#define ADDINTERACTION_H

#include <QWidget>
#include"interactions.h"
namespace Ui {
class addInteraction;
}

class addInteraction : public QWidget
{
    Q_OBJECT

public:
    explicit addInteraction(QWidget *parent = nullptr);
    ~addInteraction();

signals:
    void inter(Interactions *);
    void sendlTodo(list<todo *>);

private slots:
    void on_pushButton_3_clicked();

    void on_save_clicked();

    void on_interactionEdit_textEdited(const QString &arg1);

    void on_textEdit_textChanged();

    void on_pushButton_2_clicked();

    void on_addtodo_clicked();

private:
    Ui::addInteraction *ui;
    Interactions *i;
};

#endif // ADDINTERACTION_H
