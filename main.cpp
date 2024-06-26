/*
5.	Строка состоит из слов. Слова в исходной строке разделяются некоторым множеством разделителей.
Среди слов, состоящих только из цифр, найти слово, содержащее максимальное число нулей. Если таких
слов больше одного, найти предпоследнее из них. Слова в исходной строке разделяются некоторым
множеством разделителей. Слова в новой строке должны разделяться ровно одним пробелом.

Гриб Дарья, 6 группа

пример для записи в файл input.txt

...сегодня 075600:000  голова  ' ' 3 00 020202
0000 00000 000 0000 2323000000000000 k k k kkkkkkkk///////
45454 02 030 00. 000.0002.03030555555

что программа записывает в файл output.txt

000 2323000000000000 0002

Идея алгоритма: будем читать строчки файла и заносить их в строку str, пока не дойдем до конца файла.
Далее убедимся что первый элемент строки это не разделитель и что последний элемент это разделитель. Если
это не так то исправляем. Далее выделяем по одному слову и проверяем состоит ли оно только из цифр. Если это так,
то считаем его количество 0. В цикле м ызапоминаем не только максимальное но и предыдущее максимальное, чтобы в
случае существования нескольких слов с максимальным количеством нулей мы могли вывести предыдущее. Каждое нужное
нам слово мы заносим в отдельную строку, которая в конце программы будет состоять из слов с максимальным числом
нулей каждой строки, слова разделены пробелом. Получившаяся строка и будет записываться в выходной файл.

*/
#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFile>
#include <QString>
#include <QStringList>
#include <QDebug>
#include <QTextEdit>

using namespace std;

int poisk_null(QString s)
{
    int k = 0;
    int n = s.length();
    int i;
    for (i = 0; i < n; i++)
    {
        if (s[i] == '0')
            k++;
    }
    return k;
}

int cifra(QString s)
{
    int n = s.length();
    QString str = "0123456789";
    for (int i = 0; i < n; i++)
    {
        if (!str.contains(s[i]))
            return 0;
    }
    return 1;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Создаем основное окно приложения
    QWidget window;

    // Создаем виджеты
    QLabel label("Вывод в output.txt");
    QPushButton button("Cтарт");
    QTextEdit inputText;
    QTextEdit outputText;

    // Создаем вертикальный лейаут и добавляем виджеты в него
    QVBoxLayout layout;
    layout.addWidget(&label);
    layout.addWidget(&button);
    //layout.addWidget(&inputText);
    layout.addWidget(&outputText);

    // Устанавливаем лейаут для основного окна
    window.setLayout(&layout);

    // Подключаем обработчик события нажатия на кнопку
    QObject::connect(&button, &QPushButton::clicked, [&]() {
        // Обработка кода при нажатии на кнопку
        QFile fin("input.txt");
        QFile fout("output.txt");
        QString rez_st = "", slovo, seps(",:.!? "), ms = "", pms = "";
        fin.open(QIODevice::ReadOnly | QIODevice::Text);
        if (!fin.isOpen())
        {
            outputText.setPlainText("Ошибка: файл не открылся");
            return;
        }
        if (fin.atEnd())
        {
            outputText.setPlainText("Ошибка: файл пустой");
            return;
        }

        while (!fin.atEnd())
        {
            QString str = fin.readLine();
            int n = str.length();
            if (!seps.contains(str[n - 1]))
                str = str + " ";

            while (seps.contains(str[0]))
            {
                str.remove(0, 1);
            }

            int i = 0, mx = 0, k = 0, pmx;
            while (str != "")
            {
                if (seps.contains(str[i]))
                {
                    slovo = str.left(i);
                    str.remove(0, i + 1);
                    i = 0;
                    if (cifra(slovo))
                    {
                        k = poisk_null(slovo);
                        if (k >= mx)
                        {
                            pmx = mx;
                            mx = k;
                            pms = ms;
                            ms = slovo;
                        }
                    }
                }
                else
                    i++;
            }
            if (mx == pmx)
            {
                rez_st = rez_st + pms + " ";
            }
            else
                rez_st = rez_st + ms + " ";
        }
        fout.open(QIODevice::WriteOnly | QIODevice::Text);
        if (!fout.isOpen())
        {
            outputText.setPlainText("Ошибка: файл не открылся");
            return;
        }
        else
        {
            QTextStream out(&fout);
            out << rez_st;
            outputText.setPlainText(rez_st);
        }

        fin.close();
        fout.close();

        //outputText.setPlainText("Обработка файла завершена");
    });

    // Показываем основное окно
    window.show();

    // Запускаем главный цикл обработки событий приложения
    return app.exec();
}
