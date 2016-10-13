#ifndef ATTRDEFLIST_H
#define ATTRDEFLIST_H

#include <QString>
#include <QList>

struct AttrDef
{
    QString ID;
    QString Name;
    QString DatatypeID;
};

class AttrDefList
{
public:
    AttrDefList();
    void AddItem(struct AttrDef newitem);
    QString FindAttrFromID(QString id);

private:
    QList<AttrDef> theList_;
};

#endif // ATTRDEFLIST_H
