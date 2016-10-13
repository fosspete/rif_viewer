#include "rifparser.h"

#include <QDebug>

RifParser::RifParser()
{

}

bool RifParser::parseElement(QString element, QXmlStreamReader *xml)
{
    QString temp;
    bool parseSuccessful=false;

    if(element == "AUTHOR")
    {
        temp = this->parseSingleParameterObject(xml);
        qDebug() << "AUTHOR: " << temp;
        this->_docAuthor = temp;
    }
    if(element == "CREATION-TIME")
    {
        temp = this->parseSingleParameterObject(xml);
        qDebug() << "CREATION-TIME: " << temp;
    }
    if(element == "SOURCE-TOOL-ID")
    {
        temp = this->parseSingleParameterObject(xml);
        qDebug() << "SOURCE-TOOL-ID: " << temp;
    }
    if(element == "TITLE")
    {
        temp = this->parseSingleParameterObject(xml);
        qDebug() << "TITLE: " << temp;
        this->_docName = temp;
    }
    if(element == "VERSION")
    {
        temp = this->parseSingleParameterObject(xml);
        qDebug() << "VERSION: " << temp;
    }
    if(element == "DATATYPE-DEFINITION-STRING")
    {
       this->parseDataTypeDefString(xml);
    }
    if(element == "ATTRIBUTE-DEFINITION-SIMPLE")
    {
       this->parseAttrDefSimple(xml);
    }
    if(element == "SPEC-OBJECT")
    {
        this->parseSpecObject(xml);
    }
    return parseSuccessful;
}

QString RifParser::parseSingleParameterObject(QXmlStreamReader *xml)
{
    QString temp;

    temp = xml->readElementText();

    while (!xml->isEndElement())
    {
        xml->readNext();
    }
    return temp;
}


void RifParser::parseDataTypeDefSimple(QXmlStreamReader *xml)
{
    bool debug = false;

    struct DataType_String temp;
    if(debug){qDebug()<< "Parsing type def simple:";}
    while (!(xml->isEndElement() && xml->name().toString() == "ATTRIBUTE-DEFINITION-SIMPLE"))
    {
        QString elem = xml->name().toString();
        if(debug){qDebug() << "   element name = " << elem << "\n";}

        if(elem == "IDENTIFIER")
        {
            temp.ID = xml->readElementText();
            if(debug){qDebug() << "   ID = " << temp.ID;}
        }
        else if(elem == "LAST-CHANGE")
        {
            temp.LastChanged = xml->readElementText();
            if(debug){qDebug() << "   LastChagned = " << temp.LastChanged;}
        }
        else if(elem == "LONG-NAME")
        {
            temp.Name = xml->readElementText();
            if(debug){qDebug() << "   Name = " << temp.Name;}
        }
        else if(elem == "MAX-LENGTH")
        {
            temp.MaxLength = xml->readElementText();
            if(debug){qDebug() << "   MaxLength = " << temp.MaxLength;}
        }
        else if(elem == "DATATYPE-DEFINITION-STRING-REF")
        {
            QString qtemp;
            qtemp = xml->readElementText();
            if(debug){qDebug() << "   String ref = " << qtemp;}
        }
        xml->readNext();

    }
    if(debug){qDebug() << "found end of definition simple" << endl;}

}

void RifParser::parseSpecObject(QXmlStreamReader *xml)
{
    QString temp;
    bool debug = false;

    // We found a new requirement (or folder), create new item
    this->req_list_.AddRequirement();

    while (!(xml->isEndElement() && xml->name().toString() == "SPEC-OBJECT"))
    {
        QString elem = xml->name().toString();

        if(elem == "ATTRIBUTE-VALUE-SIMPLE")
        {
            this->parseAttrValueSimple(xml);
        }

        if(elem == "LONG-NAME")
        {
            temp = xml->readElementText();
            if(debug){qDebug() << "   SPEC-OBJECT-NAME = " << temp;}
            this->req_list_.SetName(temp);
        }
        else if(elem == "LAST-CHANGE")
        {
            temp = xml->readElementText();
            if(debug){qDebug() << "   LastChagned = " << temp;}
        }
        else if (elem == "XHTML-CONTENT")
        {
            this->parseXhtmlContent(xml);
        }

        xml->readNext();

    }
    if(debug){qDebug() << "found end of spec object" << endl;}

    // We have parsed the complete spec object, add it if all mandatory information was found
    this->req_list_.StoreIfComplete();

   // this->req_list_.DebugDump();
}

void RifParser::parseXhtmlContent(QXmlStreamReader *xml)
{
    bool debug = false;

    QString reqtext;

    // TODO fix so that we get complete xhtml content
    if(debug){qDebug()<< "XHTML-CONTENT:";}
//    while (!(xml->isEndElement() && xml->name().toString() == "XHTML-CONTENT"))
  //  {

    reqtext = xml->readElementText(QXmlStreamReader::IncludeChildElements);
        //xml->readNext();
    //}
    this->req_list_.SetReqText(reqtext);
}


void RifParser::parseAttrValueSimple(QXmlStreamReader *xml)
{
    bool debug = false;
    QString ref;
    QString valuetype;
    QString value;

    if(debug){qDebug()<< "ATTRIBUTE-VALUE-SIMPLE:";}

    while (!(xml->isEndElement() && xml->name().toString() == "ATTRIBUTE-VALUE-SIMPLE"))
    {
        QString elem = xml->name().toString();

        if(elem == "ATTRIBUTE-DEFINITION-SIMPLE-REF")
        {
            ref = xml->readElementText();
            if(debug){qDebug() << "   Ref = " << ref;}
            valuetype = this->attr_list_.FindAttrFromID(ref);
            if(debug){qDebug() << "   valuetype = " << valuetype;}
        }
        else if(elem == "THE-VALUE")
        {
            value = xml->readElementText();
            if(debug){qDebug() << "   Value = " << value;}
            if(valuetype != "" && value != "")
            {
                if(valuetype == "Class")
                    this->req_list_.SetClass(value);
                if(valuetype == "ID")
                    this->req_list_.SetReqID(value);
                if(valuetype == "Revision")
                    this->req_list_.SetRevision(value);
                if(valuetype == "State")
                    this->req_list_.SetState(value);
                if(valuetype == "Type")
                    this->req_list_.SetType(value);
            }
        }
        xml->readNext();
    }
    if(debug){qDebug() << "ATTRIBUTE-VALUE-SIMPLE" << endl;}
}

/********************************************************************
 *  Methods parsing type definitions and references                 *
 ********************************************************************/

void RifParser::parseAttrDefSimple(QXmlStreamReader *xml)
{
    bool debug = false;
    struct AttrDef temp;

    if(debug){qDebug()<< "ATTRIBUTE-DEFINITION-SIMPLE:";}

    while (!(xml->isEndElement() && xml->name().toString() == "ATTRIBUTE-DEFINITION-SIMPLE"))
    {
        QString elem = xml->name().toString();

        if(elem == "IDENTIFIER")
        {
            temp.ID = xml->readElementText();
            if(debug){qDebug() << "   ID = " << temp.ID;}
        }
        else if(elem == "LONG-NAME")
        {
            temp.Name = xml->readElementText();
            if(debug){qDebug() << "   Name = " << temp.Name;}
        }


        xml->readNext();
    }
    this->attr_list_.AddItem(temp);
    if(debug){qDebug() << "found end of ATTRIBUTE-DEFINITION-SIMPLE" << endl;}
}

void RifParser::parseDataTypeDefString(QXmlStreamReader *xml)
{
    bool debug = false;

    struct DataType_String temp;
    if(debug){qDebug()<< "Parsing type def string:";}
    while (!(xml->isEndElement() && xml->name().toString() == "DATATYPE-DEFINITION-STRING"))
    {
        QString elem = xml->name().toString();

        if(elem == "IDENTIFIER")
        {
            temp.ID = xml->readElementText();
            if(debug){qDebug() << "   ID = " << temp.ID;}
        }
        if(elem == "LAST-CHANGE")
        {
            temp.LastChanged = xml->readElementText();
            if(debug){qDebug() << "   LastChagned = " << temp.LastChanged;}
        }
        if(elem == "LONG-NAME")
        {
            temp.Name = xml->readElementText();
            if(debug){qDebug() << "   Name = " << temp.Name;}
        }
        if(elem == "MAX-LENGTH")
        {
            temp.MaxLength = xml->readElementText();
            if(debug){qDebug() << "   MaxLength = " << temp.MaxLength;}
        }

        xml->readNext();
    }

    if(debug){qDebug() << "found end of definition string" << endl;}
    this->DT_StringList.append(temp);
}

RequirementList *RifParser::getReqList()
{
    return &this->req_list_;
}
