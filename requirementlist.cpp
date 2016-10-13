#include "requirementlist.h"
#include "QDebug"
#include <QFile>

RequirementList::RequirementList()
{

}

void RequirementList::AddRequirement()
{
    // Clear all fields, actual store is done in method StoreIfComplete
    this->current_requirement.name = "";
    this->current_requirement.reqtext = "";
    this->current_requirement.req_class = "";
    this->current_requirement.req_id = "";
    this->current_requirement.revision = "";
    this->current_requirement.state = "";
}

void RequirementList::SetReqID(QString id)
{
    this->current_requirement.req_id = id;
}

void RequirementList::SetRevision(QString rev)
{
    this->current_requirement.revision = rev;
}

void RequirementList::SetState(QString state)
{
    this->current_requirement.state = state;
}

void RequirementList::SetClass(QString reqclass)
{
    this->current_requirement.req_class = reqclass;
}

void RequirementList::SetType(QString type)
{
    this->current_requirement.req_type = type;
}

void RequirementList::SetName(QString name)
{
    this->current_requirement.name = name;
}

void RequirementList::SetReqText(QString reqtext)
{
    if(this->current_requirement.reqtext == "")
    {
        this->current_requirement.reqtext = reqtext;
    }
}

void RequirementList::StoreIfComplete()
{
    bool debug = true;

    if(current_requirement.name != "" && current_requirement.req_class != "")
    {
        if(current_requirement.req_id=="")
        {
            current_requirement.req_id = "-";
        }
        current_requirement.req_class = current_requirement.req_class + "-" + current_requirement.req_type;
        this->theList_.append(this->current_requirement);
    }
    else
    {
        if(debug){qDebug() << "StoreIfComplete: Tried to add requirement with incomplete information";}
        if(debug){qDebug() << "   req_id = " << current_requirement.req_id;}
        if(debug){qDebug() << "   name = " << current_requirement.name;}
        if(debug){qDebug() << "   class = " << current_requirement.req_class;}
    }
}

void RequirementList::DebugDump()
{
    for (int i=0;i<this->theList_.count();i++)
    {
        qDebug() << i <<": Req ID: " << theList_.at(i).req_id << ", Revision: " << theList_.at(i).revision << ", Title: "<<theList_.at(i).name << ", class = " << theList_.at(i).req_class;
    }
}

void RequirementList::Clear()
{
    theList_.clear();
}

void RequirementList::GoToStart()
{
    this->current_index_=0;
}

QString RequirementList::GoToNextReqId(QString search_string)
{
    QString nextid = "";

    if(search_string == "")
    {
        if(this->current_index_ < (theList_.count()-1))
        {
            this->current_index_++;
            nextid = theList_.at(this->current_index_).req_id;
        }
    }

    return nextid;
}

QString RequirementList::GoToReqWithID(QString id)
{
    QString nextid = "";

    for (int i=0;i<theList_.count();i++)
    {
        if(theList_.at(i).req_id == id)
        {
            //req found
            nextid = id;
            this->current_index_ = i;
            break;
        }
    }
    return nextid;
}

QString RequirementList::GetNameOfReq()
{
    return this->theList_.at(this->current_index_).name;
}

QString RequirementList::GetRevOfReq()
{
    return this->theList_.at(this->current_index_).revision;
}

QString RequirementList::GetStateOfReq()
{
    return this->theList_.at(this->current_index_).state;
}

QString RequirementList::GetClassOfReq()
{
    return this->theList_.at(this->current_index_).req_class;
}

QString RequirementList::GetTextOfReq()
{
    return this->theList_.at(this->current_index_).reqtext;
}

QString RequirementList::GetIdOfReq()
{
    return this->theList_.at(this->current_index_).req_id;
}

void RequirementList::SaveToCSV(QString filename)
{
    QFile csvFile(filename);

    if (csvFile.open(QFile::WriteOnly | QFile::Truncate))
    {
        QTextStream data( &csvFile );

        QStringList strList;

        //Add headers
        strList << "Requirement ID" << "Revision" << "Requirement type" << "State" << "Title";
        data << strList.join(";");
        data << "\n";
        strList.clear();

        //Add requirements from list
        for( int i = 0; i < this->theList_.count(); i++ )
        {
            strList << theList_.at(i).req_id << theList_.at(i).revision << theList_.at(i).req_class << theList_.at(i).state << theList_.at(i).name;
            data << strList.join(";");
            data << "\n";
            strList.clear();
        }
        csvFile.close();
    }
}


