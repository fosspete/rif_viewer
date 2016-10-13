#ifndef REQUIREMENTLIST_H
#define REQUIREMENTLIST_H

#include <QString>
#include <QList>

struct requirement
{
    QString req_id;
    QString revision;
    QString state;
    QString req_class;
    QString req_type;
    QString name;
    QString reqtext;
};

class RequirementList
{
public:
    RequirementList();
    void AddRequirement();
    void SetReqID(QString id);
    void SetRevision(QString rev);
    void SetState(QString state);
    void SetClass(QString reqclass);
    void SetType(QString type);
    void SetName(QString name);
    void SetReqText(QString reqtext);
    void StoreIfComplete(void);
    void DebugDump(void);
    void Clear(void);

    int GetListLength();
    void GoToStart();
    QString GoToNextReqId(QString search_string);
    QString GoToReqWithID(QString id);
    QString GetNameOfReq();
    QString GetRevOfReq();
    QString GetStateOfReq();
    QString GetClassOfReq();
    QString GetTextOfReq();
    QString GetIdOfReq();

    void SaveToCSV(QString filename);
private:
    QList<struct requirement> theList_;
    struct requirement current_requirement;
    int current_index_;

};

#endif // REQUIREMENTLIST_H
