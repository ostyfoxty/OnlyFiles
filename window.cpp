#include <QtWidgets>
#include <thread>

#include "window.h"

enum {absoluteFileNameRole=Qt::UserRole+1};

Window::Window(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle(tr("Find Files"));

   startButton = new QPushButton(tr("&Start"), this);
    connect(startButton, &QAbstractButton::clicked, this, &Window::findLeft);

    QPushButton *browseButtonLeft = new QPushButton(tr("&Browse..."), this);
    connect(browseButtonLeft, &QAbstractButton::clicked, this, &Window::browseLeft);
    findButtonLeft = new QPushButton(tr("&Find"), this);
    connect(findButtonLeft, &QAbstractButton::clicked, this, &Window::findLeft);

    onlyFilesLeft=new QRadioButton("searching only files",this);
    onlySubdirLeft=new QRadioButton("searching for only subdirectories",this);
    allLeft=new QRadioButton("searching files and subdirectories",this);
    filesOrDirLeft= new QGroupBox(this);
    QVBoxLayout *vBox2Left = new QVBoxLayout;
     vBox2Left->addWidget(onlyFilesLeft);
     vBox2Left->addWidget(onlySubdirLeft);
     vBox2Left->addWidget(allLeft);
     filesOrDirLeft->setLayout(vBox2Left);

    lowPriorityLeft=new QRadioButton("low priority",this);
    highPriorityLeft=new QRadioButton("high priority",this);
    priorityLeft= new QGroupBox(this);
    QVBoxLayout *vBoxLeft = new QVBoxLayout;
     vBoxLeft->addWidget(lowPriorityLeft);
     vBoxLeft->addWidget(highPriorityLeft);
     priorityLeft->setLayout(vBoxLeft);

    fileComboBoxLeft = createComboBox(tr("*"));
    connect(fileComboBoxLeft->lineEdit(), &QLineEdit::returnPressed,
            this, &Window::animateFindClickLeft);
    textComboBoxLeft = createComboBox();
    connect(textComboBoxLeft->lineEdit(), &QLineEdit::returnPressed,
            this, &Window::animateFindClickLeft);
    directoryComboBoxLeft = createComboBox(QDir::toNativeSeparators(QDir::currentPath()));
    connect(directoryComboBoxLeft->lineEdit(), &QLineEdit::returnPressed,
            this, &Window::animateFindClickLeft);

    filesFoundLabelLeft = new QLabel;

    createFilesTableLeft();

    QPushButton *browseButtonRight = new QPushButton(tr("&Browse..."), this);
    connect(browseButtonRight, &QAbstractButton::clicked, this, &Window::browseRight);
    findButtonRight = new QPushButton (tr("&Find"),this);
    connect(findButtonRight, &QAbstractButton::clicked,this, &Window::findRight);

    onlyFilesRight=new QRadioButton("searching only files",this);
    onlySubdirRight=new QRadioButton("searching for only subdirectories",this);
    allRight=new QRadioButton("searching files and subdirectories",this);
    filesOrDirRight= new QGroupBox(this);
    QVBoxLayout *vBox2Right = new QVBoxLayout;
     vBox2Right->addWidget(onlyFilesRight);
     vBox2Right->addWidget(onlySubdirRight);
      vBox2Right->addWidget(allRight);
     filesOrDirRight->setLayout(vBox2Right);

     lowPriorityRight=new QRadioButton("low priority",this);
     highPriorityRight=new QRadioButton("high priority",this);
     priorityRight= new QGroupBox(this);
     QVBoxLayout *vBoxRight = new QVBoxLayout;
      vBoxRight->addWidget(lowPriorityRight);
      vBoxRight->addWidget(highPriorityRight);
      priorityRight->setLayout(vBoxRight);

    fileComboBoxRight = createComboBox(tr("*"));
    connect(fileComboBoxRight->lineEdit(), &QLineEdit::returnPressed,
            this, &Window::animateFindClickRight);
    textComboBoxRight = createComboBox();
    connect(textComboBoxRight->lineEdit(), &QLineEdit::returnPressed,
            this, &Window::animateFindClickRight);
    directoryComboBoxRight = createComboBox(QDir::toNativeSeparators(QDir::currentPath()));
    connect(directoryComboBoxRight->lineEdit(), &QLineEdit::returnPressed,
            this, &Window::animateFindClickRight);

    filesFoundLabelRight = new QLabel;

    createFilesTableRight();

    QGridLayout *mainLayout=new QGridLayout(this);

    mainLayout->addWidget(new QLabel(tr("Named:")), 0, 0);
    mainLayout->addWidget(fileComboBoxLeft, 0, 1, 1, 2);
   mainLayout->addWidget(new QLabel(tr("Named:")), 0, 3);
   mainLayout->addWidget(fileComboBoxRight, 0, 4, 1, 5);

    mainLayout->addWidget(new QLabel(tr("Depth of searching:")), 1, 0);
    mainLayout->addWidget(textComboBoxLeft, 1, 1, 1, 2);
   mainLayout->addWidget(new QLabel(tr("Depth of searching:")), 1, 3);
   mainLayout->addWidget(textComboBoxRight, 1, 4, 1, 5);

    mainLayout->addWidget(new QLabel(tr("In directory:")), 2, 0);
    mainLayout->addWidget(directoryComboBoxLeft, 2, 1);
    mainLayout->addWidget(new QLabel(tr("In directory:")), 2, 3);
    mainLayout->addWidget(directoryComboBoxRight, 2, 4);

    mainLayout->addWidget(browseButtonLeft, 2, 2);
    mainLayout->addWidget(priorityLeft,3,0);
    mainLayout->addWidget(filesOrDirLeft,4,0);
    mainLayout->addWidget(filesTableLeft, 5, 0, 1, 3);
    mainLayout->addWidget(filesFoundLabelLeft, 6, 0, 1, 2);
    mainLayout->addWidget(findButtonLeft, 6, 2);


    mainLayout->addWidget(browseButtonRight, 2, 5);
     mainLayout->addWidget(priorityRight,3,3);
       mainLayout->addWidget(filesOrDirRight,4,3);
    mainLayout->addWidget(filesTableRight, 5,3, 1, 6);
    mainLayout->addWidget(filesFoundLabelRight, 6, 3, 1, 2);
    mainLayout->addWidget(findButtonRight,6,5);

    mainLayout->addWidget(startButton,7,0);

    connect(new QShortcut(QKeySequence::Quit, this), &QShortcut::activated,
        qApp, &QApplication::quit);
}

void Window::browseLeft()
{
    QString directory =
        QDir::toNativeSeparators(QFileDialog::getExistingDirectory(this, tr("Find Files"), QDir::currentPath()));

    if (!directory.isEmpty()) {
        if (directoryComboBoxLeft->findText(directory) == -1)
            directoryComboBoxLeft->addItem(directory);
        directoryComboBoxLeft->setCurrentIndex(directoryComboBoxLeft->findText(directory));
    }
}

void Window::browseRight()
{
    QString directory =
        QDir::toNativeSeparators(QFileDialog::getExistingDirectory(this, tr("Find Files"), QDir::currentPath()));

    if (!directory.isEmpty()) {
        if (directoryComboBoxRight->findText(directory) == -1)
            directoryComboBoxRight->addItem(directory);
        directoryComboBoxRight->setCurrentIndex(directoryComboBoxRight->findText(directory));
    }
}


static void updateComboBox(QComboBox *comboBox)
{
    if (comboBox->findText(comboBox->currentText()) == -1)
        comboBox->addItem(comboBox->currentText());
}

void Window::findLeft()
{
    filesTableLeft->setRowCount(0);

    QString fileName = fileComboBoxLeft->currentText();
    QString text = textComboBoxLeft->currentText();
    QString path = QDir::cleanPath(directoryComboBoxLeft->currentText());
    currentDirLeft = QDir(path);

    updateComboBox(fileComboBoxLeft);
    updateComboBox(textComboBoxLeft);
    updateComboBox(directoryComboBoxLeft);

    QStringList filter;
    if (!fileName.isEmpty())
        filter << fileName;
    QDirIterator it(path, filter, QDir::AllEntries | QDir::NoSymLinks | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
    QStringList files;
    while (it.hasNext())
        files << it.next();
    if (!text.isEmpty())
        files = findFiles(files, text);
    files.sort();
    showFilesLeft(files);
}

void Window::findRight()
{
    filesTableRight->setRowCount(0);

    QString fileName = fileComboBoxRight->currentText();
    QString text = textComboBoxRight->currentText();
    QString path = QDir::cleanPath(directoryComboBoxRight->currentText());
    currentDirRight = QDir(path);

    updateComboBox(fileComboBoxRight);
    updateComboBox(textComboBoxRight);
    updateComboBox(directoryComboBoxRight);

    QStringList filter;
    if (!fileName.isEmpty())
        filter << fileName;
    QDirIterator it(path, filter, QDir::AllEntries | QDir::NoSymLinks | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
    QStringList files;
    while (it.hasNext())
        files << it.next();
    if (!text.isEmpty())
        files = findFiles(files, text);
    files.sort();
    showFilesRight(files);
}

void Window::animateFindClickLeft()
{
    findButtonLeft->animateClick();
}

void Window::animateFindClickRight()
{
    findButtonRight->animateClick();
}

QStringList Window::findFiles(const QStringList &files, const QString &text)
{

    QStringList foundFiles;

    for (int i = 0; i < files.size(); ++i) {
        const QString fileName = files.at(i);

        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly)) {
            QString line;
            QTextStream in(&file);
            while (!in.atEnd()) {
                line = in.readLine();
                if (line.contains(text, Qt::CaseInsensitive)) {
                    foundFiles << files[i];
                    break;
                }
            }
        }
    }
    return foundFiles;
}

void Window::createFilesTableLeft()
{
    filesTableLeft = new QTableWidget(0, 1);
    filesTableLeft->setSelectionBehavior(QAbstractItemView::SelectRows);

    QStringList labels;
    labels << tr("Filename");
    filesTableLeft->setHorizontalHeaderLabels(labels);
    filesTableLeft->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    filesTableLeft->verticalHeader()->hide();
    filesTableLeft->setShowGrid(false);

}


void Window::createFilesTableRight()
{
    filesTableRight = new QTableWidget(0, 1);
    filesTableRight->setSelectionBehavior(QAbstractItemView::SelectRows);

    QStringList labels;
    labels << tr("Filename");
    filesTableRight->setHorizontalHeaderLabels(labels);
    filesTableRight->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    filesTableRight->verticalHeader()->hide();
    filesTableRight->setShowGrid(false);

}

void Window::showFilesLeft(const QStringList &paths)
{
    for (const QString &filePath : paths) {
        const QString toolTip = QDir::toNativeSeparators(filePath);
        const QString relativePath = QDir::toNativeSeparators(currentDirLeft.relativeFilePath(filePath));
        QTableWidgetItem *fileNameItem = new QTableWidgetItem(relativePath);
        fileNameItem->setData(absoluteFileNameRole, QVariant(filePath));
        fileNameItem->setToolTip(toolTip);
        fileNameItem->setFlags(fileNameItem->flags() ^ Qt::ItemIsEditable);

        int row = filesTableLeft->rowCount();
        filesTableLeft->insertRow(row);
        filesTableLeft->setItem(row, 0, fileNameItem);
    }
    filesFoundLabelLeft->setText(tr("%n file(s) found", nullptr, paths.size()));
    filesFoundLabelLeft->setWordWrap(true);
}


void Window::showFilesRight(const QStringList &paths)
{
    for (const QString &filePath : paths) {
        const QString toolTip = QDir::toNativeSeparators(filePath);
        const QString relativePath = QDir::toNativeSeparators(currentDirRight.relativeFilePath(filePath));
        QTableWidgetItem *fileNameItem = new QTableWidgetItem(relativePath);
        fileNameItem->setData(absoluteFileNameRole, QVariant(filePath));
        fileNameItem->setToolTip(toolTip);
        fileNameItem->setFlags(fileNameItem->flags() ^ Qt::ItemIsEditable);

        int row = filesTableRight->rowCount();
        filesTableRight->insertRow(row);
        filesTableRight->setItem(row, 0, fileNameItem);
    }
    filesFoundLabelRight->setText(tr("%n file(s) found", nullptr, paths.size()));
    filesFoundLabelRight->setWordWrap(true);
}


QComboBox *Window::createComboBox(const QString &text)
{
    QComboBox *comboBox = new QComboBox;
    comboBox->setEditable(true);
    comboBox->addItem(text);
    comboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    return comboBox;
}



