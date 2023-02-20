#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QDir>


QT_BEGIN_NAMESPACE
class QComboBox;
class QGroupBox;
class QRadioButton;
class QLabel;
class QPushButton;
class QTableWidget;
class QTableWidgetItem;
class QVBoxLayout;
QT_END_NAMESPACE


class Window : public QWidget
{
    Q_OBJECT

public:
    Window(QWidget *parent = nullptr);

private slots:
    void browseLeft();
    void findLeft();
    void animateFindClickLeft();
    void browseRight();
    void findRight();
    void animateFindClickRight();

private:
    QStringList findFiles(const QStringList &files, const QString &text);
    QComboBox *createComboBox(const QString &text = QString());

    void showFilesLeft(const QStringList &paths);
    void createFilesTableLeft();

    void showFilesRight(const QStringList &paths);
    void createFilesTableRight();



    QComboBox *fileComboBoxLeft;
    QComboBox *textComboBoxLeft;
    QComboBox *directoryComboBoxLeft;
    QLabel *filesFoundLabelLeft;
    QPushButton *findButtonLeft;
    QTableWidget *filesTableLeft;
    QGroupBox *priorityLeft;
    QGroupBox *filesOrDirLeft;
    QRadioButton *lowPriorityLeft;
    QRadioButton *highPriorityLeft;
    QRadioButton *onlyFilesLeft;
    QRadioButton *onlySubdirLeft;
    QRadioButton *allLeft;


    QComboBox *fileComboBoxRight;
    QComboBox *textComboBoxRight;
    QComboBox *directoryComboBoxRight;
    QLabel *filesFoundLabelRight;
    QPushButton *findButtonRight;
    QTableWidget *filesTableRight;
    QGroupBox *priorityRight;
    QGroupBox *filesOrDirRight;
    QRadioButton *lowPriorityRight;
    QRadioButton *highPriorityRight;
    QRadioButton *onlyFilesRight;
    QRadioButton *onlySubdirRight;
    QRadioButton *allRight;

    QDir currentDirLeft;
    QDir currentDirRight;

    QPushButton *startButton;
};


#endif
