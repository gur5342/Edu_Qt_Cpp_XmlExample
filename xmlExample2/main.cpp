#include <QCoreApplication>
#include <QXmlStreamWriter>
#include <QFile>
#include <QDomDocument>
#include <QDomElement>
#include <iostream>
#include <string>

using namespace  std;

void save_xml(){
    QFile file("test.xml"); // 파일을 만들어준다.
    if(!file.open(QFile::WriteOnly | QFile::Text)) // 쓰기 모드가 아닌경우
        return;
    else {
        QXmlStreamWriter xwrite;
        xwrite.setDevice(&file);
        xwrite.setAutoFormatting(true); // 자동으로 탭을 넣을 수 있다?

        xwrite.writeStartDocument();
        //xwrite.writeDTD("<test xml>"); //
        xwrite.writeComment("xml test code");
        xwrite.writeStartElement("empinfo");
        xwrite.writeStartElement("employees");
        xwrite.writeStartElement("employee");
        xwrite.writeAttribute("name", "James");
        xwrite.writeAttribute("age", "40");
        xwrite.writeEndElement(); // employee

        xwrite.writeStartElement("employee");
        xwrite.writeAttribute("name", "Jean");
        xwrite.writeAttribute("age", "45");
        xwrite.writeEndElement();
        xwrite.writeStartElement("employee");
        xwrite.writeAttribute("name", "Crusher");
        xwrite.writeAttribute("age", "25");
        xwrite.writeEndElement();// employee

        xwrite.writeEndElement();// employees
        xwrite.writeEndElement();// enpinfo
        xwrite.writeEndDocument();

        file.close();
    }
}

int main(int argc, char *argv[])
{
    save_xml();
    QFile file("test.xml");

    QDomDocument doc;
    QString errorStr;
    if(!doc.setContent(&file, true, &errorStr)){
        cout << errorStr.toLocal8Bit().constData() << endl;
    }

    QDomElement root = doc.documentElement();
    QDomElement employees = root.firstChildElement();
    QDomElement employee = employees.firstChildElement();

    while(!employee.isNull()){
        cout << employee.attribute("age").toStdString() << endl;
        employee = employee.nextSiblingElement();
    }
}
