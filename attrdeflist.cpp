#include "attrdeflist.h"
#include <QDebug>


AttrDefList::AttrDefList()
{

}

QString AttrDefList::FindAttrFromID(QString id)
{
    struct AttrDef temp;
    bool debug = false;

    QString value = "";

    if(debug){qDebug() << "FindAttrFromID: Finding ID " << id << "our of " << theList_.count() << "items";}

    for (int i = 0; i < this->theList_.size(); ++i)
    {
        temp = theList_.at(i);

        if(debug){qDebug() << "  Checking id "<< id << " with name " << theList_.at(i).Name;}

        if (temp.ID == id)
        {
            value = temp.Name;
            if(debug){qDebug() << "  Found item with value "<< value << "\n";}
        }
    }
    return value;
}

void AttrDefList::AddItem(struct AttrDef newitem)
{
    this->theList_.append(newitem);
}
