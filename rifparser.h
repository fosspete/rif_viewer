#ifndef RIFPARSER_H
#define RIFPARSER_H
#include <QString>
#include <QXmlStreamReader>
#include <QList>

#include "attrdeflist.h"
#include "requirementlist.h"

struct DataType_String
{
    QString ID;
    QString Name;
    QString MaxLength;
    QString LastChanged;
};




class RifParser
{
public:
    RifParser();
    bool parseElement(QString element,QXmlStreamReader *xml);
    QString parseSingleParameterObject(QXmlStreamReader *xml);

    QString _docAuthor;
    QString _docName;



    //signals:

    //public slots:
    RequirementList *getReqList();
private:
    void parseDataTypeDefString(QXmlStreamReader *xml);
    QList<DataType_String> DT_StringList;
    AttrDefList attr_list_;
    RequirementList req_list_;
    void parseDataTypeDefSimple(QXmlStreamReader *xml);
    void parseSpecObject(QXmlStreamReader *xml);
    void parseAttrDefSimple(QXmlStreamReader *xml);
    void parseAttrValueSimple(QXmlStreamReader *xml);
    void parseXhtmlContent(QXmlStreamReader *xml);
};

#endif // RIFPARSER_H
